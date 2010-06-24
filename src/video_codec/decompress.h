#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

class	decompress
{
public:
  decompress();

  void		loadImage();
  void		saveImage(short int*,int,int,IplImage*);
  void		setRecontructionImage(int,int);
  short int		**getRecontructionImage();
  bool		CalcBlocSize(int,int,int,int);

private:
  int		BlocW;
  int		BlocH;
  short int		**ImgRec; //ImgRec[width][height]
};

#endif // !DECOMPRESS_H