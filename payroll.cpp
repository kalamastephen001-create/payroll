#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Employee {
    std::string name;
    double hoursWorked;
    double hourlyRate;
    double taxRate;
};

struct Paycheck {
    double regularPay;
    double overtimePay;
    double grossPay;
    double taxWithheld;
    double netPay;
};

int readEmployeeCount() {
    int count;
    while (true) {
        std::cout << "Number of employees (1-500): ";
        if (std::cin >> count && count >= 1 && count <= 500) {
            return count;
        }

        std::cout << "Enter a whole number from 1 to 500.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Paycheck calculatePay(const Employee& employee) {
    const double regularHours = employee.hoursWorked < 40.0 ? employee.hoursWorked : 40.0;
    const double overtimeHours = employee.hoursWorked > 40.0 ? employee.hoursWorked - 40.0 : 0.0;
    const double regularPay = regularHours * employee.hourlyRate;
    const double overtimePay = overtimeHours * employee.hourlyRate * 1.5;
    const double grossPay = regularPay + overtimePay;
    const double taxWithheld = grossPay * employee.taxRate / 100.0;

    return {regularPay, overtimePay, grossPay, taxWithheld, grossPay - taxWithheld};
}

double readNumber(const std::string& prompt, double minimum, double maximum) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minimum && value <= maximum) {
            return value;
        }

        std::cout << "Enter a number from " << minimum << " to " << maximum << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    std::cout << "Weekly Payroll Calculator\n"
              << "Overtime is paid at 1.5x for hours over 40.\n\n";

    const double taxRate = readNumber("Tax withholding rate (%): ", 0.0, 100.0);
    const int employeeCount = readEmployeeCount();
    std::vector<Employee> employees;
    employees.reserve(employeeCount);

    for (int index = 0; index < employeeCount; ++index) {
        Employee employee{};
        std::cout << "\nEmployee " << index + 1 << " name: ";
        std::cin >> std::ws;
        std::getline(std::cin, employee.name);
        while (employee.name.empty()) {
            std::cout << "Name cannot be empty. Enter the employee name: ";
            std::getline(std::cin, employee.name);
        }

        employee.hoursWorked = readNumber("Hours worked this week (0-168): ", 0.0, 168.0);
        employee.hourlyRate = readNumber("Hourly rate ($): ", 0.0, 1000000.0);
        employee.taxRate = taxRate;
        employees.push_back(employee);
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nPayroll Summary\n"
              << std::left << std::setw(24) << "Employee"
              << std::right << std::setw(12) << "Regular"
              << std::setw(12) << "Overtime"
              << std::setw(12) << "Gross"
              << std::setw(12) << "Tax"
              << std::setw(12) << "Net" << '\n';
    std::cout << std::string(84, '-') << '\n';

    double totalGross = 0.0;
    double totalTax = 0.0;
    double totalNet = 0.0;
    for (const Employee& employee : employees) {
        const Paycheck paycheck = calculatePay(employee);
        std::cout << std::left << std::setw(24) << employee.name
                  << std::right << std::setw(12) << paycheck.regularPay
                  << std::setw(12) << paycheck.overtimePay
                  << std::setw(12) << paycheck.grossPay
                  << std::setw(12) << paycheck.taxWithheld
                  << std::setw(12) << paycheck.netPay << '\n';
        totalGross += paycheck.grossPay;
        totalTax += paycheck.taxWithheld;
        totalNet += paycheck.netPay;
    }

    std::cout << std::string(84, '-') << '\n'
              << std::left << std::setw(48) << "Totals"
              << std::right << std::setw(12) << totalGross
              << std::setw(12) << totalTax
              << std::setw(12) << totalNet << '\n';

    return 0;
}
