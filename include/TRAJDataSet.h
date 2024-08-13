#pragma once

#include <vector>

class TRAJDataSet
{
public:
    int sampling_timelong;      // ����ʱ�䳤�ȣ���λ���룩
    int sampling_numberlong;    // ����������

private:
    int sampling_frequency;     // �����ʣ���λ��Hz��
    double domain_min;          // ��ķ�Χ
    double domain_max;

public:
    // ���캯��
    TRAJDataSet();
    TRAJDataSet(std::vector<double>* matrix, int timelong);

    // ���ò���ʱ�䳤��
    void setSamplingTimelong(int timelong);

    // ��ȡ������
    void getSamplingFrequency(const char* stringLog) const;
    int getSamplingFrequency() const;

    // ��ȡ�켣����
    void getTrajectoryDomain(const char* stringLog) const;
    std::vector<double> getTrajectoryDomain() const;

private:
    // ���²�����
    void updateSamplingFrequency();

    // ȷ�Ϲ켣����
    void setTrajectoryDomain(std::vector<double>* matrix);

};
