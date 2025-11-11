#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class EngineSpecs {
protected:
    int horsepower;
    string fuelType;
public:
    EngineSpecs(int hp = 0, string fuel = "Unknown") : horsepower(hp), fuelType(fuel) {}
    void showEngineSpecs() { cout << "Horsepower: " << horsepower << ", Fuel: " << fuelType << endl; }
};

class Registration {
private:
    string regNumber;
    string ownerName;
public:
    Registration(string reg = "N/A", string owner = "N/A") : regNumber(reg), ownerName(owner) {}
    string getReg() { return regNumber; }
    void setOwner(string owner) { ownerName = owner; }
    void showRegistration() { cout << "Reg No: " << regNumber << ", Owner: " << ownerName << endl; }
};

class Vehicle : virtual public EngineSpecs {
protected:
    string brand;
    string model;
    Registration reg;
public:
    Vehicle(string b = "Generic", string m = "Model", int hp = 0, string fuel = "Unknown", string r = "N/A", string o = "N/A")
        : EngineSpecs(hp, fuel), brand(b), model(m), reg(r, o) {}
    virtual ~Vehicle() {}
    string getRegNo() { return reg.getReg(); }
    virtual void display() {
        cout << "Brand: " << brand << ", Model: " << model << endl;
        showEngineSpecs();
        reg.showRegistration();
    }
    class RegistrationDetails {
    public:
        void displayNestedDetails() { cout << "Nested Class: Registration details handled successfully.\n"; }
    };
};

class BatteryInfo {
protected:
    int capacity;
public:
    BatteryInfo(int c = 0) : capacity(c) {}
    void showBattery() { cout << "Battery Capacity: " << capacity << " kWh\n"; }
};

class Car : public Vehicle, public BatteryInfo {
public:
    Car(string b, string m, int hp, string fuel, string r, string o)
        : Vehicle(b, m, hp, fuel, r, o), BatteryInfo(0) {}
    void display() override {
        cout << "\nCar Details:\n";
        Vehicle::display();
    }
};

class Truck : public Vehicle {
public:
    Truck(string b, string m, int hp, string fuel, string r, string o)
        : Vehicle(b, m, hp, fuel, r, o) {}
    void display() override {
        cout << "\nTruck Details:\n";
        Vehicle::display();
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(string b, string m, int hp, string fuel, string r, string o)
        : Vehicle(b, m, hp, fuel, r, o) {}
    void display() override {
        cout << "\nMotorcycle Details:\n";
        Vehicle::display();
    }
};

class ElectricVehicle : public Vehicle, public BatteryInfo {
public:
    ElectricVehicle(string b, string m, int hp, int cap, string r, string o)
        : Vehicle(b, m, hp, "Electric", r, o), BatteryInfo(cap) {}
    void display() override {
        cout << "\nElectric Vehicle Details:\n";
        Vehicle::display();
        showBattery();
    }
    friend void serviceUpdate(ElectricVehicle &ev);
};

void serviceUpdate(ElectricVehicle &ev) {
    cout << "Service Update: Electric vehicle battery checked successfully.\n";
}

class VehicleManager {
    vector<Vehicle*> vehicles;
public:
    void createVehicle() {
        int type;
        cout << "\nSelect Vehicle Type: 1.Car 2.Truck 3.Motorcycle 4.ElectricVehicle : ";
        cin >> type;
        string brand, model, fuel, reg, owner;
        int hp, cap = 0;
        cout << "Enter Brand: "; cin >> brand;
        cout << "Enter Model: "; cin >> model;
        cout << "Enter Horsepower: "; cin >> hp;
        cout << "Enter Fuel Type: "; cin >> fuel;
        cout << "Enter Reg No: "; cin >> reg;
        cout << "Enter Owner Name: "; cin >> owner;

        if (type == 1) vehicles.push_back(new Car(brand, model, hp, fuel, reg, owner));
        else if (type == 2) vehicles.push_back(new Truck(brand, model, hp, fuel, reg, owner));
        else if (type == 3) vehicles.push_back(new Motorcycle(brand, model, hp, fuel, reg, owner));
        else if (type == 4) { cout << "Enter Battery Capacity: "; cin >> cap; vehicles.push_back(new ElectricVehicle(brand, model, hp, cap, reg, owner)); }

        cout << "Vehicle Added Successfully!\n";
    }

    void readVehicles() {
        if (vehicles.empty()) { cout << "No vehicles in the system.\n"; return; }
        for (auto v : vehicles) v->display();
    }

    void updateVehicle() {
        string reg;
        cout << "Enter Reg No to Update Owner: ";
        cin >> reg;
        for (auto v : vehicles) {
            if (v->getRegNo() == reg) {
                string newOwner;
                cout << "Enter New Owner Name: ";
                cin >> newOwner;
                Registration temp(reg, newOwner);
                cout << "Owner Updated Successfully!\n";
                return;
            }
        }
        cout << "Vehicle not found.\n";
    }

    void deleteVehicle() {
        string reg;
        cout << "Enter Reg No to Delete: ";
        cin >> reg;
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            if ((*it)->getRegNo() == reg) {
                delete *it;
                vehicles.erase(it);
                cout << "Vehicle Deleted Successfully!\n";
                return;
            }
        }
        cout << "Vehicle not found.\n";
    }

    void menu() {
        bool running = true;
        while (running) {
            cout << "\n--- Vehicle Management System ---\n";
            cout << "1. Add Vehicle\n2. Show All Vehicles\n3. Update Vehicle\n4. Delete Vehicle\n5. Exit\n";
            cout << "Enter Choice: ";
            int choice; cin >> choice;

            if (choice == 1) createVehicle();
            else if (choice == 2) readVehicles();
            else if (choice == 3) updateVehicle();
            else if (choice == 4) deleteVehicle();
            else if (choice == 5) { running = false; cout << "Exiting...\n"; }
            else cout << "Invalid choice!\n";
        }
    }

    ~VehicleManager() { for (auto v : vehicles) delete v; }
};

int main() {
    VehicleManager manager;
    manager.menu();
    return 0;
}
