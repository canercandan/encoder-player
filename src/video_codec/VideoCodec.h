#ifndef VIDEOCODEC_H
#define VIDEOCODEC_H

#include <list>
#include <string>

#include "Image.h"

class	VideoCodec
{
public:
    VideoCodec();

    void		SaveImgInList(int **, int,int);
    void		createFile(std::string);
    void		compression(int,int);
    void		decompression();
    int			**lectureFichier();
    void		SaveFlux(); // creation fichier type

private:
    std::list<Image>		ListImage;
    std::string			FileName;
};

#endif
