// openCV.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace std;

int main(int ac, char** av)
{
  if (ac < 2)
    {
      std::cout << "No file used" << std::endl;
      return 1;
    }

  char key = 'a';
  IplImage *image;
  int height,width,step,channels;
  uchar *data;
  int i,j,k;
  CvCapture *capture;

  capture = cvCreateFileCapture(av[1]);
  //capture = cvCreateCameraCapture(CV_CAP_ANY);

  if (!capture)
    {
      std::cout << "Ouverture du flux vidéo impossible !\n" << std::endl;
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

      std::cout << "Processing a " << height << "x" << width << " image with " << channels << " channels" << std::endl;

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
