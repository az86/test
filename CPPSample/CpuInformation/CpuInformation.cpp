#include <stdio.h>
#include <pdh.h>  
#pragma comment(lib, "Pdh.lib") //��ʽ����Pdh.lib  
int main(int arvc, char* argv[])  
{  
	PDH_STATUS status = ERROR_SUCCESS;  
	HQUERY hQuery = NULL;                       //������������  
	HCOUNTER hCounter = NULL;                   //���������  
	PDH_FMT_COUNTERVALUE DisplayValue;          //������ֵ  
	DWORD dwCounterType = 0;                    //����������  
	status = PdhOpenQuery(NULL, 0, &hQuery);    //�򿪼���������  
	if (ERROR_SUCCESS == status)  
	{  
		//PdhAddCounter()������Ӽ�������������Processor�������������(0)��ʾ          ��1������������ʵ�������������������������������2������������ʵ���ã�1��     ��ʾ  
		//% Processor Time��ʾ��������ȡ�ô�����ռ��ʱ�䣩,ע��%�����и��ո�  
		status = PdhAddCounter(hQuery, L"\\Processor(0)\\% Processor Time", 0, &hCounter);  
		if (ERROR_SUCCESS == status)  
		{  
			// PdhCollectQueryData()�����ռ����������ε���, PdhCollectQuery  DataExֻ��һ��  
			PdhCollectQueryData(hQuery);        //�״��ռ�����  
			while(true)  
			{  
				PdhCollectQueryData(hQuery);    //�ٴ��ռ�����  
				status = PdhGetFormattedCounterValue(hCounter,   
					PDH_FMT_DOUBLE,   
					&dwCounterType, &DisplayValue);  
				//ȡ���ռ�������ֵ  
				printf("CPUռ�� %.2f\n", DisplayValue.doubleValue);  
				Sleep(1000);                    //1���ռ�1��  
			}  
		}  
		PdhCloseQuery(hQuery);                  //�رռ���������  
	}  
}  