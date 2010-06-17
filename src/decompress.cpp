
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
	IplImage *subimg;
	int height,width;
	int x,y,k,j;
 
	image = subimg = cvLoadImage("C:/Users/Public/Pictures/Sample Pictures/Tulips.jpg");
	height = image->height;
	width = image->width; 
	for (x = 0; x <= width; x+=8)
	{
		for(y=0; y <= height; y+=8)
		{
			if (this->CalcBlocSize(width,height,y,x) == true)
			{
				if (this->BlocH != 8 || this->BlocW != 8)
					std::cout << "x:" << x << "y: " << y << "blocW: " << this->BlocW << "blocH: " << this->BlocH << std::endl;
				CvRect rect = cvRect(x, y, this->BlocW,this->BlocH);
				cvSetImageROI(image, rect);
				subimg = cvCreateImage(cvGetSize(image),
	            	                   image->depth,
	                	               image->nChannels);
				cvCopy(image, subimg, NULL);
				cvResetImageROI(image);
				/*cvShowImage( "Window", subimg);
				cvShowImage( "Window 2", image);
				cvDestroyWindow("Window");
				cvDestroyWindow("Window 2");*/
			}
		}
	}
}
