#pragma once
#include "pch.h"
#include "uGaussKernel.h"
#include "Divergence.h"

//TODO: Blurly bug, don't know why
Mat uSolver(Mat u, Mat w, Mat original_image, Mat b, Mat lambda,double theta) {
	int height = u.rows;
	int width = u.cols;
	int channel = u.channels();
	int rowsize = width * channel;
	int i, j, k;
	Mat divergence = Divergence(w - b);
	//Data conversation
	double* _u = (double*)u.data;
	double* _d = (double*)divergence.data;
	double* _f = (double*)original_image.data;
	double* _l = (double*)lambda.data;	
	double* _u_prev; //previous row
	double* _u_next; //next row
	_u_next = _u + rowsize;
	//top - left corner
	for (i = 0; i < channel; i++) {
		_u[i] = uGaussKernel(_u[i],_f[i],_l[i],theta,_d[i],_u[i],_u[i+channel],_u[i],_u_next[i]);
	}
	//top-bar line
	for (i = channel; i < rowsize - channel; i++) {
		_u[i] = uGaussKernel(_u[i], _f[i], _l[i], theta, _d[i], _u[i - channel], _u[i + channel], _u[i], _u_next[i]);
	}
	//top - right corner
	for (i = rowsize - channel; i < rowsize; i++) {
		_u[i] = uGaussKernel(_u[i], _f[i], _l[i], theta, _d[i], _u[i - channel], _u[i], _u[i], _u_next[i]);
	}
	//body
	for (k = 1; k < height-1; k++) {
		// new line on memory;
		_u_prev = _u;
		_u += rowsize; 
		_u_next += rowsize;
		_d += rowsize;
		_f += rowsize;
		_l += rowsize;
		//body - front
		for (i = 0; i < channel; i++) {
			_u[i] = uGaussKernel(_u[i], _f[i], _l[i], theta, _d[i], _u_prev[i], _u[i + channel], _u[i], _u_next[i]);
		}
		//body - interior
		for (i = channel; i < rowsize - channel; i++) {
			_u[i] = uGaussKernel(_u[i], _f[i], _l[i], theta, _d[i], _u[i - channel], _u[i + channel], _u_prev[i], _u_next[i]);			
		}
		//body - rear
		for (i = rowsize - channel; i < rowsize; i++) {
			_u[i] = uGaussKernel(_u[i], _f[i], _l[i], theta, _d[i], _u[i - channel], _u[i], _u[i + channel], _u_next[i]);
		}
	}
	// new line on memory;
	_u_prev = _u;
	_u += rowsize;
	_d += rowsize;
	_f += rowsize;
	_l += rowsize;
	//bottom-left
	for (i = 0; i < channel; i++) {
		_u[i] = uGaussKernel(_u[i], _f[i], _l[i], theta, _d[i], _u[i], _u[i + channel], _u_prev[i], _u[i]);
	}
	//bottom - bar line
	for (i = channel; i < rowsize - channel; i++) {
		_u[i] = uGaussKernel(_u[i], _f[i], _l[i], theta, _d[i], _u[i - channel], _u[i + channel], _u_prev[i], _u[i]);
	}
	//bottom-right
	for (i = rowsize - channel; i < rowsize; i++) {
		_u[i] = uGaussKernel(_u[i], _f[i], _l[i], theta, _d[i], _u[i - channel], _u[i], _u_prev[i], _u[i]);
	}
	return u;
}