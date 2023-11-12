using System;
using System.Collections.Generic;

namespace api.Models;

public partial class VehicleMaintenance
{
    public int Id { get; set; }

    public int VehicleId { get; set; }

    public string Description { get; set; } = null!;

    public DateTime Time { get; set; }

    public decimal CostTotal { get; set; }

    public virtual Vehicle Vehicle { get; set; } = null!;
}
