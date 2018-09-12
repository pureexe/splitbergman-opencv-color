#pragma once
#include "pch.h"
double uGaussKernel(double u, double z, double lambda, double theta, double divergence, double omega,int depth, double u_left, double u_right, double u_above, double u_under)
{
	double h = pow(2, depth - 1);
	double lapacian = (1 / pow(h,2))*(u_left + u_right + u_above + u_under); 
	double buffer = lambda * z - theta * divergence + theta * lapacian;
	double u_new = (pow(h,2) / (lambda * pow(h, 2) + 4 * theta))*buffer;
	return (1 - omega)*u + omega * u_new;
}

