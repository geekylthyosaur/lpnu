using System;
using System.Collections.Generic;

namespace api.Models;

public partial class DriverRoute
{
    public int Id { get; set; }

    public int DriverId { get; set; }

    public int VehicleId { get; set; }

    public int RouteId { get; set; }

    public virtual Driver Driver { get; set; } = null!;

    public virtual Route Route { get; set; } = null!;

    public virtual Vehicle Vehicle { get; set; } = null!;
}
