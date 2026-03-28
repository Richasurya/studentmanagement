#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class Student {
private:
    int id;
    string name;
    float marks;

public:
    Student() {}

    Student(int i, string n, float m) {
        id = i;
        name = n;
        marks = m;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    float getMarks() const { return marks; }

    void update() {
        cout << "Enter new name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter new marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "ID: " << id 
             << " | Name: " << name 
             << " | Marks: " << marks << endl;
    }

    string serialize() const {
        return to_string(id) + "," + name + "," + to_string(marks);
    }

    static Student deserialize(string line) {
        int pos1 = line.find(',');
        int pos2 = line.rfind(',');

        int id = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        float marks = stof(line.substr(pos2 + 1));

        return Student(id, name, marks);
    }
};

vector<Student> students;

// Load from file
void loadData() {
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        students.push_back(Student::deserialize(line));
    }
    file.close();
}

// Save to file
void saveData() {
    ofstream file("students.txt");

    for (auto &s : students) {
        file << s.serialize() << endl;
    }
    file.close();
}

// Add student
void addStudent() {
    int id;
    string name;
    float marks;

    cout << "Enter ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Marks: ";
    cin >> marks;

    students.push_back(Student(id, name, marks));
    saveData();

    cout << "✅ Student Added\n";
}

// Display all
void displayStudents() {
    cout << "\n--- Student List ---\n";
    for (auto &s : students) {
        s.display();
    }
}

// Search
void searchStudent() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    for (auto &s : students) {
        if (s.getId() == id) {
            s.display();
            return;
        }
    }

    cout << "❌ Not Found\n";
}

// Delete
void deleteStudent() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    auto it = remove_if(students.begin(), students.end(),
        [id](Student &s) { return s.getId() == id; });

    if (it != students.end()) {
        students.erase(it, students.end());
        saveData();
        cout << "✅ Deleted\n";
    } else {
        cout << "❌ Not Found\n";
    }
}

// Update
void updateStudent() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    for (auto &s : students) {
        if (s.getId() == id) {
            s.update();
            saveData();
            cout << "✅ Updated\n";
            return;
        }
    }

    cout << "❌ Not Found\n";
}

// Sort by marks
void sortStudents() {
    sort(students.begin(), students.end(),
         [](Student a, Student b) {
             return a.getMarks() > b.getMarks();
         });

    cout << "✅ Sorted by Marks (Descending)\n";
    displayStudents();
}

// Main menu
int main() {
    loadData();

    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add\n2. Display\n3. Search\n4. Delete\n5. Update\n6. Sort by Marks\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: sortStudents(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid\n";
        }

    } while (choice != 7);

    return 0;
}

