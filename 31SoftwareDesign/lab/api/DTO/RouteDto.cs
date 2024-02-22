namespace api.DTO;

public partial class RouteDto
{
    public int Id { get; set; }

    public string Name { get; set; } = null!;

    public int FirstStopId { get; set; }

    public int LastStopId { get; set; }

    public virtual ICollection<DriverRouteDto> DriverRoutes { get; set; } = new List<DriverRouteDto>();

    public virtual StopDto FirstStop { get; set; } = null!;

    public virtual StopDto LastStop { get; set; } = null!;

    public virtual ICollection<RouteStopDto> RouteStops { get; set; } = new List<RouteStopDto>();

    public virtual ICollection<RouteVehicleDto> RouteVehicles { get; set; } = new List<RouteVehicleDto>();

    public virtual ICollection<ScheduleDto> Schedules { get; set; } = new List<ScheduleDto>();

    public virtual ICollection<TicketDto> Tickets { get; set; } = new List<TicketDto>();
}
