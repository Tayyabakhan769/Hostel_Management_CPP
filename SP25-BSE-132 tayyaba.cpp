#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
//Constants
const int HOSTELS = 3;
const int ROOMS = 5;
const int SLOTS = 2;
//structures
struct Student {
    string name;
    int rollNo;
    string department;
    float cgpa;
    bool isScholarship;
};
//storage
Student* hostel[HOSTELS][ROOMS][SLOTS] = {nullptr};
//check if roll no already exists
bool rollExists(int roll) {
    for (int h = 0; h < HOSTELS; h++) {
        for (int r = 0; r < ROOMS; r++) {
            for (int s = 0; s < SLOTS; s++) {
                if (hostel[h][r][s] != nullptr && hostel[h][r][s]->rollNo == roll) {
                    return true;
                }
            }
        }
    }
    return false;
}
//adding new student
void addStudent() {
    Student* s = new Student;
    cout << "\n===============================================";
    cout << "\n*************** ADD NEW STUDENT ***************\n";
    cout << "===============================================\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s->name);
    cout << "===============================================\n";
    cout << "Enter Roll No: ";
    cin >> s->rollNo;
    cout << "===============================================\n";
    if (rollExists(s->rollNo)) {
        cout << "\n*** Error: Roll No already exists. Please try again ***\n";
        delete s;
        return;
    }
    cout << "Enter Department: ";
    cin.ignore();
    getline(cin, s->department);
    cout << "===============================================\n";
    cout << "Enter CGPA: ";
    cin >> s->cgpa;
    cout << "===============================================\n";
    if (s->cgpa < 2.0) {
        cout << "\n*** Sorry to say but, CGPA too low. Admission not allowed. ***\n";
        delete s;
        return;
    }
    cout << "Scholarship? (press 1 for Yes, press 0 for No): ";
    cin >> s->isScholarship;
    cout << "===============================================\n";
    bool placed = false;
    for (int h = 0; h < HOSTELS && !placed; h++) {
        for (int r = 0; r < ROOMS && !placed; r++) {
            if (s->isScholarship && r >= 3) break;
            for (int sl = 0; sl < SLOTS; sl++) {
                if (hostel[h][r][sl] == nullptr) {
                    hostel[h][r][sl] = s;
                    cout << "\n*** Student placed in Hostel " << h+1 
                         << " | Room " << r+1 
                         << " | Slot " << sl+1 << " ***\n";
                    placed = true;
                    break;
                }
            }
        }
    }
    if (!placed) {
        cout << "\n*** No space available for the student. ***\n";
        delete s;
    }
}
//room status
void showRooms() {
    cout << "\n*************** ROOM STATUS ***************\n";
    for (int h = 0; h < HOSTELS; h++) {
        cout << "\n============= HOSTEL " << h+1 << " =============\n";
        for (int r = 0; r < ROOMS; r++) {
            int count = 0;
            for (int s = 0; s < SLOTS; s++) {
                if (hostel[h][r][s] != nullptr)
                    count++;
            }
            cout << "\nRoom " << r+1 << ": ";
            if (count == 0) cout << "Empty";
            else if (count == 2) cout << "Full";
            else cout << "Partially Filled";
            cout << "\n-----------------------------------------------\n";
            for (int s = 0; s < SLOTS; s++) {
                if (hostel[h][r][s] != nullptr) {
                    Student* st = hostel[h][r][s];
                    cout << "  * " << st->name
                         << " | Roll No: " << st->rollNo
                         << " | Dept: " << st->department
                         << " | CGPA: " << st->cgpa
                         << " | Scholarship: " << (st->isScholarship ? "Yes" : "No") << "\n";
                }
            }
        }
    }
}
//searching by roll no
void searchStudent() {
    int roll;
    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;
    for (int h = 0; h < HOSTELS; h++) {
        for (int r = 0; r < ROOMS; r++) {
            for (int s = 0; s < SLOTS; s++) {
                Student* st = hostel[h][r][s];
                if (st != nullptr && st->rollNo == roll) {
                    cout << "\n*************** STUDENT FOUND ***************\n";
                    cout << "Name        : " << st->name << "\n";
                    cout << "Roll No     : " << st->rollNo << "\n";
                    cout << "Department  : " << st->department << "\n";
                    cout << "CGPA        : " << st->cgpa << "\n";
                    cout << "Scholarship : " << (st->isScholarship ? "Yes" : "No") << "\n";
                    cout << "Hostel      : " << h+1 << "\n";
                    cout << "Room        : " << r+1 << "\n";
                    cout << "Slot        : " << s+1 << "\n";
                    return;
                }
            }
        }
    }
    cout << "\n*** Student with roll number " << roll << " not found. ***\n";
}
//transfer student
void transferStudent() {
    int roll;
    cout << "\nEnter Roll Number to Transfer: ";
    cin >> roll;
    for (int h = 0; h < HOSTELS; h++) {
        for (int r = 0; r < ROOMS; r++) {
            for (int s = 0; s < SLOTS; s++) {
                Student* st = hostel[h][r][s];
                if (st != nullptr && st->rollNo == roll) {
                    for (int nh = 0; nh < HOSTELS; nh++) {
                        for (int nr = 0; nr < ROOMS; nr++) {
                            if (st->isScholarship && nr >= 3) continue;
                            for (int ns = 0; ns < SLOTS; ns++) {
                                if (hostel[nh][nr][ns] == nullptr) {
                                    hostel[nh][nr][ns] = st;
                                    hostel[h][r][s] = nullptr;
                                    cout << "\n*** Student transferred to Hostel " << nh+1 
                                         << " | Room " << nr+1 
                                         << " | Slot " << ns+1 << " ***\n";
                                    return;
                                }
                            }
                        }
                    }
                    cout << "\n*** No space available to transfer. ***\n";
                    return;
                }
            }
        }
    }
    cout << "\n*** Student not found. ***\n";
}
//academic summary
void showSummary() {
    int total = 0;
    float totalCGPA = 0;
    int scholarshipCount = 0;
    int cgpaAbove3Hostel[HOSTELS] = {0};
    for (int h = 0; h < HOSTELS; h++) {
        for (int r = 0; r < ROOMS; r++) {
            for (int s = 0; s < SLOTS; s++) {
                if (hostel[h][r][s] != nullptr) {
                    Student* st = hostel[h][r][s];
                    total++;
                    totalCGPA += st->cgpa;
                    if (st->isScholarship)
                        scholarshipCount++;
                    if (st->cgpa > 3.0)
                        cgpaAbove3Hostel[h]++;
                }
            }
        }
    }
    cout << "\n*************** ACADEMIC SUMMARY ***************\n";
    cout << "* Total Students       : " << total << "\n";
    cout << "===============================================\n";
    cout << "* Average CGPA         : " << (total > 0 ? totalCGPA / total : 0.0) << "\n";
    cout << "===============================================\n";
    cout << "* Scholarship Holders  : " << scholarshipCount << "\n";
    cout << "===============================================\n";
    for (int h = 0; h < HOSTELS; h++) {
        cout << "* Hostel " << h+1 << " - CGPA > 3.0 Students : " << cgpaAbove3Hostel[h] << "\n";
    }
    cout << "************************************************\n";
}
//menu
int main() {
    int choice;
    do {
        cout << "\n******************************************\n";
        cout << "*        HOSTEL MANAGEMENT MENU         *\n";
        cout << "******************************************\n";
        cout << "* 1. Add Student                        *\n";
        cout << "* 2. Show Room Status                   *\n";
        cout << "* 3. Show Academic Summary              *\n";
        cout << "* 4. Search Student                     *\n";
        cout << "* 5. Transfer Student                   *\n";
        cout << "* 6. Exit                               *\n";
        cout << "******************************************\n";
        cout << "Select Option: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                showRooms();
                break;
            case 3:
                showSummary();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                transferStudent();
                break;
            case 6:
                cout << "\n===============================================\n";
                cout << "Exiting Program. Goodbye!\n";
                cout << "===============================================\n";
                break;
            default:
                cout << "\n===============================================\n";
                cout << "*** Invalid option. Try again. ***\n";
                cout << "===============================================\n";
        }
    } while (choice != 6);
    return 0;
}
