using api.Models;
using api.Services.DriverService;
using Microsoft.AspNetCore.Mvc;

namespace api.Controllers;

[ApiController]
[Route("[controller]/")]
public class DriverController : ControllerBase
{
    private readonly IDriverService _driverService;

    public DriverController(IDriverService driverService)
    {
        _driverService = driverService;
    }
    
    [HttpPost(Name = "AddDriver")]
    public ActionResult AddDriver([FromBody] Driver driver) 
    {
        try
        {
            _driverService.AddDriver(driver);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
    
    [HttpGet("{id:int}", Name = "GetDriver")]
    public ActionResult<Driver> GetDriver(int id) 
    {
        try
        {
            var driver = _driverService.GetDriver(id);
            return Ok(driver);
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
    
    [HttpGet(Name = "GetDrivers")]
    public ActionResult<IEnumerable<Driver>> GetDrivers() 
    {
        try
        {
            var drivers = _driverService.GetDrivers();
            return Ok(drivers);
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
    
    [HttpPut(Name = "UpdateDriver")]
    public ActionResult UpdateDriver([FromBody] Driver driver) 
    {
        try
        {
            _driverService.UpdateDriver(driver);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
    
    [HttpDelete("{id:int}", Name = "DeleteDriver")]
    public ActionResult DeleteDriver(int id) 
    {
        try
        {
            _driverService.DeleteDriver(id);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(new { message = e.ToString()});
        }
    }
}