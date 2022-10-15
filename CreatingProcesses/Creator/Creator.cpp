#include <iostream>
#include <fstream>
#include "Employee.h"

void WritingToBinFileEmployee(char* binfile_name, int amount) {
	std::cout << binfile_name << " " << amount << std::endl;

	std::ofstream bin_file(binfile_name, std::ios::binary);

	std::cout << "Enter " << amount << " employees (num, name, hours)\n";
	for (int i = 0; i < amount; i++) {
		Employee temp;
		std::cout << i + 1 << ": ";
		std::cin >> temp;
		bin_file.write((char*)&temp, sizeof(temp));
	}
}

int main(int argc, char* argv[])
{
	char binfile_name[50];
	strcpy(binfile_name, argv[1]);
	int amount = std::atoi(argv[2]);
	WritingToBinFileEmployee(binfile_name, amount);
}

