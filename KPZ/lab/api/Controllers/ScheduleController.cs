using api.Models;
using api.Services.ScheduleService;
using Microsoft.AspNetCore.Mvc;

namespace api.Controllers;

[ApiController]
    [Route("[controller]/")]
    public class ScheduleController : ControllerBase
    {
        private readonly IScheduleService _scheduleService;

        public ScheduleController(IScheduleService scheduleService)
        {
            _scheduleService = scheduleService;
        }

        [HttpPost(Name = "AddSchedule")]
        public ActionResult AddSchedule([FromBody] Schedule schedule)
        {
            try
            {
                _scheduleService.AddSchedule(schedule);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpGet("{id:int}", Name = "GetSchedule")]
        public ActionResult<Schedule> GetSchedule(int id)
        {
            try
            {
                var schedule = _scheduleService.GetSchedule(id);
                return Ok(schedule);
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpGet(Name = "GetSchedules")]
        public ActionResult<IEnumerable<Schedule>> GetSchedules()
        {
            try
            {
                var schedules = _scheduleService.GetSchedules();
                return Ok(schedules);
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpPut(Name = "UpdateSchedule")]
        public ActionResult UpdateSchedule([FromBody] Schedule schedule)
        {
            try
            {
                _scheduleService.UpdateSchedule(schedule);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpDelete("{id:int}", Name = "DeleteSchedule")]
        public ActionResult DeleteSchedule(int id)
        {
            try
            {
                _scheduleService.DeleteSchedule(id);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }
    }