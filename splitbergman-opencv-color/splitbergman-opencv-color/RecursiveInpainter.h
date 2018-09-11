#pragma once

#include "pch.h"

#include "SplitBergmanSolver.h"
#include "MergeResult.h"

Mat RecusriveInpainter(Mat original_image, Mat inpainted_domain, double lambda, double theta, double tolerant, int max_iteration, int max_step, int current_step)
{
	Mat toinpaint_image;
	if (current_step < max_step) {
		int height = original_image.rows;
		int width = original_image.cols;
		Mat half_image, half_domain, half_result, upscale_result;
		resize(original_image, half_image, cv::Size(width * 0.5, height * 0.5));
		resize(inpainted_domain, half_domain, cv::Size(width * 0.5, height * 0.5));
		half_result = RecusriveInpainter(half_image, half_domain, lambda, theta, tolerant, max_iteration, max_step, current_step + 1);
		resize(half_result, upscale_result, cv::Size(width, height));
		toinpaint_image = MergeResult(original_image, inpainted_domain, upscale_result);
	}
	else {
		toinpaint_image = original_image;
	}
	Mat inpainted_lambda = (inpainted_domain == 0);
	inpainted_lambda.convertTo(inpainted_lambda, CV_64F);
	inpainted_lambda = inpainted_lambda / 255.0 * lambda;
	if (current_step != 1) {
		if (current_step == max_step) {
			max_iteration = 10;
		}
		else {
			max_iteration = 3;
		}
	}
	/*if (current_step == 1) {
		return toinpaint_image;
	}*/
	return SplitBergmanSolver(toinpaint_image, inpainted_lambda, theta, tolerant, max_iteration, current_step);
}