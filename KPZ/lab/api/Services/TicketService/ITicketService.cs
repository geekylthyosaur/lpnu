using api.DTO;

namespace api.Services.TicketService;

public interface ITicketService
{
    void AddTicket(TicketDto ticket);
    TicketDto GetTicket(int id);
    IEnumerable<TicketDto> GetTickets();
    void UpdateTicket(TicketDto ticket);
    void DeleteTicket(int id);
}