using api.Models;

namespace api.Services.VehicleService;

public class VehicleService : IVehicleService
{
    private readonly MyContext _myContext;

    public VehicleService(MyContext myContext)
    {
        _myContext = myContext;
    }

    public void AddVehicle(Vehicle vehicle)
    {
        if (_myContext.Vehicles.Find(vehicle) is not null)
            throw new Exception("Already exists");
        _myContext.Vehicles.Add(vehicle);
    }

    public Vehicle GetVehicle(int id)
    {
        var vehicle = _myContext.Vehicles.Find(id);
        if (vehicle is null) throw new Exception("Not found");
        return vehicle;
    }

    public IEnumerable<Vehicle> GetVehicles()
    {
        return _myContext.Vehicles.ToList();
    }

    public void UpdateVehicle(Vehicle vehicle)
    {
        if (_myContext.Vehicles.Find(vehicle) is null) throw new Exception("Not found");
        _myContext.Vehicles.Update(vehicle);
    }

    public void DeleteVehicle(int id)
    {
        var vehicle = _myContext.Vehicles.Find(id);
        if (vehicle is null) throw new Exception("Not found");
        _myContext.Vehicles.Remove(vehicle);
    }
}