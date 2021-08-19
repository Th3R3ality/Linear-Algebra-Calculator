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

    std::string type;
    
    printf("\tplease enter what mode you want\n");
    printf("\tget a & b with x & y in linear function (xy)\n");
    printf("\tget intersection of 2 linear functions with a & b (inter)\n");
    printf("\tget a in constant linear function from 1 point (const)\n");


    while (true) {
        printf("\tq/quit to exit\n");
        type = "";
        std::cin >> type;
        

        if (type == "xy") {

            double x1, y1, x2, y2, a, b;
            printf("\t\tPlease enter 4 numbers, 2 x & 2 y values!\n");

            std::cin >> x1 >> y1 >> x2 >> y2;
            std::tie(a, b) = linearxy(x1, y1, x2, y2);
            printf("\n");
            std::cout << "x1: " << x1 << "\ty1: " << y1 << "\tx2: " << x2 << "\ty2: " << y2 << "\na: " << a << "\tb: " << b << "\n\n" << std::endl;
            f << "x1: " << x1 << "\ty1: " << y1 << "\tx2: " << x2 << "\ty2: " << y2 << "\na: " << a << "\tb: " << b << "\n" << std::endl;
        }
        else if (type == "inter") {
            double x, a1, b1, a2, b2;
            std::cout << "\t\tplease enter 4 numbers 2 a & 2 b variables" << std::endl;
            std::cin >> a1 >> b1 >> a2 >> b2;
            x = intersection(a1, b1, a2, b2);
            printf("\n");
            std::cout << "a1: " << a1 << "\tb1: " << b1 << "\ta2: " << a2 << "\tb2: " << b2 << "\nx: " << x << "\n" << std::endl;
            f << "a1: " << a1 << "\tb1: " << b1 << "\ta2: " << a2 << "\tb2: " << b2 << "\nx: " << x << "\n" << std::endl;
        }
        else if (type == "const") {
            double x, y, k;
            printf("\t\tplease enter 2 numbers, x & y\n");
            std::cin >> x >> y;
            k = constant(x, y);
            printf("\nx: %f\ty: %f\nconstant: %f", x, y, k);
            f << "x: " << x << "\ty: " << y << "\nconstant: " << k << "\n" << std::endl;
        }
        else if (type == "reg") {
            std::vector<double> x, y;
            double r;
            printf("enter x values (non-numbers to continue)\n");
            x = fillVector(x);
            printf("enter y values (non-numbers to continue)\n");
            y = fillVector(y);

            r = pearson(x, y);
            printf("r: %f\n", r);
        }
        else if (type == "q" || type == "quit") {
            f.close();
            return 0;
        }
        else {
            printf("\nplease enter a valid mode\n\n");
        }
    }
}