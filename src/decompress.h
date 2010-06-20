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
  void		saveImage(IplImage*,int,int,IplImage*);
  void		setRecontructionImage(IplImage*);
  IplImage	*getRecontructionImage();
  bool		CalcBlocSize(int,int,int,int);

private:
  int		BlocW;
  int		BlocH;
  IplImage	*ImgRec;
};

#endif // !DECOMPRESS_H
