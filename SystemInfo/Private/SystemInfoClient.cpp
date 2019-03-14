#include "SystemInfoPrivatePCH.h"
#include "SystemInfo/Public/SystemInfoClient.h"

SystemInfoClient::SystemInfoClient()
{
}

SystemInfoClient::~SystemInfoClient()
{
}

string SystemInfoClient::getOsInfo()
{
	OSVERSIONINFO osver = { sizeof(OSVERSIONINFO) };
	GetVersionEx(&osver);
	std::string os_name = "os name: ";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)
		os_name.append("Windows 2000");
	else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
		os_name.append("Windows XP");
	else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
		os_name.append("Windows 2003");
	else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
		os_name.append("windows vista");
	else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
		os_name.append("windows 7");
	else
		os_name.append("windows 10");

	//std::cout << "os name: " << os_name << std::endl;
	return os_name;
}

#ifdef _WIN64

// method 2: usde winapi, works for x86 and x64
#include <intrin.h>
string SystemInfoClient::getCpuInfo()
{
	string cpu_info;
	int cpuInfo[4] = { -1 };
	char cpu_manufacture[32] = { 0 };
	char cpu_type[32] = { 0 };
	char cpu_freq[32] = { 0 };

	__cpuid(cpuInfo, 0x80000002);
	memcpy(cpu_manufacture, cpuInfo, sizeof(cpuInfo));

	__cpuid(cpuInfo, 0x80000003);
	memcpy(cpu_type, cpuInfo, sizeof(cpuInfo));

	__cpuid(cpuInfo, 0x80000004);
	memcpy(cpu_freq, cpuInfo, sizeof(cpuInfo));

	cpu_info = "CPU manufacture: ";
	cpu_info.append(cpu_manufacture);
	cpu_info.append("CPU type: ");
	cpu_info.append(cpu_type);
	cpu_info.append("CPU main frequency: ");
	cpu_info.append(cpu_freq);
	return cpu_info;
}

#else

// mothed 1: this kind asm embedded in code only works in x86 build
// save 4 register variables
DWORD deax;
DWORD debx;
DWORD decx;
DWORD dedx;

// init cpu in assembly language
void initCpu(DWORD veax)
{
	__asm
	{
		mov eax, veax
		cpuid
		mov deax, eax
		mov debx, ebx
		mov decx, ecx
		mov dedx, edx
	}
}

long getCpuFreq()
{
	int start, over;
	_asm
	{
		RDTSC
		mov start, eax
	}
	Sleep(50);
	_asm
	{
		RDTSC
		mov over, eax
	}
	return (over - start) / 50000;
}

std::string getManufactureID()
{
	char manuID[25];
	memset(manuID, 0, sizeof(manuID));

	initCpu(0);
	memcpy(manuID + 0, &debx, 4); // copy to array
	memcpy(manuID + 4, &dedx, 4);
	memcpy(manuID + 8, &decx, 4);

	return manuID;
}

std::string getCpuType()
{
	const DWORD id = 0x80000002; // start 0x80000002 end to 0x80000004
	char cpuType[49];
	memset(cpuType, 0, sizeof(cpuType));

	for (DWORD t = 0; t < 3; t++)
	{
		initCpu(id + t);

		memcpy(cpuType + 16 * t + 0, &deax, 4);
		memcpy(cpuType + 16 * t + 4, &debx, 4);
		memcpy(cpuType + 16 * t + 8, &decx, 4);
		memcpy(cpuType + 16 * t + 12, &dedx, 4);
	}

	return cpuType;
}

string SystemInfoClient::getCpuInfo()
{
	string cpu_info;
	cpu_info = "CPU manufacture: ";
	cpu_info.append(getManufactureID());
	cpu_info.append("CPU type: ");
	cpu_info.append(getCpuType());
	cpu_info.append("CPU main frequency: ");
	cpu_info.append(getCpuFreq());
	return cpu_info;
}

#endif

string SystemInfoClient::getMemoryInfo()
{
	std::string memory_info;
	MEMORYSTATUSEX statusex;
	statusex.dwLength = sizeof(statusex);
	if (GlobalMemoryStatusEx(&statusex))
	{
		unsigned long long total = 0, remain_total = 0, avl = 0, remain_avl = 0;
		double decimal_total = 0, decimal_avl = 0;
		remain_total = statusex.ullTotalPhys % GBYTES;
		total = statusex.ullTotalPhys / GBYTES;
		avl = statusex.ullAvailPhys / GBYTES;
		remain_avl = statusex.ullAvailPhys % GBYTES;
		if (remain_total > 0)
			decimal_total = (remain_total / MBYTES) / DKBYTES;
		if (remain_avl > 0)
			decimal_avl = (remain_avl / MBYTES) / DKBYTES;

		decimal_total += (double)total;
		decimal_avl += (double)avl;
		char  buffer[kMaxInfoBuffer];
		sprintf_s(buffer, kMaxInfoBuffer, "total %.2f GB (%.2f GB available)", decimal_total, decimal_avl);
		memory_info.append(buffer);
	}
	return memory_info;
}

// ---- get harddisk info ---- //
std::string execCmd(const char *cmd)
{
	char buffer[128] = { 0 };
	std::string result;
	FILE *pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("_popen() failed!");
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	_pclose(pipe);

	return result;
}
string SystemInfoClient::getHardDiskInfo()
{
	std::string hd_seiral = execCmd("wmic path win32_physicalmedia get SerialNumber");
	hd_seiral.insert(0, "HardDisk Serial Number: ");
	return hd_seiral;
}
