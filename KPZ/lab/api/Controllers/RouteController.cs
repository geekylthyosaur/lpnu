using api.DTO;
using api.Services.RouteService;
using Microsoft.AspNetCore.Mvc;

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
    public ActionResult AddRoute([FromBody] RouteDto route)
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
    public ActionResult<RouteDto> GetRoute(int id)
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
    public ActionResult<IEnumerable<RouteDto>> GetRoutes()
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
    public ActionResult UpdateRoute([FromBody] RouteDto route)
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

