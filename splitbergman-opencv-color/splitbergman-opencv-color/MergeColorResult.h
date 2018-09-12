#pragma once

#include "pch.h"


Mat MergeColorResult(Mat original_image, Mat inpainted_domain, Mat upscale_result)
{
	int i, j;
	int height = original_image.rows;
	int width = original_image.cols;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (inpainted_domain.at<uchar>(i, j) > 0) {
				original_image.at<Vec3d>(i, j) = upscale_result.at<Vec3d>(i, j);
			}
		}
	}
	return original_image;
}