using api.DTO;
using api.Models;
using AutoMapper;

namespace api.Services.TicketService;

public class TicketService : ITicketService
{
    private readonly MyContext _myContext;
    private readonly IMapper _mapper;

    public TicketService(MyContext myContext, IMapper mapper)
    {
        _myContext = myContext;
        _mapper = mapper;
    }

    public void AddTicket(TicketDto ticket)
    {
        if (_myContext.Tickets.Find(ticket) is not null)
            throw new Exception("Already exists");
        _myContext.Tickets.Add(_mapper.Map<Ticket>(ticket));
    }

    public TicketDto GetTicket(int id)
    {
        var ticket = _myContext.Tickets.Find(id);
        if (ticket is null) throw new Exception("Not found");
        return _mapper.Map<TicketDto>(ticket);
    }

    public IEnumerable<TicketDto> GetTickets()
    {
        return _mapper.Map<IEnumerable<TicketDto>>(_myContext.Tickets.ToList());
    }

    public void UpdateTicket(TicketDto ticket)
    {
        if (_myContext.Tickets.Find(ticket) is null) throw new Exception("Not found");
        _myContext.Tickets.Update(_mapper.Map<Ticket>(ticket));
    }

    public void DeleteTicket(int id)
    {
        var ticket = _myContext.Tickets.Find(id);
        if (ticket is null) throw new Exception("Not found");
        _myContext.Tickets.Remove(ticket);
    }
}