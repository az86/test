#include <Windows.h>
#pragma comment(lib, "Gdi32.lib")
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	POINT pts[5];
	pts[0].x = 10;
	pts[0].y = 10;

	pts[1].x = 20;
	pts[1].y = 30;

	pts[2].x = 30;
	pts[2].y = 20;

	pts[3].x = 50;
	pts[3].y = 50;

	pts[4].x = 80;
	pts[4].y = 10;
	POINT *ptxmax = max_element(pts, pts + 5, [](POINT &pt1, POINT&pt2){return pt1.x < pt2.x;});
	POINT *ptxmin = min_element(pts, pts + 5, [](POINT &pt1, POINT&pt2){return pt1.x < pt2.x;});
	cout << ptxmax->x << " , " << ptxmin->x << endl;
 	HRGN hrgn = CreatePolygonRgn(pts, 5, ALTERNATE);//��������Ľ����һ����ʼ��и���

	//�ͷ��ⲿ�ִ��룬��������Ļ���Ͻǿ�����״������ø����ӵ�ͼ�β���һ��
	HDC hScr = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	HBRUSH hBrush = CreateSolidBrush(RGB(0,0,255));
	FillRgn(hScr, hrgn, hBrush);
	DeleteObject(hBrush);
	DeleteDC(hScr);
	
	int x = 50;  //�����Ƿ��������ڵĵ�����
	int y = 30;

	BOOL isPtInRegion = PtInRegion(hrgn, x, y);
	string result = isPtInRegion == TRUE ? "pt is in region" : "pt is not in region";
	cout << result << endl;
	DeleteObject(hrgn);
}