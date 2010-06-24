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
  short int	**getTab();
  void	setWidth(int);
  void	setHeight(int);
  void	setTab(short int **);
  

private:
  int		width;
  int		height;
  short int		**tab;
};

#endif // !IMAGE_H