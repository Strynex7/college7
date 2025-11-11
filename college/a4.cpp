#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

class Employee {
protected:
    string name;
    int id;
public:
    Employee(string n, int i): name(n), id(i) {}
    virtual void display() const = 0;
    virtual string getType() const = 0;
    virtual string serialize() const = 0;
    virtual ~Employee() {}
    int getId() const { return id; }
    void setName(const string& n) { name = n; }
};

class FullTimeEmployee : public Employee {
    double salary;
public:
    FullTimeEmployee(string n, int i, double s): Employee(n,i), salary(s) {}
    void display() const override {
        cout << "FullTimeEmployee - Name: " << name << ", ID: " << id << ", Salary: " << salary << endl;
    }
    string getType() const override { return "FullTime"; }
    string serialize() const override {
        return "FullTime," + name + "," + to_string(id) + "," + to_string(salary);
    }
};

class PartTimeEmployee : public Employee {
    double hourlyRate;
public:
    PartTimeEmployee(string n, int i, double r): Employee(n,i), hourlyRate(r) {}
    void display() const override {
        cout << "PartTimeEmployee - Name: " << name << ", ID: " << id << ", HourlyRate: " << hourlyRate << endl;
    }
    string getType() const override { return "PartTime"; }
    string serialize() const override {
        return "PartTime," + name + "," + to_string(id) + "," + to_string(hourlyRate);
    }
};

class Intern : public Employee {
    string university;
public:
    Intern(string n, int i, string u): Employee(n,i), university(u) {}
    void display() const override {
        cout << "Intern - Name: " << name << ", ID: " << id << ", University: " << university << endl;
    }
    string getType() const override { return "Intern"; }
    string serialize() const override {
        return "Intern," + name + "," + to_string(id) + "," + university;
    }
};

class EmployeeManager {
    vector<shared_ptr<Employee>> employees;
    string dbFile = "employee_db.txt";

public:
    void load() {
        employees.clear();
        ifstream fin(dbFile);
        if (!fin) return;
        string type, name, extra;
        int id;
        while (getline(fin, type, ',')) {
            getline(fin, name, ',');
            fin >> id;
            fin.ignore();
            if (type == "FullTime") {
                double s; fin >> s;
                employees.push_back(make_shared<FullTimeEmployee>(name, id, s));
            } else if (type == "PartTime") {
                double r; fin >> r;
                employees.push_back(make_shared<PartTimeEmployee>(name, id, r));
            } else if (type == "Intern") {
                string uni; getline(fin, uni);
                employees.push_back(make_shared<Intern>(name, id, uni));
            }
            fin.ignore();
        }
        fin.close();
    }

    void save() {
        ofstream fout(dbFile);
        for (auto &e : employees)
            fout << e->serialize() << endl;
        fout.close();
    }

    void create() {
        string name, type;
        int id;
        cout << "Enter Employee Type (FullTime/PartTime/Intern): ";
        cin >> type;
        cout << "Enter Name: ";
        cin >> ws; getline(cin, name);
        cout << "Enter ID: ";
        cin >> id;

        if (type == "FullTime") {
            double s;
            cout << "Enter Salary: "; cin >> s;
            employees.push_back(make_shared<FullTimeEmployee>(name, id, s));
        } else if (type == "PartTime") {
            double r;
            cout << "Enter Hourly Rate: "; cin >> r;
            employees.push_back(make_shared<PartTimeEmployee>(name, id, r));
        } else {
            string u;
            cout << "Enter University: "; cin >> ws; getline(cin, u);
            employees.push_back(make_shared<Intern>(name, id, u));
        }
        save();
    }

    void read() const {
        for (auto &e : employees) e->display();
    }

    void update() {
        int id; cout << "Enter ID to update: "; cin >> id;
        for (auto &e : employees) {
            if (e->getId() == id) {
                string newName;
                cout << "Enter new name: ";
                cin >> ws; getline(cin, newName);
                e->setName(newName);
                save();
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void remove() {
        int id; cout << "Enter ID to delete: "; cin >> id;
        employees.erase(remove_if(employees.begin(), employees.end(),
            [id](shared_ptr<Employee> &e){ return e->getId() == id; }), employees.end());
        save();
    }
};

int main() {
    EmployeeManager m;
    m.load();
    string action;
    while (true) {
        cout << "\nEnter action (create/read/update/delete/exit): ";
        cin >> action;
        if (action == "create") m.create();
        else if (action == "read") m.read();
        else if (action == "update") m.update();
        else if (action == "delete") m.remove();
        else if (action == "exit") break;
        else cout << "Invalid command.\n";
    }
    return 0;
}
