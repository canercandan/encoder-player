#include <cstdlib>
#include "dct.h"
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

  	image = bloc = cvLoadImage("C:/Users/guillaume/Pictures/26978_1389454369924_1039030242_1160709_2796358_n.jpg");
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
				
	      		//traitement de l'image suivant la DCT avec le code de GUY
	      		this->saveImage(temp,x,y,bloc); //permet de commencer la reconstruction par bloc
	    	}
		}
    }
	VC.SaveImgInList(this->ImgRec,width,height);
	
	VC.createFile("test.GuiGuy");
	
	VC.SaveFlux();
}

void	decompress::setRecontructionImage(int height,int width)
{
	//imRec[width][height]
	this->ImgRec = new short int*[width];
	for(int i=0; i < width; i++)
		this->ImgRec[i] = new short int[height];
}

short int		**decompress::getRecontructionImage()
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
	
	// x=1 y=4 blocH=8 blocW=8
	//hauteur x largeur + i
	while (count < blocSize)
	{
		if ((i == 7) && (j == 7))
			break ;
		if (j == 7)
		{
			i++;
			j = 0;
		}
		this->ImgRec[x+i][y+j] = tab[count];
		j++;
		count++;
	}
}
