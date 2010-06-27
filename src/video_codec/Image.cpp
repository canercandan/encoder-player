#include "Image.h"

Image::Image()
{}

void	Image::setHeight(int height)
{
    this->height = height;
}

void 	Image::setWidth(int width)
{
    this->width = width;
}

void	Image::setTab(int **tab,int width,int height)
{
    this->tab = new int*[width];
    for(int i=0; i < width; i++)
	this->tab[i] = new int[height];

    for(int i=0; i<width;i++)
	for(int j=0; j<height;j++)
	    this->tab[i][j] = tab[i][j];
}

int		Image::getHeight()
{
    return(this->height);
}

int 	Image::getWidth()
{
    return(this->width);
}

int		**Image::getTab()
{
    return(this->tab);
}
