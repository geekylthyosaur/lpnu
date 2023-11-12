using System;
using System.Collections.Generic;

namespace api.Models;

public partial class Vehicle
{
    public int Id { get; set; }

    public string Type { get; set; } = null!;

    public string LicensePlate { get; set; } = null!;

    public int Capacity { get; set; }

    public virtual ICollection<DriverRoute> DriverRoutes { get; set; } = new List<DriverRoute>();

    public virtual ICollection<RouteVehicle> RouteVehicles { get; set; } = new List<RouteVehicle>();

    public virtual ICollection<Schedule> Schedules { get; set; } = new List<Schedule>();

    public virtual ICollection<Ticket> Tickets { get; set; } = new List<Ticket>();

    public virtual ICollection<VehicleMaintenance> VehicleMaintenances { get; set; } = new List<VehicleMaintenance>();
}
