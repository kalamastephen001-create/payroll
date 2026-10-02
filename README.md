# Weekly Payroll Calculator

A small C++17 console program that calculates weekly pay for up to 500 employees.

## Build and run

With `g++` installed, open a terminal in this folder and run:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic payroll.cpp -o payroll.exe
.\payroll.exe
```

Enter a withholding percentage, the number of employees, and each employee's name, weekly hours, and hourly rate. The program prints regular pay, overtime pay, gross pay, estimated tax withholding, net pay, and payroll totals.

## Calculation

Hours over 40 in a week are paid at 1.5 times the hourly rate. Withholding is a single percentage entered for the payroll run and applied to each employee's gross pay. This is a basic example; it does not calculate jurisdiction-specific taxes, benefits, or other deductions.
