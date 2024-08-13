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

// boostIntegral2: ������ػ��ֵ�ͨ�ú���
// ������
// - func: ������������������ double ���Ͳ��������� double ���ͽ��
// - x_min: �����ֵ�����
// - x_max: �����ֵ�����
// - y_min: �ڲ���ֵ�����
// - y_max: �ڲ���ֵ�����
// - tolerance: ��ֵ���ֵ��ݲĬ��ֵΪ 1e-6��
// ����ֵ��
// - ���ػ��ֵĽ��
double boostIntegral2(const std::function<double(double, double)>& func,
    double x_min, double x_max,
    double y_min, double y_max,
    const double tolerance = 1e-6);

// boostInnerIntegral: �ڲ���ֺ������̶� x ��� y ���л���
// ������
// - func: ������������������ double ���Ͳ��������� double ���ͽ��
// - x: �̶��� x ֵ
// - y_min: ���ֵ�����
// - y_max: ���ֵ�����
// - tolerance: ��ֵ���ֵ��ݲ�
// ����ֵ��
// - �� y �Ļ��ֽ��
double boostInnerIntegral(const std::function<double(double, double)>& func,
    double x, double y_min, double y_max,
    const double tolerance = 1e-6);