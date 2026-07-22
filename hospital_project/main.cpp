#include <iostream>
#include "PatientList.h"
#include "DoctorList.h"
#include "Appointment.h"

using namespace std;

// Global managers
PatientList patients;
DoctorList doctors;
AppointmentQueue appointments;

// Pause function to wait for user input
void pause()
{
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}

// Show main menu
void showMenu()
{
    cout << "\n========== HOSPITAL MANAGEMENT SYSTEM ==========\n";
    cout << "1. Add Patient\n";
    cout << "2. Add Doctor\n";
    cout << "3. Book Appointment\n";
    cout << "4. Cancel Appointment\n";
    cout << "5. Display Doctor Schedule\n";
    cout << "6. Display All Patients\n";
    cout << "7. Search Patient\n";
    cout << "8. Display Patient Appointments\n";
    cout << "9. Reschedule Appointment\n";
    cout << "10. Undo Last Cancellation\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main()
{
    patients.loadFromCSV();

    int choice;

    do
    {
        showMenu();

        if (!(cin >> choice))
        {
            cin.clear();            // clear error
            cin.ignore(1000, '\n'); // discard bad input
            cout << "Invalid input. Try again.\n";
            continue;
        }

        cin.ignore(); // clear newline

        switch (choice)
        {
        case 1:
            patients.addPatient();
            pause();
            break;

        case 2:
            doctors.addDoctor();
            pause();
            break;

        case 3:
            appointments.bookAppointment(patients, doctors);
            pause();
            break;

        case 4:
            appointments.cancelAppointment();
            pause();
            break;

        case 5:
            appointments.displayByDoctor();
            pause();
            break;

        case 6:
            patients.displayPatients();
            pause();
            break;

        case 7:
        {
            int id;
            cout << "Enter Patient ID: ";
            cin >> id;
            Patient *p = patients.searchPatient(id);
            if (p)
            {
                cout << "Patient found: ID=" << p->id << ", Name=" << p->name << ", Age=" << p->age << endl;
            }
            else
            {
                cout << "Patient not found.\n";
            }
            pause();
            break;
        }

        case 8:
            appointments.displayByPatient();
            pause();
            break;

        case 9:
            appointments.rescheduleAppointment();
            pause();
            break;
        case 10:
            appointments.undoLastBooking();
            pause();
            break;

        case 0:
            cout << "Exiting system...\n";
            break;

        default:
            cout << "Invalid option. Try again.\n";
            pause();
        }

    } while (choice != 0);

    // Save data to CSV before exiting
    patients.saveToCSV();

    return 0;
}
