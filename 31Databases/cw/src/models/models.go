package models

import (
	"database/sql"
	"time"
)

type Route struct {
	ID   int    `json:"id"`
	Name string `json:"name"`
}

type Stop struct {
	ID   int     `json:"id"`
	Name string  `json:"name"`
	Lat  float64 `json:"lat"`
	Lon  float64 `json:"lon"`
}

type RouteStop struct {
	RouteID  int `json:"route_id"`
	StopID   int `json:"stop_id"`
	OrdIndex int `json:"ord_idx"`
}

type Schedule struct {
	ID        int       `json:"id"`
	RouteID   int       `json:"route_id"`
	StopID    int       `json:"stop_id"`
	Arrival   time.Time `json:"arr"`
	Departure time.Time `json:"dep"`
}

type Vehicle struct {
	License  string `json:"license"`
	Capacity int    `json:"capacity"`
	RouteID  int    `json:"route_id"`
}

type TicketDiscount string

type Ticket struct {
	ID       string         `json:"id"`
	Discount TicketDiscount `json:"discount"`
	Balance  float64        `json:"balance"`
}

type Transaction struct {
	ID        string    `json:"id"`
	TicketID  string    `json:"ticket_id"`
	RouteID   int       `json:"route_id"`
	VehicleID string    `json:"vehicle_id"`
	FromStop  int       `json:"from_stop_id"`
	ToStop    int       `json:"to_stop_id"`
	Fare      float64   `json:"fare"`
	Timestamp time.Time `json:"timestamp"`
}

type Driver struct {
	ID        int            `json:"id"`
	Name      string         `json:"name"`
	VehicleID sql.NullString `json:"vehicle_id"`
}

type Maintenance struct {
	ID          int       `json:"id"`
	VehicleID   string    `json:"vehicle_id"`
	DriverID    int       `json:"driver_id"`
	Description string    `json:"description"`
	Time        time.Time `json:"time"`
	Cost        float64   `json:"cost"`
}

type MaintenanceForm struct {
	VehicleID   string  `json:"vehicle_id"`
	DriverID    int     `json:"driver_id"`
	Description string  `json:"description"`
	Cost        float64 `json:"cost"`
}

type RouteWithStops struct {
	FromStopID   int    `json:"from_stop_id"`
	FromStopName string `json:"from_stop_name"`
	ToStopID     int    `json:"to_stop_id"`
	ToStopName   string `json:"to_stop_name"`
	RouteID      int    `json:"route_id"`
	RouteName    string `json:"route_name"`
}

type ArrivalWithStopsIn struct {
	FromStopID   int    `json:"from_stop_id"`
	FromStopName string `json:"from_stop_name"`
	ToStopID     int    `json:"to_stop_id"`
	ToStopName   string `json:"to_stop_name"`
	RouteID      int    `json:"route_id"`
	RouteName    string `json:"route_name"`
	ArrIn        string `json:"arr_in"`
}

type NextStop struct {
	NextStopID int    `json:"next_stop_id"`
	StopName   string `json:"stop_name"`
	ArrIn      string `json:"arr_in"`
}
