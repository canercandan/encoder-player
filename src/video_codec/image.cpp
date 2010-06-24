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

void	image::setTab(short int **tab)
{
	this->tab = tab;
}

int		image::getHeight()
{
	return(this->height);
}

int 	image::getWidth()
{
	return(this->width);
}

short int		**image::getTab()
{
	return(this->tab);
}

