#include <iostream>
using namespace std;

template <class T>
class Matrice
{
	T** _matrice;
	int _nrLinii;
	int _nrColoane;
public:
	
	Matrice() :
		_nrLinii(0),
		_nrColoane(0)
	{
		_matrice = NULL;
	}				

	Matrice(int linii, int coloane) :
		_nrLinii(linii),
		_nrColoane(coloane)
	{
		_matrice = new T*[linii];
		for (int i = 0; i < linii; i++)
		{
			_matrice[i] = new T[coloane];
			for (int j = 0; j < coloane; j++)
			{
				_matrice[i][j] = T();
			}
		}
	}
	Matrice(Matrice<T> &matrix)
	{
		_nrLinii = 0;
		_nrColoane = 0;
		_matrice = NULL;
		*this = matrix;
	}
	~Matrice() 
	{
		for (int i = 0; i < _nrLinii; i++)
		{
			delete[] _matrice[i];
		}
		delete[] _matrice;
	}
	const int getNrLinii();												  
	const int getNrColoane();											  
	Matrice<T> operator +(const Matrice<T> & matrix)const;					  
	T* operator[](int linie);										      
	Matrice<T> operator -(const Matrice<T> & matrix)const;					  
	Matrice<T> operator *(const Matrice<T> & matrix)const;					  
	Matrice<T> operator *(T numar)const;								     
	friend Matrice operator * (T numar, Matrice& matrix)
	{
		Matrice<T> aux(matrix.getNrLinii(), matrix.getNrColoane());
		for (int i = 0; i < matrix.getNrLinii(); i++)
		{
			for (int j = 0; j < matrix.getNrColoane(); j++)
			{
				aux._matrice[i][j] = numar*matrix[i][j];
			}
		}
		return aux;
	}
	Matrice & operator =(const Matrice & matrix);						  
	T determinant();												  
	bool inversabilitate();											     
	void matriceOrdinInferiorLinie(int linie);                            
	void matriceOrdinInferiorColoana(int coloana);                        
	void matriceOrdinInferiorLinieSiColoana(int linie, int coloana);      

	friend istream& operator >>(istream & input, Matrice & matrix)
	{
		if (matrix._nrLinii == 0 || matrix._nrColoane == 0)
		{
			throw ("Eroare! Matricea este nula!");
		}
		else
		{
			for (int i = 0; i < matrix._nrLinii; i++)
			{
				for (int j = 0; j < matrix._nrColoane; j++)
				{
					input >> matrix._matrice[i][j];
				}
			}
			return input;
		}
	}

	friend ostream & operator <<(ostream & output, Matrice & matrix)
	{
		if (matrix._nrLinii == 0 || matrix._nrColoane == 0)
			output << "Matricea este nula!" << endl;
		else
		{
			for (int i = 0; i < matrix._nrLinii; i++)
			{
				for (int j = 0; j < matrix._nrColoane; j++)
				{
					output << matrix._matrice[i][j] << " ";
				}
				output << endl;
			}
		}
		return output;
	}
};



template <class T>
const int Matrice<T>::getNrLinii()
{
	return _nrLinii;
}

template <class T>
const int Matrice<T>::getNrColoane()
{
	return _nrColoane;
}

template <class T>
Matrice<T> Matrice<T>::operator +(const Matrice<T> & matrix) const
{
	//Trebuie sa ne asiguram ca adunarea a doua matrici este posibila,
	//adica cele doua matrice sa aiba acelasi numar de linii, respectiv acelasi numar de coloane.
	if (_nrLinii != matrix._nrLinii || _nrColoane != matrix._nrColoane)
	{
		throw ("Eroare! Cele doua matrici nu au acelasi numar de linii sau de coloane!");
	}
	else
	{
		Matrice<T> aux(_nrLinii, _nrColoane);
		for (int i = 0; i < _nrLinii; i++)
		{
			for (int j = 0; j < _nrColoane; j++)
			{
				aux._matrice[i][j] = _matrice[i][j] + matrix._matrice[i][j];
			}
		}
		return aux;
	}
}

template <class T>
T* Matrice<T>::operator[](int linie)
{
	//_matrice este de tip int** (sau "un vector de vectori"), deci returnand _matrice[linie] returnez un int*. 
	return _matrice[linie];
}

template <class T>
Matrice<T> Matrice<T>::operator -(const Matrice<T> & matrix) const
{
	//Trebuie verificata aceeasi conditie ca la operatorul "+" pentru adunarea a doua matrici
	//si anume ca ambele sa aiba acelasi numar de linii, respectiv coloane;
	if (_nrLinii != matrix._nrLinii || _nrColoane != matrix._nrColoane)
	{
		throw ("Eroare! Matricele nu au acelasi numar de linii/coloane!");
	}
	else
	{
		Matrice<T> aux(_nrLinii, _nrColoane);
		for (int i = 0; i < _nrLinii; i++)
		{
			for (int j = 0; j < _nrColoane; j++)
			{
				aux._matrice[i][j] = _matrice[i][j] - matrix._matrice[i][j];
			}
		}
		return aux;
	}
}

template <class T>
Matrice<T> Matrice<T>::operator *(T numar) const
{
	Matrice<T> aux(_nrLinii, _nrColoane);
	for (int i = 0; i < _nrLinii; i++)
	{
		for (int j = 0; j < _nrColoane; j++)
		{
			aux._matrice[i][j] = numar*_matrice[i][j];
		}
	}
	return aux;
}


template <class T>
Matrice<T> Matrice<T>::operator *(const Matrice<T> & matrix) const
{
	Matrice<T> aux(_nrLinii, matrix._nrColoane);
	for (int i = 0; i < _nrLinii; i++)
	{
		for (int j = 0; j < matrix._nrColoane; j++)
		{
			for (int l = 0; l < matrix._nrColoane; l++)
			{
				aux._matrice[i][j] += _matrice[i][l] * matrix._matrice[l][j];
			}
		}
	}
	return aux;
}

template <class T>
Matrice<T> & Matrice<T>::operator =(const Matrice<T> & matrix)
{
	//Daca matricea in care atribui ceva deja exista, nu pot aloca din nou memorie pentru acelasi obiect, asa ca mai intai dezaloc tot ce se afla deja la memoria respectiva
	//apoi aloc memorie pentru a putea atribui alt obiect de tip Matrice.
	if (_matrice != NULL)
	{
		for (int i = 0; i < _nrLinii; i++)
		{
			delete[] _matrice[i];
		}
		delete[] _matrice;
	}

	_nrLinii = matrix._nrLinii;
	_nrColoane = matrix._nrColoane;
	_matrice = new T*[_nrLinii];
	for (int i = 0; i < _nrLinii; i++)
	{
		_matrice[i] = new T[_nrColoane];
		for (int j = 0; j < _nrColoane; j++)
		{
			_matrice[i][j] = matrix._matrice[i][j];
		}
	}
	return *this;
}

template <class T>
T Matrice<T>::determinant()
{
	//Verific daca matricea este paratica, altfel nu pot calcula determinantul.
	if (_nrLinii != _nrColoane)
	{
		throw ("Eroare! Matricea nu este patratica!");
	}

	//Functia mea este recursiva, iar acest if este conditia de oprire deoarece stiu sa calculez deterinantul unei matrice de gradul 2.
	if (_nrLinii == 2)
	{
		return (_matrice[0][0] * _matrice[1][1] - _matrice[0][1] * _matrice[1][0]);
	}

	//"d" reprezinta valoarea determinantului la fiecare apel al functiei.
	//Construiesc o copie a obiectului curent pentru a nu-l modifica.
	//Calculez determinantul de ordin n dezvoltand dupa prima linie si construiesc determinantii (matricele) de ordin inferior.
	//Valoarea determinantului se calculeaza dupa formula: primul element de pe linia dupa care dezvold * -1 la puterea i+j 
	//( unde i si j sunt pozitiile in matrice) * determinantul de ordin inferior rezultat din eliminarea primei linii si coloanei curente. 
	//"aux.determinant()" -> apelez functia determinant() pentru matricea mea auxiliara (rezultata din eliminarea unei linii si unei coloane din matricea initiala (this)),
	//iar la reapelare matricea auxiliara va fi o copie a matricei de ordin inferior din apelul anterior, copie din care voi construi alta matrice de ordin inferior
	//pana voi ajunge la o matrice de ordin 2 unde ii pot calcula determinantul fara artificii. CU aceasta valoare ma intorc in apelul anterior si calculez valoarea determinantului
	//dupa formula "d += _matrice[0][i] * pow(-1, i)* aux.determinant()" si returnez aceasta valoarea cu care ma intorc in apelurile functiei pana se termina for-ul.
	//Valoarea finala returnata va fi valoarea determinantului cautat. 

	T d = 0;
	for (int i = 0; i < _nrColoane; i++)
	{
		Matrice<T> aux = *this;
		aux.matriceOrdinInferiorLinieSiColoana(1, i + 1);
		d += _matrice[0][i] * (int)pow(-1, i)* aux.determinant();
	}
	return d;
}

template <class T>
bool Matrice<T>::inversabilitate()
{
	if (_nrLinii != _nrColoane || determinant() == 0)
	{
		return false;
	}
	return true;
}

template <class T>
void Matrice<T>::matriceOrdinInferiorLinie(int linie)
{
	Matrice<T> aux(_nrLinii - 1, _nrColoane);
	for (int i = 0, k = 0; i < _nrLinii, k < _nrLinii - 1; i++, k++)
	{
		if (i == linie - 1)
		{
			i++;
		}

		for (int j = 0; j < _nrColoane; j++)
		{
			aux._matrice[k][j] = _matrice[i][j];
		}
	}
	*this = aux;
}

template <class T>
void Matrice<T>::matriceOrdinInferiorColoana(int coloana)
{
	Matrice<T> aux(_nrLinii, _nrColoane - 1);
	for (int i = 0; i < _nrLinii; i++)
	{
		for (int j = 0, k = 0; j < _nrColoane; j++, k++)
		{
			if (j == coloana - 1)
			{
				j++;
			}
			aux._matrice[i][k] = _matrice[i][j];
		}
	}
	*this = aux;
}

template <class T>
void Matrice<T>::matriceOrdinInferiorLinieSiColoana(int linie, int coloana)
{
	matriceOrdinInferiorLinie(linie);
	matriceOrdinInferiorColoana(coloana);
}

