#pragma once

class FOURIERBasis
{
	//��ʼ���б��ʹ��������
public:
	double domainUX;//private�̳��಻�ܼ̳У�
	double domainUZ;
	int agents_sampling_numberlong;
	int agents_sampling_timglong;

public:
	FOURIERBasis(double UX, double UZ, int sampling_numberlong, int sampling_timglong);
	/*����������ж�����һ���������Ĺ��캯������û�ж���Ĭ�Ϲ��캯����
	�������������Զ�����Ĭ�Ϲ��캯�����������û��Ĭ�Ϲ��캯��������
	����Ĺ��캯������ʽ���ô������Ļ��๹�캯�������������ᱨ����
	Ϊ���޷��ҵ����ʵĹ��캯������ʼ�����ಿ�֡�*/
	FOURIERBasis();

	double FitFourierBasis(double rp1, double rp2, double* xp1, double* xp2);

	double FitAllHk(double rp1, double rp2);

private:
	//double FitInnerFunction(double x, double y);

};

