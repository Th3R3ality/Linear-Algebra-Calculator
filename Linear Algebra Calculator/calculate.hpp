#pragma once
#include <iostream>
#include <Windows.h>
#include <tuple>
#include <vector>

std::tuple<double, double>linearxy(double x1, double y1, double x2, double y2)
{
	double a = 0, b = 0;
	if ((y2 - y1) == 0 && x2 - x1 == 0) {
		a = 0;
		b = y2 - a * x2;
		return { a, b };
	}
	if (y2 - y1 == 0) {
		a = 1 / (x2 - x1);
	}
	if (x2 - x1 == 0) {
		a = 1 / (y2 - y1);
	}
	a = (y2 - y1) / (x2 - x1);
	b = y2 - a * x2;
	return {a, b};
}

double intersection(double a1, double b1, double a2, double b2) {
	return (b2 - b1) / (a2 - a1);
}

double constant(double x, double y) {
	return y / x;
}

std::vector<double> fillVector(std::vector<double> x, size_t max = 0) {
	double Temp;
	while (std::cin >> Temp) {
		x.push_back(Temp);
		if (x.size() == max) {
			break;
		}
	}
	std::cin.clear();
	return x;
}

double mean(std::vector<double> x) {
	double m = 0;
	for (size_t i = 0; i < x.size(); i++) {
		m += x[i];
	}
	m /= x.size();
	return m;
}

std::tuple<double, double, double>regression(std::vector<double> &x, std::vector<double> &y, char p) {
	double r = 0, a = 0, xM = 0, yM = 0, xyM_sum = 0, xxM2_sum = 0, yyM2_sum = 0, Sx = 0, Sy = 0, b = 0;
	std::vector<double> xxM, yyM, xyM, xxM2, yyM2;
	xM = mean(x);
	yM = mean(y);
	long n = 0;

	if (p == 'p') {
		printf("( x )\t\t( y )\t\t( x - xM )\t( y - yM )\t(x-xM)*(y-yM)\t( (x-xM)^2 )\t( (y-yM)^2 )\n");
	}

	for (int i = 0; i < x.size(); i++) {
		xxM.push_back(x[i] - xM);
		yyM.push_back(y[i] - yM);
		xyM.push_back(xxM[i] * yyM[i]);
		xxM2.push_back(pow(xxM[i], 2));
		yyM2.push_back(pow(yyM[i], 2));
		xyM_sum += xyM[i];
		xxM2_sum += xxM2[i];
		yyM2_sum += yyM2[i];
		n += 1;
		if (p == 'p') {
			printf("[ %f ]\t[ %f ]\t[ %f ]\t[ %f ]\t[ %f ]\t[ %f ]\t[ %f ]\n", x[i], y[i], xxM[i], yyM[i], xyM[i], xxM2[i], yyM2[i]);
		}
	}
	printf("xM = %f\tyM = %f\t\t\t\t\t\E = %f\tE = %f\tE = %f\n\n", xM, yM, xyM_sum, xxM2_sum, yyM2_sum);


	r = xyM_sum / sqrt(xxM2_sum * yyM2_sum);

	Sy = sqrt(yyM2_sum / (n - 1));
	Sx = sqrt(xxM2_sum / (n - 1));

	a = r * (Sy / Sx);

	b = yM - a * xM;

	

	return {r, a, b};
}