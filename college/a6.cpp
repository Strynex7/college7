#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string name;
    int roll;
    int age;

    cout << "Enter Student Name: ";
    getline(cin, name);
    cout << "Enter Roll Number: ";
    cin >> roll;
    cout << "Enter Age: ";
    cin >> age;

    ofstream fout("student.txt");
    if (!fout) {
        cerr << "Error opening file for writing.\n";
        return 1;
    }

    fout << "Name: " << name << endl;
    fout << "Roll Number: " << roll << endl;
    fout << "Age: " << age << endl;
    fout.close();

    cout << "\nData written successfully to 'student.txt'\n";

    ifstream fin("student.txt");
    if (!fin) {
        cerr << "Error opening file for reading.\n";
        return 1;
    }

    cout << "\nReading Data from File:\n";
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();

    return 0;
}
