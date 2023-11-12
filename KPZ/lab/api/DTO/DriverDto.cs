using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class DriverDto
{
    public int Id { get; set; }

    public string FirstName { get; set; } = null!;

    public string LastName { get; set; } = null!;

    public decimal Salary { get; set; }

    public virtual ICollection<DriverRouteDto> DriverRoutes { get; set; } = new List<DriverRouteDto>();
}
