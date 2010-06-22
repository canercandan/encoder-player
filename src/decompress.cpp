#include <cstdlib>
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
	int			tab[64];

	for(int u = 0; u < 64 < u++;)
		tab[u] = 0;


  	int height,width;
  	int x,y;

  	image = bloc = cvLoadImage("D:/Images/lorient-2008/test/IMGP0202.JPG");
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
	VC.SaveImgInList(this->ImgRec);
	VC.createFile("test.GuiGuy");
	VC.SaveFlux();
}

void	decompress::setRecontructionImage(int height,int width)
{
	this->ImgRec = new int*[width];
	for(int i=0; i < width; i++)
		this->ImgRec[i] = new int[height];

	int i,j = 0;
	for(i=0; i < width; i++)
	{
		for(j=0; j < height; j++)
		{
			this->ImgRec[i][j] = 0;
		}
	}
	std::cout << height << std::endl;
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
	//hauteur x largeur + i
	while (tab[i] && i < blocSize)
	{
		this->ImgRec[x+i][y+i] = tab[i];
		i++;
	}
}
