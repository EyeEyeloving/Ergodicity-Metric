#include "TRAJDataSet.h"
#include <iostream>
#include <vector>

TRAJDataSet::TRAJDataSet()
{
}
TRAJDataSet::TRAJDataSet(std::vector<double>* matrix, int timelong)
    : sampling_numberlong((int)matrix->size()), sampling_timelong(timelong)
{
    updateSamplingFrequency();
    setTrajectoryDomain(matrix);
}

void TRAJDataSet::setSamplingTimelong(int timelong) {
    sampling_timelong = timelong;
    if (sampling_numberlong != 0) {
        updateSamplingFrequency();  // 更新采样时间长度后计算采样率
    }
}

void TRAJDataSet::updateSamplingFrequency() {
    if (sampling_timelong != 0) {
        sampling_frequency = sampling_numberlong / sampling_timelong;
    }
    else {
        sampling_frequency = 0;  // 避免除零错误
    }
}

void TRAJDataSet::getSamplingFrequency(const char* stringLog) const {
    if (stringLog == "Log") {
        std::cout << "The Sampling Frequency is :  " << std::endl;
        std::cout << sampling_frequency << "(Hz)" << std::endl;
    }
}
int TRAJDataSet::getSamplingFrequency() const {
    return sampling_frequency;
}

void TRAJDataSet::setTrajectoryDomain(std::vector<double>* matrix) {
    // 找到最小值和最大值的迭代器
    auto ptr_min = std::min_element(matrix->begin(), matrix->end());
    domain_min = *ptr_min;
    auto ptr_max = std::max_element(matrix->begin(), matrix->end());
    domain_max = *ptr_max;
}

void TRAJDataSet::getTrajectoryDomain(const char* stringLog) const {
    if (stringLog == "Log") {
        std::cout << "The Trajectory Domain is :  " << std::endl;
        std::cout << "Min : " << domain_min << std::endl;
        std::cout << "Max : " << domain_max << std::endl;
    }
}
std::vector<double> TRAJDataSet::getTrajectoryDomain() const {
    return { domain_min, domain_max };
}