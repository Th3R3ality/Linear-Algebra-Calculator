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

std::vector<double> fillVector(std::vector<double> x) {
	double Temp;
	while (std::cin >> Temp) {
		x.push_back(Temp);
	}
	std::cin.clear();
	for (int i = 0; i < x.size(); i++) {
		printf("x[%i]\t=\t%f\n", i, x[i]);
	}
	std::cin.get();
	return x;
}

double mean(std::vector<double> x) {
	double m = 0;
	for (int i = 0; i < x.size(); i++) {
		m += x[i];
	}
	return m;
}

double pearson(std::vector<double> x, std::vector<double> y) {
	double r = 0, xM = 0, yM = 0, xyM_sum = 0, xxM2_sum = 0, yyM2_sum = 0;
	std::vector<double> xxM, yyM, xyM, xxM2, yyM2;
	xM = mean(x);
	yM = mean(y);
	for (int i = 0; i < x.size(); i++) {
		xxM[i] = x[i] - xM;
		yyM[i] = y[i] - xM;
		xyM[i] = xxM[i] * yyM[i];
		xxM2[i] = pow(xxM[i], 2);
		yyM2[i] = pow(yyM[i], 2);
		xyM_sum += xyM[i];
		xxM2_sum += xxM2[i];
		yyM2_sum += yyM2[i];
	}
	r = xyM_sum / sqrt(xxM2_sum * yyM2_sum);


	return r;
}