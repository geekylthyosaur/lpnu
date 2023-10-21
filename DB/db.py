import psycopg2
import os

# Database connection parameters
db_params = {
    "user": "user",
    "password": "password",
    "host": "localhost",
    "port": "5432",
}

# Database name to be created or dropped
db_name = "my"

# Connect to the PostgreSQL server (the default database)
try:
    conn = psycopg2.connect(**db_params)
    conn.autocommit = True
    cursor = conn.cursor()
except psycopg2.Error as e:
    print(f"Error connecting to PostgreSQL: {e}")
    exit(1)

# Drop the database if it exists
try:
    cursor.execute(f"DROP DATABASE IF EXISTS {db_name}")
    print(f"Database '{db_name}' dropped successfully (if it existed).")
except psycopg2.Error as e:
    print(f"Error dropping database '{db_name}' (if it existed): {e}")

# Close the connection to the default database
cursor.close()
conn.close()

# Connect to the PostgreSQL server again
try:
    conn = psycopg2.connect(**db_params)
    conn.autocommit = True
    cursor = conn.cursor()
except psycopg2.Error as e:
    print(f"Error connecting to PostgreSQL: {e}")
    exit(1)

# Create the database
try:
    cursor.execute(f"CREATE DATABASE {db_name}")
    print(f"Database '{db_name}' created successfully.")
except psycopg2.Error as e:
    print(f"Error creating database '{db_name}': {e}")

# Close the connection to the default database
cursor.close()
conn.close()

# Connect to the new database
db_params["dbname"] = db_name
conn = psycopg2.connect(**db_params)
cursor = conn.cursor()

# List of SQL files in the desired execution order
sql_files_in_order = [
    "stop.sql",
    "vehicle.sql",
    "driver.sql",
    "route.sql",
    "route_stop.sql",
    "ticket.sql",
    "driver_route.sql",
    "feedback.sql",
    "route_vehicle.sql",
    "schedule.sql",
    "vehicle_maintenance.sql",
]

# Directory containing SQL files
sql_directory = "./sql"

# Execute SQL files in the specified order
for filename in sql_files_in_order:
    file_path = os.path.join(sql_directory, filename)
    with open(file_path, "r") as sql_file:
        sql_script = sql_file.read()
        try:
            cursor.execute(sql_script)
            conn.commit()
            print(f"Executed SQL script from {filename}")
        except psycopg2.Error as e:
            print(f"Error executing SQL script from {filename}: {e}")

# Close the cursor and the database connection
cursor.close()
conn.close()
