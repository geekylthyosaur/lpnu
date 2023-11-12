using api.Models;

namespace api.Services.TicketService;

public interface ITicketService
{
    void AddTicket(Ticket ticket);
    Ticket GetTicket(int id);
    IEnumerable<Ticket> GetTickets();
    void UpdateTicket(Ticket ticket);
    void DeleteTicket(int id);
}