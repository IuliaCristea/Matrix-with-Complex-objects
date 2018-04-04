#include <iostream>
#include "Matrice.hpp"
#include "Complex.hpp"
using namespace std;

int main()
{
	Matrice<Matrice<Matrice<Matrice<int>>>> a(2,2);
	
	cin >> a;

	return 0;
}