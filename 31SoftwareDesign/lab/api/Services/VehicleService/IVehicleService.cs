using api.DTO;

namespace api.Services.VehicleService;

public interface IVehicleService
{
    void AddVehicle(VehicleDto vehicle);
    VehicleDto GetVehicle(int id);
    IEnumerable<VehicleDto> GetVehicles();
    void UpdateVehicle(VehicleDto vehicle);
    void DeleteVehicle(int id);
}