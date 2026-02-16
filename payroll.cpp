#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class Employee
{
public:
    int id;
    string name;
    string department;
    double basicSalary;

    Employee() {}

    Employee(int id, string name, string dept, double salary)
    {
        this->id = id;
        this->name = name;
        this->department = dept;
        this->basicSalary = salary;
    }
};

class PayrollSystem
{
private:
    vector<Employee> employees;
    const string fileName = "employees.csv";

public:
    // Load employees from file
    void loadFromFile()
    {
        employees.clear();
        ifstream file(fileName);
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string temp;
            Employee e;

            getline(ss, temp, ',');
            e.id = stoi(temp);

            getline(ss, e.name, ',');
            getline(ss, e.department, ',');

            getline(ss, temp, ',');
            e.basicSalary = stod(temp);

            employees.push_back(e);
        }
        file.close();
    }

    // Save employees to file
    void saveToFile()
    {
        ofstream file(fileName);
        for (auto &e : employees)
        {
            file << e.id << ","
                 << e.name << ","
                 << e.department << ","
                 << e.basicSalary << endl;
        }
        file.close();
    }

    // Add employee
    void addEmployee()
    {
        int id;
        string name, dept;
        double salary;

        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Department: ";
        getline(cin, dept);

        cout << "Enter Basic Salary: ";
        cin >> salary;

        employees.push_back(Employee(id, name, dept, salary));
        saveToFile();
        cout << "Employee added successfully.\n";
    }

    // Find employee index by ID
    int findEmployeeIndex(int id)
    {
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i].id == id)
                return i;
        }
        return -1;
    }

    // Update employee
    void updateEmployee()
    {
        int id;
        cout << "Enter Employee ID to update: ";
        cin >> id;

        int index = findEmployeeIndex(id);
        if (index == -1)
        {
            cout << "Employee not found.\n";
            return;
        }

        cin.ignore();
        cout << "Enter new name: ";
        getline(cin, employees[index].name);

        cout << "Enter new department: ";
        getline(cin, employees[index].department);

        cout << "Enter new salary: ";
        cin >> employees[index].basicSalary;

        saveToFile();
        cout << "Employee updated successfully.\n";
    }

    // Delete employee
    void deleteEmployee()
    {
        int id;
        cout << "Enter Employee ID to delete: ";
        cin >> id;

        int index = findEmployeeIndex(id);
        if (index == -1)
        {
            cout << "Employee not found.\n";
            return;
        }

        employees.erase(employees.begin() + index);
        saveToFile();
        cout << "Employee deleted successfully.\n";
    }

    // Display all employees
    void displayEmployees()
    {
        cout << "\nEmployee List\n";
        cout << left << setw(5) << "ID"
             << setw(15) << "Name"
             << setw(15) << "Department"
             << setw(10) << "Salary" << endl;

        for (auto &e : employees)
        {
            cout << left << setw(5) << e.id
                 << setw(15) << e.name
                 << setw(15) << e.department
                 << setw(10) << e.basicSalary << endl;
        }
    }

    // Salary calculation
    double calculateNetSalary(double basic)
    {
        double bonus = basic * 0.10;
        double tax = basic * 0.05;
        return basic + bonus - tax;
    }

    // Generate payslip
    void generatePayslip()
    {
        int id;
        cout << "Enter Employee ID: ";
        cin >> id;

        int index = findEmployeeIndex(id);
        if (index == -1)
        {
            cout << "Employee not found.\n";
            return;
        }

        Employee e = employees[index];
        double netSalary = calculateNetSalary(e.basicSalary);

        string file = "payslip_" + to_string(e.id) + ".txt";
        ofstream out(file);

        out << "------ PAYSLIP ------\n";
        out << "ID: " << e.id << endl;
        out << "Name: " << e.name << endl;
        out << "Department: " << e.department << endl;
        out << "Basic Salary: " << e.basicSalary << endl;
        out << "Bonus (10%): " << e.basicSalary * 0.10 << endl;
        out << "Tax (5%): " << e.basicSalary * 0.05 << endl;
        out << "Net Salary: " << netSalary << endl;

        out.close();
        cout << "Payslip generated: " << file << endl;
    }

    // Payroll report
    void payrollReport()
    {
        double total = 0;
        for (auto &e : employees)
        {
            total += calculateNetSalary(e.basicSalary);
        }
        cout << "Total Payroll Expense: " << total << endl;
    }
};

int main()
{
    PayrollSystem system;
    system.loadFromFile();

    int choice;
    do
    {
        cout << "\n==== Payroll Management System ====\n";
        cout << "1. Add Employee\n";
        cout << "2. Update Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. View Employees\n";
        cout << "5. Generate Payslip\n";
        cout << "6. Payroll Report\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.addEmployee();
            break;
        case 2:
            system.updateEmployee();
            break;
        case 3:
            system.deleteEmployee();
            break;
        case 4:
            system.displayEmployees();
            break;
        case 5:
            system.generatePayslip();
            break;
        case 6:
            system.payrollReport();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}