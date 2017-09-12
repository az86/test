// 这是主 DLL 文件。

#include "stdafx.h"

#include "CLI.h"
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace Linq;
bool dd(int val)
{
	return true;
}
CLI::CTestWrap::CTestWrap()
{
	m_core = new CTest;
}

array<int>^ CLI::CTestWrap::GetArray(AWrap a)
{
	int tmp[5];
	m_core->GetArray(tmp, 5, (A)a);
	array<int>^ pArr = gcnew array<int>(5);
	Marshal::Copy(IntPtr(tmp), pArr, 0, 5);	//非托管到托管内存拷贝
	return pArr;
}

