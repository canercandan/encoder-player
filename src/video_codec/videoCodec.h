#ifndef VIDEOCODEC_H
#define VIDEOCODEC_H

#include <list>
#include <string>
#include "image.h"

class	videoCodec
{
public:
  videoCodec();
  void		SaveImgInList(int **, int,int);
  void		createFile(std::string);
  void		compression(int,int);
  void		decompression();
  int		**lectureFichier();
  void		SaveFlux(); // creation fichier type

private:
  std::list<image>		ListImage;
  std::string			FileName;
};

#endif
