using System;
using System.Collections.Generic;

namespace api.Models;

public partial class Driver
{
    public int Id { get; set; }

    public string FirstName { get; set; } = null!;

    public string LastName { get; set; } = null!;

    public decimal Salary { get; set; }

    public virtual ICollection<DriverRoute> DriverRoutes { get; set; } = new List<DriverRoute>();
}
