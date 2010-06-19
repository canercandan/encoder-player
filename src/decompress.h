#ifndef __DECOMPRESS_H__
#define __DECOMPRESS_H__

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <stdlib.h>

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
		IplImage *ImgRec;
};

#endif