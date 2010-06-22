#include <cstdlib>

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
  	int height,width;
  	int x,y;

  	image = bloc = cvLoadImage("C:/Users/Public/Pictures/Sample Pictures/Tulips.jpg");
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
	      		//traitement de l'image suivant la DCT avec le code de GUY
	      		//this->saveImage(tab,x,y,bloc); //permet de commencer la reconstruction par bloc
	    	}
		}
    }
}

void	decompress::setRecontructionImage(int height,int width)
{
	int size = height * width;
	int i = 0;

	this->ImgRec = (int**)malloc(height*sizeof(int*));
	while(i < height)
	{
		this->ImgRec[i] = (int*)malloc(width*sizeof(int*));
		i++;
	}
}

int		**decompress::getRecontructionImage()
{
  	return (this->ImgRec);
}

void	decompress::saveImage(int *tab,int x, int y, IplImage *bloc)
{
	int blocH = bloc->height;
   	int blocW = bloc->width;
	int blocSize = blocH*blocW;
	int	i = 0;
	
	// x=1 y=4 blocH=8 blocW=8
	while (tab[i] && i < blocSize)
	{
		this->ImgRec[x+i][y+i] = tab[i];
		i++;
	}
}
