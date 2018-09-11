// splitbergman-opencv-color.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "SplitBergmanSolver.h"
#include "RecursiveInpainter.h"


void TestTask();
void TestOpenCV();
void TestSplitBergman();

int main()
{
	//Variable Configuration
	double lambda_value = 250;
	double theta = 5;
	double tolerant = 5*1e-4;
	int max_iteration = 10000;

	//load image
	Mat imageToInpaintUint8 = imread("../../images/256x256_color/case2_toinpaint.png");
	Mat imageInpaintDomainUint8 = imread("../../images/256x256_color/case2_inpaintdomain.png");
	//Covert to 64FC3 for faster convergence
	Mat toInpaint = imageToInpaintUint8;
	Mat inpaintDomain = imageInpaintDomainUint8;
	toInpaint.convertTo(toInpaint, CV_64FC3, 1/255.0);	
	
	Mat inpaintDomains[3];
	split(inpaintDomain, inpaintDomains);

	
	
	//Inpainting In Progress
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	Mat toInpaints[3];
	split(toInpaint, toInpaints);
	Mat results[3];
	for (int i = 0; i < 3; i++) {
		//Mat inpainted_lambda = (inpaintDomains[i] == 0);
		//inpainted_lambda.convertTo(inpainted_lambda, CV_64F);
		//inpainted_lambda = inpainted_lambda / 255.0 * lambda_value;
		//results[i] = SplitBergmanSolver(toInpaints[i], inpainted_lambda, theta, tolerant, max_iteration,1);
		results[i] = RecusriveInpainter(toInpaints[i], inpaintDomains[i],lambda_value,theta,tolerant, max_iteration, 2,1);
	}
	Mat resultImage;
	merge(results, 3, resultImage);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	printf("Split bergman inpainted time: %.6f\n", (duration / 1000000.0));	
	//Convert Back to U8C3 color
	resultImage.convertTo(resultImage, CV_8UC3, 255.0);
	imshow("Result", resultImage);
	waitKey(0);

}

