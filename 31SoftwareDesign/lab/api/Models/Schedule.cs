using System;
using System.Collections.Generic;

namespace api.Models;

public partial class Schedule
{
    public int Id { get; set; }

    public int VehicleId { get; set; }

    public int RouteId { get; set; }

    public int StopId { get; set; }

    public DateTime DepartureTime { get; set; }

    public DateTime ArrivalTime { get; set; }

    public virtual Route Route { get; set; } = null!;

    public virtual Stop Stop { get; set; } = null!;

    public virtual Vehicle Vehicle { get; set; } = null!;
}
