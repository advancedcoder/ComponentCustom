#pragma once
#include "Intfaces.h"

//const __declspec(dllexport) int AEqualsZeroException = 1;
//const __declspec(dllexport) int NegativeDescriminantException = 2;
//const __declspec(dllexport) int EmptyStringException = 3;

class AEqualsZeroException {};
class NegativeDescriminantException {};
class EmptyStringException {};

class FuncRealisation : public INumRoots, public ISolveEquat, public IWho
{
public:
	FuncRealisation();
	~FuncRealisation();
	// IUnknown
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	// Interface INumRoots
	virtual void __stdcall num_of_roots(double a, double b, double c, double* num);

	// Interface ISolveEquat
	virtual void __stdcall solve_equation(double a, double b, double c, double* x1, double * x2);

	// Interface IWho
	virtual void __stdcall WhoAmI(std::string input, std::string* output);

private:
	// Reference count
	long ref_count;
	double find_descr(double a, double b, double c);
};

