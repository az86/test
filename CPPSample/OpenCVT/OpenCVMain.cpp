#pragma warning(disable:4996)
#include <cv.h>
#include <highgui.h> 
#pragma warning(default:4996)
#pragma comment(lib, "opencv_highgui248.lib")
#pragma comment(lib, "opencv_core248.lib")
#pragma comment(lib, "opencv_imgproc248.lib")
#include <iostream>

int main(int argc, char *argv[])
{
	IplImage *pimg = cvCreateImage(cvSize(200,200), 8, 1);
	CvPoint ** pts = new CvPoint*[1]; 
	pts[0] = new CvPoint[4];
	pts[0][0] = cvPoint(0, 0);
	pts[0][1] = cvPoint(0,100);
	pts[0][2] = cvPoint(100,100);
	pts[0][3] = cvPoint(100,0);
	int c[] = {4}; 
	cvPolyLine( pimg, pts, c, 1, 1, CV_RGB(255,255,255)); 
	cvFillPoly(pimg, pts, c, 1, CV_RGB(255,255,255));
	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
	cvShowImage("mainWin", pimg); 

	std::cout << (unsigned)*cvPtr2D(pimg,100,100) << " , " << (unsigned)*cvPtr2D(pimg,100,101) << std::endl;
	cvWaitKey(0); 
	// load an image  
	IplImage* img=cvLoadImage("E:\\Backup\\ПаІб\\BB\\IMAG0908.jpg");
	IplImage *pDstImg = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
 	cvDilate(img, pDstImg);
	cvNot(pDstImg, pDstImg);
	cvSaveImage("E:\\Backup\\ПаІб\\BB\\IMAG090811111.jpg", pDstImg);

	cvReleaseImage(&img);
	cvReleaseImage(&pDstImg);
	
	return 0;
}