using System;
using System.Collections.Generic;

namespace api.Models;

public partial class RouteStop
{
    public int Id { get; set; }

    public int RouteId { get; set; }

    public int StopId { get; set; }

    public int OrdIndex { get; set; }

    public virtual Route Route { get; set; } = null!;

    public virtual Stop Stop { get; set; } = null!;
}
