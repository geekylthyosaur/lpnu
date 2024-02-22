using api.DTO;
using api.Models;
using AutoMapper;
using Route = api.Models.Route;

namespace api.Services.RouteService;

public class RouteService : IRouteService
{
    private readonly MyContext _myContext;
    private readonly IMapper _mapper;

    public RouteService(MyContext myContext, IMapper mapper)
    {
        _myContext = myContext;
        _mapper = mapper;
    }

    public void AddRoute(RouteDto route)
    {
        if (_myContext.Routes.Find(route) is not null)
            throw new Exception("Already exists");
        _myContext.Routes.Add(_mapper.Map<Route>(route));
    }

    public RouteDto GetRoute(int id)
    {
        var route = _myContext.Routes.Find(id);
        if (route is null) throw new Exception("Not found");
        return _mapper.Map<RouteDto>(route);
    }

    public IEnumerable<RouteDto> GetRoutes()
    {
        return _mapper.Map<IEnumerable<RouteDto>>(_myContext.Routes.ToList());
    }

    public void UpdateRoute(RouteDto route)
    {
        if (_myContext.Routes.Find(route) is null) throw new Exception("Not found");
        _myContext.Routes.Update(_mapper.Map<Route>(route));
    }

    public void DeleteRoute(int id)
    {
        var route = _myContext.Routes.Find(id);
        if (route is null) throw new Exception("Not found");
        _myContext.Routes.Remove(route);
    }
}

