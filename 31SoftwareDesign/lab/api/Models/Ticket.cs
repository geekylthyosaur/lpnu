using System;
using System.Collections.Generic;

namespace api.Models;

public partial class Ticket
{
    public int Id { get; set; }

    public string TransactionId { get; set; } = null!;

    public decimal Fare { get; set; }

    public DateTime Time { get; set; }

    public int RouteId { get; set; }

    public int? VehicleId { get; set; }

    public virtual Route Route { get; set; } = null!;

    public virtual Vehicle? Vehicle { get; set; }
}
