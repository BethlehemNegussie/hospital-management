#include <iostream>
#include "Appointment.h"
#include "PatientList.h"
#include "DoctorList.h"

using namespace std;

AppointmentQueue::AppointmentQueue()
{
    front = rear = nullptr;
    undoTop = nullptr;
    nextId = 1;
}

bool AppointmentQueue::hasOverlap(int doctorId, int day, int hour)
{
    Appointment *curr = front;
    while (curr)
    {
        if (curr->doctorId == doctorId &&
            curr->day == day &&
            curr->hour == hour)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void AppointmentQueue::bookAppointment(PatientList &patients,
                                       DoctorList &doctors)
{
    int pid, did, day, hour, emer;

    cout << "Patient ID: ";
    cin >> pid;

    cout << "Doctor ID: ";
    cin >> did;

    if (!patients.exists(pid))
    {
        cout << "Error: Patient does not exist.\n";
        return;
    }

    if (!doctors.exists(did))
    {
        cout << "Error: Doctor does not exist.\n";
        return;
    }

    cout << "Day: ";
    cin >> day;

    cout << "Hour (0–23): ";
    cin >> hour;

    cout << "Emergency? (1=yes, 0=no): ";
    cin >> emer;

    if (hasOverlap(did, day, hour))
    {
        cout << "Error: Doctor already booked at that time.\n";
        return;
    }

    Appointment *node = new Appointment;
    node->appointmentId = nextId++;
    node->patientId = pid;
    node->doctorId = did;
    node->day = day;
    node->hour = hour;
    node->emergency = emer;
    node->next = nullptr;

    if (!front)
    {
        front = rear = node;
    }
    else if (emer)
    {
        node->next = front;
        front = node;
    }
    else
    {
        rear->next = node;
        rear = node;
    }

    cout << "Appointment booked.\n";
}

void AppointmentQueue::cancelAppointment()
{
    int id;
    cout << "Appointment ID to cancel: ";
    cin >> id;

    if (!front)
    {
        cout << "No appointments to cancel.\n";
        return;
    }

    Appointment *curr = front;
    Appointment *prev = nullptr;

    while (curr && curr->appointmentId != id)
    {
        prev = curr;
        curr = curr->next;
    }

    if (!curr)
    {
        cout << "Appointment not found.\n";
        return;
    }

    UndoNode *undo = new UndoNode;
    undo->data = *curr;
    undo->next = undoTop;
    undoTop = undo;

    if (prev)
    {
        prev->next = curr->next;
        if (curr == rear)
            rear = prev;
    }
    else
    {
        front = curr->next;
        if (!front)
            rear = nullptr;
    }

    delete curr;
    cout << "Appointment cancelled.\n";
}

void AppointmentQueue::rescheduleAppointment()
{
    int id;
    cout << "Appointment ID to reschedule: ";
    cin >> id;

    Appointment *curr = front;
    while (curr && curr->appointmentId != id)
        curr = curr->next;

    if (!curr)
    {
        cout << "Appointment not found.\n";
        return;
    }

    int newDay, newHour;
    cout << "New Day: ";
    cin >> newDay;
    cout << "New Hour (0–23): ";
    cin >> newHour;

    Appointment *temp = front;
    bool overlap = false;
    while (temp)
    {
        if (temp != curr && temp->doctorId == curr->doctorId &&
            temp->day == newDay && temp->hour == newHour)
        {
            overlap = true;
            break;
        }
        temp = temp->next;
    }

    if (overlap)
    {
        cout << "Error: Doctor already booked at that time.\n";
        return;
    }

    curr->day = newDay;
    curr->hour = newHour;
    cout << "Appointment rescheduled.\n";
}

void AppointmentQueue::undoLastBooking()
{
    if (!undoTop)
    {
        cout << "No actions to undo.\n";
        return;
    }

    Appointment *restored = new Appointment;
    *restored = undoTop->data;
    restored->next = nullptr;

    if (!rear)
    {
        front = rear = restored;
    }
    else
    {
        rear->next = restored;
        rear = restored;
    }

    UndoNode *temp = undoTop;
    undoTop = undoTop->next;
    delete temp;

    cout << "Last cancellation undone.\n";
}

void AppointmentQueue::displayByDoctor()
{
    int did;
    cout << "Doctor ID: ";
    cin >> did;

    cout << "Appointments for Doctor " << did << ":\n";
    Appointment *curr = front;
    bool found = false;
    while (curr)
    {
        if (curr->doctorId == did)
        {
            cout << "ID: " << curr->appointmentId << ", Patient: " << curr->patientId
                 << ", Day: " << curr->day << ", Hour: " << curr->hour
                 << ", Emergency: " << (curr->emergency ? "Yes" : "No") << endl;
            found = true;
        }
        curr = curr->next;
    }
    if (!found)
        cout << "No appointments found.\n";
}

void AppointmentQueue::displayByPatient()
{
    int pid;
    cout << "Patient ID: ";
    cin >> pid;

    cout << "Appointments for Patient " << pid << ":\n";
    Appointment *curr = front;
    bool found = false;
    while (curr)
    {
        if (curr->patientId == pid)
        {
            cout << "ID: " << curr->appointmentId << ", Doctor: " << curr->doctorId
                 << ", Day: " << curr->day << ", Hour: " << curr->hour
                 << ", Emergency: " << (curr->emergency ? "Yes" : "No") << endl;
            found = true;
        }
        curr = curr->next;
    }
    if (!found)
        cout << "No appointments found.\n";
}
