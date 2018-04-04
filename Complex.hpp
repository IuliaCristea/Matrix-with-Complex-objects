#pragma once
#include<iostream>
using namespace std;

class Complex
{
private:
	double* _re;
	double* _im;
public:
	Complex(double re = 0, double im = 0);
	Complex(const Complex& complex);
	Complex operator +(const Complex &) const;
	Complex operator +(const int) const;
	Complex operator -(const Complex &) const;
	Complex operator -(const int) const;
	Complex operator *(const int) const { Complex ob; return ob; };
	Complex & operator =(const Complex &);
	bool operator ==(const Complex &);
	void afisare();
	operator double() const;
	operator bool() const;
	friend Complex operator +(const int, const Complex &);
	friend Complex operator -(const int, const Complex &);
	friend istream& operator>>(istream & input, Complex & complex);
	friend ostream& operator<<(ostream & output, Complex & complex);
	~Complex();
};