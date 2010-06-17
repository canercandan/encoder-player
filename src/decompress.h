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
		void	loadImage();
		bool	CalcBlocSize(int,int,int,int);

	private:
		int		BlocW;
		int		BlocH;
};

#endif