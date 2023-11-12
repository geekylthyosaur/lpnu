using System;
using System.Collections.Generic;

namespace api.Models;

public partial class Route
{
    public int Id { get; set; }

    public string Name { get; set; } = null!;

    public int FirstStopId { get; set; }

    public int LastStopId { get; set; }

    public virtual ICollection<DriverRoute> DriverRoutes { get; set; } = new List<DriverRoute>();

    public virtual Stop FirstStop { get; set; } = null!;

    public virtual Stop LastStop { get; set; } = null!;

    public virtual ICollection<RouteStop> RouteStops { get; set; } = new List<RouteStop>();

    public virtual ICollection<RouteVehicle> RouteVehicles { get; set; } = new List<RouteVehicle>();

    public virtual ICollection<Schedule> Schedules { get; set; } = new List<Schedule>();

    public virtual ICollection<Ticket> Tickets { get; set; } = new List<Ticket>();
}
