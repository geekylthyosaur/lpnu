using api.Mapping;
using api.Models;
using api.Services.DriverService;
using api.Services.FeedbackService;
using api.Services.RouteService;
using api.Services.ScheduleService;
using api.Services.StopService;
using api.Services.TicketService;
using api.Services.VehicleService;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddDbContext<MyContext>();

// Add services to the container.
builder.Services.AddScoped<IDriverService, DriverService>();
builder.Services.AddScoped<IStopService, StopService>();
builder.Services.AddScoped<IRouteService, RouteService>();
builder.Services.AddScoped<ITicketService, TicketService>();
builder.Services.AddScoped<IVehicleService, VehicleService>();
builder.Services.AddScoped<IScheduleService, ScheduleService>();
builder.Services.AddScoped<IFeedbackService, FeedbackService>();

builder.Services.AddAutoMapper(typeof(MappingProfile));

builder.Services.AddControllers();

// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

app.UseCors(
    options => options.WithOrigins("http://localhost:8080", "http://localhost:4200").AllowAnyMethod()
);

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();