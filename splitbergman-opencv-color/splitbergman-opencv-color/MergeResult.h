#pragma once

#include "pch.h"

string type2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

Mat MergeResult(Mat original_image, Mat inpainted_domain, Mat upscale_result)
{
	Mat upscale_condition = (inpainted_domain > 0) / 255.0;
	Mat original_condition = (inpainted_domain == 0) / 255.0;
	upscale_condition.convertTo(upscale_condition, CV_64F);
	original_condition.convertTo(original_condition, CV_64F);
	return  (upscale_result.mul(upscale_condition)) + (original_image.mul(original_condition));
}