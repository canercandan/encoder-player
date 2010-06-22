#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "videoCodec.h"

videoCodec::videoCodec()
{
}

void		videoCodec::SaveImgInList(int **tab)
{
	this->ListImage.push_back(tab);
}

void		videoCodec::createFile(std::string filename) //creation du fichier de sortie avec le nom que tu veu
{
	FILE * file;
	this->FileName = filename;
	
	file = fopen(filename.c_str(), "wb");
	if (file == NULL)
		std::cout << "Problem created" << std::endl;
	else
		fclose(file);
}

void		videoCodec::SaveFlux() //enregistrement de la liste remplie des datas images dans le flux de sortie en binaire
{
	std::ofstream file(this->FileName.c_str(), std::ios::out | std::ios::binary);
	std::list<int**>::iterator	it;
	int width=0,height=0;

	it = this->ListImage.begin();
  	if (!file.is_open())
    	std::cout << "Impossible d'ouvrir le fichier en lecture !" << std::endl;
  	else
  	{
		for (it = this->ListImage.begin(); it != this->ListImage.end(); it++) //parcours de chaq image stocker dans la list
		{
			int **tab = *it; //data de l'image restocker dans un tableau a deux dimension

			 //calcul de la taille du tableau width / height
			while(tab[width])
				width++;
			while(tab[0][height])
				height++;
			
			for(int i = 0; i < width-1; i++)
				for(int j=0; j < height-1; j++)
					file.write ((char*)&tab[i][j],sizeof(int)); //ajout de chaque octets dans le fichier un a un
		}
	}

	file.close();
	/*std::ifstream file2(this->FileName.c_str(), std::ios::in | std::ios::binary);
	int a;
	while(!file2.eof())
	{
		file2.read((char*)&a, sizeof(int));
		std::cout << a << std::endl;
	}*/
}