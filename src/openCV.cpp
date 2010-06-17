// openCV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
   	char key = 'a';
	IplImage *image;
	int height,width,step,channels;
	uchar *data;
	int i,j,k;
	CvCapture *capture;
 
	capture = cvCreateFileCapture("D:/Film/31306.avi");
	//capture = cvCreateCameraCapture(CV_CAP_ANY);

	if (!capture)
	{
	   printf("Ouverture du flux vidéo impossible !\n");
	   return 1;
	}
 
	cvNamedWindow("GeckoGeek Window", CV_WINDOW_AUTOSIZE);
	while (key != 'q' && key != 'Q') 
	{
	   image = cvQueryFrame(capture);
	   height    = image->height;
	   width     = image->width;
	   step      = image->widthStep;
	   channels  = image->nChannels;
	   data      = (uchar *)image->imageData;
	   
	   printf("Processing a %dx%d image with %d channels\n",height,width,channels);

		 // for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++)
		  //  data[i*step+j*channels+k]=255-data[i*step+j*channels+k];

		 // cvShowImage("mainWin", image );
		cvWaitKey(0);
	   cvShowImage( "GeckoGeek Window", image);
	   //key = cvWaitKey(5);
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("GeckoGeek Window");
	return 0;
}

