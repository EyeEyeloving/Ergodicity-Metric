#include "FOURIERBasis.h"
#include "cdef_value.h"
#include "cdef_function.h"

#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>
#include <boost/math/quadrature/trapezoidal.hpp>

FOURIERBasis::FOURIERBasis()
	: domainUX(0), domainUZ(0), agents_sampling_numberlong(0), agents_sampling_timglong(0)
{
}
FOURIERBasis::FOURIERBasis(double UX, double UZ, int sampling_numberlong, int sampling_timglong)
	: domainUX(UX), domainUZ(UZ), agents_sampling_numberlong(sampling_numberlong), agents_sampling_timglong(sampling_timglong)
{

}

double FOURIERBasis::FitFourierBasis(double rp1, double rp2, double* xp1x, double* xp2z) {
	double fp1 = rp1 * ppi / domainUX;
	double fp2 = rp2 * ppi / domainUZ;
	double allHk = FitAllHk(fp1, fp2);
	//std::cout << allHk << std::endl;
	double nt = (double)agents_sampling_timglong / (double)agents_sampling_numberlong;//int除法是整数除法，会截断小数部分

	std::vector<double> zp1(agents_sampling_numberlong);
	std::vector<double> zxp1x(xp1x, xp1x + agents_sampling_numberlong);
	std::transform(zxp1x.begin(), zxp1x.end(), zp1.begin(), [fp1](double a){ return std::cos(fp1 * a); });

	std::vector<double> zp2(agents_sampling_numberlong);
	std::vector<double>* zxp2z = new std::vector<double>(xp2z, xp2z + agents_sampling_numberlong);
	std::transform(zxp2z->begin(), zxp2z->end(), zp2.begin(), [fp2](double a) { return std::cos(fp2 * a); });

	std::vector<double> zp_xz(agents_sampling_numberlong);
	std::transform(zp1.begin(), zp1.end(), zp2.begin(), zp_xz.begin(), [allHk](double a, double b) { return a * b / allHk; });//二元用法

	/*对应matlab中trapz方法*/
	std::vector<double> zp(agents_sampling_numberlong - 1);
	std::transform(zp_xz.begin() + 1, zp_xz.end(), zp_xz.begin(), zp.begin(),
		[nt](double a, double b) { return (a + b) / 2 * nt; });

	double integral_trapz = std::accumulate(zp.begin(), zp.end(), 0.0);

	return integral_trapz ;
}

double FOURIERBasis::FitAllHk(double fp1, double fp2) {
	double allHk = boostIntegral2([fp1, fp2](double x, double y) {return pow(std::cos(fp1 * x), 2) * pow(std::cos(fp2 * y), 2); }, 0, domainUX, 0, domainUZ);
	
	return std::sqrt(allHk);
}

// 定义被积函数
double FitInnerFunction(double x, double y) {
	return pow(std::cos(x),2) * pow(std::cos(y),2);
}