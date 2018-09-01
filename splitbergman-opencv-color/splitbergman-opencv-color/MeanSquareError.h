#pragma once
#include "pch.h"
double MeanSquareError(Mat input, Mat reference) {
	double sum = 0.0;
	double diff = 0;
	int height = input.rows;
	int width = input.cols;
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			diff = input.at<double>(i, j) - reference.at<double>(i, j);
			sum += diff * diff;
		}
	}
	sum = sum / (height*width);
	return sum;
}