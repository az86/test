#include "BreezeJoeLib.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <Windows.h>
#pragma comment(lib, "Gdi32.lib")
using namespace std;

namespace BreezeJoe
{
	bool GetRegionPnts( vector<POINT>& region, POINT* path, int len)
	{

		// 先从边界path生成多边形
		HRGN edge = CreatePolygonRgn(path,len,ALTERNATE);
		if(!edge)
			return false;

		// 找到多边形的最小外界矩形，矩形的四边分别与图像两轴平行
		POINT *pnt = max_element(path, path+len, []( POINT& pnt1, POINT& pnt2){ return pnt1.x<pnt2.x;});
		int xmax = pnt->x; 
		pnt = max_element(path, path+len, []( POINT& pnt1, POINT& pnt2){ return pnt1.y<pnt2.y; });
		int ymax = pnt->y; 
		pnt = min_element(path, path+len, []( POINT& pnt1, POINT& pnt2){ return pnt1.x<pnt2.x; });
		int xmin = pnt->x;
		pnt = min_element(path, path+len, []( POINT& pnt1, POINT& pnt2){ return pnt1.y<pnt2.y; });
		int ymin = pnt->y;

		cout<<"xmax = "<<xmax<<endl;
		cout<<"ymax = "<<ymax<<endl;
		cout<<"xmin = "<<xmin<<endl;
		cout<<"ymin = "<<ymin<<endl;

		auto pathMirx = new POINT[len];
		auto pathMiry = new POINT[len];
		auto pathMirxy = new POINT[len];
		for (int i = 0; i != len; ++i)
		{
			pathMirx[i].x = xmax - path[i].x;
			pathMirx[i].y = path[i].y;
			
			pathMiry[i].x = path[i].x;
			pathMiry[i].y = ymax - path[i].y;

			pathMirxy[i].x = xmax - path[i].x;
			pathMirxy[i].y = ymax - path[i].y;
		}
		HRGN edgeMirx = CreatePolygonRgn(pathMirx,len,ALTERNATE);	 //创建x方向镜像解决右边界问题
		HRGN edgeMiry = CreatePolygonRgn(pathMiry,len,ALTERNATE); // 创建y方向镜像解决上边界问题
		HRGN edgeMirxy = CreatePolygonRgn(pathMirxy,len,ALTERNATE);	// 创建xy方向镜像解决右上角问题
		delete[] pathMirx;
		delete[] pathMiry;
		delete[] pathMirxy;
		POINT tmp;
		for ( int i=xmin; i<=xmax; i++)
		{
			for ( int j=ymin; j<=ymax; j++)
			{
				cout<<"( "<<i<<", "<<j<<") ----  ";
				if (PtInRegion(edge,i,j) || PtInRegion(edgeMirx, xmax - i, j) || PtInRegion(edgeMiry, i, ymax-j) || PtInRegion(edgeMirxy, xmax - i, ymax-j))
				{
					tmp.x = i;
					tmp.y = j;
					region.push_back( tmp );
					cout<<"int"<<endl;
				}
				else
					cout<<"out"<<endl;
			}
		}

		// 删除内核对象
		DeleteObject(edge);
		DeleteObject(edgeMirx);
		DeleteObject(edgeMiry);
		DeleteObject(edgeMirxy);
		return true;
	}
}

