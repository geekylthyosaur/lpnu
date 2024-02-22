using api.DTO;

namespace api.Services.RouteService;

public interface IRouteService
{
    void AddRoute(RouteDto route);
    RouteDto GetRoute(int id);
    IEnumerable<RouteDto> GetRoutes();
    void UpdateRoute(RouteDto route);
    void DeleteRoute(int id);
}
