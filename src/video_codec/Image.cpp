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

void	Image::setTab(int *tab,int width,int height)
{
    this->tab = new int[height * width * 3];
    for(int i = 0; i < height * width * 3; i++)
	    this->tab[i] = tab[i];
}

int		Image::getHeight()
{
    return(this->height);
}

int 	Image::getWidth()
{
    return(this->width);
}

int		*Image::getTab()
{
    return(this->tab);
}
