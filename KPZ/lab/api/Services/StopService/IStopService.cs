using api.DTO;

namespace api.Services.StopService;

public interface IStopService
{
    void AddStop(StopDto stop);
    StopDto GetStop(int id);
    IEnumerable<StopDto> GetStops();
    void UpdateStop(StopDto stop);
    void DeleteStop(int id);
}