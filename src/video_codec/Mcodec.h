#ifndef		MCODEC_H
#define		MCODEC_H
/**			INCLUDE SYSTEME			**/
#include	<cv.h>
#include	<cxcore.h>
#include	<highgui.h>
#include	<cstdlib>
#include	<iostream>
#include 	<iostream>
#include 	<utility>
#include 	<string>
/**			INCLUDES				**/
#include	"video_codec/DCT.h"
#include	"video_codec/Quantizer.h"
#include	"video_codec/VideoCodec.h"

class		Mcodec
{
public:
/**			C-TOR				**/
			Mcodec();
	/**
	*@param string the path of the image to be compress using our algorithm
	**/
	void	compressImage(std::string);
	/**
	*@param IplImage the image to be reconstructed
	**/
	void	compressImage(IplImage *);
	/**
	*extract the information from a file
	**/
	void	uncompressImage();
	void	saveImage(short int*,int,int,IplImage*);
	void	setRecontructionImage(int,int);
	int		**getRecontructionImage();
	bool	CalcBlocSize(int,int,int,int);
	/**
	*@param IplImage the image to be displayed
	*@warning the memory management is not handled by this function
	**/
	void	dislay_picture(IplImage *image);
private:
/**			ATTRIBUTES			**/
	int		BlocW;
	int		BlocH;
	int		**ImgRec; /*ImgRec[width][height]*/
/**			METHODS				**/
	/**
	*@param int ** a 2-dimension array
	*@param int the height of the array in parameter
	*@param int the width of the array in parameter
	**/
	short int	*twoDimensionToOneDimension(int **tab_src, int height, int width);
};

#endif		/*!MCODEC_H*/