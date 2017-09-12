#pragma once
#include <vector>
#include <Windows.h>
using namespace std;

namespace BreezeJoe
{
	bool GetRegionPnts( vector<POINT>& region, POINT* path, int len );
}