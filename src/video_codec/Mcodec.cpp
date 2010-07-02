
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
    VideoCodec		VC;
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
			temp[y * width + x] = cvGet2D(image, y, x);
	img = new int[height * width * 3];
	for (int i = 0, ; i < height; i++)
		for (int j = 0, index = 0; j < width; j++, index += 3)
		{
			img[i * width + index] = (int)temp[i * width + j].val[0];
			img[i * width + index + 1] = (int)temp[i * width + j].val[1];
			img[i * width + index + 2] = (int)temp[i * width + j].val[2];
		}
	VC.SaveImgInList(img, height, width);
}

void							Mcodec::uncompressImage()
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

	vc.decompression();
	infos = vc.lectureFichier();
	it = infos.begin();
	for (it = infos.begin(); it != infos.end(); it++)
	{
		int *tab = it->getTab();
		width = it->getWidth();
		height = it->getHeight();
		temp = new CvScalar[height * width];
		image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
		for (int i = 0; i < height; i++)
			for (int j = 0, index = 0; j < width; j++, index += 3)
			{
				temp[i * width + j].val[0] = tab[i * width + index];
				temp[i * width + j].val[1] = tab[i * width + index + 1];
				temp[i * width + j].val[2] = tab[i * width + index + 2];
			}
		for (int x = 0; x < height; x++)
			for(int y = 0; y < width; y++)
				cvSet2D(image, x, y, temp[x * width + y]);
		this->dislay_picture(image);
		delete [] temp;
	}
	  /*	std::cout << "video codec decompression ()" << std::endl;
	vc.decompression();
	std::cout << "lecture du fichier" << std::endl;
	infos = vc.lectureFichier();
	height = infos.getHeight(); //recuperation de la heuteur
	width = infos.getWidth(); //recuperation de la largeur
     	if ((height * width) % 8)
		return ;
	image = cvCreateImage(cvSize(height, width),IPL_DEPTH_8U,1);
	std::cout << "conversion tableau begin." << std::endl;
	values = this->twoDimensionToOneDimension(test, height, width);
	std::cout << "conversion tableau end." << std::endl;
	datas = (uchar *) image->imageData;
	std::cout << "reverse dct and quantization starting." << std::endl;
	for (int cpt = 0; cpt < height * width; cpt+= 8)
	{
		qt.unquantizeDCTMatrix(values + cpt);
		dct.referenceIDCT(values + cpt, datas +cpt);
	}
	this->dislay_picture(image);
	std::cout << "reverse dct and quantization complete." << std::endl;
	delete (values);*/
	
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
    IplImage		*bloc;
    VideoCodec		VC;
    DCT				dct;
    Quantizer		Q;
    short int		temp[64];
    int				height,width;
    int				x,y;

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

void	Mcodec::setRecontructionImage(int height,int width)
{
    //imRec[width][height]
  this->ImgRec = new int[height*width*3];
}

int		*Mcodec::getRecontructionImage()
{
    return (this->ImgRec);
}

/*void	Mcodec::saveImage(short int *tab,int x, int y, IplImage *bloc)
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
	}*/
