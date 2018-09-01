#pragma once
#include "stdafx.h"

Mat MultiplyMatrixElement(Mat A, Mat B) {
	int i, j;
	int height = A.rows;
	int width = A.cols;
	Mat result = A.clone();
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			result.at<double>(i, j) *= B.at<double>(i, j);
		}
	}
	return result;
}
