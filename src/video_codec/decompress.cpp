#include <cstdlib>
#include "DCT.h"
#include "Quantizer.h"
#include "videoCodec.h"
#include <iostream>

#include "decompress.h"

decompress::decompress()
{
}

bool	decompress::CalcBlocSize(int width, int height, int y, int x)
{
  	if (height - y >= 8)
    	this->BlocH = 8;
  	else
	    this->BlocH = height - y;
  	if (width - x >= 8)
	    this->BlocW = 8;
  	else
	    this->BlocW = width - x;
  	if (this->BlocH == 0 || this->BlocW == 0)
	    return false;
  	else
	    return true;
}

void	decompress::loadImage()
{
  	IplImage *image;
  	IplImage *bloc;
	videoCodec	VC;
	DCT			dct;
	Quantizer	Q;
	short		int temp[64];

  	int height,width;
  	int x,y;

  	image = bloc = cvLoadImage("C:/Users/guillaume/Pictures/1.jpg");
  	height = image->height;
  	width = image->width;
  	this->setRecontructionImage(height,width);
  	for (x = 0; x <= width; x+=8)
    {
		for(y=0; y <= height; y+=8)
		{
	  		if (this->CalcBlocSize(width,height,y,x) == true)
	    	{
	      		CvRect rect = cvRect(x, y, this->BlocW,this->BlocH);
	      		cvSetImageROI(image, rect);
				bloc = cvCreateImage(cvGetSize(image),
								 	image->depth,
				   					image->nChannels);
	      		cvCopy(image, bloc, NULL);
	      		cvResetImageROI(image);
				dct.referenceDCT((uchar *)bloc->imageData,temp);
				Q.quantizeDCTMatrix(temp);
				
	      		this->saveImage(temp,x,y,bloc);
	    	}
		}
    }
	VC.SaveImgInList(this->ImgRec,width,height);
	delete(this->ImgRec);
	VC.createFile("test.GuiGuy");
	VC.SaveFlux();
}

void	decompress::setRecontructionImage(int height,int width)
{
	//imRec[width][height]
	this->ImgRec = new int*[width];
	for(int i=0; i < width; i++)
		this->ImgRec[i] = new int[height];
}

int		**decompress::getRecontructionImage()
{
  	return (this->ImgRec);
}

void	decompress::saveImage(short int *tab,int x, int y, IplImage *bloc)
{
	int blocH = bloc->height;
   	int blocW = bloc->width;
	int blocSize = blocH*blocW;
	int	i = 0;
	int j = 0;
	int count = 0;
	
	while (count < blocSize)
	{
		if ((i == 8) && (j == 8))
			break ;
		if (j == 8)
		{
			i++;
			j = 0;
		}
		this->ImgRec[x+i][y+j] = (int)tab[count];
		j++;
		count++;
	}
}
