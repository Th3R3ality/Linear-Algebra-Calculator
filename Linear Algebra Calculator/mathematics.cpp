#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tuple>
#include "calculate.hpp"

bool checkFile(const char* name) {
    std::ifstream f("svar.txt", std::ios::in);
    if (f.fail()) {
        printf("kunne ikke finde svar fil\n");
        f.close();
        return 0;
    }
    else {
        printf("fandt svar fil\n");
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
        printf("åbner svar fil\n");
        f.open("svar.txt", std::ios::app);
    }
    else {
        printf("laver svar fil\n");
        f.open("svar.txt", std::ios::out);
    }

    Sleep(1500);
    clearCon();
    std::string type;
    while (true) {
        printf("\n\nvælg hvad du vil regne / skriv hvad det der står i (parenteserne)\n");
        printf("\t udregn a & b ud fra 2 punkter (xy)\n");
        printf("\tfind skæringspunktet med 2 a & b vaerdier (inter)\n");
        printf("\tfind den konstante haeldning ud fra 1 punkt (konst)\n");
        printf("\tudregn den linaere regression a/r, x & b fra en maengde x og y vaerdier (reg)\n");
        printf("\tfind y vaerdien/haeldningen med given a, b og x (axb)\n");
        printf("\tfind x og y med 2 ukendte variabler via determinent metoden (det)\n");
        printf("\tq / quit for at lukke programmet\tc / clear for at rydde skaermen\n");
        

        type = "";
        std::cin >> type;
        
        clearCon();

        if (type == "xy") {
            double x1, y1, x2, y2, a, b;
            printf("\t\tSkriv 2 punkter med x & y\n");


            std::cin >> x1 >> y1 >> x2 >> y2;
            std::tie(a, b) = linearxy(x1, y1, x2, y2);

            std::cout << "\nx1: " << x1 << "\ty1: " << y1 << "\tx2: " << x2 << "\ty2: " << y2 << "\na: " << a << "\tb: " << b << "\n\n" << std::endl;
            f << "x1: " << x1 << "\ty1: " << y1 << "\tx2: " << x2 << "\ty2: " << y2 << "\na: " << a << "\tb: " << b << "\n" << std::endl;
            std::cin.clear();
        }
        else if (type == "inter") {
            double x, a1, b1, a2, b2;
            printf("\t\tSkriv 2 a & b vaerdier\n");

            std::cin >> a1 >> b1 >> a2 >> b2;
            x = intersection(a1, b1, a2, b2);

            std::cout << "\na1: " << a1 << "\tb1: " << b1 << "\ta2: " << a2 << "\tb2: " << b2 << "\nx: " << x << "\n" << std::endl;
            f << "a1: " << a1 << "\tb1: " << b1 << "\ta2: " << a2 << "\tb2: " << b2 << "\nx: " << x << "\n" << std::endl;
            std::cin.clear();
        }
        else if (type == "konst") {
            double x, y, k;
            printf("\t\tSkriv 1 punkt\n");

            std::cin >> x >> y;
            k = constant(x, y);

            printf("\nx: %f\ty: %f\nkonstant: %f\n", x, y, k);
            f << "x: " << x << "\ty: " << y << "\nkonstant: " << k << "\n" << std::endl;
            std::cin.clear();
        }
        else if (type == "reg") {
            std::vector<double> x, y;
            double r, a, b;
            char p; std::string pTemp;
            printf("Skriv dine x vaerdier (bogstaver for at gå videre / p for at se mellem regninger)\n");
            x = fillVector(x);
            std::cin >> pTemp;
            if (pTemp[0] == 'p') {
                p = 'p';
            }
            else {
                p = 'x';
            }
            std::cin.clear();
            printf("Skriv dine y vaerdier\n");
            y = fillVector(y, x.size());
            
            std::tie(r, a, b) = regression(x, y, p);

            printf("r: %f\ta: %f\tb: %f\n", r, a, b);

            std::cout << "x = [";
            for (int i = 0; i < x.size() - 1; i++) {
                std::cout << x[i] << ", ";
            }
            std::cout << x[x.size() - 1] << "]\n";

            std::cout << "y = [";
            for (int i = 0; i < y.size() - 1; i++) {
                std::cout << y[i] << ", ";
            }
            std::cout << y[y.size() - 1] << "]\n";

            f << "x = [";
            for (int i = 0; i < x.size() - 1; i++) {
                f << x[i] << ", ";
            }
            f << x[x.size() - 1] << "]\n";

            f << "y = [";
            for (int i = 0; i < y.size() - 1; i++) {
                f << y[i] << ", ";
            }
            f << y[y.size() - 1] << "]\n";

            
            f << "r: " << r << "\na: " << a << "\nb: " << b << "\n" << std::endl;
            std::cin.clear();
        }
        else if (type == "abx") {
            printf("indtast a, x og b vaerdierne\n");
            double a, b, x, y;
            std::cin >> a >> b >> x;
            y = a * x + b;
            printf("a: %f\tb: %f\tx: %f\ny: %f", a, b, x, y);
            f << "a: " << a << "\tb: " << b << "\tx: " << x << "\ny: " << y << std::endl;
        }
        else if (type == "det") {
            printf("indtast a1, b1, c1, a2, b2 og c2\n");
            double a1, a2, b1, b2, c1, c2, x, y;
            std::cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
            std::tie(x, y) = determinant(a1, a2, b1, b2, c1, c2);
            std::cout << "\na1: " << a1 << "\tb1: " << b1 << "\tc1: " << c1 << 
                "\na2: " << a2 << "\tb2: " << b2 << "\tc2: " << c2 <<
                "\nx: " << x << "\ty: " << y << std::endl;

            f << "\na1: " << a1 << "\tb1: " << b1 << "\tc1: " << c1 <<
                "\na2: " << a2 << "\tb2: " << b2 << "\tc2: " << c2 <<
                "\nx: " << x << "\ty: " << y << std::endl;
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
            std::cout << "\ntype: " << type << "\ter ikke en gyldig type\n" << std::endl;
        }
    }
}