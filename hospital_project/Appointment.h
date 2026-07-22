#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "PatientList.h"
#include "DoctorList.h"

// Appointment node
struct Appointment
{
    int appointmentId;
    int patientId;
    int doctorId;
    int day;  // simple integer day
    int hour; // 0–23
    bool emergency;

    Appointment *next;
};

// Stack node for undo
struct UndoNode
{
    Appointment data;
    UndoNode *next;
};

class AppointmentQueue
{
private:
    Appointment *front;
    Appointment *rear;

    UndoNode *undoTop;
    int nextId;

    bool hasOverlap(int doctorId, int day, int hour);

public:
    AppointmentQueue();

    void bookAppointment(PatientList &patients, DoctorList &doctors);
    void cancelAppointment();
    void rescheduleAppointment();

    void displayByDoctor();
    void displayByPatient();

    void undoLastBooking();
};

#endif
