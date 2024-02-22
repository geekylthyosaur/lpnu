using System;
using System.Collections.Generic;

namespace api.DTO;

public partial class FeedbackDto
{
    public int Id { get; set; }

    public string Message { get; set; } = null!;

    public string Email { get; set; } = null!;

    public string Name { get; set; } = null!;

    public DateTime Time { get; set; }
}
