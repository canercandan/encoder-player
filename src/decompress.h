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
  void		saveImage(int*,int,int,IplImage*);
  void		setRecontructionImage(int,int);
  int		**getRecontructionImage();
  bool		CalcBlocSize(int,int,int,int);

private:
  int		BlocW;
  int		BlocH;
  int		**ImgRec; //ImgRec[width][height]
};

#endif // !DECOMPRESS_H
