using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class RouteVehicleDto
{
    public int Id { get; set; }

    public int RouteId { get; set; }

    public decimal? LastLat { get; set; }

    public decimal? LastLon { get; set; }

    public DateTime? LastCoordsTime { get; set; }

    public int? NextStop { get; set; }

    public int VehicleId { get; set; }

    public virtual StopDto? NextStopNavigation { get; set; }

    public virtual Route Route { get; set; } = null!;

    public virtual VehicleDto Vehicle { get; set; } = null!;
}
