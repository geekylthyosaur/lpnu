using api.Models;

namespace api.Services.ScheduleService;

public interface IScheduleService
{
    void AddSchedule(Schedule schedule);
    Schedule GetSchedule(int id);
    IEnumerable<Schedule> GetSchedules();
    void UpdateSchedule(Schedule schedule);
    void DeleteSchedule(int id);
}