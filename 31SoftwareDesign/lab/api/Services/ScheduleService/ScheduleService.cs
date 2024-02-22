using api.DTO;
using api.Models;
using AutoMapper;

namespace api.Services.ScheduleService;

public class ScheduleService : IScheduleService
{
    private readonly MyContext _myContext;
    private readonly IMapper _mapper;

    public ScheduleService(MyContext myContext, IMapper mapper)
    {
        _myContext = myContext;
        _mapper = mapper;
    }

    public void AddSchedule(ScheduleDto schedule)
    {
        if (_myContext.Schedules.Find(schedule) is not null)
            throw new Exception("Already exists");
        _myContext.Schedules.Add(_mapper.Map<Schedule>(schedule));
    }

    public ScheduleDto GetSchedule(int id)
    {
        var schedule = _myContext.Schedules.Find(id);
        if (schedule is null) throw new Exception("Not found");
        return _mapper.Map<ScheduleDto>(schedule);
    }

    public IEnumerable<ScheduleDto> GetSchedules()
    {
        return _mapper.Map<IEnumerable<ScheduleDto>>(_myContext.Schedules.ToList());
    }

    public void UpdateSchedule(ScheduleDto schedule)
    {
        if (_myContext.Schedules.Find(schedule) is null) throw new Exception("Not found");
        _myContext.Schedules.Update(_mapper.Map<Schedule>(schedule));
    }

    public void DeleteSchedule(int id)
    {
        var schedule = _myContext.Schedules.Find(id);
        if (schedule is null) throw new Exception("Not found");
        _myContext.Schedules.Remove(schedule);
    }
}