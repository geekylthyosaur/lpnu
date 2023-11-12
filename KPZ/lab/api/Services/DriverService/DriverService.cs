using api.Models;

namespace api.Services.DriverService;

public class DriverService : IDriverService
{
    private readonly MyContext _myContext;

    public DriverService(MyContext myContext)
    {
        _myContext = myContext;
    }
    
    public void AddDriver(Driver driver)
    {
        if (_myContext.Drivers.Find(driver) is not null)
            throw new Exception("Already exists");
        _myContext.Drivers.Add(driver);
    }

    public Driver GetDriver(int id)
    {
        var driver = _myContext.Drivers.Find(id);
        if (driver is null) throw new Exception("Not found");
        return driver;
    }

    public IEnumerable<Driver> GetDrivers()
    {
        return _myContext.Drivers.ToList();
    }

    public void UpdateDriver(Driver driver)
    {
        if (_myContext.Drivers.Find(driver) is null) throw new Exception("Not found");
        _myContext.Drivers.Update(driver);
    }

    public void DeleteDriver(int id)
    {
        var driver = _myContext.Drivers.Find(id);
        if (driver is null) throw new Exception("Not found");
        _myContext.Drivers.Remove(driver);
    }
}