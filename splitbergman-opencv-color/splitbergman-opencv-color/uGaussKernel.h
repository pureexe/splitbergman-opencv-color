#pragma once
#include "pch.h"
double uGaussKernel(double u, double z,double lambda, double theta, double divergence,
	double u_left, double u_right, double u_above, double u_under, int current_step)
{
	double h = pow(2,current_step-1);
	double lapacian = (1/h*h)*(u_left + u_right + u_above + u_under);
	double buffer = lambda * z - theta * divergence + theta * lapacian;
	return ((h*h) / (lambda*(h*h) + 4 * theta))*buffer;
}

/*
u(i,j) = (1-omega)*u(i,j)+omega*((lambda(i,j)*G(i,j)-theta_dot_grad_w_b(i,j))+(1/h^2)*...
(D(i, j)*(u(i + 1, j) + u(i, j + 1)) + D(i - 1, j)*u(i - 1, j) + D(i, j - 1)*u(i, j - 1))) / ...
(lambda(i, j) + (1 / h ^ 2)*(2 * D(i, j) + D(i - 1, j) + D(i, j - 1)));

u(i,j) = (lambda(i,j) * z(i,j) - theta*divergence(i,j))+(1/h^2) * (1*(u_above + u_right) + 1*u+under + 1*u_left)) / (lambda(i, j) + (1 / h ^ 2)*(2 * 1 + 1 + 1));
*/