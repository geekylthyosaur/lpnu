using api.Models;
using Route = api.Models.Route;

namespace api.Services.RouteService;

public interface IRouteService
{
    void AddRoute(Route route);
    Route GetRoute(int id);
    IEnumerable<Route> GetRoutes();
    void UpdateRoute(Route route);
    void DeleteRoute(int id);
}
