#include <iostream>
#include <iomanip>
#include <conio.h>
#include <objbase.h>
#include <string>
#include "Intface.h"

using namespace std;

class AEqualsZeroException {};
class NegativeDescriminantException {};
class EmptyStringException {};

int menu()
{
	int choice;

	cout << "Choose your destiny:" << endl << "1.Number of roots" << endl << "2.Solve Equation" << endl << "3.WhoAmI" << endl << "4.Exit" << endl << ">>";
	cin >> choice;

	return choice;
}

void input(double* a, double* b, double* c)
{
	cout << "A: ";
	cin >> *a;
	cout << "B: ";
	cin >> *b;
	cout << "C: ";
	cin >> *c;
}

int main()
{
	::CoInitialize(NULL);

	INumRoots* pNumRoots = NULL;
	ISolveEquat* pSolveEquat = NULL;
	IWho* pWho = NULL;

	HRESULT hr = ::CoCreateInstance(CLSID_Component, NULL, CLSCTX_INPROC_SERVER, IID_INumRoots, (void**)&pNumRoots);
	HRESULT hrSolve;
	HRESULT hrWho;

	if (SUCCEEDED(hr))
	{
		cout << "Succeeded getting INumRoot." << endl << endl;
		for (;;) {
			int choice;
			double a;
			double b;
			double c;
			double x1;
			double x2;
			double num;
			string name;
			string helloName;

			choice = menu();

			try
			{
				switch (choice)
				{
				case 1:
					input(&a, &b, &c);
					pNumRoots->num_of_roots(a, b, c, &num);
					
					cout << "Number of root(s): " << num << endl;
					break;
				case 2:
					input(&a, &b, &c);

					if (pSolveEquat == NULL) 
					{
						hrSolve = pNumRoots->QueryInterface(IID_ISolveEquat, (void**)&pSolveEquat);
					}
					
					if (SUCCEEDED(hrSolve))
					{
						cout << "Succeeded getting ISolveEquat." << endl;
						pSolveEquat->solve_equation(a, b, c, &x1, &x2);
						cout << "X1 = " << x1 << endl << "X2 = " << x2 << endl;
					}
					else
					{
						cout << "Could not get the interface ISolveEquat" << endl;
					}
					
					break;
				case 3:
					cout << "Input your name: ";
					cin.ignore();
					getline(cin, name);

					if (pWho == NULL) 
					{
						hrWho = pNumRoots->QueryInterface(IID_IWho, (void**)&pWho);
					}

					if (SUCCEEDED(hrWho)) 
					{
						cout << "Succeeded getting IWho." << endl;
						pWho->WhoAmI(name, &helloName);
						cout << helloName << endl;
					}
					else
					{
						cout << "Could not get the interface IWho" << endl;
					}

					break;
				case 4:
					CoUninitialize();
					return 0;
				default:
					break;
				}
			}
			catch (AEqualsZeroException)
			{
				cout << "A shouldn't been equal to \"0\"" << endl;
			}
			catch (NegativeDescriminantException)
			{
				cout << "Equation has no roots" << endl;
			}
			catch (EmptyStringException)
			{
				cout << "Hello, Noname" << endl;
			}
			catch (...) {
				cout << "Unknown error" << endl;
			}
		}
	}
	else
	{
		cout << "Can't create instance of component!" << endl;
	}

	CoUninitialize();

	return 0;
}