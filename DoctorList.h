#ifndef DOCTORLIST_H
#define DOCTORLIST_H

#include <iostream>
#include <cstring>
using namespace std;

// Doctor node for BST
struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    Doctor* left;
    Doctor* right;
};

class DoctorList {
private:
    Doctor* root;

    Doctor* insert(Doctor* r, int id, const char* name, const char* spec);
    Doctor* search(Doctor* r, int id) const;
    void inorder(Doctor* r) const;

public:
    DoctorList();

    void addDoctor();
    bool exists(int id) const;
    void displayDoctors() const;
};

#endif
