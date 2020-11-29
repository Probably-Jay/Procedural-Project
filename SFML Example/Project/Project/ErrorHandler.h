#pragma once
#include <string>
#include <iostream>
using std::string; using std::cout; using std::endl;
class ErrorHandler
{
public:
	ErrorHandler();
	void DieWithPrint(string msg);

	void Die();

private:
	void PrintError(string msg);

	bool ReportError();
};

