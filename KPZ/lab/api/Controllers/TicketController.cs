using api.Models;
using api.Services.TicketService;
using Microsoft.AspNetCore.Mvc;

namespace api.Controllers;

[ApiController]
    [Route("[controller]/")]
    public class TicketController : ControllerBase
    {
        private readonly ITicketService _ticketService;

        public TicketController(ITicketService ticketService)
        {
            _ticketService = ticketService;
        }

        [HttpPost(Name = "AddTicket")]
        public ActionResult AddTicket([FromBody] Ticket ticket)
        {
            try
            {
                _ticketService.AddTicket(ticket);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpGet("{id:int}", Name = "GetTicket")]
        public ActionResult<Ticket> GetTicket(int id)
        {
            try
            {
                var ticket = _ticketService.GetTicket(id);
                return Ok(ticket);
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpGet(Name = "GetTickets")]
        public ActionResult<IEnumerable<Ticket>> GetTickets()
        {
            try
            {
                var tickets = _ticketService.GetTickets();
                return Ok(tickets);
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpPut(Name = "UpdateTicket")]
        public ActionResult UpdateTicket([FromBody] Ticket ticket)
        {
            try
            {
                _ticketService.UpdateTicket(ticket);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }

        [HttpDelete("{id:int}", Name = "DeleteTicket")]
        public ActionResult DeleteTicket(int id)
        {
            try
            {
                _ticketService.DeleteTicket(id);
                return Ok();
            }
            catch (Exception e)
            {
                return BadRequest(new { message = e.ToString() });
            }
        }
    }