using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class StopDto
{
    public int Id { get; set; }

    public string Name { get; set; } = null!;

    public decimal Lat { get; set; }

    public decimal Lon { get; set; }

    public virtual ICollection<Route> RouteFirstStops { get; set; } = new List<Route>();

    public virtual ICollection<Route> RouteLastStops { get; set; } = new List<Route>();

    public virtual ICollection<RouteStopDto> RouteStops { get; set; } = new List<RouteStopDto>();

    public virtual ICollection<RouteVehicleDto> RouteVehicles { get; set; } = new List<RouteVehicleDto>();

    public virtual ICollection<ScheduleDto> Schedules { get; set; } = new List<ScheduleDto>();
}
