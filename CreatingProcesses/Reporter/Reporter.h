#include <iostream>
#include <Employee.h>
#include <vector>
#include <fstream>
#include <conio.h>

std::vector <Employee> ReadingBinFile(char* binfile_name) {
    std::vector <Employee> result;
    Employee temp;

    std::ifstream f1(binfile_name, std::ifstream::in | std::ios::binary);
    if (f1.is_open()) {
        std::cout << binfile_name << " is open!\n";
        while (!f1.eof()) {
            f1.read((char*)&temp, sizeof(temp));
            if (f1.good()) {
                result.push_back(temp);
            }
        }
        std::cout << binfile_name << " is read!\n";

        f1.close();
    }
    else {
        std::cout << binfile_name << " isn't open!\n";
    }

    return result;
}

void GetReport(std::ostream& report, char* binfile_name, double payment_by_hour) {
    auto employees = ReadingBinFile(binfile_name);
    report << "File report \"" << binfile_name << "\".\n";

    for (int i = 0; i < employees.size(); i++) {
        double salary = employees[i].hours * payment_by_hour;
        report << employees[i].num << ' ' << employees[i].name << ' ' << employees[i].hours << ' ' << salary << '\n';
    }
}

void GetBinFile(std::ostream& report, char* binfile_name) {
    auto employees = ReadingBinFile(binfile_name);
    report << binfile_name << '\n';

    for (int i = 0; i < employees.size(); i++) {
        report << employees[i].num << ' ' << employees[i].name << ' ' << employees[i].hours << '\n';
    }
}
