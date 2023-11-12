using api.DTO;
using api.Services.StopService;
using Microsoft.AspNetCore.Mvc;

namespace api.Controllers;

[ApiController]
[Route("[controller]/")]
public class StopController : ControllerBase
{
    private readonly IStopService _stopService;

    public StopController(IStopService stopService)
    {
        _stopService = stopService;
    }
    
    [HttpPost(Name = "AddStop")]
    public ActionResult AddStop([FromBody] StopDto stop) 
    {
        try
        {
            _stopService.AddStop(stop);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
    
    [HttpGet("{id:int}", Name = "GetStop")]
    public ActionResult<StopDto> GetStop(int id) 
    {
        try
        {
            var stop = _stopService.GetStop(id);
            return Ok(stop);
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
    
    [HttpGet(Name = "GetStops")]
    public ActionResult<IEnumerable<StopDto>> GetStops() 
    {
        try
        {
            var drivers = _stopService.GetStops();
            return Ok(drivers);
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
    
    [HttpPut(Name = "UpdateStop")]
    public ActionResult UpdateStop([FromBody] StopDto stop) 
    {
        try
        {
            _stopService.UpdateStop(stop);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
    
    [HttpDelete("{id:int}", Name = "DeleteStop")]
    public ActionResult DeleteStop(int id) 
    {
        try
        {
            _stopService.DeleteStop(id);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
}