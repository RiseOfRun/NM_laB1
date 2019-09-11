// NM1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <math.h>
#include <cstdio>
#include <fstream>

typedef float form;

class Matrix
{
public:
	form **A;
	int n;
	int m;
	int k;

	Matrix(int n, int m)
	{
		this->n = n;
		this->m = m;
		k = m / 2;
		A = new form*[n];
		for (int i = 0; i < n; i++)
		{

			A[i] = new form[m];
			for (int j = 0; j < m; j++)
			{
				A[i][j] = 0;
			}
		}
	}

	Matrix(std::ifstream fi, int n, int m)
	{
		fi.open("input.txt");
		A = new form*[n];
		for (int i = 0; i < n; i++)
		{
			this->n = n;
			this->m = m;
			k = m / 2;
			A[i] = new form[m];
			for (int j = 0; j < m; j++)
			{
				fi >> A[i][j];
			}
		}
	}

	Matrix(Matrix *M)
	{
		A = M->A;
		this->k = M->k;
		this->m = M->m;
		this->n = M->n;
	}

	form & operator ()(const int &row, const int &column) const
	{
		bool contains = false; //проверить
		if (abs(row - column) > k)
		{
			form tmp = 0;
			return tmp;
		}
		int di = k + 1;
		return A[row][di - row + column];
	}

	/*form operator ()(const int i, const int j) const
	{
		return 0;
	}*/
};


int main()
{

	Matrix M(3, 4);
	M(2, 2) = 4;
	Matrix L(M);
	Matrix U(M);
	M(2, 2) = 5;
	for (int i = 0; i < M.n; i++)
	{
		form sum = 0;
		for (int k = abs(i - (M.k + 1)); k < i; k++)
		{
			sum += L(i, k)*U(k, i);
		}
		U(i, i) = M(i, i) - sum;
		for (int j = i + 1; j < i + M.k&&j < M.n; j++)
		{
			sum = 0;
			form sum2 = 0;
			for (int k = i - M.k + 1; k < i; k++)
			{
				sum += L(i, k)*U(k, j);
			}
			U(i, j) = M(i, j) - sum;

			sum = 0;
			for (int k = i - M.k + 1; k < i; k++)
			{
				sum += L(j, k)*U(k, i);
			}
			L(j,i) = (M(j, i) - sum) / U(i, i);
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
