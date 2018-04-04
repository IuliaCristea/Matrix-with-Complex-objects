#include<iostream>
#include "Complex.hpp"
using namespace std;

Complex::Complex(double re, double im)
{
	_re = new double(re);
	_im = new double(im);
}

Complex::Complex(const Complex& newComplex)
{
	_re = new double(*newComplex._re);
	_im = new double(*newComplex._im);
}

Complex::~Complex()
{
	delete(_re);
	delete(_im);
}

Complex Complex::operator +(const Complex & arg) const
{
	return Complex((*_re) + (*arg._re), (*_im) + (*arg._im));
}

Complex Complex::operator +(const int arg) const
{
	return Complex((*_re) + arg, (*_im));
}

Complex Complex::operator -(const Complex & arg) const
{
	return Complex((*_re) - (*arg._re), (*_im) - (*arg._im));
}

Complex Complex::operator -(const int arg) const
{
	return Complex((*_re) - arg, (*_im));
}

Complex & Complex::operator =(const Complex & arg)
{
	(*_re) = (*arg._re);
	(*_im) = (*arg._im);
	return *this;
}

bool Complex::operator ==(const Complex & arg)
{
	return ((*_re) == (*arg._re) && (*_im) == (*arg._im));
}

Complex::operator double() const
{
	return (*_re);
}

Complex::operator bool() const
{
	return((*_re) && (*_im));
}

void Complex::afisare()
{
	cout << (*_re) << " + " << (*_im) << "i" << endl;
}

Complex operator +(const int b, const Complex & a)
{
	return Complex(b + (*a._re), (*a._im));
}

Complex operator -(const int b, const Complex & a)
{
	return Complex(b - (*a._re), (*a._im));
}

istream& operator>>(istream & input, Complex & complex)
{
	input >> (*complex._re) >> (*complex._im);
	return input;
}

ostream& operator<<(ostream & output, Complex & complex)
{
	output <<(*complex._re) <<" + i"<< (*complex._im);
	return output;
}