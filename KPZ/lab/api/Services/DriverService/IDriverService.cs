using api.DTO;

namespace api.Services.DriverService;

public interface IDriverService
{
    void AddDriver(DriverDto driver);
    DriverDto GetDriver(int id);
    IEnumerable<DriverDto> GetDrivers();
    void UpdateDriver(DriverDto driver);
    void DeleteDriver(int id);
}