using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class VehicleDto
{
    public int Id { get; set; }

    public string Type { get; set; } = null!;

    public string LicensePlate { get; set; } = null!;

    public int Capacity { get; set; }

    public virtual ICollection<DriverRouteDto> DriverRoutes { get; set; } = new List<DriverRouteDto>();

    public virtual ICollection<RouteVehicleDto> RouteVehicles { get; set; } = new List<RouteVehicleDto>();

    public virtual ICollection<ScheduleDto> Schedules { get; set; } = new List<ScheduleDto>();

    public virtual ICollection<TicketDto> Tickets { get; set; } = new List<TicketDto>();

    public virtual ICollection<VehicleMaintenanceDto> VehicleMaintenances { get; set; } = new List<VehicleMaintenanceDto>();
}
