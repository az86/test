#include "../DicomLib/DICOMAppHelper.h"
#include "../DicomLib/DICOMParser.h"

#pragma warning(disable:4996)
#include <cv.h>
#include <highgui.h> 
#pragma warning(default:4996)
#pragma comment(lib, "opencv_highgui248.lib")
#pragma comment(lib, "opencv_core248.lib")
#pragma comment(lib, "opencv_imgproc248.lib")

#include <algorithm>
int main()
{
	const char *filePath = "D:\\Data\\dicom\\PT01668\\CT1224_1.2.840.113619.2.55.3.2474910077.148.1348617711.18.1224.DCM";
	
	DICOMParser parser;
	DICOMAppHelper h;
	h.RegisterCallbacks(&parser);
	h.RegisterPixelDataCallback(&parser);

	if (!parser.OpenFile(filePath))
		cout << "open failed!" << endl;
	parser.ReadHeader();
	void *pData;
	DICOMParser::VRTypes dt;
	unsigned long len;
	h.GetImageData(pData, dt, len);
	auto p = static_cast<short*>(pData);
	short minVal = *min_element(p, p + len/2);
	short maxVal = *max_element(p, p + len/2);
	auto pp = (double)0xFFFF / (maxVal - minVal);
	for_each(p, p + len/2, [&pp, &minVal](short &val){val -= minVal; val *= pp;});
	IplImage *pimg = cvCreateImage(cvSize(h.GetWidth(), h.GetHeight()), 16, 1);
	pimg->imageData = static_cast<char*>(pData);
	memcpy(pimg->imageData, pData, h.GetBitsAllocated());
	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
	cvShowImage("mainWin", pimg); 
	cvWaitKey(0); 

	CvMat* mat  = cvCreateMat(512,512,CV_32FC1);
	for (int i = 0; i != 512 * 512; ++i)
	{
		mat->data.fl[i] = p[i];
	}
	CvMat * mat_test2=cvCreateMat(512,512,CV_32FC1);
	cvDFT(mat,mat_test2,CV_DXT_FORWARD);
	return 0;
}