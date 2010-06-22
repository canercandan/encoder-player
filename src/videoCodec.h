#ifndef VIDEOCODEC_H
#define VIDEOCODEC_H

#include <list>
#include <string>

class	videoCodec
{
public:
  videoCodec();
  void		SaveImgInList(int **);
  void		createFile(std::string);
  void		SaveFlux(); // creation fichier type

private:
  std::list<int**>		ListImage;
  std::string			FileName;
};

#endif // !VIDEOCODEC_H
