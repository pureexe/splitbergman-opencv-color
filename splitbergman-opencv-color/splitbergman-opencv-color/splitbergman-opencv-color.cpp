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
	int max_iteration = 10;

	//load image
	Mat imageToInpaintUint8 = imread("../../images/256x256_color/caseA_toinpaint.png");
	Mat imageInpaintDomainUint8 = imread("../../images/256x256_color/caseA_inpaintdomain.png");
	//Covert to 64FC3 for faster convergence
	Mat toInpaint = imageToInpaintUint8;
	Mat inpaintDomain = imageInpaintDomainUint8;
	toInpaint.convertTo(toInpaint, CV_64FC3);	
	toInpaint /= 255.0;
	
	/*Mat lambda = (inpaintDomain == 0);
	lambda.convertTo(lambda, CV_64FC3);
	lambda *= lambda_value;	
	
	Mat lambdas[3];
	split(lambda, lambdas);
	*/
	
	Mat inpaintDomains[3];
	split(inpaintDomain, inpaintDomains);

	
	
	//Inpainting In Progress
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	Mat toInpaints[3];
	split(toInpaint, toInpaints);
	Mat results[3];
	for (int i = 0; i < 3; i++) {
		//results[i] = SplitBergmanSolver(toInpaints[i], lambdas[i], theta, tolerant, max_iteration);
		results[i] = RecusriveInpainter(toInpaints[i], inpaintDomains[i],lambda_value,theta,tolerant, max_iteration, 4,1);
	}
	Mat resultImage;
	merge(results, 3, resultImage);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	printf("Split bergman inpainted time: %.6f\n", (duration / 1000000.0));	
	//Convert Back to U8C3 color
	resultImage *= 255;
	resultImage.convertTo(resultImage, CV_8UC3);
	imshow("Result", resultImage);
	waitKey(0);

}

