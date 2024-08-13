#include <iostream>
#include <fstream>
#include <vector>
#include <functional> // std::function

#pragma once

std::vector<std::vector<double>>* readArrayFromTXT(const std::string& filename);

std::vector<double>* extractColumn(const std::vector<std::vector<double>>* matrix, size_t columnIndex);

void printMatrix(const std::vector<double>* vec);
void printMatrix(const std::vector<std::vector<double>>* matrix);

/*Boost*/
double FitInnerFunction(double x, double y);

// boostIntegral2: 计算二重积分的通用函数
// 参数：
// - func: 被积函数，接受两个 double 类型参数，返回 double 类型结果
// - x_min: 外层积分的下限
// - x_max: 外层积分的上限
// - y_min: 内层积分的下限
// - y_max: 内层积分的上限
// - tolerance: 数值积分的容差（默认值为 1e-6）
// 返回值：
// - 二重积分的结果
double boostIntegral2(const std::function<double(double, double)>& func,
    double x_min, double x_max,
    double y_min, double y_max,
    const double tolerance = 1e-6);

// boostInnerIntegral: 内层积分函数，固定 x 后对 y 进行积分
// 参数：
// - func: 被积函数，接受两个 double 类型参数，返回 double 类型结果
// - x: 固定的 x 值
// - y_min: 积分的下限
// - y_max: 积分的上限
// - tolerance: 数值积分的容差
// 返回值：
// - 对 y 的积分结果
double boostInnerIntegral(const std::function<double(double, double)>& func,
    double x, double y_min, double y_max,
    const double tolerance = 1e-6);