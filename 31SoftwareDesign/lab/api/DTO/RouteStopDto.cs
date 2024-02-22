using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class RouteStopDto
{
    public int Id { get; set; }

    public int RouteId { get; set; }

    public int StopId { get; set; }

    public int OrdIndex { get; set; }

    public virtual Route Route { get; set; } = null!;

    public virtual StopDto Stop { get; set; } = null!;
}
