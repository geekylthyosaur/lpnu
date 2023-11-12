using api.Models;

namespace api.Services.DriverService;

public interface IDriverService
{
    void AddDriver(Driver driver);
    Driver GetDriver(int id);
    IEnumerable<Driver> GetDrivers();
    void UpdateDriver(Driver driver);
    void DeleteDriver(int id);
}