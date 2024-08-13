#pragma once

class FOURIERBasis
{
	//初始化列表的使用条件？
public:
	double domainUX;//private继承类不能继承？
	double domainUZ;
	int agents_sampling_numberlong;
	int agents_sampling_timglong;

public:
	FOURIERBasis(double UX, double UZ, int sampling_numberlong, int sampling_timglong);
	/*如果你在类中定义了一个带参数的构造函数，而没有定义默认构造函数，
	编译器不会再自动生成默认构造函数。如果基类没有默认构造函数，而派
	生类的构造函数不显式调用带参数的基类构造函数，编译器将会报错，因
	为它无法找到合适的构造函数来初始化基类部分。*/
	FOURIERBasis();

	double FitFourierBasis(double rp1, double rp2, double* xp1, double* xp2);

	double FitAllHk(double rp1, double rp2);

private:
	//double FitInnerFunction(double x, double y);

};

