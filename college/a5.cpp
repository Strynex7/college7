#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Student {
protected:
    string name;
    mutable double grade;
public:
    explicit Student(string n, double g): name(n), grade(g) {}
    virtual void display() const = 0;
    virtual string getType() const = 0;
    virtual string serialize() const = 0;
    virtual ~Student() {}
    string getName() const { return name; }
    double getGrade() const { return grade; }
    void setGrade(double g) const { grade = g; }
    void setName(const string& n) { name = n; }

    virtual Student& operator+(const Student& s) {
        grade = (grade + s.grade) / 2;
        return *this;
    }
    virtual bool operator>(const Student& s) const {
        return grade > s.grade;
    }
};

class UndergraduateStudent : public Student {
public:
    UndergraduateStudent(string n, double g): Student(n,g) {}
    void display() const override {
        cout << "Undergraduate - Name: " << name << ", Grade: " << grade << endl;
    }
    string getType() const override { return "Undergraduate"; }
    string serialize() const override {
        return "Undergraduate," + name + "," + to_string(grade);
    }
};

class GraduateStudent : public Student {
public:
    GraduateStudent(string n, double g): Student(n,g) {}
    void display() const override {
        cout << "Graduate - Name: " << name << ", Grade: " << grade << endl;
    }
    string getType() const override { return "Graduate"; }
    string serialize() const override {
        return "Graduate," + name + "," + to_string(grade);
    }
};

class StudentManager {
    vector<Student*> students;
    string dbFile = "student_db.txt";

public:
    void load() {
        students.clear();
        ifstream fin(dbFile);
        if (!fin) return;
        string type, name;
        double grade;
        while (getline(fin, type, ',')) {
            getline(fin, name, ',');
            fin >> grade;
            fin.ignore();
            if (type == "Undergraduate")
                students.push_back(new UndergraduateStudent(name, grade));
            else
                students.push_back(new GraduateStudent(name, grade));
        }
        fin.close();
    }

    void save() {
        ofstream fout(dbFile);
        for (auto s : students)
            fout << s->serialize() << endl;
        fout.close();
    }

    void create() {
        string type, name;
        double grade;
        cout << "\n1. Undergraduate\n2. Graduate\nChoose student type: ";
        int choice; cin >> choice;
        type = (choice == 1) ? "Undergraduate" : "Graduate";

        cout << "Enter Name: ";
        cin >> ws; getline(cin, name);
        cout << "Enter Grade: ";
        cin >> grade;

        if (type == "Undergraduate")
            students.push_back(new UndergraduateStudent(name, grade));
        else
            students.push_back(new GraduateStudent(name, grade));

        save();
        cout << "✅ Student added successfully.\n";
    }

    void read() const {
        if (students.empty()) {
            cout << "\nNo student records found.\n";
            return;
        }
        cout << "\n------ Student List ------\n";
        for (auto s : students) s->display();
        cout << "---------------------------\n";
    }

    void update() {
        string name;
        cout << "Enter student name to update: ";
        cin >> ws; getline(cin, name);
        for (auto s : students) {
            if (s->getName() == name) {
                double g;
                cout << "Enter new grade: ";
                cin >> g;
                s->setGrade(g);
                save();
                cout << "✅ Grade updated successfully.\n";
                return;
            }
        }
        cout << "⚠️ Student not found.\n";
    }

    void remove() {
        string name;
        cout << "Enter name to delete: ";
        cin >> ws; getline(cin, name);
        auto it = remove_if(students.begin(), students.end(),
            [&](Student* s){ return s->getName() == name; });
        if (it != students.end()) {
            for (auto i = it; i != students.end(); ++i) delete *i;
            students.erase(it, students.end());
            save();
            cout << "✅ Student deleted successfully.\n";
        } else {
            cout << "⚠️ Student not found.\n";
        }
    }

    ~StudentManager() {
        for (auto s : students) delete s;
    }
};

int main() {
    StudentManager sm;
    sm.load();
    int choice;

    while (true) {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Student";
        cout << "\n2. Read All Students";
        cout << "\n3. Update Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) sm.create();
        else if (choice == 2) sm.read();
        else if (choice == 3) sm.update();
        else if (choice == 4) sm.remove();
        else if (choice == 5) {
            cout << "\nExiting... Data saved to database.\n";
            break;
        }
        else cout << "Invalid choice. Try again.\n";
    }

    return 0;
}
