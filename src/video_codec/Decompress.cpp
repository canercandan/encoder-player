#include <cstdlib>
#include <iostream>

#include "DCT.h"
#include "Quantizer.h"
#include "VideoCodec.h"
#include "Decompress.h"

Decompress::Decompress()
{}

bool	Decompress::CalcBlocSize(int width, int height, int y, int x)
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

void	Decompress::loadImage()
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

void	Decompress::setRecontructionImage(int height,int width)
{
    //imRec[width][height]
    this->ImgRec = new int*[width];
    for(int i=0; i < width; i++)
	this->ImgRec[i] = new int[height];
}

int		**Decompress::getRecontructionImage()
{
    return (this->ImgRec);
}

void	Decompress::saveImage(short int *tab,int x, int y, IplImage *bloc)
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
