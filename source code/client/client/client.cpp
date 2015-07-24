// client.cpp : Defines the entry point for the console application.
//

//#define UNICODE
//#define _UNICODE
#include "stdafx.h"
#pragma comment(lib, "rpcrt4.lib")

/*liscenced under GPLv3
 -An Artificial Intelligence Program Called CAST(completely automated self thinking ai).
    -Copyright (C) 2015  Mukund

    -This program is free software: you can redistribute it and/or modify
    -it under the terms of the GNU General Public License as published by
    -the Free Software Foundation, either version 3 of the License, or
    -(at your option) any later version.

    -This program is distributed in the hope that it will be useful,
    -but WITHOUT ANY WARRANTY; without even the implied warranty of
    -MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    -GNU General Public License for more details.

    -You should have received a copy of the GNU General Public License
    -along with this program.  If not, see http://www.gnu.org/licenses/.
	-check this folder's root directory for a copy of the program.
    -you can contact me at justmukund2012@gmail.com or admin@mail.siblingz.net*/
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <wchar.h>


#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <voce.h>


#define BUFSIZE 512
using namespace std;
const char **argv;
int argc;
string q1;

string  ftb()
{
	//voce::synthesize();
	UUID uuid;
	UuidCreate(&uuid);
	char *str;
	UuidToStringA(&uuid, (RPC_CSTR*)&str);
	cout << str << endl;
	RpcStringFreeA((RPC_CSTR*)&str);
	string f = "Hello My Name is CAST Version 1.0";
	voce::synthesize(f);
    cout << f << endl;
	string mystring;
	string j = "whats your age?";
	string age;
	voce::synthesize(j);
	cout << j << endl;
	string h = "whats your name?";
	cin >> age;
	cout << h << endl;
	voce::synthesize(h);
	cin >> mystring;
	string lkd = "hello ";
	string gh = " Who is ";
	string hj = " years old";
	//string k = lkd + mystring + gh + age + hj;
	//cout << "hello " << mystring << " Who is " << age << " years old.\n ";
	cout << lkd << mystring << gh << age << hj <<endl;
	voce::synthesize(lkd);
	voce::synthesize(mystring);
	voce::synthesize(gh);
	voce::synthesize(age);
	voce::synthesize(lkd);
	string l = "ask me a question";
	cout << l << endl;
	voce::synthesize(l);
	string question;
	
	cin.ignore();
	getline(cin, question);
	return question;
}


int _tmain(int argc, TCHAR *argv[]) 
{ 
   HANDLE hPipe; 
   char  chBuf[BUFSIZE]; 
   BOOL   fSuccess = FALSE; 
   DWORD  cbRead, cbToWrite, cbWritten, dwMode; 
   LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe"); 
   
     
	string s= ftb();
	int n1;
	char *array;
	n1 = s.length();
	array = new char[n1+1];
	strcpy_s(array,n1+1,s.c_str()); 


// Try to open a named pipe; wait for it, if necessary. 
 
   while (1) 
   { 
      hPipe = CreateFile( 
         lpszPipename,   // pipe name 
         GENERIC_READ |  // read and write access 
         GENERIC_WRITE, 
         0,              // no sharing 
         NULL,           // default security attributes
         OPEN_EXISTING,  // opens existing pipe 
         0,              // default attributes 
         NULL);          // no template file 
 
   // Break if the pipe handle is valid. 
 
      if (hPipe != INVALID_HANDLE_VALUE) 
         break; 
 
      // Exit if an error other than ERROR_PIPE_BUSY occurs. 
 
      if (GetLastError() != ERROR_PIPE_BUSY) 
      {
         cout << "Could not open pipe. GLE= " << GetLastError() << "\n"; 
         return -1;
      }
 
      // All pipe instances are busy, so wait for 20 seconds. 
 
      if ( ! WaitNamedPipe(lpszPipename, 20000)) 
      { 
         cout << "Could not open pipe: 20 second wait timed out." << "\n" ; 
         return -1;
      } 
   } 
 
// The pipe connected; change to message-read mode. 
 
   dwMode = PIPE_READMODE_MESSAGE; 
   fSuccess = SetNamedPipeHandleState( 
      hPipe,    // pipe handle 
      &dwMode,  // new pipe mode 
      NULL,     // don't set maximum bytes 
      NULL);    // don't set maximum time 
   if ( ! fSuccess) 
   {
      cout << "SetNamedPipeHandleState failed. GLE= " << GetLastError() << "\n"; 
      return -1;
   }
 
// Send a message to the pipe server. 

   cbToWrite = (strlen(array)+1)*sizeof(char);
   cout << "Sending " << cbToWrite << " byte message: " << array  <<  "\n"; 

   fSuccess = WriteFile( 
      hPipe,                  // pipe handle 
      array,                  // message 
      strlen(array)+ 1,       // message length 
      &cbWritten,             // bytes written 
      NULL);                  // not overlapped 

   if ( ! fSuccess) 
   {
      cout << "WriteFile to pipe failed. GLE= " << GetLastError() << "\n"; 
      return -1;
   }

   cout << "\nMessage sent to server, receiving reply as follows:" << "\n";
 
   do 
   { 
   // Read from the pipe. 
 
      fSuccess = ReadFile( 
         hPipe,    // pipe handle 
         chBuf,    // buffer to receive reply 
         sizeof(chBuf), ///BUFSIZE*sizeof(TCHAR),  // size of buffer 
         &cbRead,  // number of bytes read 
         NULL);    // not overlapped 
 
      if ( ! fSuccess && GetLastError() != ERROR_MORE_DATA )
         break; 
 
		cout << chBuf  << "\n"; 

   } while ( ! fSuccess);  // repeat loop if ERROR_MORE_DATA 

   if ( ! fSuccess)
   {
      cout << "ReadFile from pipe failed. GLE= " << GetLastError() << "\n" ;
      return -1;
   }

   cout << "\n<End of message, press ENTER to terminate connection and exit>" ;
   _getch();
 
   CloseHandle(hPipe); 
 
   return 0; 
}

