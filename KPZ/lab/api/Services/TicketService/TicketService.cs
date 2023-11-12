using api.Models;

namespace api.Services.TicketService;

public class TicketService : ITicketService
{
    private readonly MyContext _myContext;

    public TicketService(MyContext myContext)
    {
        _myContext = myContext;
    }

    public void AddTicket(Ticket ticket)
    {
        if (_myContext.Tickets.Find(ticket) is not null)
            throw new Exception("Already exists");
        _myContext.Tickets.Add(ticket);
    }

    public Ticket GetTicket(int id)
    {
        var ticket = _myContext.Tickets.Find(id);
        if (ticket is null) throw new Exception("Not found");
        return ticket;
    }

    public IEnumerable<Ticket> GetTickets()
    {
        return _myContext.Tickets.ToList();
    }

    public void UpdateTicket(Ticket ticket)
    {
        if (_myContext.Tickets.Find(ticket) is null) throw new Exception("Not found");
        _myContext.Tickets.Update(ticket);
    }

    public void DeleteTicket(int id)
    {
        var ticket = _myContext.Tickets.Find(id);
        if (ticket is null) throw new Exception("Not found");
        _myContext.Tickets.Remove(ticket);
    }
}