using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class VehicleMaintenanceDto
{
    public int Id { get; set; }

    public int VehicleId { get; set; }

    public string Description { get; set; } = null!;

    public DateTime Time { get; set; }

    public decimal CostTotal { get; set; }

    public virtual VehicleDto Vehicle { get; set; } = null!;
}
