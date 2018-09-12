// splitbergman-opencv-color.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "SplitBergmanSolver.h"
#include "RecursiveColorInpainter.h"


void TestTask();
void TestOpenCV();
void TestSplitBergman();

int main()
{
	//Variable Configuration
	double lambda = 250;
	double theta = 5;
	double omega = 1.0;
	
	// loop termination properties
	double tolerant = 5 * 10e-6;
	int multi_fine = 100;
	int multi_mid = 3;
	int multi_coarse = 10000;
	int multi_depth = 4;
	int max_gauss_seidel = 1;
	int depth = 1;

	//load image
	Mat inpaintDomain = imread("../../images/256x256_color/case2_inpaintdomain.png", CV_LOAD_IMAGE_GRAYSCALE);
	Mat toInpaint = imread("../../images/256x256_color/case2_toinpaint.png");
	toInpaint.convertTo(toInpaint, CV_64FC3, 1/255.0);	
	
	//Inpainting In Progress
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	Mat resultImage = RecursiveColorInpainter(toInpaint, inpaintDomain, lambda, theta, tolerant, omega, max_gauss_seidel, multi_coarse, multi_mid, multi_fine, multi_depth, 1);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	printf("Split bergman inpainted time: %.6f\n", (duration / 1000000.0));	
	//Convert Back to U8C3 color
	resultImage.convertTo(resultImage, CV_8UC3, 255.0);
	imshow("Result", resultImage);
	waitKey(0);

}

