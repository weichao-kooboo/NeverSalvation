#pragma once

#include "CoreMinimal.h"
#include <iostream> 
#include <string>
#include <string.h>
#include <winsock2.h> // include must before window.h
#include <iphlpapi.h>
#include <windows.h>  

#pragma comment(lib, "iphlpapi.lib")

#pragma warning(disable: 4996) // avoid GetVersionEx to be warned

// ***** global macros ***** //
static const int kMaxInfoBuffer = 256;
#define  GBYTES  1073741824  
#define  MBYTES  1048576  
#define  KBYTES  1024  
#define  DKBYTES 1024.0  

using namespace std;

class SYSTEMINFO_API SystemInfoClient
{
public:
	SystemInfoClient();
	~SystemInfoClient();
	string getOsInfo();
	string getCpuInfo();
	string getMemoryInfo();
	string getHardDiskInfo();
};
