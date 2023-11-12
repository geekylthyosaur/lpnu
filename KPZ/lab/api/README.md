```shell
dotnet add package Microsoft.EntityFrameworkCore.Design
```
```shell
dotnet add package Npgsql.EntityFrameworkCore.PostgreSQL
```
```shell
dotnet ef dbcontext scaffold "Host=192.168.1.9;Port=5432;Database=my;Username=user;Password=password;" Npgsql.EntityFrameworkCore.PostgreSQL -o Models
```
