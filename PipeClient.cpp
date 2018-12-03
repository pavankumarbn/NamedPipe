/*Author: Pavan Kumar B N 
#Description: This is the Client program which reads message recived from server and prints on console
# Date: 12/03/2018
#*/

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;

//
// Main Function
//
int main()
{
	cout << "\t\t....NamedPipe Client..." << endl;
	cout << endl;
	//
	// Local Variable Definitions
	//
	HANDLE     hCreatefile = INVALID_HANDLE_VALUE;
	BOOL       bCallNamedPipe = TRUE;
	DWORD      dwNoBytesRead = 0;
	DWORD      dwNoBytesWrite = 0;
	BOOL       bReadfile = TRUE;
	BOOL       bWritefile = TRUE;
	char       szReadFileBuffer[1023] = { 0 };
	//char       szWriteFileBuffer[1023] = "Hi";
	DWORD      dwReadFileBufferSize = sizeof(szReadFileBuffer);
	//DWORD      dwWriteFileBufferSize = sizeof(szWriteFileBuffer);
	BOOL       bFlushBuffer = TRUE;
	BOOL       bClosehandle = TRUE;
	
	// CreateFile for Pipe
	//
	hCreatefile = CreateFile(
		L"\\\\.\\pipe\\mynamedpipe",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,//CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hCreatefile)
	{
		cout << "File Creation Failed = " << GetLastError() << endl;
		goto CleanUp;
	}// if
	else
	{
		cout << "File Creation Success" << endl;
	}
	 //
	 // ReadFile
	 //
	bReadfile = ReadFile(
		hCreatefile,
		szReadFileBuffer,
		dwReadFileBufferSize,
		&dwNoBytesRead,
		NULL);
	if (TRUE == bReadfile)
	{
		cout << "ReadFile Success" << endl;
	}// if
	else
	{
		cout << "ReadFile Failed = " << GetLastError() << endl;
		goto CleanUp;
	}// else
	cout << " DATA from python server  -> " << szReadFileBuffer << endl;
	 //
	 // Cleanup Function
	 //
CleanUp:
	bClosehandle = CloseHandle(hCreatefile);
	if (TRUE == bClosehandle)
	{
		cout << "CreateFile closeHandle Success" << endl;
	}// if
	else
	{
		cout << "CreateFile closeHandle Failed = " << GetLastError() << endl;
	}// else

	system("PAUSE");
	return 0;
}// End of Main Function