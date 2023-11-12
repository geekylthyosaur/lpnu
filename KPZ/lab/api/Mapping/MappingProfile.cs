using api.DTO;
using api.Models;
using AutoMapper;
using Route = api.Models.Route;

namespace api.Mapping;

public class MappingProfile : Profile
{
    public MappingProfile()
    {
        CreateMap<Driver, DriverDto>();
        CreateMap<DriverDto, Driver>();

        CreateMap<DriverRoute, DriverRouteDto>();
        CreateMap<DriverRouteDto, DriverRoute>();

        CreateMap<Feedback, FeedbackDto>();
        CreateMap<FeedbackDto, Feedback>();

        CreateMap<Route, RouteDto>();
        CreateMap<RouteDto, Route>();

        CreateMap<RouteStop, RouteStopDto>();
        CreateMap<RouteStopDto, RouteStop>();

        CreateMap<RouteVehicle, RouteVehicleDto>();
        CreateMap<RouteVehicleDto, RouteVehicle>();

        CreateMap<Schedule, ScheduleDto>();
        CreateMap<ScheduleDto, Schedule>();

        CreateMap<Stop, StopDto>();
        CreateMap<StopDto, Stop>();

        CreateMap<Ticket, TicketDto>();
        CreateMap<TicketDto, Ticket>();

        CreateMap<Vehicle, VehicleDto>();
        CreateMap<VehicleDto, Vehicle>();

        CreateMap<VehicleMaintenance, VehicleMaintenanceDto>();
        CreateMap<VehicleMaintenanceDto, VehicleMaintenance>();
    }
}