//
// System Header File
//

#include <Windows.h>
#include <iostream>
using namespace std;

//
// Main Function
//
int main()
{
    cout<<"\t\t....NAMED PIPE CLIENT...."<<endl;
    cout<<endl;
    //
    // Local Variable Definitions
    //
    HANDLE     hCreatefile              = INVALID_HANDLE_VALUE;
    BOOL       bCallNamedPipe           = TRUE;
    DWORD      dwNoBytesRead            = 0;
    DWORD      dwNoBytesWrite           = 0;
    BOOL       bReadfile                = TRUE;
    BOOL       bWritefile               = TRUE;
    char       szReadFileBuffer[1023]   = { 0 };
    char       szWriteFileBuffer[1023]  = "Hello From NamedPipe Client!";
    DWORD      dwReadFileBufferSize     = sizeof( szReadFileBuffer );
    DWORD      dwWriteFileBufferSize    = sizeof( szWriteFileBuffer );
    BOOL       bFlushBuffer             = TRUE;
    BOOL       bClosehandle             = TRUE;
    //  DWORD      PipeReadMode             = PIPE_READMODE_MESSAGE;
    //   BOOL       bSetNamePipeHandleState  = TRUE;
    //
    // CreateFile for Pipe
    //
    hCreatefile = CreateFile(
        L"\\\\.\\pipe\\MYNAMEDPIPE",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,//CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL );

    if( INVALID_HANDLE_VALUE == hCreatefile )
    {
        cout<<"File Creation Failed = "<<GetLastError( )<<endl;
        goto CleanUp;
    }// if
    else
    {
        cout<<"File Creation Success"<<endl;
    }// else

    //
    //SetNamedPipeHandleState
    //
    //bSetNamePipeHandleState = SetNamedPipeHandleState(
    //    hCreatefile,
    //    &PipeReadMode,
    //    NULL,
    //    NULL );
    //if( TRUE == bSetNamePipeHandleState )
    //{
    //    cout<<"SetNamePipeHandleState Success"<<endl;
    //}// if
    //else
    //{
    //    cout<<"SetNamePipeHandleState Failed = "<<GetLastError( )<<endl;
    //    if( hCreatefile != NULL )
    //    {
    //      goto CleanUp;
    //    }// if
    //}// else

    //
    // ReadFile
    //
    bReadfile = ReadFile(
        hCreatefile,
        szReadFileBuffer,
        dwReadFileBufferSize,
        &dwNoBytesRead,
        NULL );
    if( TRUE == bReadfile )
    {
        cout<<"ReadFile Success"<<endl;
    }// if
    else
    {
        cout<<"ReadFile Failed = "<<GetLastError( )<<endl;
        goto CleanUp;
    }// else
    cout<<" DATA FROM SERVER IS -> "<<szReadFileBuffer<<endl;

    //
    // Writefile Operation
    //
    bWritefile = WriteFile(
        hCreatefile,
        szWriteFileBuffer,
        dwWriteFileBufferSize,
        &dwNoBytesWrite,
        NULL );
    if( TRUE == bWritefile )
    {
        cout<<"WriteFile Success"<<endl;
    }// if
    else
    {
        cout<<"WriteFile Failed = "<<GetLastError( )<<endl;
        goto CleanUp;
    }// else

    //
    // Cleanup Function
    //
CleanUp:
    bClosehandle = CloseHandle( hCreatefile );
    if( TRUE == bClosehandle )
    {
        cout<<"CreateFile closeHandle Success"<<endl;
    }// if
    else
    {
        cout<<"CreateFile closeHandle Failed = "<<GetLastError( )<<endl;
    }// else

    system("PAUSE");
    return 0;
}// End of Main Function
