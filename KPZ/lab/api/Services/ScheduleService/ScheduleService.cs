using api.Models;

namespace api.Services.ScheduleService;

public class ScheduleService : IScheduleService
{
    private readonly MyContext _myContext;

    public ScheduleService(MyContext myContext)
    {
        _myContext = myContext;
    }

    public void AddSchedule(Schedule schedule)
    {
        if (_myContext.Schedules.Find(schedule) is not null)
            throw new Exception("Already exists");
        _myContext.Schedules.Add(schedule);
    }

    public Schedule GetSchedule(int id)
    {
        var schedule = _myContext.Schedules.Find(id);
        if (schedule is null) throw new Exception("Not found");
        return schedule;
    }

    public IEnumerable<Schedule> GetSchedules()
    {
        return _myContext.Schedules.ToList();
    }

    public void UpdateSchedule(Schedule schedule)
    {
        if (_myContext.Schedules.Find(schedule) is null) throw new Exception("Not found");
        _myContext.Schedules.Update(schedule);
    }

    public void DeleteSchedule(int id)
    {
        var schedule = _myContext.Schedules.Find(id);
        if (schedule is null) throw new Exception("Not found");
        _myContext.Schedules.Remove(schedule);
    }
}