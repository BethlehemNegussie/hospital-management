#ifndef PATIENTLIST_H
#define PATIENTLIST_H

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// Patient node for BST
struct Patient
{
    int id;
    char name[50];
    int age;
    Patient *left;
    Patient *right;
};

class PatientList
{
private:
    Patient *root;

    Patient *insert(Patient *r, int id, const char *name, int age);
    Patient *search(Patient *r, int id) const;
    void inorder(Patient *r) const;
    void saveToCSV(Patient *r, ofstream &file) const;

public:
    PatientList();

    void addPatient();
    bool exists(int id) const;
    void displayPatients() const;
    Patient *searchPatient(int id) const;
    void saveToCSV() const;
    void loadFromCSV();
};

#endif
