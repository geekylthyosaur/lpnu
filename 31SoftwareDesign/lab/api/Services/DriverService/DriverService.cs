using api.DTO;
using api.Models;
using AutoMapper;

namespace api.Services.DriverService;

public class DriverService : IDriverService
{
    private readonly MyContext _myContext;
    private readonly IMapper _mapper;

    public DriverService(MyContext myContext, IMapper mapper)
    {
        _myContext = myContext;
        _mapper = mapper;
    }
    
    public void AddDriver(DriverDto driver)
    {
        if (_myContext.Drivers.Find(driver) is not null)
            throw new Exception("Already exists");
        _myContext.Drivers.Add(_mapper.Map<Driver>(driver));
    }

    public DriverDto GetDriver(int id)
    {
        var driver = _myContext.Drivers.Find(id);
        if (driver is null) throw new Exception("Not found");
        return _mapper.Map<DriverDto>(driver);
    }

    public IEnumerable<DriverDto> GetDrivers()
    {
        return _mapper.Map<IEnumerable<DriverDto>>(_myContext.Drivers.ToList());
    }

    public void UpdateDriver(DriverDto driver)
    {
        if (_myContext.Drivers.Find(driver) is null) throw new Exception("Not found");
        _myContext.Drivers.Update(_mapper.Map<Driver>(driver));
    }

    public void DeleteDriver(int id)
    {
        var driver = _myContext.Drivers.Find(id);
        if (driver is null) throw new Exception("Not found");
        _myContext.Drivers.Remove(driver);
    }
}