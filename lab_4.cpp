#include <iostream>
#include <string>

using namespace std;

class Vehicle {
private:
    string brand;
public:
    Vehicle(string br = "Unknown") : brand(br) {
        cout << "Vehicle constructor called" << endl;
    }
    ~Vehicle() {
        cout << "Vehicle destructor called" << endl;
    }
    void display() const {
        cout << "Brand: " << brand << endl;
    }
};

class Car : public Vehicle {
private:
    string licensePlate;
    string model;
public:
    static int carCount;

    Car() : Vehicle(), licensePlate("Unknown"), model("Unknown") {
        carCount++;
    }
    Car(string lp, string mdl, string br = "Unknown") : Vehicle(br), licensePlate(lp), model(mdl) {
        carCount++;
    }

    Car(const Car& other) : Vehicle(other), licensePlate(other.licensePlate), model(other.model) {
        carCount++;
        cout << "Copy constructor called" << endl;
    }

    Car(Car&& other) noexcept : Vehicle(other), licensePlate(move(other.licensePlate)), model(move(other.model)) {
        cout << "Move constructor called" << endl;
    }

    ~Car() {
        carCount--;
    }

    void display() const {
        Vehicle::display();
        cout << "Car: " << model << " [" << licensePlate << "]" << endl;
    }

    Car& setLicensePlate(string lp) {
        this->licensePlate = lp;
        return *this;
    }

    bool operator==(const Car& other) const {
        return (licensePlate == other.licensePlate) && (model == other.model);
    }

    Car& operator=(const Car& other) {
        if (this != &other) {
            Vehicle::operator=(other);
            licensePlate = other.licensePlate;
            model = other.model;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Car& car) {
        os << "Car: " << car.model << " [" << car.licensePlate << "]";
        return os;
    }

    friend istream& operator>>(istream& is, Car& car) {
        cout << "Enter model: ";
        is.ignore();
        getline(is, car.model);
        cout << "Enter license plate: ";
        is >> car.licensePlate;
        return is;
    }
};

int Car::carCount = 0;

class ElectricCar : public Car {
private:
    int batteryCapacity;
public:
    ElectricCar(string lp, string mdl, string br, int capacity) : Car(lp, mdl, br), batteryCapacity(capacity) {
        cout << "ElectricCar constructor called" << endl;
    }

    ElectricCar(const ElectricCar& other) : Car(other), batteryCapacity(other.batteryCapacity) {
        cout << "ElectricCar Copy constructor called" << endl;
    }

    ElectricCar(ElectricCar&& other) noexcept : Car(move(other)), batteryCapacity(other.batteryCapacity) {
        cout << "ElectricCar Move constructor called" << endl;
    }

    ElectricCar& operator=(const ElectricCar& other) {
        if (this != &other) {
            Car::operator=(other);
            batteryCapacity = other.batteryCapacity;
        }
        return *this;
    }

    ElectricCar& operator=(ElectricCar&& other) noexcept {
        if (this != &other) {
            Car::operator=(move(other));
            batteryCapacity = other.batteryCapacity;
        }
        return *this;
    }

    void display() const {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

class ParkingLot {
private:
    int capacity;
    int occupied;
    static int totalLots;
public:
    ParkingLot() : ParkingLot(50, 0) {}
    ParkingLot(int cap, int occ) : capacity(cap), occupied(occ) {
        totalLots++;
    }
    ~ParkingLot() {}

    bool parkCar() {
        if (occupied < capacity) {
            occupied++;
            return true;
        }
        return false;
    }

    void display() const {
        cout << "Parking Lot: " << occupied << "/" << capacity << " occupied." << endl;
    }

    static int getTotalLots() {
        return totalLots;
    }
};

int ParkingLot::totalLots = 0;

class Ticket {
private:
    int ticketNumber;
    double price;
public:
    Ticket() : Ticket(0, 10.0) {}
    Ticket(int num, double p) : ticketNumber(num), price(p) {}
    ~Ticket() {}
    void display() const {
        cout << "Ticket #" << ticketNumber << " | Price: $" << price << endl;
    }
};

class PremiumTicket : public Ticket {
private:
    double discount;
public:
    PremiumTicket(int num, double p, double d) : Ticket(num, p), discount(d) {}
    void display() const {
        Ticket::display();
        cout << "Discount: " << discount << "%" << endl;
    }
};

class Garage {
private:
    Car storedCar;
public:
    Garage(const Car& c) : storedCar(c) {}
    void display() const {
        cout << "Garage contains: ";
        storedCar.display();
    }
};

int main() {
    Car car1("AB1234CD", "Toyota", "Toyota");
    Car car2;
    cin >> car2;
    cout << car2 << endl;

    ElectricCar eCar("EV5678GH", "Tesla Model S", "Tesla", 100);

    ParkingLot lot(100, 20);
    Ticket ticket1(101, 10.0);
    PremiumTicket pTicket(102, 15.0, 10.0);

    car1.display();
    eCar.display();
    lot.display();
    ticket1.display();
    pTicket.display();

    Car car3 = car1;
    Car car4 = move(car2);

    if (car1 == car2) {
        cout << "Cars are the same!" << endl;
    } else {
        cout << "Cars are different!" << endl;
    }

    Garage myGarage(car1);
    myGarage.display();

    cout << "Total lots: " << ParkingLot::getTotalLots() << endl;
    cout << "Total cars: " << Car::carCount << endl;

    return 0;
}
