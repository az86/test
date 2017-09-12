// CLI.h

#pragma once

using namespace System;
using namespace System::Windows; // for Point by zyj

#include "../Cpp/Test.h"
namespace CLI {
	public enum class AWrap
	{
		All7Wrap = All7,
		All9Wrap = All9
	};

	public ref class CTestWrap
	{
		// TODO: 在此处添加此类的方法。
		CTest *m_core;
		array<Point> ^mEdge;// by zyj
		array<System::Windows::Point^> ^mPath;//by zyj

	public:
		CTestWrap();
		array<int>^ GetArray(AWrap a);
		IntPtr GetCore()
		{
			return IntPtr(m_core);
		}
	public:	
		void SetValuess(System::String^ str)
		{

		}
		property array<Point> ^Edge     // by zyj
		{
			void set(array<Point> ^value){ mEdge = value; }
			array<Point>^ get(){ return mEdge; }
		}
		property Point^ Pt
		{
			Point^ get(){return gcnew Point();}
		}
		property array<System::Windows::Point^> ^Path   // by zyj. A: Point is declared as struct which type is value type. Only reference type need to add ^ operator.
		{
			void set(array<System::Windows::Point^> ^value){ mPath = value; }
			array<System::Windows::Point^>^ get(){ return mPath; }
		}
	};
}
