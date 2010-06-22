#include <cstdlib>
#include <iostream>
#include<cstdio>
#include "videoCodec.h"

videoCodec::videoCodec()
{
}

void		videoCodec::SaveImgInList(int **tab)
{
	this->ListImage.push_back(tab);
}

void		videoCodec::createFile(std::string filename)
{
	FILE * file;
	this->FileName = filename;
	
	file = fopen(filename.c_str(), "wb");
	if (file == NULL)
		std::cout << "Problem created" << std::endl;
	else
		fclose(file);
}
void		videoCodec::SaveFlux()
{
	FILE * file;
	std::list<int**>::iterator	it;

	it = this->ListImage.begin();

	file = fopen(this->FileName.c_str(), "wb");
  	if (file == NULL)
    	std::cout << "Impossible d'ouvrir le fichier en lecture !" << std::endl;
  	else
  	{
		for (it = this->ListImage.begin(); it != this->ListImage.end(); it++) //parcours de chaq image stocker dans la list
		{
			int **tab = *it; //data de l'image restocker dans un tableau a deux dimension

			for(int i = 0; i < 3264; i++)
			{
				for(int j=0; j< 2448; j++)
				{
					fwrite (&tab[i][j],sizeof(int),1,file); //ajout de chaque octets dans le fichier un a un
				}
			}
			
		}
	}
}