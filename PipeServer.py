#Author: Pavan Kumar B N 
#Description: This is the Server program which connects to client and sends message to client
# Date: 12/03/2018
#

import time
import sys
import win32pipe, win32file, pywintypes
from ctypes import *

PIPE_ACCESS_DUPLEX = 0x3
PIPE_TYPE_MESSAGE = 0x4
PIPE_READMODE_MESSAGE = 0x2
PIPE_WAIT = 0
PIPE_UNLIMITED_INSTANCES = 255
BUFSIZE = 4096
NMPWAIT_USE_DEFAULT_WAIT = 0
INVALID_HANDLE_VALUE = -1
ERROR_PIPE_CONNECTED = 535

MESSAGE = "Default answer from server\0"
szPipename = "\\\\.\\pipe\\mynamedpipe"
test_data = "HelloClient".encode("ascii")

def main():
    THREADFUNC = CFUNCTYPE(c_int, c_int)
    #thread_func = THREADFUNC(ReadWrite_ClientPipe_Thread)
    hPipe = win32pipe.CreateNamedPipe(szPipename,win32pipe.PIPE_ACCESS_DUPLEX,win32pipe.PIPE_TYPE_MESSAGE | win32pipe.PIPE_READMODE_MESSAGE | win32pipe.PIPE_WAIT, win32pipe.PIPE_UNLIMITED_INSTANCES, BUFSIZE, BUFSIZE, 0,None)
    try:
        print("waiting for client")
        win32pipe.ConnectNamedPipe(hPipe, None)
        print ("Client connected")
        win32file.WriteFile(hPipe,test_data,None)
        print("Writing finished")
    finally:
        win32file.CloseHandle(hPipe)
    return 0
if __name__ == "__main__":
    main()
