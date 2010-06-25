#include "image.h"

image::image()
{
}

void	image::setHeight(int height)
{
	this->height = height;
}

void 	image::setWidth(int width)
{
	this->width = width;
}

void	image::setTab(int **tab,int width,int height)
{
	this->tab = new int*[width];
	for(int i=0; i < width; i++)
		this->tab[i] = new int[height];

	for(int i=0; i<width;i++)
		for(int j=0; j<height;j++)
			this->tab[i][j] = tab[i][j];
}

int		image::getHeight()
{
	return(this->height);
}

int 	image::getWidth()
{
	return(this->width);
}

int		**image::getTab()
{
	return(this->tab);
}

