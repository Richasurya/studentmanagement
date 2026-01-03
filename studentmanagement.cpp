#include <iostream>
#include <vector>
using namespace std;

class Student {
public:
    int roll;
    string name;
    int marks;
};

vector<Student> students;

void addStudent() {
    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.roll;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Marks: ";
    cin >> s.marks;

    students.push_back(s);
    cout << "Student Added Successfully!\n";
}

void viewStudents() {
    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }

    for (auto s : students) {
        cout << "Roll: " << s.roll
             << ", Name: " << s.name
             << ", Marks: " << s.marks << endl;
    }
}

void searchStudent() {
    int roll;
    cout << "Enter Roll Number to search: ";
    cin >> roll;

    for (auto s : students) {
        if (s.roll == roll) {
            cout << "Student Found!\n";
            cout << "Name: " << s.name << ", Marks: " << s.marks << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
