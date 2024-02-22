```shell
dotnet add package Microsoft.EntityFrameworkCore.Design
dotnet add package Npgsql.EntityFrameworkCore.PostgreSQL
dotnet ef dbcontext scaffold "Host=192.168.1.9;Port=5432;Database=my;Username=user;Password=password;" Npgsql.EntityFrameworkCore.PostgreSQL -o Models
```
```shell
dotnet ef migrations add MyMigration
dotnet ef database drop
dotnet ef database update MyMigration
```
