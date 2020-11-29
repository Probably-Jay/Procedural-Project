#include "ErrorHandler.h"

ErrorHandler::ErrorHandler()
{
}



void ErrorHandler::PrintError(string msg)
{
	cout << "Error: " + msg << endl;
}


void ErrorHandler::DieWithPrint(string msg)
{
	PrintError(msg);
	Die();
}

void ErrorHandler::Die()
{
#ifdef _DEBUG
	abort();
#else
	exit(1);
#endif
}


bool ErrorHandler::ReportError()
{
	return false;
}
