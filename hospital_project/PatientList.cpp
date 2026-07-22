#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include "PatientList.h"

using namespace std;

PatientList::PatientList()
{
    root = nullptr;
}

Patient *PatientList::insert(Patient *r, int id, const char *name, int age)
{
    if (!r)
    {
        Patient *p = new Patient{id, "", age, nullptr, nullptr};
        strcpy(p->name, name);
        return p;
    }

    if (id < r->id)
        r->left = insert(r->left, id, name, age);
    else
        r->right = insert(r->right, id, name, age);

    return r;
}

Patient *PatientList::search(Patient *r, int id) const
{
    if (!r || r->id == id)
        return r;

    if (id < r->id)
        return search(r->left, id);

    return search(r->right, id);
}

bool PatientList::exists(int id) const
{
    return search(root, id) != nullptr;
}

void PatientList::addPatient()
{
    int id, age;
    char name[50];

    cout << "Patient ID: ";
    cin >> id;
    cout << "Patient Name: ";
    cin >> name;
    cout << "Patient Age: ";
    cin >> age;

    if (exists(id))
    {
        cout << "Patient already exists.\n";
        return;
    }

    root = insert(root, id, name, age);
    saveToCSV();

    cout << "Patient added.\n";
}

void PatientList::inorder(Patient *r) const
{
    if (!r)
        return;
    inorder(r->left);
    cout << r->id << " " << r->name << " " << r->age << endl;
    inorder(r->right);
}

void PatientList::displayPatients() const
{
    inorder(root);
}

Patient *PatientList::searchPatient(int id) const
{
    return search(root, id);
}

void PatientList::saveToCSV(Patient *r, ofstream &file) const
{
    if (!r)
        return;
    saveToCSV(r->left, file);
    file << r->id << "," << r->name << "," << r->age << endl;
    saveToCSV(r->right, file);
}

void PatientList::saveToCSV() const
{
    ofstream file("patients.csv");
    if (!file.is_open())
    {
        cout << "Error opening file!\n";
        return;
    }
    file << "ID,Name,Age\n"; // header
    saveToCSV(root, file);
    cout << "Patients saved to patients.csv\n";
}

void PatientList::loadFromCSV()
{
    ifstream file("patients.csv");
    if (!file.is_open())
    {

        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line))
    {
        if (line.empty())
            continue; // skip empty lines

        stringstream ss(line);
        string idStr, name, ageStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');

        if (idStr.empty() || ageStr.empty())
            continue; // skip invalid lines

        int id = stoi(idStr);
        int age = stoi(ageStr);

        // Remove quotes if present
        if (!name.empty() && name[0] == '"')
            name = name.substr(1);
        if (!name.empty() && name.back() == '"')
            name = name.substr(0, name.size() - 1);

        root = insert(root, id, name.c_str(), age);
    }
}
