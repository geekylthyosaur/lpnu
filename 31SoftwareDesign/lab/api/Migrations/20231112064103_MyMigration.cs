using System;
using Microsoft.EntityFrameworkCore.Migrations;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;

#nullable disable

namespace api.Migrations
{
    /// <inheritdoc />
    public partial class MyMigration : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "driver",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    first_name = table.Column<string>(type: "character varying(64)", maxLength: 64, nullable: false),
                    last_name = table.Column<string>(type: "character varying(64)", maxLength: 64, nullable: false),
                    salary = table.Column<decimal>(type: "numeric(8,2)", precision: 8, scale: 2, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("driver_pk", x => x.id);
                });

            migrationBuilder.CreateTable(
                name: "feedback",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    message = table.Column<string>(type: "text", nullable: false),
                    email = table.Column<string>(type: "character varying(255)", maxLength: 255, nullable: false),
                    name = table.Column<string>(type: "character varying(64)", maxLength: 64, nullable: false),
                    time = table.Column<DateTime>(type: "timestamp with time zone", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("feedback_pk", x => x.id);
                });

            migrationBuilder.CreateTable(
                name: "stop",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    name = table.Column<string>(type: "character varying(64)", maxLength: 64, nullable: false),
                    lat = table.Column<decimal>(type: "numeric(8,6)", precision: 8, scale: 6, nullable: false),
                    lon = table.Column<decimal>(type: "numeric(9,6)", precision: 9, scale: 6, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("stop_pk", x => x.id);
                });

            migrationBuilder.CreateTable(
                name: "vehicle",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    type = table.Column<string>(type: "character varying(64)", maxLength: 64, nullable: false),
                    license_plate = table.Column<string>(type: "character varying(64)", maxLength: 64, nullable: false),
                    capacity = table.Column<int>(type: "integer", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("vehicle_pk", x => x.id);
                });

            migrationBuilder.CreateTable(
                name: "route",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    name = table.Column<string>(type: "character varying(64)", maxLength: 64, nullable: false),
                    first_stop_id = table.Column<int>(type: "integer", nullable: false),
                    last_stop_id = table.Column<int>(type: "integer", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("route_pk", x => x.id);
                    table.ForeignKey(
                        name: "route_stop_id_fk",
                        column: x => x.first_stop_id,
                        principalTable: "stop",
                        principalColumn: "id");
                    table.ForeignKey(
                        name: "route_stop_id_fk2",
                        column: x => x.last_stop_id,
                        principalTable: "stop",
                        principalColumn: "id");
                });

            migrationBuilder.CreateTable(
                name: "vehicle_maintenance",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    vehicle_id = table.Column<int>(type: "integer", nullable: false),
                    description = table.Column<string>(type: "text", nullable: false),
                    time = table.Column<DateTime>(type: "timestamp with time zone", nullable: false, defaultValueSql: "now()"),
                    cost_total = table.Column<decimal>(type: "numeric(8,2)", precision: 8, scale: 2, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("vehicle_maintenance_pk", x => x.id);
                    table.ForeignKey(
                        name: "vehicle_maintenance_vehicle_id_fk",
                        column: x => x.vehicle_id,
                        principalTable: "vehicle",
                        principalColumn: "id");
                });

            migrationBuilder.CreateTable(
                name: "driver_route",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    driver_id = table.Column<int>(type: "integer", nullable: false),
                    vehicle_id = table.Column<int>(type: "integer", nullable: false),
                    route_id = table.Column<int>(type: "integer", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("driver_route_pk", x => x.id);
                    table.ForeignKey(
                        name: "driver_route_driver_id_fk",
                        column: x => x.driver_id,
                        principalTable: "driver",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "driver_route_route_id_fk",
                        column: x => x.route_id,
                        principalTable: "route",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "driver_route_vehicle_id_fk",
                        column: x => x.vehicle_id,
                        principalTable: "vehicle",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "route_stop",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    route_id = table.Column<int>(type: "integer", nullable: false),
                    stop_id = table.Column<int>(type: "integer", nullable: false),
                    ord_index = table.Column<int>(type: "integer", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("table_name_pk", x => x.id);
                    table.ForeignKey(
                        name: "table_name_route_id_fk",
                        column: x => x.route_id,
                        principalTable: "route",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "table_name_stop_id_fk",
                        column: x => x.stop_id,
                        principalTable: "stop",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "route_vehicle",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    route_id = table.Column<int>(type: "integer", nullable: false),
                    last_lat = table.Column<decimal>(type: "numeric(8,6)", precision: 8, scale: 6, nullable: true),
                    last_lon = table.Column<decimal>(type: "numeric(9,6)", precision: 9, scale: 6, nullable: true),
                    last_coords_time = table.Column<DateTime>(type: "timestamp with time zone", nullable: true),
                    next_stop = table.Column<int>(type: "integer", nullable: true),
                    vehicle_id = table.Column<int>(type: "integer", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("route_vehicle_pk", x => x.id);
                    table.ForeignKey(
                        name: "route_vehicle_route_id_fk",
                        column: x => x.route_id,
                        principalTable: "route",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "route_vehicle_stop_id_fk",
                        column: x => x.next_stop,
                        principalTable: "stop",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "route_vehicle_vahicle_id_fk",
                        column: x => x.vehicle_id,
                        principalTable: "vehicle",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "schedule",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    vehicle_id = table.Column<int>(type: "integer", nullable: false),
                    route_id = table.Column<int>(type: "integer", nullable: false),
                    stop_id = table.Column<int>(type: "integer", nullable: false),
                    departure_time = table.Column<DateTime>(type: "timestamp with time zone", nullable: false),
                    arrival_time = table.Column<DateTime>(type: "timestamp with time zone", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("timetable_pk", x => x.id);
                    table.ForeignKey(
                        name: "timetable_route_id_fk",
                        column: x => x.route_id,
                        principalTable: "route",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "timetable_stop_id_fk",
                        column: x => x.stop_id,
                        principalTable: "stop",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                    table.ForeignKey(
                        name: "timetable_vehicle_id_fk",
                        column: x => x.vehicle_id,
                        principalTable: "vehicle",
                        principalColumn: "id",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateTable(
                name: "ticket",
                columns: table => new
                {
                    id = table.Column<int>(type: "integer", nullable: false)
                        .Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
                    transaction_id = table.Column<string>(type: "character varying(64)", maxLength: 64, nullable: false),
                    fare = table.Column<decimal>(type: "numeric(8,2)", precision: 8, scale: 2, nullable: false),
                    time = table.Column<DateTime>(type: "timestamp with time zone", nullable: false),
                    route_id = table.Column<int>(type: "integer", nullable: false),
                    vehicle_id = table.Column<int>(type: "integer", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("ticket_pk", x => x.id);
                    table.ForeignKey(
                        name: "ticket_route_id_fk",
                        column: x => x.route_id,
                        principalTable: "route",
                        principalColumn: "id");
                    table.ForeignKey(
                        name: "ticket_vehicle_id_fk",
                        column: x => x.vehicle_id,
                        principalTable: "vehicle",
                        principalColumn: "id");
                });

            migrationBuilder.CreateIndex(
                name: "IX_driver_route_driver_id",
                table: "driver_route",
                column: "driver_id");

            migrationBuilder.CreateIndex(
                name: "IX_driver_route_route_id",
                table: "driver_route",
                column: "route_id");

            migrationBuilder.CreateIndex(
                name: "IX_driver_route_vehicle_id",
                table: "driver_route",
                column: "vehicle_id");

            migrationBuilder.CreateIndex(
                name: "IX_route_first_stop_id",
                table: "route",
                column: "first_stop_id");

            migrationBuilder.CreateIndex(
                name: "IX_route_last_stop_id",
                table: "route",
                column: "last_stop_id");

            migrationBuilder.CreateIndex(
                name: "IX_route_stop_stop_id",
                table: "route_stop",
                column: "stop_id");

            migrationBuilder.CreateIndex(
                name: "route_stop_route_id_ord_index_key",
                table: "route_stop",
                columns: new[] { "route_id", "ord_index" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "route_stop_route_id_stop_id_key",
                table: "route_stop",
                columns: new[] { "route_id", "stop_id" },
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_route_vehicle_next_stop",
                table: "route_vehicle",
                column: "next_stop");

            migrationBuilder.CreateIndex(
                name: "IX_route_vehicle_route_id",
                table: "route_vehicle",
                column: "route_id");

            migrationBuilder.CreateIndex(
                name: "IX_route_vehicle_vehicle_id",
                table: "route_vehicle",
                column: "vehicle_id");

            migrationBuilder.CreateIndex(
                name: "IX_schedule_route_id",
                table: "schedule",
                column: "route_id");

            migrationBuilder.CreateIndex(
                name: "IX_schedule_stop_id",
                table: "schedule",
                column: "stop_id");

            migrationBuilder.CreateIndex(
                name: "IX_schedule_vehicle_id",
                table: "schedule",
                column: "vehicle_id");

            migrationBuilder.CreateIndex(
                name: "IX_ticket_route_id",
                table: "ticket",
                column: "route_id");

            migrationBuilder.CreateIndex(
                name: "IX_ticket_vehicle_id",
                table: "ticket",
                column: "vehicle_id");

            migrationBuilder.CreateIndex(
                name: "IX_vehicle_maintenance_vehicle_id",
                table: "vehicle_maintenance",
                column: "vehicle_id");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "driver_route");

            migrationBuilder.DropTable(
                name: "feedback");

            migrationBuilder.DropTable(
                name: "route_stop");

            migrationBuilder.DropTable(
                name: "route_vehicle");

            migrationBuilder.DropTable(
                name: "schedule");

            migrationBuilder.DropTable(
                name: "ticket");

            migrationBuilder.DropTable(
                name: "vehicle_maintenance");

            migrationBuilder.DropTable(
                name: "driver");

            migrationBuilder.DropTable(
                name: "route");

            migrationBuilder.DropTable(
                name: "vehicle");

            migrationBuilder.DropTable(
                name: "stop");
        }
    }
}
