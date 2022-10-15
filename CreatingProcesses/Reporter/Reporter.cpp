#include "Reporter.h"

int main(int argc, char* argv[])
{
    char binfile_name[50];
    strcpy(binfile_name, argv[1]);

    char txtfile_name[50];
    strcpy(txtfile_name, argv[2]);

    double payment_by_hour = strtod(argv[3], nullptr);
    std::ofstream report(txtfile_name);
    GetReport(report, binfile_name, payment_by_hour);
    _cputs("Press any key to finish.\n");
    _getch();
}
