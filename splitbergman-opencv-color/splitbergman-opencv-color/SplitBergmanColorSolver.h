#pragma once
#include "pch.h"
#include "SplitBergmanSolver.h"

Mat SplitBergmanColorSolver(Mat toinpaint_image,Mat inpaint_domain,double lambda,double theta,int depth,double tolerant,double omega,int max_gauss_seidel,int max_iteration)
{
	int i;
	int channel = toinpaint_image.channels();
	Mat toInpaints[3],results[3],result;
	split(toinpaint_image, toInpaints);
	for (i = 0; i < 3; i++) {
		results[i] = SplitBergmanSolver(toInpaints[i], inpaint_domain, lambda, theta, depth, tolerant, omega, max_gauss_seidel, max_iteration);
	}
	merge(results, 3, result);
	return result;
}