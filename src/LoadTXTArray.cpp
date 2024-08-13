#include <iostream>
#include <fstream>
#include <vector>

// ����һ����������ȡ���󲢷��ؾ����ַ
// std::vector<std::vector<double>> ��һ�� vector �� vector������ʾһ����ά��������ÿ��Ԫ�أ���ÿһ�У�����һ�� std::vector<double>��
// std::vector<double> ��һ����̬���飬���Դ洢 double ���͵�Ԫ�ء���֧���Զ���չ��С�͸��ֲ���������ӡ�ɾ���ͷ���Ԫ�ء�
std::vector<std::vector<double>>* readArrayFromTXT(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::vector<std::vector<double>>* matrix = new std::vector<std::vector<double>>(); 
    double num1, num2, num3;

    if (inputFile.is_open()) {
        while (inputFile >> num1 >> num2 >> num3) {  // ÿ�ζ�ȡһ�е���������
            matrix->emplace_back(std::vector<double>{num1, num2, num3});  // ��ӵ�����
        }
        inputFile.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
        delete matrix;  // ����ļ��򲻿���ɾ���Ѿ�������ڴ�
        return nullptr;  // ���ؿ�ָ���ʾʧ��
    }

    return matrix;  // ���ؾ���ĵ�ַ
}


// �Ӿ�������ȡָ���еĺ���
// �������:
// - matrix: ָ�����������ָ��
// - columnIndex: ��Ҫ��ȡ��������
// ����ֵ:
// - ָ�������ȡ������е� std::vector<double> ָ��
std::vector<double>* extractColumn(const std::vector<std::vector<double>>* matrix, size_t columnIndex) {
    // ����һ���µ� std::vector<double> ���ڴ洢��ȡ��������
    auto* result = new std::vector<double>();

    // ����������ָ���Ƿ�Ϊ null
    if (matrix == nullptr) {
        std::cerr << "Input matrix pointer is null!" << std::endl;
        return result;  // ���ؿյĽ������
    }

    // ����������Ƿ��ںϷ���Χ��
    if (matrix->empty() || columnIndex >= (*matrix)[0].size()) {
        std::cerr << "Column index is out of bounds!" << std::endl;
        return result;  // ���ؿյĽ������
    }

    // ������������ÿһ��
    for (const auto& row : *matrix) {
        // ���ָ���е�Ԫ�ص����������
        result->push_back(row[columnIndex]);
    }

    // ���ذ�����ȡ�н����������ָ��
    return result;
}


// forѭ���ڵĴ���
// ��ӡ��ά����ĺ���
// �������:
// - matrix: ָ�����������ָ��
void printMatrix(const std::vector<std::vector<double>>* matrix) {
    if (matrix == nullptr) {
        std::cerr << "Matrix pointer is null!" << std::endl;
        return;
    }

    // ����ÿһ��
    for (const auto& row : *matrix) {
        // ������ǰ�е�ÿһ��Ԫ��
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;  // �����Դ�ӡ��һ��
    }
}

// ��ӡһά�����ĺ���
// �������:
// - vec: ָ�������������ָ��
void printMatrix(const std::vector<double>* vec) {
    if (vec == nullptr) {
        std::cerr << "Vector pointer is null!" << std::endl;
        return;
    }

    // ����ÿһ��Ԫ��
    for (const auto& element : *vec) {
        std::cout << element << std::endl;
    }
}

//std::ifstream File("dat/data_trajectory_1.txt");
//std::string line;
//if (File.is_open()) {
//    while (std::getline(File, line)) { // ���ж�ȡ�ļ�
//        std::cout << line << std::endl; // ���ÿ������
//    }
//    File.close(); // �ر��ļ�
//}
//else {
//    std::cerr << "Unable to open file";
//}
/*getline:���������ж�ȡ�ַ���ֱ���������з���\n���򵽴��ļ�ĩβ��EOF����������ȡ���ַ��洢��һ���ַ��������У������ǵ��ʻ�����֮��Ŀո�*/