#include <iostream>
#include <fstream>
#include <vector>

// 定义一个函数，读取矩阵并返回矩阵地址
// std::vector<std::vector<double>> 是一个 vector 的 vector。它表示一个二维矩阵，其中每个元素（即每一行）都是一个 std::vector<double>。
// std::vector<double> 是一个动态数组，可以存储 double 类型的元素。它支持自动扩展大小和各种操作，如添加、删除和访问元素。
std::vector<std::vector<double>>* readArrayFromTXT(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::vector<std::vector<double>>* matrix = new std::vector<std::vector<double>>(); 
    double num1, num2, num3;

    if (inputFile.is_open()) {
        while (inputFile >> num1 >> num2 >> num3) {  // 每次读取一行的三个数字
            matrix->emplace_back(std::vector<double>{num1, num2, num3});  // 添加到矩阵
        }
        inputFile.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
        delete matrix;  // 如果文件打不开，删除已经分配的内存
        return nullptr;  // 返回空指针表示失败
    }

    return matrix;  // 返回矩阵的地址
}


// 从矩阵中提取指定列的函数
// 输入参数:
// - matrix: 指向待处理矩阵的指针
// - columnIndex: 需要提取的列索引
// 返回值:
// - 指向包含提取结果的列的 std::vector<double> 指针
std::vector<double>* extractColumn(const std::vector<std::vector<double>>* matrix, size_t columnIndex) {
    // 创建一个新的 std::vector<double> 用于存储提取的列数据
    auto* result = new std::vector<double>();

    // 检查输入矩阵指针是否为 null
    if (matrix == nullptr) {
        std::cerr << "Input matrix pointer is null!" << std::endl;
        return result;  // 返回空的结果向量
    }

    // 检查列索引是否在合法范围内
    if (matrix->empty() || columnIndex >= (*matrix)[0].size()) {
        std::cerr << "Column index is out of bounds!" << std::endl;
        return result;  // 返回空的结果向量
    }

    // 遍历输入矩阵的每一行
    for (const auto& row : *matrix) {
        // 添加指定列的元素到结果向量中
        result->push_back(row[columnIndex]);
    }

    // 返回包含提取列结果的向量的指针
    return result;
}


// for循环内的处理？
// 打印二维矩阵的函数
// 输入参数:
// - matrix: 指向待处理矩阵的指针
void printMatrix(const std::vector<std::vector<double>>* matrix) {
    if (matrix == nullptr) {
        std::cerr << "Matrix pointer is null!" << std::endl;
        return;
    }

    // 遍历每一行
    for (const auto& row : *matrix) {
        // 遍历当前行的每一个元素
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;  // 换行以打印下一行
    }
}

// 打印一维向量的函数
// 输入参数:
// - vec: 指向待处理向量的指针
void printMatrix(const std::vector<double>* vec) {
    if (vec == nullptr) {
        std::cerr << "Vector pointer is null!" << std::endl;
        return;
    }

    // 遍历每一个元素
    for (const auto& element : *vec) {
        std::cout << element << std::endl;
    }
}

//std::ifstream File("dat/data_trajectory_1.txt");
//std::string line;
//if (File.is_open()) {
//    while (std::getline(File, line)) { // 逐行读取文件
//        std::cout << line << std::endl; // 输出每行内容
//    }
//    File.close(); // 关闭文件
//}
//else {
//    std::cerr << "Unable to open file";
//}
/*getline:从输入流中读取字符，直到遇到换行符（\n）或到达文件末尾（EOF），并将读取的字符存储到一个字符串对象中，不考虑单词或数字之间的空格*/