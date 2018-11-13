#pragma once
#include <objbase.h>

interface INumRoots : IUnknown
{
	virtual void __stdcall num_of_roots(double a, double b, double c, double* num) = 0;
};


interface ISolveEquat : IUnknown
{
	virtual void __stdcall solve_equation(double a, double b, double c, double* x1, double * x2) = 0;
};


interface IWho : IUnknown
{
	virtual void __stdcall WhoAmI(std::string input, std::string* output) = 0;
};

// Declaration of GUIDs for interfaces and component.
extern "C" const IID IID_INumRoots;
extern "C" const IID IID_ISolveEquat;
extern "C" const IID IID_IWho;

extern "C" const CLSID CLSID_Component;