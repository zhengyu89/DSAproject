// Add these new includes at the top if not already present
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Forward declarations
class Student;
class Staff;
class Vehicle;
class Sticker;

// Add these enums for sorting options
enum class VehicleSortType {
    MODEL,
    COLOR,
    NAME
};

enum class StudentSortType {
    LAST_REGISTER,
    STATUS,
    NAME
};

// Student Node and List
class StudentNode {
public:
    Student* data;
    StudentNode* next;
    StudentNode* prev;
    StudentNode(Student* student) : data(student), next(nullptr), prev(nullptr) {}
};

class StudentList {
private:
    StudentNode* head;
    StudentNode* tail;
    int size;

public:
    StudentList() : head(nullptr), tail(nullptr), size(0) {}
    void insertAtEnd(Student* student);
    void remove(Student* student);
    Student* searchByMatric(string matricNum);
    Student* searchByMatric(string matricNum, StudentNode* current);
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    StudentNode* getHead() {return head;}
    void registerStudent(StudentList& studentList);
};

// Staff Node and List
class StaffNode {
public:
    Staff* data;
    StaffNode* next;
    StaffNode* prev;
    StaffNode(Staff* staff) : data(staff), next(nullptr), prev(nullptr) {}
};

class StaffList {
private:
    StaffNode* head;
    StaffNode* tail;
    int size;

public:
    StaffList() : head(nullptr), tail(nullptr), size(0) {}
    void insertAtEnd(Staff* staff);
    void remove(Staff* staff);
    Staff* searchById(string staffId);
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    void registerStaff(StaffList& staffList);
};

// Vehicle Node and List
class VehicleNode {
public:
    Vehicle* data;
    VehicleNode* next;
    VehicleNode* prev;
    VehicleNode(Vehicle* vehicle) : data(vehicle), next(nullptr), prev(nullptr) {}
};

class VehicleList {
private:
    VehicleNode* head;
    VehicleNode* tail;
    int size;

public:
    VehicleList() : head(nullptr), tail(nullptr), size(0) {}
    void insertAtEnd(Vehicle* vehicle);
    void remove(Vehicle* vehicle);
    Vehicle* searchByPlate(string plateNumber);
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    VehicleNode* getHead() {return head;}
};

// Add this to your forward declarations
class Status {
public:
    enum StatusType {
        PENDING,
        APPROVED,
        REJECTED
    };
    
    Status(string studentId, string vehicleId, StatusType status, string date)
        : studentMatricNumber(studentId), vehicleId(vehicleId), 
          currentStatus(status), applicationDate(date) {}

    string getStudentId() const { return studentMatricNumber; }
    string getVehicleId() const { return vehicleId; }
    StatusType getStatus() const { return currentStatus; }
    string getDate() const { return applicationDate; }

private:
    string studentMatricNumber;
    string vehicleId;
    StatusType currentStatus;
    string applicationDate;
};

// Stack for status
class StatusStack {
private:
    static const int MAX_SIZE = 50; // Maximum size of stack
    Status* arr[MAX_SIZE];
    int top;

public:
    StatusStack() : top(-1) {}
    
    bool push(Status* status) {
        if (top >= MAX_SIZE - 1) {
            cout << "Stack overflow - Cannot add more applications" << endl;
            return false;
        }
        arr[++top] = status;
        return true;
    }
    
    Status* pop() {
        if (isEmpty()) {
            return nullptr;
        }
        return arr[top--];
    }
    
    Status* stackTop() const {
        if (isEmpty()) {
            return nullptr;
        }
        return arr[top];
    }
    
    bool isEmpty() const {
        return top == -1;
    }
    
    int size() const {
        return top + 1;
    }
    
    // Function to get all statuses for display purposes
    void getAllStatuses(vector<Status*>& statuses) const {
        statuses.clear();
        for (int i = 0; i <= top; i++) {
            statuses.push_back(arr[i]);
        }
    }
};

class Student {
private:
    string studentMatricNumber;
    string student_name;
    string student_password;
    int yearOfStudy;
    VehicleList* vehicles;
    StatusStack applicationHistory;

public:
    Student(string matricNum, string name, string password, int year)
        : studentMatricNumber(matricNum), student_name(name),
          student_password(password), yearOfStudy(year) {
        vehicles = new VehicleList();
    }
          
    // Existing getters
    string getMatricNumber() const { return studentMatricNumber; }
    string getName() const { return student_name; }
    string getPassword() const { return student_password; }
    int getYearOfStudy() const { return yearOfStudy; }
    bool applySticker(Vehicle* vehicle, string applicationDate);
    bool initapplySticker(Vehicle* vehicle, string applicationDate);
    StatusStack& getApplicationHistory() { return applicationHistory; }
    void viewStatus();
    void updateInfo();
};

// Add these methods to the Staff class
class Staff {
private:
    string staffID;
    string staff_name;
    string staff_password;

    // Private helper methods for bubble sort
    void bubbleSortVehicles(vector<Vehicle*>& vehicles, VehicleSortType sortType);
    void bubbleSortStudents(vector<Student*>& students, StudentSortType sortType);

public:
    Staff(string id, string name, string password)
        : staffID(id), staff_name(name), staff_password(password) {}
        
    string getStaffID() const { return staffID; }
    string getName() const { return staff_name; }
    string getPassword() const { return staff_password; }

    // Methods
    void viewVehicleInfo(VehicleList* vehicleList, VehicleSortType sortType);
    void viewStudentInfo(StudentList* studentList, StudentSortType sortType);
    Student* searchStudent(StudentList* studentList, string searchTerm);
    void approveSticker(Student* student);
    void displayVehicleTable(vector<Vehicle*>& vehicles);
    void displayStudentTable(vector<Student*>& students);
};

class Vehicle {
private:
    string vehicleID;
    string carColor;
    string carModel;
    string plateNumber;
    Student* owner;

public:
    Vehicle(string id, string color, string model, string plate)
        : vehicleID(id), carColor(color), carModel(model), plateNumber(plate), owner(NULL) {}
        
    string getVehicleID() const { return vehicleID; }
    string getColor() const { return carColor; }
    string getModel() const { return carModel; }
    string getPlateNumber() const { return plateNumber; }
    Student* getowner() const{ return owner;}
    void setowner(Student* student){ owner=student;}
};

class Sticker {
private:
    string StickerID;
    string ValidDate;

public:
    Sticker(string id, string date) : StickerID(id), ValidDate(date) {}
    
    string getStickerID() const { return StickerID; }
    string getValidDate() const { return ValidDate; }
};

//FUNCTION DEFINITIONNNNN
// StudentList implementations
void StudentList::insertAtEnd(Student* student) {
    StudentNode* newNode = new StudentNode(student);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void StudentList::remove(Student* student) {
    StudentNode* current = head;
    while (current) {
        if (current->data == student) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            delete current;
            size--;
            return;
        }
        current = current->next;
    }
}

//Recursive Function
Student* StudentList::searchByMatric(string matricNum) {
    return searchByMatric(matricNum, head);  // Initial call with the head node
}

Student* StudentList::searchByMatric(string matricNum, StudentNode* current) {
    if (!current) {
        return nullptr;  // Base case: end of list
    }
    if (current->data->getMatricNumber() == matricNum) {
        return current->data;  // Found the student
    }
    return searchByMatric(matricNum, current->next);  // Recursive call
}

void StudentList::registerStudent(StudentList& studentList)
{
    string matricNum, name, password;
    int year;
    
    cout << "\n=== Student Registration ===" << endl;
    cout << "Enter Matric Number: ";
    cin >> matricNum;
    
    // Check if matric number already exists
    if (studentList.searchByMatric(matricNum) != NULL) {
        cout << "A student with this matric number already exists!" << endl;
        return;
    }
    
    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter Password: ";
    cin >> password;
    
    cout << "Enter Year of Study (1-4): ";
    cin >> year;
    
    // Validate year of study
    if (year < 1 || year > 4) {
        cout << "Invalid year of study! Must be between 1 and 4." << endl;
        return;
    }
    
    // Create new student and add to list
    Student* newStudent = new Student(matricNum, name, password, year);
    studentList.insertAtEnd(newStudent);
    cout << "Student registration successful!" << endl;
}

// StaffList implementations
void StaffList::insertAtEnd(Staff* staff) {
    StaffNode* newNode = new StaffNode(staff);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void StaffList::remove(Staff* staff) {
    StaffNode* current = head;
    while (current) {
        if (current->data == staff) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            delete current;
            size--;
            return;
        }
        current = current->next;
    }
}

Staff* StaffList::searchById(string staffId) {
    StaffNode* current = head;
    while (current) {
        if (current->data->getStaffID() == staffId) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void StaffList::registerStaff(StaffList& staffList) {
    string staffId, name, password;
    
    cout << "\n=== Staff Registration ===" << endl;
    cout << "Enter Staff ID: ";
    cin >> staffId;
    
    // Check if staff ID already exists
    if (staffList.searchById(staffId) != nullptr) {
        cout << "A staff member with this ID already exists!" << endl;
        return;
    }
    
    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter Password: ";
    cin >> password;
    
    // Create new staff and add to list
    Staff* newStaff = new Staff(staffId, name, password);
    staffList.insertAtEnd(newStaff);
    cout << "Staff registration successful!" << endl;
}

// VehicleList implementations
void VehicleList::insertAtEnd(Vehicle* vehicle) {
    VehicleNode* newNode = new VehicleNode(vehicle);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void VehicleList::remove(Vehicle* vehicle) {
    VehicleNode* current = head;
    while (current) {
        if (current->data == vehicle) {
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;
            delete current;
            size--;
            return;
        }
        current = current->next;
    }
}

Vehicle* VehicleList::searchByPlate(string plateNumber) {
    VehicleNode* current = head;
    while (current) {
        if (current->data->getPlateNumber() == plateNumber) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

bool Student::applySticker(Vehicle* vehicle, string applicationDate) {
    if (vehicles->getSize() >= 1) {
        cout << "You already have a registered vehicle. Only one vehicle allowed per student." << endl;
        return false;
    }

    Status* newApplication = new Status(
        studentMatricNumber,
        vehicle->getVehicleID(),
        Status::PENDING,
        applicationDate
    );

    if (!applicationHistory.push(newApplication)) {
        delete newApplication;
        return false;
    }

    vehicle->setowner(this);
    vehicles->insertAtEnd(vehicle);

    cout << "Sticker application submitted successfully for vehicle " 
         << vehicle->getPlateNumber() << endl;
    return true;
}

bool Student::initapplySticker(Vehicle* vehicle, string applicationDate) {
    Status* newApplication = new Status(
        studentMatricNumber,
        vehicle->getVehicleID(),
        Status::PENDING,
        applicationDate
    );

    if (!applicationHistory.push(newApplication)) {
        delete newApplication;
        return false;
    }

    vehicle->setowner(this);
    vehicles->insertAtEnd(vehicle);
    return true;
}

void Student::viewStatus() {
    if (applicationHistory.isEmpty()) {
        cout << "No application history found." << endl;
        return;
    }

    cout << "\nApplication History for " << student_name << ":" << endl;
    cout << "----------------------------------------" << endl;

    vector<Status*> statuses;
    applicationHistory.getAllStatuses(statuses);

    for (Status* status : statuses) {
        cout << "Date: " << status->getDate() << endl;
        cout << "Vehicle ID: " << status->getVehicleId() << endl;
        cout << "Status: ";
        switch (status->getStatus()) {
            case Status::PENDING:
                cout << "Pending Review";
                break;
            case Status::APPROVED:
                cout << "Approved";
                break;
            case Status::REJECTED:
                cout << "Rejected";
                break;
        }
        cout << "\n----------------------------------------" << endl;
    }
}

void Student::updateInfo() {
    string choice;
    cout << "\nUpdate Information for " << student_name << endl;
    cout << "1. Update Name" << endl;
    cout << "2. Update Password" << endl;
    cout << "3. Update Year of Study" << endl;
    cout << "Enter choice (1-3): ";
    cin >> choice;

    switch (choice[0]) {
        case '1': {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, student_name);
            cout << "Name updated successfully!" << endl;
            break;
        }
        case '2': {
            cout << "Enter new password: ";
            cin >> student_password;
            cout << "Password updated successfully!" << endl;
            break;
        }
        case '3': {
            cout << "Enter new year of study: ";
            cin >> yearOfStudy;
            cout << "Year of study updated successfully!" << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

// Bubble sort implementation for vehicles
void Staff::bubbleSortVehicles(vector<Vehicle*>& vehicles, VehicleSortType sortType) {
    int n = vehicles.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool shouldSwap = false;
            
            switch (sortType) {
                case VehicleSortType::MODEL:
                    shouldSwap = vehicles[j]->getModel() > vehicles[j + 1]->getModel();
                    break;
                case VehicleSortType::COLOR:
                    shouldSwap = vehicles[j]->getColor() > vehicles[j + 1]->getColor();
                    break;
                case VehicleSortType::NAME:
                    if(vehicles[j]->getowner() && vehicles[j+1]->getowner()){
                        shouldSwap = vehicles[j]->getowner()->getName() >vehicles[j+1]->getowner()->getName();
                    }
                    break;
            }
            
            if (shouldSwap) {
                Vehicle* temp = vehicles[j];
                vehicles[j] = vehicles[j + 1];
                vehicles[j + 1] = temp;
            }
        }
    }
}

// Bubble sort implementation for students
void Staff::bubbleSortStudents(vector<Student*>& students, StudentSortType sortType) {
    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool shouldSwap = false;
            
            switch (sortType) {
                case StudentSortType::NAME:
                    shouldSwap = students[j]->getName() > students[j + 1]->getName();
                    break;
                    
                case StudentSortType::LAST_REGISTER: {
                    bool hasApp1 = !students[j]->getApplicationHistory().isEmpty();
                    bool hasApp2 = !students[j + 1]->getApplicationHistory().isEmpty();
                    
                    if (!hasApp1 && hasApp2) shouldSwap = true;
                    else if (hasApp1 && hasApp2) {
                        shouldSwap = students[j]->getApplicationHistory().stackTop()->getDate() < 
                                   students[j + 1]->getApplicationHistory().stackTop()->getDate();
                    }
                    break;
                }
                
                case StudentSortType::STATUS: {
                    bool hasApp1 = !students[j]->getApplicationHistory().isEmpty();
                    bool hasApp2 = !students[j + 1]->getApplicationHistory().isEmpty();

                    if (!hasApp1 && hasApp2) {
                        shouldSwap = true;  // Students with no history are considered "lesser"
                    } else if (hasApp1 && hasApp2) {
                        // Compare the status of the last application in the history
                        Status::StatusType status1 = students[j]->getApplicationHistory().stackTop()->getStatus();
                        Status::StatusType status2 = students[j + 1]->getApplicationHistory().stackTop()->getStatus();
                        shouldSwap = status1 > status2;  // Adjust comparison for desired order
                    }
                    break;
                }
            }
            
            if (shouldSwap) {
                Student* temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Display methods remain the same
void Staff::displayVehicleTable(vector<Vehicle*>& vehicles) {
    cout << setfill('-') << setw(80) << "-" << endl;
    cout << setfill(' ');
    cout << left 
         << setw(15) << "Vehicle ID" 
         << setw(15) << "Plate Number" 
         << setw(20) << "Model" 
         << setw(15) << "Color" 
         << setw(15) << "Name" << endl;
    cout << setfill('-') << setw(80) << "-" << endl;
    cout << setfill(' ');

    for (const auto& vehicle : vehicles) {
        cout << left 
             << setw(15) << vehicle->getVehicleID()
             << setw(15) << vehicle->getPlateNumber()
             << setw(20) << vehicle->getModel()
             << setw(15) << vehicle->getColor()
             << setw(15) << vehicle->getowner()->getName() << endl;
    }
    cout << setfill('-') << setw(80) << "-" << endl;
}

void Staff::displayStudentTable(vector<Student*>& students) {
    cout << setfill('-') << setw(100) << "-" << endl;
    cout << setfill(' ');
    cout << left 
         << setw(15) << "Matric No"
         << setw(25) << "Name"
         << setw(15) << "Year"
         << setw(20) << "Last Register"
         << setw(25) << "Application Status" << endl;
    cout << setfill('-') << setw(100) << "-" << endl;
    cout << setfill(' ');

    for (const auto& student : students) {
        string status = "No Application";
        if (!student->getApplicationHistory().isEmpty()) {
            Status* lastStatus = student->getApplicationHistory().stackTop();
            switch (lastStatus->getStatus()) {
                case Status::PENDING: status = "Pending"; break;
                case Status::APPROVED: status = "Approved"; break;
                case Status::REJECTED: status = "Rejected"; break;
            }
        }

        cout << left 
             << setw(15) << student->getMatricNumber()
             << setw(25) << student->getName()
             << setw(15) << student->getYearOfStudy()
             << setw(20) << (student->getApplicationHistory().isEmpty() ? "N/A" : 
                            student->getApplicationHistory().stackTop()->getDate())
             << setw(25) << status << endl;
    }
    cout << setfill('-') << setw(100) << "-" << endl;
}

void Staff::viewVehicleInfo(VehicleList* vehicleList, VehicleSortType sortType) {
    vector<Vehicle*> vehicles;
    VehicleNode* current = vehicleList->getHead();
    while (current) {
        vehicles.push_back(current->data);
        current = current->next;
    }

    bubbleSortVehicles(vehicles, sortType);
    displayVehicleTable(vehicles);
}

void Staff::viewStudentInfo(StudentList* studentList, StudentSortType sortType) {
    vector<Student*> students;
    StudentNode* current = studentList->getHead();
    while (current) {
        students.push_back(current->data);
        current = current->next;
    }

    bubbleSortStudents(students, sortType);
    displayStudentTable(students);
}

Student* Staff::searchStudent(StudentList* studentList, string searchTerm) {
    Student* result = studentList->searchByMatric(searchTerm);
    if (result) {
        cout << "\nStudent found:" << endl;
        vector<Student*> studentToDisplay = {result};
        displayStudentTable(studentToDisplay);
    } else {
        cout << "Student not found." << endl;
    }
    return result;
}

void Staff::approveSticker(Student* student) {
    if (!student->getApplicationHistory().isEmpty()) {
        Status* currentStatus = student->getApplicationHistory().stackTop();
        if (currentStatus->getStatus() == Status::PENDING) {
            Status* newStatus = new Status(
                student->getMatricNumber(),
                currentStatus->getVehicleId(),
                Status::APPROVED,
                currentStatus->getDate()
            );
            student->getApplicationHistory().push(newStatus);
            cout << "Sticker application approved for student " 
                 << student->getMatricNumber() << endl;
        } else {
            cout << "No pending application found for this student." << endl;
        }
    } else {
        cout << "No applications found for this student." << endl;
    }
}


int main() {
    // Create lists to store data
    StudentList studentList;
    StaffList staffList;
    VehicleList vehicleList;

    // Create sample data
    // Sample students
    Student* student1 = new Student("A23CS5016", "John Doe", "stu123", 2);
    Student* student2 = new Student("A23CS5017", "Jane Smith", "pass456", 3);
    Student* student3 = new Student("A23CS5018", "Alice Brown", "alice789", 2);
    Student* student4 = new Student("A23CS5019", "Bob White", "bob2023", 4);
    Student* student5 = new Student("A23CS5020", "Charlie Green", "charlie007", 2);
    Student* student6 = new Student("A23CS5021", "Diana Prince", "diana456", 3);
    Student* student7 = new Student("A23CS5022", "Edward Black", "edward123", 4);
    Student* student8 = new Student("A23CS5023", "Fiona Hill", "fiona789", 2);
    Student* student9 = new Student("A23CS5024", "George King", "george2023", 2);
    Student* student10 = new Student("A23CS5025", "Hannah Taylor", "hannah456", 3);

    studentList.insertAtEnd(student1);
    studentList.insertAtEnd(student2);
    studentList.insertAtEnd(student3);
    studentList.insertAtEnd(student4);
    studentList.insertAtEnd(student5);
    studentList.insertAtEnd(student6);
    studentList.insertAtEnd(student7);
    studentList.insertAtEnd(student8);
    studentList.insertAtEnd(student9);
    studentList.insertAtEnd(student10);

    // Sample staff
    Staff* staff1 = new Staff("ST001", "Admin User", "admin123");
    Staff* staff2 = new Staff("ST002", "Manager 1", "manager123");
    Staff* staff3 = new Staff("ST003", "Supervisor A", "superA456");
    Staff* staff4 = new Staff("ST004", "HR Officer", "hr789");
    Staff* staff5 = new Staff("ST005", "IT Support", "itpass2023");
    Staff* staff6 = new Staff("ST006", "Finance Lead", "finance007");
    Staff* staff7 = new Staff("ST007", "Research Assistant", "research123");
    Staff* staff8 = new Staff("ST008", "Lab Technician", "labtech456");
    Staff* staff9 = new Staff("ST009", "Registrar", "regpass2023");
    Staff* staff10 = new Staff("ST010", "Dean Office", "dean1234");

    staffList.insertAtEnd(staff1);
    staffList.insertAtEnd(staff2);
    staffList.insertAtEnd(staff3);
    staffList.insertAtEnd(staff4);
    staffList.insertAtEnd(staff5);
    staffList.insertAtEnd(staff6);
    staffList.insertAtEnd(staff7);
    staffList.insertAtEnd(staff8);
    staffList.insertAtEnd(staff9);
    staffList.insertAtEnd(staff10);

    // Sample vehicles
    Vehicle* vehicle1 = new Vehicle("V001", "Red", "Toyota Corolla", "ABC123");
    Vehicle* vehicle2 = new Vehicle("V002", "Blue", "Honda Civic", "XYZ789");
    Vehicle* vehicle3 = new Vehicle("V003", "Black", "Ford Mustang", "MUS456");
    Vehicle* vehicle4 = new Vehicle("V004", "White", "Tesla Model 3", "TESLA99");
    Vehicle* vehicle5 = new Vehicle("V005", "Gray", "Chevrolet Malibu", "CHEV123");

    vehicleList.insertAtEnd(vehicle1);
    vehicleList.insertAtEnd(vehicle2);
    vehicleList.insertAtEnd(vehicle3);
    vehicleList.insertAtEnd(vehicle4);
    vehicleList.insertAtEnd(vehicle5);

    // Add sample applications
    student1->initapplySticker(vehicle1, "2025-01-10");
    student2->initapplySticker(vehicle2, "2025-01-15");
    student5->initapplySticker(vehicle3, "2025-02-01");
    student8->initapplySticker(vehicle4, "2025-02-05");
    student10->initapplySticker(vehicle5, "2025-02-10");


    while (true) {
        cout << "\n=== Parking Sticker Management System ===" << endl;
        cout << "1. Student Login" << endl;
        cout << "2. Staff Login" << endl;
        cout << "3. Register" <<endl;
        cout << "4. Exit" << endl;
        cout << "Choose option: ";
        
        string choice;
        cin >> choice;

        if (choice == "1") {
            // Student Login
            string matricNum, password;
            cout << "Enter Matric Number: ";
            cin >> matricNum;
            cout << "Enter Password: ";
            cin >> password;

            Student* currentStudent = studentList.searchByMatric(matricNum);
            if (currentStudent && currentStudent->getPassword() == password) {
                cout << "Login successful!" << endl;
                
                // Student Menu Loop
                while (true) {
                    cout << "\nStudent Menu - Welcome " << currentStudent->getName() << endl;
                    cout << "1. Apply for Parking Sticker" << endl;
                    cout << "2. View Application Status" << endl;
                    cout << "3. Update Personal Information" << endl;
                    cout << "4. Logout" << endl;
                    cout << "Choose option: ";

                    string studentChoice;
                    cin >> studentChoice;

                    if (studentChoice == "1") {
                        // Apply for sticker
                        string plateNum, color, model;
                        cout << "Enter Vehicle Details:" << endl;
                        cout << "Plate Number: ";
                        cin >> plateNum;
                        cout << "Color: ";
                        cin >> color;
                        cout << "Model: ";
                        cin.ignore();
                        getline(cin, model);

                        Vehicle* newVehicle = new Vehicle("V" + to_string(vehicleList.getSize() + 1),
                                                        color, model, plateNum);
                        vehicleList.insertAtEnd(newVehicle);
                        currentStudent->applySticker(newVehicle, "2025-01-15");
                    }
                    else if (studentChoice == "2") {
                        currentStudent->viewStatus();
                    }
                    else if (studentChoice == "3") {
                        currentStudent->updateInfo();
                    }
                    else if (studentChoice == "4") {
                        cout << "Logging out..." << endl;
                        break;
                    }
                    else {
                        cout << "Invalid choice!" << endl;
                    }
                }
            }
            else {
                cout << "Invalid credentials!" << endl;
            }
        }
        else if (choice == "2") {
            // Staff Login
            string staffId, password;
            cout << "Enter Staff ID: ";
            cin >> staffId;
            cout << "Enter Password: ";
            cin >> password;

            Staff* currentStaff = staffList.searchById(staffId);
            if (currentStaff && currentStaff->getPassword() == password) {
                cout << "Staff login successful!" << endl;
                
                // Staff Menu Loop
                while (true) {
                    cout << "\nStaff Menu - Welcome " << currentStaff->getName() << endl;
                    cout << "1. View Vehicle Information" << endl;
                    cout << "2. View Student Information" << endl;
                    cout << "3. Search Student" << endl;
                    cout << "4. Approve Sticker" << endl;
                    cout << "5. Logout" << endl;
                    cout << "Choose option: ";

                    string staffChoice;
                    cin >> staffChoice;

                    if (staffChoice == "1") {
                        cout << "\nSort by:" << endl;
                        cout << "1. Model" << endl;
                        cout << "2. Color" << endl;
                        cout << "3. Driver ID" << endl;
                        cout << "Choose sorting method: ";
                        string sortChoice;
                        cin >> sortChoice;
                        
                        VehicleSortType sortType;
                        if (sortChoice == "1") sortType = VehicleSortType::MODEL;
                        else if (sortChoice == "2") sortType = VehicleSortType::COLOR;
                        else sortType = VehicleSortType::NAME;
                        currentStaff->viewVehicleInfo(&vehicleList, sortType);
                    }
                    else if (staffChoice == "2") {
                        cout << "\nSort by:" << endl;
                        cout << "1. Last Register" << endl;
                        cout << "2. Status" << endl;
                        cout << "3. Name" << endl;
                        cout << "Choose sorting method: ";
                        string sortChoice;
                        cin >> sortChoice;
                        
                        StudentSortType sortType;
                        if (sortChoice == "1") sortType = StudentSortType::LAST_REGISTER;
                        else if (sortChoice == "2") sortType = StudentSortType::STATUS;
                        else sortType = StudentSortType::NAME;
                        
                        currentStaff->viewStudentInfo(&studentList, sortType);
                    }
                    else if (staffChoice == "3") {
                        cout << "Enter student matric number: ";
                        string searchTerm;
                        cin >> searchTerm;
                        currentStaff->searchStudent(&studentList, searchTerm);
                    }
                    else if (staffChoice == "4") {
                        cout << "Enter student matric number: ";
                        string matricNum;
                        cin >> matricNum;
                        Student* student = studentList.searchByMatric(matricNum);
                        if (student) {
                            currentStaff->approveSticker(student);
                        }
                        else {
                            cout << "Student not found." << endl;
                        }
                    }
                    else if (staffChoice == "5") {
                        cout << "Logging out..." << endl;
                        break;
                    }
                    else {
                        cout << "Invalid choice!" << endl;
                    }
                }
            }
            else {
                cout << "Invalid staff credentials!" << endl;
            }
        }
        else if (choice == "3") {
            cout << "\n=== Registration ===" << endl;
            cout << "1. Student Registration" << endl;
            cout << "2. Staff Registration" << endl;
            cout << "Enter choice: ";
            
            string regChoice;
            cin >> regChoice;
            
            if (regChoice == "1") {
                studentList.registerStudent(studentList);
            }
            else if (regChoice == "2") {
                staffList.registerStaff(staffList);
            }
            else {
                cout << "Invalid choice!" << endl;
            }
        }
        else if (choice == "4") {
            cout << "Thank you for using the Parking Sticker Management System!" << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    // Cleanup memory
    delete student1;
    delete student2;
    delete staff1;
    delete vehicle1;
    delete vehicle2;

    return 0;
}