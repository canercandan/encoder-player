
#include "decompress.h"

decompress::decompress()
{
}

bool		decompress::CalcBlocSize(int width, int height, int y, int x)
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

void		decompress::loadImage()
{
	IplImage *image;
	IplImage *bloc;
	int height,width;
	int x,y,k,j;
 
	image = bloc = cvLoadImage("C:/Users/Public/Pictures/Sample Pictures/Tulips.jpg");
	cvShowImage("window origin", image);
	this->setRecontructionImage(image);
	cvShowImage("window final au debut", this->ImgRec);
	height = image->height;
	width = image->width; 
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
				this->saveImage(image,x,y,bloc); //permet de commencer la reconstruction par bloc
			}
		}
	}
	//affichage de cette image
	cvShowImage("window End", this->ImgRec);
	cvWaitKey(0);
}

void		decompress::setRecontructionImage(IplImage *image)
{
	this->ImgRec = cvCreateImage(cvGetSize(image),
								image->depth,
								image->nChannels);
	cvSet( this->ImgRec, cvScalar( 0, 0, 0 ));
}

IplImage	*decompress::getRecontructionImage()
{
	return (this->ImgRec);
}

void		decompress::saveImage(IplImage *image,int x, int y, IplImage *bloc)
{
	int			blocH;
	int			blocW;

	blocH = bloc->height;
	blocW = bloc->width;

	CvRect rect = cvRect(x, y, this->BlocW,this->BlocH);
	cvSetImageROI(this->ImgRec, rect);
	cvAdd(this->ImgRec,bloc,this->ImgRec,0);
	cvResetImageROI(this->ImgRec);
}
