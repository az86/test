#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	HANDLE hFile = ::CreateFile(L"C:\\MapMemory.txt", GENERIC_READ | GENERIC_WRITE , 0, NULL, OPEN_ALWAYS|TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	HANDLE hFileMapping = ::CreateFileMapping(hFile,NULL,PAGE_READWRITE, 0, 64,NULL);
	CHAR* pbFile = (CHAR*)::MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);
	cin.getline(pbFile, 64);
	::UnmapViewOfFile(pbFile);
	::CloseHandle(hFileMapping);
	::CloseHandle(hFile);
	return 0;
}