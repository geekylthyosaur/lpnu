using api.DTO;
using api.Models;
using AutoMapper;

namespace api.Services.VehicleService;

public class VehicleService : IVehicleService
{
    private readonly MyContext _myContext;
    private readonly IMapper _mapper;

    public VehicleService(MyContext myContext, IMapper mapper)
    {
        _myContext = myContext;
        _mapper = mapper;
    }

    public void AddVehicle(VehicleDto vehicle)
    {
        if (_myContext.Vehicles.Find(vehicle) is not null)
            throw new Exception("Already exists");
        _myContext.Vehicles.Add(_mapper.Map<Vehicle>(vehicle));
    }

    public VehicleDto GetVehicle(int id)
    {
        var vehicle = _myContext.Vehicles.Find(id);
        if (vehicle is null) throw new Exception("Not found");
        return _mapper.Map<VehicleDto>(vehicle);
    }

    public IEnumerable<VehicleDto> GetVehicles()
    {
        return _mapper.Map<IEnumerable<VehicleDto>>(_myContext.Vehicles.ToList());
    }

    public void UpdateVehicle(VehicleDto vehicle)
    {
        if (_myContext.Vehicles.Find(vehicle) is null) throw new Exception("Not found");
        _myContext.Vehicles.Update(_mapper.Map<Vehicle>(vehicle));
    }

    public void DeleteVehicle(int id)
    {
        var vehicle = _myContext.Vehicles.Find(id);
        if (vehicle is null) throw new Exception("Not found");
        _myContext.Vehicles.Remove(vehicle);
    }
}