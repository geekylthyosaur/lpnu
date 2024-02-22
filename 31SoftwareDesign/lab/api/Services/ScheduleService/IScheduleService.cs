using api.DTO;

namespace api.Services.ScheduleService;

public interface IScheduleService
{
    void AddSchedule(ScheduleDto schedule);
    ScheduleDto GetSchedule(int id);
    IEnumerable<ScheduleDto> GetSchedules();
    void UpdateSchedule(ScheduleDto schedule);
    void DeleteSchedule(int id);
}