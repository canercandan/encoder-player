#ifndef VIDEOCODEC_H
#define VIDEOCODEC_H

#include <list>
#include <string>
#include "image.h"

class	videoCodec
{
public:
  videoCodec();
  void		SaveImgInList(short int **, int,int);
  void		createFile(std::string);
  void		compression(int,int);
  int		**decompression();
  void		SaveFlux(); // creation fichier type

private:
  std::list<image>		ListImage;
  std::string			FileName;
};

#endif // !VIDEOCODEC_H
