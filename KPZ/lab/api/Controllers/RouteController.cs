using api.Services.RouteService;
using Microsoft.AspNetCore.Mvc;
using Route = api.Models.Route;

namespace api.Controllers;

[ApiController]
[Route("[controller]/")]
public class RouteController : ControllerBase
{
    private readonly IRouteService _routeService;

    public RouteController(IRouteService routeService)
    {
        _routeService = routeService;
    }

    [HttpPost(Name = "AddRoute")]
    public ActionResult AddRoute([FromBody] Route route)
    {
        try
        {
            _routeService.AddRoute(route);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString() });
        }
    }

    [HttpGet("{id:int}", Name = "GetRoute")]
    public ActionResult<Route> GetRoute(int id)
    {
        try
        {
            var route = _routeService.GetRoute(id);
            return Ok(route);
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString() });
        }
    }

    [HttpGet(Name = "GetRoutes")]
    public ActionResult<IEnumerable<Route>> GetRoutes()
    {
        try
        {
            var routes = _routeService.GetRoutes();
            return Ok(routes);
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString() });
        }
    }

    [HttpPut(Name = "UpdateRoute")]
    public ActionResult UpdateRoute([FromBody] Route route)
    {
        try
        {
            _routeService.UpdateRoute(route);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString() });
        }
    }

    [HttpDelete("{id:int}", Name = "DeleteRoute")]
    public ActionResult DeleteRoute(int id)
    {
        try
        {
            _routeService.DeleteRoute(id);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString() });
        }
    }
}

