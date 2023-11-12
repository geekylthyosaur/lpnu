using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class DriverRouteDto
{
    public int Id { get; set; }

    public int DriverId { get; set; }

    public int VehicleId { get; set; }

    public int RouteId { get; set; }

    public virtual DriverDto Driver { get; set; } = null!;

    public virtual Route Route { get; set; } = null!;

    public virtual VehicleDto Vehicle { get; set; } = null!;
}
