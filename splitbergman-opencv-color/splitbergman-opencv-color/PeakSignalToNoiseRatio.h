#pragma once
#include "pch.h"
#include "MeanSquareError.h"
#include <cmath>

double PeakSignalToNoiseRatio(Mat input, Mat refererence) {
	double MSE = MeanSquareError(input, refererence);
	return 10 * log10(1/MSE); //if use [0-255] please change 1 to 255*255
}