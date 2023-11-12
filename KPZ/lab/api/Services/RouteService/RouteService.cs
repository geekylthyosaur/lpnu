using api.Models;
using Route = api.Models.Route;

namespace api.Services.RouteService;

public class RouteService : IRouteService
{
    private readonly MyContext _myContext;

    public RouteService(MyContext myContext)
    {
        _myContext = myContext;
    }

    public void AddRoute(Route route)
    {
        if (_myContext.Routes.Find(route) is not null)
            throw new Exception("Already exists");
        _myContext.Routes.Add(route);
    }

    public Route GetRoute(int id)
    {
        var route = _myContext.Routes.Find(id);
        if (route is null) throw new Exception("Not found");
        return route;
    }

    public IEnumerable<Route> GetRoutes()
    {
        return _myContext.Routes.ToList();
    }

    public void UpdateRoute(Route route)
    {
        if (_myContext.Routes.Find(route) is null) throw new Exception("Not found");
        _myContext.Routes.Update(route);
    }

    public void DeleteRoute(int id)
    {
        var route = _myContext.Routes.Find(id);
        if (route is null) throw new Exception("Not found");
        _myContext.Routes.Remove(route);
    }
}

