#ifndef IMAGE_H
#define IMAGE_H

#include <list>
#include <string>

class	image
{
public:
  image();
  int	getWidth();
  int	getHeight();
  int	**getTab();
  void	setWidth(int);
  void	setHeight(int);
  void	setTab(int **,int,int);
  

private:
  int		width;
  int		height;
  int		**tab;
};

#endif // !IMAGE_H