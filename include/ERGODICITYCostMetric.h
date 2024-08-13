#pragma once

#include "FOURIERBasis.h"

class ERGODICITYCostMetric :
    public FOURIERBasis
{
public:
    int k_resolution;
    int agents_expertnumber;

public:
    ERGODICITYCostMetric();
    ERGODICITYCostMetric(int k_r);

    double FitMetric(double* xp1, double* xp2, double** phi_r);

    double** FitSigmak(double* xp1, double* xp2);

};

