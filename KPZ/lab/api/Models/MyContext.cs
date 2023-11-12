using Microsoft.EntityFrameworkCore;

namespace api.Models;

public partial class MyContext : DbContext
{
    public MyContext()
    {
    }

    public MyContext(DbContextOptions<MyContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Driver> Drivers { get; set; }

    public virtual DbSet<DriverRoute> DriverRoutes { get; set; }

    public virtual DbSet<Feedback> Feedbacks { get; set; }

    public virtual DbSet<Route> Routes { get; set; }

    public virtual DbSet<RouteStop> RouteStops { get; set; }

    public virtual DbSet<RouteVehicle> RouteVehicles { get; set; }

    public virtual DbSet<Schedule> Schedules { get; set; }

    public virtual DbSet<Stop> Stops { get; set; }

    public virtual DbSet<Ticket> Tickets { get; set; }

    public virtual DbSet<Vehicle> Vehicles { get; set; }

    public virtual DbSet<VehicleMaintenance> VehicleMaintenances { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
#warning To protect potentially sensitive information in your connection string, you should move it out of source code. You can avoid scaffolding the connection string by using the Name= syntax to read it from configuration - see https://go.microsoft.com/fwlink/?linkid=2131148. For more guidance on storing connection strings, see http://go.microsoft.com/fwlink/?LinkId=723263.
        => optionsBuilder.UseNpgsql("Host=192.168.1.9;Port=5432;Database=my;Username=user;Password=password;");

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Driver>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("driver_pk");

            entity.ToTable("driver");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.FirstName)
                .HasMaxLength(64)
                .HasColumnName("first_name");
            entity.Property(e => e.LastName)
                .HasMaxLength(64)
                .HasColumnName("last_name");
            entity.Property(e => e.Salary)
                .HasPrecision(8, 2)
                .HasColumnName("salary");
        });

        modelBuilder.Entity<DriverRoute>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("driver_route_pk");

            entity.ToTable("driver_route");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.DriverId).HasColumnName("driver_id");
            entity.Property(e => e.RouteId).HasColumnName("route_id");
            entity.Property(e => e.VehicleId).HasColumnName("vehicle_id");

            entity.HasOne(d => d.Driver).WithMany(p => p.DriverRoutes)
                .HasForeignKey(d => d.DriverId)
                .HasConstraintName("driver_route_driver_id_fk");

            entity.HasOne(d => d.Route).WithMany(p => p.DriverRoutes)
                .HasForeignKey(d => d.RouteId)
                .HasConstraintName("driver_route_route_id_fk");

            entity.HasOne(d => d.Vehicle).WithMany(p => p.DriverRoutes)
                .HasForeignKey(d => d.VehicleId)
                .HasConstraintName("driver_route_vehicle_id_fk");
        });

        modelBuilder.Entity<Feedback>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("feedback_pk");

            entity.ToTable("feedback");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Email)
                .HasMaxLength(255)
                .HasColumnName("email");
            entity.Property(e => e.Message).HasColumnName("message");
            entity.Property(e => e.Name)
                .HasMaxLength(64)
                .HasColumnName("name");
            entity.Property(e => e.Time).HasColumnName("time");
        });

        modelBuilder.Entity<Route>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("route_pk");

            entity.ToTable("route");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.FirstStopId).HasColumnName("first_stop_id");
            entity.Property(e => e.LastStopId).HasColumnName("last_stop_id");
            entity.Property(e => e.Name)
                .HasMaxLength(64)
                .HasColumnName("name");

            entity.HasOne(d => d.FirstStop).WithMany(p => p.RouteFirstStops)
                .HasForeignKey(d => d.FirstStopId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("route_stop_id_fk");

            entity.HasOne(d => d.LastStop).WithMany(p => p.RouteLastStops)
                .HasForeignKey(d => d.LastStopId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("route_stop_id_fk2");
        });

        modelBuilder.Entity<RouteStop>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("table_name_pk");

            entity.ToTable("route_stop");

            entity.HasIndex(e => new { e.RouteId, e.OrdIndex }, "route_stop_route_id_ord_index_key").IsUnique();

            entity.HasIndex(e => new { e.RouteId, e.StopId }, "route_stop_route_id_stop_id_key").IsUnique();

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.OrdIndex).HasColumnName("ord_index");
            entity.Property(e => e.RouteId).HasColumnName("route_id");
            entity.Property(e => e.StopId).HasColumnName("stop_id");

            entity.HasOne(d => d.Route).WithMany(p => p.RouteStops)
                .HasForeignKey(d => d.RouteId)
                .HasConstraintName("table_name_route_id_fk");

            entity.HasOne(d => d.Stop).WithMany(p => p.RouteStops)
                .HasForeignKey(d => d.StopId)
                .HasConstraintName("table_name_stop_id_fk");
        });

        modelBuilder.Entity<RouteVehicle>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("route_vehicle_pk");

            entity.ToTable("route_vehicle");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.LastCoordsTime).HasColumnName("last_coords_time");
            entity.Property(e => e.LastLat)
                .HasPrecision(8, 6)
                .HasColumnName("last_lat");
            entity.Property(e => e.LastLon)
                .HasPrecision(9, 6)
                .HasColumnName("last_lon");
            entity.Property(e => e.NextStop).HasColumnName("next_stop");
            entity.Property(e => e.RouteId).HasColumnName("route_id");
            entity.Property(e => e.VehicleId).HasColumnName("vehicle_id");

            entity.HasOne(d => d.NextStopNavigation).WithMany(p => p.RouteVehicles)
                .HasForeignKey(d => d.NextStop)
                .OnDelete(DeleteBehavior.Cascade)
                .HasConstraintName("route_vehicle_stop_id_fk");

            entity.HasOne(d => d.Route).WithMany(p => p.RouteVehicles)
                .HasForeignKey(d => d.RouteId)
                .HasConstraintName("route_vehicle_route_id_fk");

            entity.HasOne(d => d.Vehicle).WithMany(p => p.RouteVehicles)
                .HasForeignKey(d => d.VehicleId)
                .HasConstraintName("route_vehicle_vahicle_id_fk");
        });

        modelBuilder.Entity<Schedule>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("timetable_pk");

            entity.ToTable("schedule");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.ArrivalTime).HasColumnName("arrival_time");
            entity.Property(e => e.DepartureTime).HasColumnName("departure_time");
            entity.Property(e => e.RouteId).HasColumnName("route_id");
            entity.Property(e => e.StopId).HasColumnName("stop_id");
            entity.Property(e => e.VehicleId).HasColumnName("vehicle_id");

            entity.HasOne(d => d.Route).WithMany(p => p.Schedules)
                .HasForeignKey(d => d.RouteId)
                .HasConstraintName("timetable_route_id_fk");

            entity.HasOne(d => d.Stop).WithMany(p => p.Schedules)
                .HasForeignKey(d => d.StopId)
                .HasConstraintName("timetable_stop_id_fk");

            entity.HasOne(d => d.Vehicle).WithMany(p => p.Schedules)
                .HasForeignKey(d => d.VehicleId)
                .HasConstraintName("timetable_vehicle_id_fk");
        });

        modelBuilder.Entity<Stop>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("stop_pk");

            entity.ToTable("stop");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Lat)
                .HasPrecision(8, 6)
                .HasColumnName("lat");
            entity.Property(e => e.Lon)
                .HasPrecision(9, 6)
                .HasColumnName("lon");
            entity.Property(e => e.Name)
                .HasMaxLength(64)
                .HasColumnName("name");
        });

        modelBuilder.Entity<Ticket>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("ticket_pk");

            entity.ToTable("ticket");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Fare)
                .HasPrecision(8, 2)
                .HasColumnName("fare");
            entity.Property(e => e.RouteId).HasColumnName("route_id");
            entity.Property(e => e.Time).HasColumnName("time");
            entity.Property(e => e.TransactionId)
                .HasMaxLength(64)
                .HasColumnName("transaction_id");
            entity.Property(e => e.VehicleId).HasColumnName("vehicle_id");

            entity.HasOne(d => d.Route).WithMany(p => p.Tickets)
                .HasForeignKey(d => d.RouteId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("ticket_route_id_fk");

            entity.HasOne(d => d.Vehicle).WithMany(p => p.Tickets)
                .HasForeignKey(d => d.VehicleId)
                .HasConstraintName("ticket_vehicle_id_fk");
        });

        modelBuilder.Entity<Vehicle>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("vehicle_pk");

            entity.ToTable("vehicle");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Capacity).HasColumnName("capacity");
            entity.Property(e => e.LicensePlate)
                .HasMaxLength(64)
                .HasColumnName("license_plate");
            entity.Property(e => e.Type)
                .HasMaxLength(64)
                .HasColumnName("type");
        });

        modelBuilder.Entity<VehicleMaintenance>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("vehicle_maintenance_pk");

            entity.ToTable("vehicle_maintenance");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.CostTotal)
                .HasPrecision(8, 2)
                .HasColumnName("cost_total");
            entity.Property(e => e.Description).HasColumnName("description");
            entity.Property(e => e.Time)
                .HasDefaultValueSql("now()")
                .HasColumnName("time");
            entity.Property(e => e.VehicleId).HasColumnName("vehicle_id");

            entity.HasOne(d => d.Vehicle).WithMany(p => p.VehicleMaintenances)
                .HasForeignKey(d => d.VehicleId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("vehicle_maintenance_vehicle_id_fk");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
