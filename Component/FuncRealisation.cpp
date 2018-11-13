#include <iostream>
#include "FuncRealisation.h"
#include "GlobalElite.h"
#define TWOROOTS 2
#define ONEROOT 1
#define NOROOT 0

using namespace std;

FuncRealisation::FuncRealisation() : ref_count(1)
{
	InterlockedIncrement(&g_ComponentCount);
}

FuncRealisation::~FuncRealisation()
{
	InterlockedDecrement(&g_ComponentCount);
	cout << "Component: Destroy self." << endl;
}

double FuncRealisation::find_descr(double a, double b, double c)
{
	if (a == 0) {
		throw AEqualsZeroException();
	}

	double descr = b * b - 4 * a * c;

	return descr;
}

void __stdcall FuncRealisation::num_of_roots(double a, double b, double c, double* num)
{
	double descr = find_descr(a, b, c);

	if (descr > 0)
	{
		*num = TWOROOTS;
	}
	else if (descr == 0)
	{
		*num = ONEROOT;
	}
	else
	{
		*num = NOROOT;
	}
}

void __stdcall FuncRealisation::solve_equation(double a, double b, double c, double* x1, double * x2)
{
	double descr = find_descr(a, b, c);

	if (descr < 0) {
		throw NegativeDescriminantException();
	}

	*x1 = ((-b + sqrt(descr)) / (a / 2));
	*x2 = ((-b - sqrt(descr)) / (a / 2));
}

void __stdcall FuncRealisation::WhoAmI(std::string input, std::string* output)
{
	if (!input.compare(""))
		throw EmptyStringException();
	*output = "Hello, " + input;
}

HRESULT __stdcall FuncRealisation::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == IID_IUnknown)
	{
		*ppv = static_cast<INumRoots*>(this);
	}
	else if (iid == IID_INumRoots)
	{
		*ppv = static_cast<INumRoots*>(this);
		cout << "Component: Return pointer to INumRoots." << endl;
	}
	else if (iid == IID_ISolveEquat)
	{
		*ppv = static_cast<ISolveEquat*>(this);
		cout << "Component: Return pointer to ISolveEquat." << endl;
	}
	else if (iid == IID_IWho)
	{
		*ppv = static_cast<IWho*>(this);
		cout << "Component: Return pointer to IWho." << endl;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return S_OK;
}

ULONG __stdcall FuncRealisation::AddRef()
{
	return InterlockedIncrement(&ref_count);
}

ULONG __stdcall FuncRealisation::Release()
{
	if (InterlockedDecrement(&ref_count) == 0)
	{
		delete this;
		return 0;
	}
	return ref_count;
}