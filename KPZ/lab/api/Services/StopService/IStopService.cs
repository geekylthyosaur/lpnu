using api.Models;

namespace api.Services.StopService;

public interface IStopService
{
    void AddStop(Stop stop);
    Stop GetStop(int id);
    IEnumerable<Stop> GetStops();
    void UpdateStop(Stop stop);
    void DeleteStop(int id);
}