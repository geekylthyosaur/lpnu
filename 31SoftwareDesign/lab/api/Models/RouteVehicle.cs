using System;
using System.Collections.Generic;

namespace api.Models;

public partial class RouteVehicle
{
    public int Id { get; set; }

    public int RouteId { get; set; }

    public decimal? LastLat { get; set; }

    public decimal? LastLon { get; set; }

    public DateTime? LastCoordsTime { get; set; }

    public int? NextStop { get; set; }

    public int VehicleId { get; set; }

    public virtual Stop? NextStopNavigation { get; set; }

    public virtual Route Route { get; set; } = null!;

    public virtual Vehicle Vehicle { get; set; } = null!;
}
