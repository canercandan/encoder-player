#ifndef 						VIDEOCODEC_H
#define 						VIDEOCODEC_H

#include 						<list>
#include 						<string>
#include						<iostream>
#include						<utility>
#include						<string>
#include 						"Image.h"

class							VideoCodec
{
public:
								VideoCodec();

    void						SaveImgInList(int *, int,int);
    void						createFile(std::string);
    void						compression();
    void						decompression(std::string);
	/**
	*@return Image an object from Image class containing two int (height and width) and int **
	**/
    std::list<Image>					lectureFichier();
    void						SaveFlux(); /* creation fichier type*/

private:
    std::list<Image>				ListImage;
    std::string					FileName;
};

#endif							/* !VIDEOCODEC_H */
