#include <iostream>
#include <fstream>
#include <string>

#include "boost/math/quadrature/trapezoidal.hpp"
#include "boost/bind/bind.hpp"

#include "cdef_function.h"
#include "TRAJDataSet.h"
#include "ERGODICITYCostMetric.h"


int main() {

	std::vector<std::vector<double>> domain_Xvec(2);
	std::vector<std::vector<double>> domain_Zvec(2);
	for (int i = 0; i < 10; i++) {
		// 不提供dat/内数据
		// txt内的3D轨迹数据的每一行是一个具有三个维度信息的观测点
		const std::string filename = "dat/data_trajectory_" + std::to_string(i + 1) + ".txt";
		std::vector<std::vector<double>>* filedata_array = readArrayFromTXT(filename);
		std::vector<double>* filedata_array_Xcol = extractColumn(filedata_array, 0);
		std::vector<double>* filedata_array_Zcol = extractColumn(filedata_array, 2);

		TRAJDataSet datasetX(filedata_array_Xcol, 30);
		//datasetX.getTrajectoryDomain("Log");
		std::vector<double> domain = datasetX.getTrajectoryDomain();
		domain_Xvec[0].push_back(domain[0]);
		domain_Xvec[1].push_back(domain[1]);

		TRAJDataSet datasetZ(filedata_array_Zcol, 30);
		//datasetZ.getTrajectoryDomain("Log");
		std::vector<double> domain_ = datasetZ.getTrajectoryDomain();
		domain_Zvec[0].push_back(domain_[0]);
		domain_Zvec[1].push_back(domain_[1]);
		
	}
	double domain_Xmin = *std::min_element(domain_Xvec[0].begin(), domain_Xvec[0].end());
	double domain_Xmax = *std::max_element(domain_Xvec[1].begin(), domain_Xvec[1].end());
	double domain_Zmin = *std::min_element(domain_Zvec[0].begin(), domain_Zvec[0].end());
	double domain_Zmax = *std::max_element(domain_Zvec[1].begin(), domain_Zvec[1].end());

	const int k_r = 5;
	ERGODICITYCostMetric ergo_metric(k_r);
	ergo_metric.domainUX = domain_Xmax - domain_Xmin;
	ergo_metric.domainUZ = domain_Zmax - domain_Zmin;

	double** Phik = new double* [k_r + 1];
	for (int i = 0; i < k_r + 1; ++i) {
		Phik[i] = new double[k_r + 1];
		std::fill(Phik[i], Phik[i] + k_r + 1, 0.0); // 将每个元素初始化为0
	}

	for (int j = 0; j < 10; j++) {
		const std::string filename = "dat/data_trajectory_" + std::to_string(j + 1) + ".txt";
		//auto filedata_array = new std::vector<std::vector<double>>;
		std::vector<std::vector<double>>* filedata_array = readArrayFromTXT(filename);
		std::vector<double>* filedata_array_Xcol = extractColumn(filedata_array, 0);
		std::vector<double>* filedata_array_Zcol = extractColumn(filedata_array, 2);

		std::vector<double> filedata_arrayA((int)filedata_array_Xcol->size());
		std::transform((*filedata_array_Xcol).begin(), (*filedata_array_Xcol).end(), filedata_arrayA.begin(), [domain_Xmin](double a) {return a - domain_Xmin; });
		std::vector<double> filedata_arrayB((int)filedata_array_Zcol->size());
		std::transform((*filedata_array_Zcol).begin(), (*filedata_array_Zcol).end(), filedata_arrayB.begin(), [domain_Zmin](double a) {return a - domain_Zmin; });

		ergo_metric.agents_expertnumber = j + 1;
		ergo_metric.agents_sampling_timglong = 30;
		ergo_metric.agents_sampling_numberlong = (int)filedata_arrayA.size();
		double** Sigmak_j = ergo_metric.FitSigmak(filedata_arrayA.data(), filedata_arrayB.data());
		for (int m = 0; m < k_r + 1; m++) {
			for (int n = 0; n < k_r + 1; n++) {
				Phik[m][n] = Phik[m][n] + Sigmak_j[m][n] / ergo_metric.agents_sampling_timglong;
			}
		}

		for (int i = 0; i < k_r + 1; ++i) {
			for (int j = 0; j < k_r + 1; ++j) {
				std::cout << Sigmak_j[i][j] / ergo_metric.agents_sampling_timglong << " ";// 
			}
			std::cout << std::endl;  // 每行结束后换行
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < k_r + 1; ++i) {
		for (int j = 0; j < k_r + 1; ++j) {
			std::cout << Phik[i][j] / ergo_metric.agents_expertnumber << " ";// 
		}
		std::cout << std::endl;  // 每行结束后换行
	}
}
