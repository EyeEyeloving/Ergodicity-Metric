#pragma once

#include <vector>

class TRAJDataSet
{
public:
    int sampling_timelong;      // 采样时间长度（单位：秒）
    int sampling_numberlong;    // 采样数据量

private:
    int sampling_frequency;     // 采样率（单位：Hz）
    double domain_min;          // 域的范围
    double domain_max;

public:
    // 构造函数
    TRAJDataSet();
    TRAJDataSet(std::vector<double>* matrix, int timelong);

    // 设置采样时间长度
    void setSamplingTimelong(int timelong);

    // 获取采样率
    void getSamplingFrequency(const char* stringLog) const;
    int getSamplingFrequency() const;

    // 获取轨迹的域
    void getTrajectoryDomain(const char* stringLog) const;
    std::vector<double> getTrajectoryDomain() const;

private:
    // 更新采样率
    void updateSamplingFrequency();

    // 确认轨迹的域
    void setTrajectoryDomain(std::vector<double>* matrix);

};
