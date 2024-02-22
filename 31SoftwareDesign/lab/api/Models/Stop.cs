using System;
using System.Collections.Generic;

namespace api.Models;

public partial class Stop
{
    public int Id { get; set; }

    public string Name { get; set; } = null!;

    public decimal Lat { get; set; }

    public decimal Lon { get; set; }

    public virtual ICollection<Route> RouteFirstStops { get; set; } = new List<Route>();

    public virtual ICollection<Route> RouteLastStops { get; set; } = new List<Route>();

    public virtual ICollection<RouteStop> RouteStops { get; set; } = new List<RouteStop>();

    public virtual ICollection<RouteVehicle> RouteVehicles { get; set; } = new List<RouteVehicle>();

    public virtual ICollection<Schedule> Schedules { get; set; } = new List<Schedule>();
}
