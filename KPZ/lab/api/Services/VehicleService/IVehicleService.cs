using api.Models;

namespace api.Services.VehicleService;

public interface IVehicleService
{
    void AddVehicle(Vehicle vehicle);
    Vehicle GetVehicle(int id);
    IEnumerable<Vehicle> GetVehicles();
    void UpdateVehicle(Vehicle vehicle);
    void DeleteVehicle(int id);
}