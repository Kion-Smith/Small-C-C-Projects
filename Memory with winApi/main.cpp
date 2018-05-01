#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

bool ProcessRunning( const char*);

int main()
{
    char* userInput = new char[256];
    std::cout << "Enter a name of a process and I'll tell you if it is on or not" << std::endl;
    std::cin >> userInput;

    if(ProcessRunning(userInput))
    {
        std::cout <<"It is Running" << std::endl;
    }
    else
    {
       std::cout <<"Is not running" << std::endl;
    }

    return 0;
}
bool ProcessRunning( const char* name )
{
    // create the process struct and set the size
    PROCESSENTRY32 processStruct;
	processStruct.dwSize = sizeof( processStruct );

	//get the snapshot of process
	HANDLE snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

    // If snapshot is not valid
	if( snapshot == INVALID_HANDLE_VALUE )
    {
        return false;
    }
    // if the first not equal then return false
	if( !Process32First( snapshot, &processStruct ) )
    {
        return false;
    }
    //Keep running and if the process struct return true
    while( Process32Next(snapshot,&processStruct))
    {
       if( strcmp( processStruct.szExeFile, name ) == 0 )
       {
           return true;
       }
    }

	return false;
}
