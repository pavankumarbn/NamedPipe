Named PIPE Server

#include <Windows.h>
#include <iostream>
using namespace std;
//
// Main function
//
int main( )
{
    cout<<"\t\t....NAMED PIPE SERVER...."<<endl;
    cout<<""<<endl;
    //
    // Local Variable Definitions
    //
    HANDLE    hCreateNamedpipe          =  INVALID_HANDLE_VALUE;
    char      szInputBuffer[1023]       = { 0 };
    char      szOutputBuffer[1023]      = { 0 };
    DWORD     dwszInputBuffer           = sizeof( szInputBuffer );
    DWORD     dwszOutputBuffer          = sizeof( szOutputBuffer );
    BOOL      bClosehandle              = TRUE;
    BOOL      bConnectNamedPipe         = TRUE;
    BOOL      bWritefile                = TRUE;
    BOOL      bReadfile                 = TRUE;
    char      szReadFileBuffer[1023]    = { 0 };
    char      szWriteFileBuffer[1023]   = "Hello From NamedPipe Server!!";
    DWORD     dwWriteBufferSize         = sizeof( szWriteFileBuffer );
    DWORD     dwReadBufferSize          = sizeof( szWriteFileBuffer );
    DWORD     dwNoBytesWrite            = 0;
    DWORD     dwNoBytesRead             = 0;
    BOOL      bDisConnectPipe           = TRUE;
    BOOL      bFlushBuffer              = TRUE;
    //
    // NamedPipe Creation
    //
    hCreateNamedpipe = CreateNamedPipe(
        L"\\\\.\\pipe\\MYNAMEDPIPE",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        dwszInputBuffer,
        dwszOutputBuffer,
        0,
        NULL );

    if( INVALID_HANDLE_VALUE == hCreateNamedpipe )
    {
        cout<<"CreateNamedPipe Failed = "<<GetLastError( )<<endl;
        goto CleanUp;
    } //if
    else
    {
        cout<<"CreateNamedPipe Success"<<endl;
    } //else

    //
    // ConnectNamedPipe
    //
    bConnectNamedPipe = ConnectNamedPipe( hCreateNamedpipe, NULL );
    if( TRUE == bConnectNamedPipe )
    {
        cout<<"Connection Success"<<endl;
    } //if
    else
    {
        cout<<"Connection Failed = "<<GetLastError( )<<endl;
        goto CleanUp;
    } //else

    //
    // Writefile Operation
    //
    bWritefile = WriteFile(
        hCreateNamedpipe,
        szWriteFileBuffer,
        dwWriteBufferSize,
        &dwNoBytesWrite,
        NULL );
    if( TRUE == bWritefile )
    {
        cout<<"WriteFile Success"<<endl;
    } //if
    else
    {
        cout<<"WriteFile Failed = "<<GetLastError( )<<endl;
        goto CleanUp;
    } //else

    //
    // Flush the File Buffer
    //

    bFlushBuffer = FlushFileBuffers( hCreateNamedpipe );
    if( TRUE == bFlushBuffer )
    {
        cout<<"WriteFile Memory Released Successfully"<<endl;
    } //if
    else
    {
        cout<<"WriteFile Memory Released Failed = "<<GetLastError( )<<endl;
        goto CleanUp;
    } //else

    //
    // ReadFile
    //
    bReadfile = ReadFile(
        hCreateNamedpipe,
        szReadFileBuffer,
        dwReadBufferSize,
        &dwNoBytesRead,
        NULL );
    if( TRUE == bReadfile )
    {
        cout<<"ReadFile Success"<<endl;
    } //if
    else
    {
        cout<<"ReadFile Failed = "<<GetLastError( )<<endl;
        goto CleanUp;
    } //else
    cout<<" DATA FROM CLIENT IS -> "<<szReadFileBuffer<<endl;

    //
    // Cleanup function
    //
CleanUp:

    //
    // Disconnect the Named Pipe
    //
    bDisConnectPipe = DisconnectNamedPipe( hCreateNamedpipe );
    if( TRUE == bDisConnectPipe )
    {
        cout<<"Disconnect NamedPipe Success"<<endl;
    } //if
    else
    {
        cout<<"Disconnect NamedPipe Failed = "<<GetLastError( )<<endl;
    } //else

    //
    // Close the handle of NamedPipe
    //
    bClosehandle = CloseHandle( hCreateNamedpipe );
    if( TRUE == bClosehandle )
    {
        cout<<"Write closeHandle Success"<<endl;
    } //if
    else
    {
        cout<<"Write closeHandle Failed = "<<GetLastError( )<<endl;
    } //else

    system("PAUSE");
    return 0;
} //Main Function
