// openCV.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace std;

int main(void)
{
    char key = 'a';
    IplImage *image;
    int height,width,step,channels;
    uchar *data;
    CvCapture* capture = cvCreateCameraCapture(-1);

    if (!capture)
	{
	    std::cout << "Ouverture du flux vidéo impossible !\n" << std::endl;
	    return 1;
	}

    cvNamedWindow("GeckoGeek Window", CV_WINDOW_AUTOSIZE);

    if (!cvGrabFrame(capture))
	{
	    std::cout << "capture failed" << std::endl;
	    return 1;
	}

    while (key != 'q' && key != 'Q')
	{
	    //image = cvQueryFrame(capture);
	    image = cvRetrieveFrame(capture);

	    height    = image->height;
	    width     = image->width;
	    step      = image->widthStep;
	    channels  = image->nChannels;
	    data      = (uchar *)image->imageData;

	    std::cout << "Processing a " << height << "x" << width << " image with " << channels << " channels" << std::endl;

	    // for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++)
	    //  data[i*step+j*channels+k]=255-data[i*step+j*channels+k];

	    // cvShowImage("mainWin", image );
	    cvShowImage( "GeckoGeek Window", image);
	    cvWaitKey(10);
	    //key = cvWaitKey(5);

	    if (!cvGrabFrame(capture))
		{
		    key = 'q';
		}
	}

    cvDestroyAllWindows();

    image = NULL;

    cvReleaseCapture(&capture);

    return 0;
}
