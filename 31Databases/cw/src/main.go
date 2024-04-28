package main

import (
	"database/sql"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
  "time"
  "strings"
  "strconv"

	"github.com/geekylthyosaur/lpnu/models"
	_ "github.com/lib/pq"
)

var db *sql.DB

func init() {
	var err error
	db, err = sql.Open("postgres", "postgres://root:password@localhost:5432/src?sslmode=disable")
	if err != nil {
		log.Fatal(err)
	}
	db.SetConnMaxLifetime(0)
	db.SetMaxOpenConns(1)
	db.SetMaxIdleConns(1)
}

func main() {
	http.HandleFunc("/search_stop", authMiddleware(searchStopHandler))
	http.HandleFunc("/search_route", authMiddleware(searchRouteHandler))
	http.HandleFunc("/route_with_stops", authMiddleware(getRouteWithStopsHandler))
	http.HandleFunc("/arrival_with_stops_in", authMiddleware(getArrivalWithStopsInHandler))
	http.HandleFunc("/insert_maintenance", authMiddleware(insertMaintenanceHandler))
	http.HandleFunc("/new_transaction", authMiddleware(newTransactionHandler))
	http.HandleFunc("/next_stop", authMiddleware(nextStopHandler))
	http.HandleFunc("/route", authMiddleware(getRouteHandler))
	http.HandleFunc("/stop", authMiddleware(getStopHandler))
	http.HandleFunc("/schedule", authMiddleware(getScheduleHandler))
	http.HandleFunc("/vehicle", authMiddleware(getVehicleHandler))
	http.HandleFunc("/vehicle/add", authMiddleware(insertVehicleHandler))
	http.HandleFunc("/vehicle/edit", authMiddleware(editVehicleHandler))
	http.HandleFunc("/ticket", authMiddleware(getTicketHandler))
	http.HandleFunc("/transaction", authMiddleware(getTransactionHandler))
	http.HandleFunc("/driver", authMiddleware(getDriverHandler))
  http.HandleFunc("/driver/delete", authMiddleware(deleteDriverHandler))
  http.HandleFunc("/driver/add", authMiddleware(insertDriverHandler))
  http.HandleFunc("/driver/edit", authMiddleware(editDriverHandler))
	http.HandleFunc("/maintenance", authMiddleware(getMaintenanceHandler))
	http.HandleFunc("/stats", authMiddleware(getStatsHandler))

	fmt.Println("Server is running on port 8080...")
	log.Fatal(http.ListenAndServe(":8080", corsHandler(http.DefaultServeMux)))
}

func authMiddleware(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		authHeader := r.Header.Get("Authorization")

		if authHeader == "" {
			http.Error(w, "Unauthorized", http.StatusUnauthorized)
			return
		}

		username := authHeader

		var role string
		switch username {
		case "passenger":
			role = "passenger"
		case "driver":
			role = "driver"
		case "manager":
			role = "manager"
		default:
			http.Error(w, "Invalid username", http.StatusUnauthorized)
			return
		}

		db.SetConnMaxLifetime(0)
		db.SetMaxOpenConns(1)
		db.SetMaxIdleConns(1)
		_, err := db.Exec(fmt.Sprintf("set role %s;", role))

		if err != nil {
			http.Error(w, "Failed to set user role", http.StatusInternalServerError)
			return
		}

		next(w, r)
	}
}

func insertMaintenanceHandler(w http.ResponseWriter, r *http.Request) {
	var maintenance models.MaintenanceForm
	err := json.NewDecoder(r.Body).Decode(&maintenance)
	if err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	sqlQuery := `
        INSERT INTO maintenance (vehicle_id, driver_id, description, cost)
        VALUES ($1, $2, $3, $4)
    `

	_, err = db.Exec(sqlQuery, maintenance.VehicleID, maintenance.DriverID, maintenance.Description, maintenance.Cost)
	if err != nil {
		fmt.Println(err.Error())
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.WriteHeader(http.StatusNoContent)
}

func searchStopHandler(w http.ResponseWriter, r *http.Request) {
	queryParams := r.URL.Query()
	name := queryParams.Get("name")

	sqlQuery := "SELECT * FROM search_stop($1)"

	rows, err := db.Query(sqlQuery, name)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var stops []models.Stop

	for rows.Next() {
		var stop models.Stop
		err := rows.Scan(&stop.ID, &stop.Name, &stop.Lat, &stop.Lon)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		stops = append(stops, stop)
	}

	json.NewEncoder(w).Encode(stops)
}

func searchRouteHandler(w http.ResponseWriter, r *http.Request) {
	queryParams := r.URL.Query()
	name := queryParams.Get("name")

	sqlQuery := "SELECT id, route_name FROM search_route($1)"

	rows, err := db.Query(sqlQuery, name)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var routes []models.Route

	for rows.Next() {
		var route models.Route
		err := rows.Scan(&route.ID, &route.Name)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		routes = append(routes, route)
	}

	json.NewEncoder(w).Encode(routes)
}

func getRouteWithStopsHandler(w http.ResponseWriter, r *http.Request) {
	queryParams := r.URL.Query()

	sqlQuery := "SELECT from_stop_id, from_stop_name, to_stop_id, to_stop_name, route_id, route_name FROM routes_with_stops WHERE 1=1"

	var args []interface{}

	fromStopID := queryParams.Get("from_stop_id")
	if fromStopID != "" {
		sqlQuery += " AND from_stop_id = $1"
		args = append(args, fromStopID)
	}
	if toStopID := queryParams.Get("to_stop_id"); toStopID != "" {
		if fromStopID == "" {
			sqlQuery += " AND to_stop_id = $1"
		} else {
			sqlQuery += " AND to_stop_id = $2"
		}
		args = append(args, toStopID)
	}

	sqlQuery += " LIMIT 10"
	rows, err := db.Query(sqlQuery, args...)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var routesWithStops []models.RouteWithStops

	for rows.Next() {
		var routeWithStops models.RouteWithStops
		err := rows.Scan(&routeWithStops.FromStopID, &routeWithStops.FromStopName, &routeWithStops.ToStopID, &routeWithStops.ToStopName, &routeWithStops.RouteID, &routeWithStops.RouteName)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		routesWithStops = append(routesWithStops, routeWithStops)
	}

	json.NewEncoder(w).Encode(routesWithStops)
}

func getArrivalWithStopsInHandler(w http.ResponseWriter, r *http.Request) {
	queryParams := r.URL.Query()

	sqlQuery := "SELECT from_stop_id, from_stop_name, to_stop_id, to_stop_name, route_id, route_name, arr_in FROM arrival_with_stops_in WHERE 1=1"

	var args []interface{}

	fromStopID := queryParams.Get("from_stop_id")
	if fromStopID != "" {
		sqlQuery += " AND from_stop_id = $1"
		args = append(args, fromStopID)
	}

	toStopID := queryParams.Get("to_stop_id")
	if toStopID != "" {
		if fromStopID == "" {
			sqlQuery += " AND to_stop_id = $1"
		} else {
			sqlQuery += " AND to_stop_id = $2"
		}
		args = append(args, toStopID)
	}
	if routeID := queryParams.Get("route_id"); routeID != "" {
		if fromStopID == "" && toStopID == "" {
			sqlQuery += " AND route_id = $1"
		} else if fromStopID == "" || toStopID == "" {
			sqlQuery += " AND route_id = $2"
		} else {
			sqlQuery += " AND route_id = $3"
		}
		args = append(args, routeID)
	}
	sqlQuery += " LIMIT 10"
	rows, err := db.Query(sqlQuery, args...)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var arrivalsWithStopsIn []models.ArrivalWithStopsIn

	for rows.Next() {
		var arrivalWithStopsIn models.ArrivalWithStopsIn
		err := rows.Scan(&arrivalWithStopsIn.FromStopID, &arrivalWithStopsIn.FromStopName, &arrivalWithStopsIn.ToStopID, &arrivalWithStopsIn.ToStopName, &arrivalWithStopsIn.RouteID, &arrivalWithStopsIn.RouteName, &arrivalWithStopsIn.ArrIn)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		arrivalsWithStopsIn = append(arrivalsWithStopsIn, arrivalWithStopsIn)
	}

	json.NewEncoder(w).Encode(arrivalsWithStopsIn)
}

func newTransactionHandler(w http.ResponseWriter, r *http.Request) {
	queryParams := r.URL.Query()
	ticketID := queryParams.Get("ticket_id")
	vehicleID := queryParams.Get("vehicle_id")
	fromStopID := queryParams.Get("from_stop_id")
	toStopID := queryParams.Get("to_stop_id")

	_, err := db.Exec("SELECT new_transaction($1, $2, $3, $4)", ticketID, vehicleID, fromStopID, toStopID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.WriteHeader(http.StatusOK)
	w.Write([]byte("New transaction executed successfully"))
}

// Handler for executing the next_stop function
func nextStopHandler(w http.ResponseWriter, r *http.Request) {
	// Parse URL query parameters
	queryParams := r.URL.Query()
	vehicleID := queryParams.Get("vehicle_id")
	stopID := queryParams.Get("stop_id")

	// Execute the next_stop function with the extracted arguments
	rows, err := db.Query("SELECT * FROM next_stop($1, $2)", vehicleID, stopID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	// Define a slice to hold the results
	var stops []models.NextStop

	// Iterate through the rows and scan the results into NextStop structs
	for rows.Next() {
		var stop models.NextStop
		err := rows.Scan(&stop.NextStopID, &stop.StopName, &stop.ArrIn)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		stops = append(stops, stop)
	}

	// Encode the results as JSON and send the response
	json.NewEncoder(w).Encode(stops)
}

func getRouteHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT id, CASE WHEN name IS NOT NULL THEN name || ' (' || full_name || ')' ELSE full_name END AS name FROM public.route;")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var routes []models.Route
	for rows.Next() {
		var route models.Route
		err := rows.Scan(&route.ID, &route.Name)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		routes = append(routes, route)
	}

	json.NewEncoder(w).Encode(routes)
}

func getStopHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT id, name, lat, lon FROM public.stop")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var stops []models.Stop
	for rows.Next() {
		var stop models.Stop
		err := rows.Scan(&stop.ID, &stop.Name, &stop.Lat, &stop.Lon)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		stops = append(stops, stop)
	}

	json.NewEncoder(w).Encode(stops)
}

func getScheduleHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT id, route_id, stop_id, arr, dep FROM public.schedule")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var schedules []models.Schedule
	for rows.Next() {
		var schedule models.Schedule
		err := rows.Scan(&schedule.ID, &schedule.RouteID, &schedule.StopID, &schedule.Arrival, &schedule.Departure)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		schedules = append(schedules, schedule)
	}

	json.NewEncoder(w).Encode(schedules)
}

func getVehicleHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT license, capacity, route_id FROM public.vehicle")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var vehicles []models.Vehicle
	for rows.Next() {
		var vehicle models.Vehicle
		err := rows.Scan(&vehicle.License, &vehicle.Capacity, &vehicle.RouteID)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		vehicles = append(vehicles, vehicle)
	}

	json.NewEncoder(w).Encode(vehicles)
}

func insertVehicleHandler(w http.ResponseWriter, r *http.Request) {
    license := r.URL.Query().Get("license")
    capacity := r.URL.Query().Get("capacity")
    routeID := r.URL.Query().Get("route_id")

    if license == "" || capacity == "" {
        http.Error(w, "License and Capacity are required fields", http.StatusBadRequest)
        return
    }

    if routeID == "" {
      query := "INSERT INTO public.vehicle (license, capacity) VALUES ($1, $2)"
      _, err := db.Exec(query, license, capacity)
      if err != nil {
          http.Error(w, err.Error(), http.StatusInternalServerError)
          return
      }
    } else {
      query := "INSERT INTO public.vehicle (license, capacity, route_id) VALUES ($1, $2, $3)"
      _, err := db.Exec(query, license, capacity, routeID)
      if err != nil {
          http.Error(w, err.Error(), http.StatusInternalServerError)
          return
      }
    }

    w.WriteHeader(http.StatusCreated)
}

func editVehicleHandler(w http.ResponseWriter, r *http.Request) {
    license := r.URL.Query().Get("license")
    capacity := r.URL.Query().Get("capacity")
    routeID := r.URL.Query().Get("route_id")

    if license == "" || capacity == "" {
        http.Error(w, "License and Capacity are required fields", http.StatusBadRequest)
        return
    }

    if routeID == "" {
      query := "UPDATE public.vehicle SET capacity = $1 WHERE license = $2"

        fmt.Println(query)
      _, err := db.Exec(query, capacity, license)
      if err != nil {
        fmt.Println(err)
          http.Error(w, err.Error(), http.StatusInternalServerError)
          return
      }
    } else {
      query := "UPDATE public.vehicle SET capacity = $1, route_id = $2 WHERE license = $3"
        fmt.Println(query)
        fmt.Println(routeID)
      _, err := db.Exec(query, capacity, routeID, license)
      if err != nil {
        fmt.Println(err)
          http.Error(w, err.Error(), http.StatusInternalServerError)
          return
      }
    }

    w.WriteHeader(http.StatusOK)
}

func getTicketHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT id, discount, balance FROM public.ticket")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var tickets []models.Ticket
	for rows.Next() {
		var ticket models.Ticket
		err := rows.Scan(&ticket.ID, &ticket.Discount, &ticket.Balance)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		tickets = append(tickets, ticket)
	}

	json.NewEncoder(w).Encode(tickets)
}

func getTransactionHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT id, ticket_id, route_id, vehicle_id, from_stop_id, to_stop_id, fare, timestamp FROM public.transaction")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var transactions []models.Transaction
	for rows.Next() {
		var transaction models.Transaction
		err := rows.Scan(&transaction.ID, &transaction.TicketID, &transaction.RouteID, &transaction.VehicleID, &transaction.FromStop, &transaction.ToStop, &transaction.Fare, &transaction.Timestamp)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		transactions = append(transactions, transaction)
	}

	json.NewEncoder(w).Encode(transactions)
}

func getDriverHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT id, name, vehicle_id FROM public.driver")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var drivers []models.Driver
	for rows.Next() {
		var driver models.Driver
		err := rows.Scan(&driver.ID, &driver.Name, &driver.VehicleID)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		drivers = append(drivers, driver)
	}

	json.NewEncoder(w).Encode(drivers)
}

func deleteDriverHandler(w http.ResponseWriter, r *http.Request) {
	driverID := r.URL.Query().Get("id")
	if driverID == "" {
		http.Error(w, "Missing driver ID", http.StatusBadRequest)
		return
	}

	_, err := db.Exec("DELETE FROM public.driver WHERE id = $1", driverID)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.WriteHeader(http.StatusOK)
}

func insertDriverHandler(w http.ResponseWriter, r *http.Request) {
	name := r.URL.Query().Get("name")
	vehicleID := r.URL.Query().Get("vehicle_id")

	if name == "" {
		http.Error(w, "Name and Vehicle ID are required fields", http.StatusBadRequest)
		return
	}

  if vehicleID == "" {
    _, err := db.Exec("INSERT INTO public.driver (name) VALUES ($1)", name)
    if err != nil {
      http.Error(w, err.Error(), http.StatusInternalServerError)
      return
    }
  } else {
    _, err := db.Exec("INSERT INTO public.driver (name, vehicle_id) VALUES ($1, $2)", name, vehicleID)
    if err != nil {
      http.Error(w, err.Error(), http.StatusInternalServerError)
      return
    }
  }

	w.WriteHeader(http.StatusCreated)
}

func editDriverHandler(w http.ResponseWriter, r *http.Request) {
	driverID := r.URL.Query().Get("id")
	name := r.URL.Query().Get("name")
	vehicleID := r.URL.Query().Get("vehicle_id")

	if driverID == "" || name == "" {
		http.Error(w, "Driver ID, name, and vehicle ID are required", http.StatusBadRequest)
		return
	}

  if vehicleID == "" {
    query := "UPDATE public.driver SET name = $1 WHERE id = $3"
    _, err := db.Exec(query, name, driverID)
    if err != nil {
      http.Error(w, err.Error(), http.StatusInternalServerError)
      return
    }
  } else {
    query := "UPDATE public.driver SET name = $1, vehicle_id = $2 WHERE id = $3"
    _, err := db.Exec(query, name, vehicleID, driverID)
    if err != nil {
      http.Error(w, err.Error(), http.StatusInternalServerError)
      return
    }
  }


	w.WriteHeader(http.StatusOK)
}

func getMaintenanceHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT id, vehicle_id, driver_id, description, time, cost FROM public.maintenance")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var maintenances []models.Maintenance
	for rows.Next() {
		var maintenance models.Maintenance
		err := rows.Scan(&maintenance.ID, &maintenance.VehicleID, &maintenance.DriverID, &maintenance.Description, &maintenance.Time, &maintenance.Cost)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		maintenances = append(maintenances, maintenance)
	}

	json.NewEncoder(w).Encode(maintenances)
}

func corsHandler(h http.Handler) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		// Set CORS headers
		w.Header().Set("Access-Control-Allow-Origin", "*") // Allow requests from any origin
		w.Header().Set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
		w.Header().Set("Access-Control-Allow-Headers", "Content-Type, Authorization")

		// If it's a preflight request, send an OK status
		if r.Method == "OPTIONS" {
			w.WriteHeader(http.StatusOK)
			return
		}

		// Call the actual handler
		h.ServeHTTP(w, r)
	}
}

func getStatsHandler(w http.ResponseWriter, r *http.Request) {
  r.ParseForm()
	routeID := r.Form.Get("route_id")
	startDateStr := r.Form.Get("start_date")
	endDateStr := r.Form.Get("end_date")

	// Build the SQL query conditionally based on provided parameters
	query := `
		SELECT DATE_TRUNC('day', timestamp) AS transaction_date, SUM(fare) AS daily_total
		FROM transaction
	`
	var args []interface{}
	var conditions []string

	// Check if routeID is provided
	if routeID != "" {
		conditions = append(conditions, "route_id = $"+strconv.Itoa(len(args)+1))
		args = append(args, routeID)
	}

	// Check if startDate is provided
	if startDateStr != "" {
		startDate, err := time.Parse("02-01-2006", startDateStr)
		if err != nil {
      fmt.Println(err);
			http.Error(w, "Invalid start date", http.StatusBadRequest)
			return
		}
		conditions = append(conditions, "timestamp >= $"+strconv.Itoa(len(args)+1))
		args = append(args, startDate)
	}

	// Check if endDate is provided
	if endDateStr != "" {
		endDate, err := time.Parse("02-01-2006", endDateStr)
		if err != nil {
      fmt.Println(err);
			http.Error(w, "Invalid end date", http.StatusBadRequest)
			return
		}
		conditions = append(conditions, "timestamp < $"+strconv.Itoa(len(args)+1))
		args = append(args, endDate)
	}

	// Construct the WHERE clause if there are conditions
	if len(conditions) > 0 {
		query += " WHERE " + strings.Join(conditions, " AND ")
	}

	query += " GROUP BY DATE_TRUNC('day', timestamp)"

	// Execute the SQL query
	rows, err := db.Query(query, args...)
	if err != nil {
      fmt.Println(err);
		http.Error(w, "Database query error", http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	// Fetch results and create Transaction objects
	var transactions []Transaction
	for rows.Next() {
		var transaction Transaction
		err := rows.Scan(&transaction.TransactionDate, &transaction.DailyTotal)
		if err != nil {
      fmt.Println(err);
			http.Error(w, "Error scanning row", http.StatusInternalServerError)
			return
		}
		transactions = append(transactions, transaction)
	}

	// Convert to JSON and write response
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(transactions)
}

// Transaction represents a row from the transaction table
type Transaction struct {
	TransactionDate time.Time `json:"transaction_date"`
	DailyTotal      float64   `json:"daily_total"`
}


