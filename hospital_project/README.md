# Hospital Management System

A console-based hospital management system written in C++ that allows managing patients, doctors, and appointments.

## Features

- Add and manage patients
- Add and manage doctors
- Book appointments
- Cancel appointments
- Display doctor schedules
- Display all patients
- Search for patients
- Display patient appointments
- Reschedule appointments

## Prerequisites

- C++ compiler (e.g., g++, MinGW on Windows)
- Windows/Linux/macOS
- PowerShell (for the automated build script on Windows)

## Building the Project

1. Ensure you have a C++ compiler installed.
2. Navigate to the project directory.
3. Compile the source files:

   ```
   g++ Appointment.cpp DoctorList.cpp main.cpp PatientList.cpp -o hospital.exe
   ```

   (Replace `hospital.exe` with `hospital` on Linux/macOS)

## Running the Application

After building, run the executable:

```
./hospital.exe
```

On Windows:

```
hospital.exe

```

## Usage

The application presents a menu with the following options:

1. Add Patient
2. Add Doctor
3. Book Appointment
4. Cancel Appointment
5. Display Doctor Schedule
6. Display All Patients
7. Search Patient
8. Display Patient Appointments
9. Reschedule Appointment
10. Exit

Follow the on-screen prompts to interact with the system.

## File Structure

- `main.cpp`: Main entry point and menu handling
- `PatientList.h` / `PatientList.cpp`: Patient management
- `DoctorList.h` / `DoctorList.cpp`: Doctor management
- `Appointment.h` / `Appointment.cpp`: Appointment management
- `patients.csv`: Patient data storage
- `README.md`: Project documentation
- `group_members.txt`: List of group members

## Data Persistence

Patient data is loaded from and saved to `patients.csv` on startup and exit.

## Contributing

Feel free to contribute by submitting pull requests or issues.
