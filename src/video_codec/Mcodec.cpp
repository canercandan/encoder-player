
#include "Mcodec.h"
#include <stdio.h>

Mcodec::Mcodec()
{}

bool	Mcodec::CalcBlocSize(int width, int height, int y, int x)
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

void				Mcodec::dislay_picture(IplImage *image)
{
    cvNamedWindow("mwindow");
    cvShowImage("mwindow", image);
    cvWaitKey();
    cvDestroyWindow("mwindow");
}

void				Mcodec::compressImage(std::string image_path)
{
    IplImage		*image;
    DCT				dct;
    Quantizer		Q;
    int				height,width;
    int				x,y;
	CvScalar		*temp;
	int				*img;

    image = cvLoadImage(image_path.c_str());
    height = image->height;
    width = image->width;
	temp = new CvScalar[height * width];
    for (x = 0; x < height; x++)
	    for(y=0; y < width; y++)
			temp[x * width + y] = cvGet2D(image, x, y);
	img = new int[height * width * 3];
	for (int i = 0; i < width; i++)
		for (int j = 0, index = 0; j < height; j++, index += 3)
		{
			img[i * height + index] = (int)temp[i * height + j].val[0];
			img[i * height + index + 1] = (int)temp[i * height + j].val[1];
			img[i * height + index + 2] = (int)temp[i * height + j].val[2];
		}
	this->VC.SaveImgInList(img, height, width);

}

void							Mcodec::uncompressImage(std::string file)
{
	VideoCodec					vc;
	//	Image							infos; //Modification du type de infos (objet image)
	short int					*values;
	unsigned char				*datas;
	DCT							dct;
	Quantizer					qt;
	int							height;
	int							width;
	IplImage					*image;
	std::list<Image>			infos;
	std::list<Image>::iterator	it;
	CvScalar					*temp;

	vc.decompression(file);
	infos = vc.lectureFichier();
	it = infos.begin();
	std::cout << "abc" << std::endl;
	for (it = infos.begin(); it != infos.end(); it++)
	{
		int *tab = it->getTab();
	
		width = it->getWidth();
		height = it->getHeight();
		temp = new CvScalar[height * width];
		image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
		for (int i = 0; i < width; i++)
			for (int j = 0, index = 0; j < height; j++, index += 3)
			{
				temp[i * height + j].val[0] = tab[i * height + index];
				temp[i * height + j].val[1] = tab[i * height + index + 1];
				temp[i * height + j].val[2] = tab[i * height + index + 2];
			}
		for (int x = 0; x < height; x++)
			for(int y = 0; y < width; y++)
				cvSet2D(image, x, y, temp[x * width + y]);
		this->dislay_picture(image);
		delete [] temp;
	}
 }

void						Mcodec::saveVideo(std::string file)
{
  	this->VC.createFile(file);
	this->VC.SaveFlux();
	this->VC.compression();
}

short int					*Mcodec::twoDimensionToOneDimension(int **tab_src, int height, int width)
{
	short int				*tab_dst;
	
	tab_dst = new short int[height * width];
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		  {
		    tab_dst[x * height + y] = (short int) tab_src[x][y];
		  }
	return (tab_dst);
}

void				Mcodec::compressImage(IplImage *image)
{
    DCT				dct;
    Quantizer			Q;
    int				height,width;
    int				x,y;
	CvScalar		*temp;
       int				*img;

    height = image->height;
    width = image->width;
	temp = new CvScalar[height * width];
    for (x = 0; x < height; x++)
	    for(y=0; y < width; y++)
			temp[x * width + y] = cvGet2D(image, x, y);
	img = new int[height * width * 3];
	for (int i = 0; i < width; i++)
		for (int j = 0, index = 0; j < height; j++, index += 3)
		{
			img[i * height + index] = (int)temp[i * height + j].val[0];
			img[i * height + index + 1] = (int)temp[i * height + j].val[1];
			img[i * height + index + 2] = (int)temp[i * height + j].val[2];
		}
	this->VC.SaveImgInList(img, height, width);    
}

void	Mcodec::setRecontructionImage(int height,int width)
{
    //imRec[width][height]
  this->ImgRec = new int[height*width*3];
}

int		*Mcodec::getRecontructionImage()
{
    return (this->ImgRec);
}

void	Mcodec::saveImage(short int *tab,int x, int y, IplImage *bloc)
{
  /*    int blocH = bloc->height;
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
	    }*/
}
