#include <iostream>
#include <cstring>
#include "DoctorList.h"

using namespace std;

DoctorList::DoctorList()
{
    root = nullptr;
}

Doctor *DoctorList::insert(Doctor *r, int id,
                           const char *name,
                           const char *spec)
{
    if (!r)
    {
        Doctor *d = new Doctor{id, "", "", nullptr, nullptr};
        strcpy(d->name, name);
        strcpy(d->specialization, spec);
        return d;
    }

    if (id < r->id)
        r->left = insert(r->left, id, name, spec);
    else
        r->right = insert(r->right, id, name, spec);

    return r;
}

Doctor *DoctorList::search(Doctor *r, int id) const
{
    if (!r || r->id == id)
        return r;

    if (id < r->id)
        return search(r->left, id);

    return search(r->right, id);
}

bool DoctorList::exists(int id) const
{
    return search(root, id) != nullptr;
}

void DoctorList::addDoctor()
{
    int id;
    char name[50], spec[50];

    cout << "Doctor ID: ";
    cin >> id;
    cin.ignore(); // clear newline from input buffer

    cout << "Doctor Name: ";
    cin.getline(name, 50);

    cout << "Doctor Specialization: ";
    cin.getline(spec, 50);

    if (exists(id))
    {
        cout << "Doctor already exists.\n";
        return;
    }

    root = insert(root, id, name, spec);
    cout << "Doctor added.\n";
}

void DoctorList::inorder(Doctor *r) const
{
    if (!r)
        return;
    inorder(r->left);
    cout << r->id << " " << r->name
         << " (" << r->specialization << ")\n";
    inorder(r->right);
}

void DoctorList::displayDoctors() const
{
    inorder(root);
}
