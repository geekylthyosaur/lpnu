package main

import (
	"database/sql"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"

	"github.com/geekylthyosaur/lpnu/models"
	_ "github.com/lib/pq"
)

var db *sql.DB

func init() {
	var err error
	db, err = sql.Open("postgres", "postgres://user:password@localhost/src?sslmode=disable")
	if err != nil {
		log.Fatal(err)
	}
	db.SetMaxOpenConns(10)
	db.SetMaxIdleConns(5)
	db.SetConnMaxLifetime(time.Minute * 5)
}

func main() {
	http.HandleFunc("/route_with_stops", getRouteWithStopsHandler)
	http.HandleFunc("/arrival_with_stops_in", getArrivalWithStopsInHandler)
	http.HandleFunc("/route", getRouteHandler)
	http.HandleFunc("/stop", getStopHandler)
	http.HandleFunc("/schedule", getScheduleHandler)
	http.HandleFunc("/vehicle", getVehicleHandler)
	http.HandleFunc("/ticket", getTicketHandler)
	http.HandleFunc("/transaction", getTransactionHandler)
	http.HandleFunc("/driver", getDriverHandler)
	http.HandleFunc("/maintenance", getMaintenanceHandler)

	fmt.Println("Server is running on port 8080...")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

func getRouteWithStopsHandler(w http.ResponseWriter, r *http.Request) {
	queryParams := r.URL.Query()

	sqlQuery := "SELECT from_stop_id, from_stop_name, to_stop_id, to_stop_name, route_id, route_name FROM routes_with_stops WHERE 1=1"

	var args []interface{}

	if fromStopID := queryParams.Get("from_stop_id"); fromStopID != "" {
		sqlQuery += " AND from_stop_id = $1"
		args = append(args, fromStopID)
	}
	if toStopID := queryParams.Get("to_stop_id"); toStopID != "" {
		sqlQuery += " AND to_stop_id = $2"
		args = append(args, toStopID)
	}

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

	// Prepare the base SQL query
	sqlQuery := "SELECT from_stop_id, from_stop_name, to_stop_id, to_stop_name, route_id, route_name, arr_in FROM arrival_with_stops_in WHERE 1=1"

	// Prepare placeholders for filter parameters and values
	var args []interface{}

	// Add filters based on query parameters
	if fromStopID := queryParams.Get("from_stop_id"); fromStopID != "" {
		sqlQuery += " AND from_stop_id = $1"
		args = append(args, fromStopID)
	}
	if toStopID := queryParams.Get("to_stop_id"); toStopID != "" {
		sqlQuery += " AND to_stop_id = $2"
		args = append(args, toStopID)
	}
	if routeID := queryParams.Get("route_id"); routeID != "" {
		sqlQuery += " AND route_id = $3"
		args = append(args, routeID)
	}

	// Execute the SQL query with prepared statement
	rows, err := db.Query(sqlQuery, args...)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	// Define a slice to hold the results
	var arrivalsWithStopsIn []models.ArrivalWithStopsIn

	// Iterate through the rows and scan the results into ArrivalWithStopsIn structs
	for rows.Next() {
		var arrivalWithStopsIn models.ArrivalWithStopsIn
		err := rows.Scan(&arrivalWithStopsIn.FromStopID, &arrivalWithStopsIn.FromStopName, &arrivalWithStopsIn.ToStopID, &arrivalWithStopsIn.ToStopName, &arrivalWithStopsIn.RouteID, &arrivalWithStopsIn.RouteName, &arrivalWithStopsIn.ArrIn)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		arrivalsWithStopsIn = append(arrivalsWithStopsIn, arrivalWithStopsIn)
	}

	// Encode the results as JSON and send the response
	json.NewEncoder(w).Encode(arrivalsWithStopsIn)
}

func getRouteHandler(w http.ResponseWriter, r *http.Request) {
	rows, err := db.Query("SELECT id, name, full_name FROM public.route")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	var routes []models.Route
	for rows.Next() {
		var route models.Route
		err := rows.Scan(&route.ID, &route.Name, &route.FullName)
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
