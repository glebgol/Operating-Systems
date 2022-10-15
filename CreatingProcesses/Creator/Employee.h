#pragma warning(disable:4996)
#include <iostream>

struct Employee
{
	int num;		// идентификационный номер сотрудника
	char name[10];	// имя сотрудника
	double hours;	// количество отработанных часов

	Employee() : num(0), hours(0.0) {
		strcpy(name, "___");
	}

	friend std::istream& operator>>(std::istream& is, Employee& emp) {
		is >> emp.num >> emp.name >> emp.hours;
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, const Employee& emp) {
		os << emp.num << ' ' << emp.name << ' ' << emp.hours;
		return os;
	}
};
