#pragma once

#include "pch.h"

#include "SplitBergmanColorSolver.h"
#include "MergeColorResult.h"
Mat RecursiveColorInpainter(Mat original_image,Mat inpaint_domain,double lambda, double theta,
	double tolerant, double omega,int max_gauss_seidel,int multi_coarse,int multi_mid,int multi_fine,int max_step,int current_step)
{
	Mat toinpaint_image;
	if (current_step < max_step) {
		int height = original_image.rows;
		int width = original_image.cols;
		Mat half_image, half_domain, half_result, upscale_result;
		resize(original_image, half_image, Size(width * 0.5, height * 0.5));
		resize(inpaint_domain, half_domain, Size(width * 0.5, height * 0.5));
		half_result = RecursiveColorInpainter(half_image, half_domain, lambda, theta, tolerant, omega, max_gauss_seidel, multi_coarse, multi_mid, multi_fine, max_step, current_step + 1);
		resize(half_result, upscale_result, Size(width, height));
		toinpaint_image = MergeColorResult(original_image, inpaint_domain, upscale_result);
	}
	else {
		toinpaint_image = original_image;
	}
	int max_iteration = multi_fine;
	if (current_step != 1) {
		if (current_step == max_step) {
			max_iteration = multi_coarse;
		}
		else {
			max_iteration = multi_mid;
		}
	}
	return SplitBergmanColorSolver(toinpaint_image, inpaint_domain, lambda, theta, current_step, tolerant, omega, max_gauss_seidel, max_iteration);
}