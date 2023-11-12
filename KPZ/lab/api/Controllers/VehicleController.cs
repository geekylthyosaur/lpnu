using api.Models;
using api.Services.VehicleService;
using Microsoft.AspNetCore.Mvc;

namespace api.Controllers;

[ApiController]
    [Route("[controller]/")]
    public class VehicleController : ControllerBase
    {
        private readonly IVehicleService _vehicleService;

        public VehicleController(IVehicleService vehicleService)
        {
            _vehicleService = vehicleService;
        }

        [HttpPost(Name = "AddVehicle")]
        public ActionResult AddVehicle([FromBody] Vehicle vehicle)
        {
            try
            {
                _vehicleService.AddVehicle(vehicle);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpGet("{id:int}", Name = "GetVehicle")]
        public ActionResult<Vehicle> GetVehicle(int id)
        {
            try
            {
                var vehicle = _vehicleService.GetVehicle(id);
                return Ok(vehicle);
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpGet(Name = "GetVehicles")]
        public ActionResult<IEnumerable<Vehicle>> GetVehicles()
        {
            try
            {
                var vehicles = _vehicleService.GetVehicles();
                return Ok(vehicles);
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpPut(Name = "UpdateVehicle")]
        public ActionResult UpdateVehicle([FromBody] Vehicle vehicle)
        {
            try
            {
                _vehicleService.UpdateVehicle(vehicle);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpDelete("{id:int}", Name = "DeleteVehicle")]
        public ActionResult DeleteVehicle(int id)
        {
            try
            {
                _vehicleService.DeleteVehicle(id);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }
    }