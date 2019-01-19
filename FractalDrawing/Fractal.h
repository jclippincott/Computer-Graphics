/*
 * Fractal.h
 *
 *  Created on: Aug 31, 2017
 *      Author: Jesse
 */

#ifndef FRACTAL_H_
#define FRACTAL_H_
#include <cmath>
#include <iostream>
#include <iomanip>

class Fractal {
public:
	Fractal();
	virtual ~Fractal();
};

class ComplexNum {
private:
	float real;
	float imag;

public:


	ComplexNum()
	{
		real=0;
		imag=0;
	}
	ComplexNum(float a,float b)
	{
		real=a;
		imag=b;
	}

	void setNewVal(ComplexNum x)
	{
		real = x.getReal();
		imag = x.getImag();
	}

	ComplexNum add(ComplexNum x)
	{
		ComplexNum temp(0,0);
		temp.real = real + x.getReal();
		temp.imag = imag + x.getImag();
		return temp;
	}

	ComplexNum subtract(ComplexNum x)
	{
		ComplexNum temp(0,0);
		temp.real = real - x.getReal();
		temp.imag = imag - x.getImag();
		return temp;
	}

	ComplexNum multiply(ComplexNum x)
	{
		ComplexNum temp(0,0);
		temp.real = (real*x.getReal()) - (imag*x.getImag());
		temp.imag = (real*x.getImag()) + (imag*x.getReal());
		return temp;
	}

	ComplexNum divide(ComplexNum x)
	{
		float divisor = pow((x.getReal()),2.0) + pow((x.getImag()), 2.0);
		ComplexNum temp(0,0);
		temp.real = ((real*x.getReal()) + (imag*x.getImag()))/divisor;
		temp.imag = ((imag*x.getReal()) + (real*x.getImag()))/divisor;
		return temp;
	}

	void squared()
	{
		float tempReal = real;
		float tempImag = imag;
		real = (tempReal*tempReal)-(tempImag*tempImag);
		imag = 2*tempReal*tempImag;
	}

	float getMagnitude()
	{
		float tempA = pow(real,2);
		float tempB = pow(imag,2);
		return sqrt(tempA + tempB);
	}

	float getReal()
	{
		return real;
	}

	float getImag()
	{
		return imag;
	}

	void setReal(float x)
	{
		real=x;
	}

	void setImag(float x)
	{
		imag=x;
	}
};

#endif /* FRACTAL_H_ */
