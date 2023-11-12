using api.Models;

namespace api.Services.StopService;

public class StopService : IStopService
{
    private readonly MyContext _myContext;

    public StopService(MyContext myContext)
    {
        _myContext = myContext;
    }
    
    public void AddStop(Stop stop)
    {
        if (_myContext.Stops.Find(stop) is not null)
            throw new Exception("Already exists");
        _myContext.Stops.Add(stop);
    }

    public Stop GetStop(int id)
    {
        var stop = _myContext.Stops.Find(id);
        if (stop is null) throw new Exception("Not found");
        return stop;
    }

    public IEnumerable<Stop> GetStops()
    {
        return _myContext.Stops.ToList();
    }

    public void UpdateStop(Stop stop)
    {
        if (_myContext.Stops.Find(stop) is null) throw new Exception("Not found");
        _myContext.Stops.Update(stop);
    }

    public void DeleteStop(int id)
    {
        var stop = _myContext.Stops.Find(id);
        if (stop is null) throw new Exception("Not found");
        _myContext.Stops.Remove(stop);
    }
}