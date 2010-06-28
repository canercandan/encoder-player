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

    void						SaveImgInList(int **, int,int);
    void						createFile(std::string);
    void						compression(int,int);
    void						decompression();
	/**
	*@return Pair<int *, int **> containing the array  of image,s dimension and it's datas
	**/
    std::pair<int *, int **>	lectureFichier();
    void						SaveFlux(); /* creation fichier type*/

private:
    std::list<Image>			ListImage;
    std::string					FileName;
};

#endif							/* !VIDEOCODEC_H */
