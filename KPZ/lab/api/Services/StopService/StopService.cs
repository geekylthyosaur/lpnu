using api.DTO;
using api.Models;
using AutoMapper;

namespace api.Services.StopService;

public class StopService : IStopService
{
    private readonly MyContext _myContext;
    private readonly IMapper _mapper;

    public StopService(MyContext myContext, IMapper mapper)
    {
        _myContext = myContext;
        _mapper = mapper;
    }
    
    public void AddStop(StopDto stop)
    {
        if (_myContext.Stops.Find(stop) is not null)
            throw new Exception("Already exists");
        _myContext.Stops.Add(_mapper.Map<Stop>(stop));
    }

    public StopDto GetStop(int id)
    {
        var stop = _myContext.Stops.Find(id);
        if (stop is null) throw new Exception("Not found");
        return _mapper.Map<StopDto>(stop);
    }

    public IEnumerable<StopDto> GetStops()
    {
        return _mapper.Map<IEnumerable<StopDto>>(_myContext.Stops.ToList());
    }

    public void UpdateStop(StopDto stop)
    {
        if (_myContext.Stops.Find(stop) is null) throw new Exception("Not found");
        _myContext.Stops.Update(_mapper.Map<Stop>(stop));
    }

    public void DeleteStop(int id)
    {
        var stop = _myContext.Stops.Find(id);
        if (stop is null) throw new Exception("Not found");
        _myContext.Stops.Remove(stop);
    }
}