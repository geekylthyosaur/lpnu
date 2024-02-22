using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class TicketDto
{
    public int Id { get; set; }

    public string TransactionId { get; set; } = null!;

    public decimal Fare { get; set; }

    public DateTime Time { get; set; }

    public int RouteId { get; set; }

    public int? VehicleId { get; set; }

    public virtual Route Route { get; set; } = null!;

    public virtual VehicleDto? Vehicle { get; set; }
}
