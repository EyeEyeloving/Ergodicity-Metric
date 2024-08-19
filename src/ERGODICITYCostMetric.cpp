#include "ERGODICITYCostMetric.h"
#include <cmath>

ERGODICITYCostMetric::ERGODICITYCostMetric()
	: k_resolution(0), agents_expertnumber(0)
{
}

ERGODICITYCostMetric::ERGODICITYCostMetric(int k_r) 
	: k_resolution(k_r), agents_expertnumber(0)
{

}

/*
输入参数：
xp1：（完整）一维数组数据的指针
xp2：（完整）一维数组数据的指针
phi_r：指针
*/
double ERGODICITYCostMetric::FitMetric(double* xp1, double* xp2, double** phi_r) {
	int n_dimension = 2;
	double result_epsilon = 0;
	double GAMMA_r;

	// xp1,xp2要平移
	for (int rp1 = 0; rp1 < k_resolution + 1; rp1++) {
		for (int rp2 = 0; rp2 < k_resolution + 1; rp2++) {
			GAMMA_r = pow((1 + std::pow(rp1, 2) + std::pow(rp2, 2)), -(n_dimension + 1) / 2);
			double sigma_r = FitFourierBasis(rp1, rp2, xp1, xp2);
			result_epsilon = GAMMA_r * pow(sigma_r - phi_r[rp1][rp2], 2) + result_epsilon;
		}
	}
	return result_epsilon;
}

double** ERGODICITYCostMetric::FitSigmak(double* xp1, double* xp2) {
	double** Sigmak = new double* [k_resolution + 1];
	//double* a[k_resolution]不可以？
	for (int i = 0; i < k_resolution + 1; i++) {
		Sigmak[i] = new double[k_resolution + 1];
	}

	for (int rp1 = 0; rp1 < k_resolution + 1; rp1++) {
		for (int rp2 = 0; rp2 < k_resolution + 1; rp2++) {
			Sigmak[rp1][rp2] = FitFourierBasis(rp1, rp2, xp1, xp2);
		}
	}

	return Sigmak;
}