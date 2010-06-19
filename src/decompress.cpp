
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
	this->setRecontructionImage(image);
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

				/*cvShowImage( "Window", subimg);
				cvShowImage( "Window 2", image);
				cvDestroyWindow("Window");
				cvDestroyWindow("Window 2");*/
			}
		}
	}
	//recuperation de l'image
	IplImage *EndImage = this->getRecontructionImage();

	//affichage de cette image
	cvShowImage("window", EndImage);
	cvWaitKey(5000);
}

void		decompress::setRecontructionImage(IplImage *image)
{
	this->ImgRec = cvCreateImage(cvGetSize(image),
								image->depth,
								image->nChannels);
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

	//reconstitution de l'image suivant chaque bloc
	/* Avec le x et y nous avons la position pour placer l'image
	// Il faut donc recuperer ImgRec pour placer le bloc dedans avec les x et y bien positionner
	*/
	this->ImgRec = bloc;
	cvShowImage("window", this->ImgRec);
	cvWaitKey(0);
	


}
