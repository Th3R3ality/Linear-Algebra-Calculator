#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tuple>
#include "calculate.hpp"

bool checkFile(const char* name) {
    std::ifstream f("answers.txt", std::ios::in);
    if (f.fail()) {
        printf("didn't find an answers file\n");
        f.close();
        return 0;
    }
    else {
        printf("found answers file\n");
        f.close();
        return 1;
    }
}

void clearCon() {
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

int main()
{
    std::fstream f;
    if (checkFile("answers.txt")) {
        printf("opening answers file\n");
        f.open("answers.txt", std::ios::app);
    }
    else {
        printf("creating answers file\n");
        f.open("answers.txt", std::ios::out);
    }

    Sleep(2000);
    clearCon();
    std::string type;
    while (true) {
        printf("\n\nplease enter what mode you want\n");
        printf("\tget a & b with x & y in linear function (xy)\n");
        printf("\tget intersection of 2 linear functions with a & b (inter)\n");
        printf("\tget a in constant linear function from 1 point (const)\n");
        printf("\tcalculate linear regression a, x & b from array (reg)\n");
        printf("\tq / quit to exit\tc / clear to clear console\n");
        

        type = "";
        std::cin >> type;
        
        clearCon();

        if (type == "xy") {
            double x1, y1, x2, y2, a, b;
            printf("\t\tPlease enter 4 numbers, 2 x & 2 y values!\n");


            std::cin >> x1 >> y1 >> x2 >> y2;
            std::tie(a, b) = linearxy(x1, y1, x2, y2);

            std::cout << "\nx1: " << x1 << "\ty1: " << y1 << "\tx2: " << x2 << "\ty2: " << y2 << "\na: " << a << "\tb: " << b << "\n\n" << std::endl;
            f << "x1: " << x1 << "\ty1: " << y1 << "\tx2: " << x2 << "\ty2: " << y2 << "\na: " << a << "\tb: " << b << "\n" << std::endl;
            std::cin.clear();
        }
        else if (type == "inter") {
            double x, a1, b1, a2, b2;
            printf("\t\tplease enter 4 numbers 2 a & 2 b variables\n");

            std::cin >> a1 >> b1 >> a2 >> b2;
            x = intersection(a1, b1, a2, b2);

            std::cout << "\na1: " << a1 << "\tb1: " << b1 << "\ta2: " << a2 << "\tb2: " << b2 << "\nx: " << x << "\n" << std::endl;
            f << "a1: " << a1 << "\tb1: " << b1 << "\ta2: " << a2 << "\tb2: " << b2 << "\nx: " << x << "\n" << std::endl;
            std::cin.clear();
        }
        else if (type == "const") {
            double x, y, k;
            printf("\t\tplease enter 2 numbers, x & y\n");

            std::cin >> x >> y;
            k = constant(x, y);

            printf("\nx: %f\ty: %f\nconstant: %f\n", x, y, k);
            f << "x: " << x << "\ty: " << y << "\nconstant: " << k << "\n" << std::endl;
            std::cin.clear();
        }
        else if (type == "reg") {
            std::vector<double> x, y;
            double r, a, b;
            char p; std::string pTemp;
            printf("enter x values (non-numbers to continue / p to print)\n");
            x = fillVector(x);
            std::cin >> pTemp;
            if (pTemp[0] == 'p') {
                p = 'p';
            }
            else {
                p = 'x';
            }
            std::cin.clear();
            printf("enter y values\n");
            y = fillVector(y, x.size());
            
            std::tie(r, a, b) = regression(x, y, p);

            printf("r: %f\ta: %f\tb: %f\n", r, a, b);
            f << "r: " << r << "\na: " << a << "\nb: " << b << "\n" << std::endl;
            std::cin.clear();
        }
        else if (type[0] == 'q') {
            f.close();
            std::cin.clear();
            clearCon();
            return 0;
        }
        else if (type[0] == 'c') {
            clearCon();
        }
        else {
            std::cin.clear();
            printf("\nplease enter a valid mode\n\n");
        }
    }
}