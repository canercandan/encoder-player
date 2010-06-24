#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "videoCodec.h"
#include "huffman.h"

videoCodec::videoCodec()
{
}

void		videoCodec::SaveImgInList(short int **tab, int width, int height)
{
	image 	img;
	img.setHeight(height);
	img.setWidth(width);
	img.setTab(tab);

	this->ListImage.push_back(img);
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

int get_file_size(FILE *fp)
{
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        return size;
}

void		videoCodec::SaveFlux() //enregistrement de la liste remplie des datas images dans le flux de sortie en binaire
{
	std::ofstream file(this->FileName.c_str(), std::ios::out | std::ios::binary);
	std::list<image>::iterator	it;
	int width=0,height=0;
	
	it = this->ListImage.begin();
  	if (!file.is_open())
    	std::cout << "Impossible d'ouvrir le fichier en lecture !" << std::endl;
  	else
  	{
		for (it = this->ListImage.begin(); it != this->ListImage.end(); it++) //parcours de chaq image stocker dans la list
		{
			short int **tab = it->getTab();
			width = it->getWidth();
			height = it->getHeight();//data de l'image restocker dans un tableau a deux dimension

			for(int i = 0; i < width; i++)
				for(int j=0; j < height; j++)
					std::cout << tab[i][j] << height << std::endl;
			//file.write ((char*)&width,sizeof(int)); //ecriture de la largeur dans le fichier
			//file.write ((char*)&width,sizeof(int)); //ecriture de la hauteur dans le fichier
			//for(int i = 0; i < width-1; i++)
			//	for(int j=0; j < height-1; j++)
			//		file.write ((char*)&tab[i][j],sizeof(int)); //ajout de chaque octets dans le fichier un a un
			//
			//this->compression(width,height);
			//int **taubleau = this->decompression();
		}	
	}
}

void		videoCodec::compression(int width, int height)
{
	unsigned char *dest,*sour;
	int usize,csize;
	Huffman huf;
	fpos_t position;

	FILE *source_file = fopen(this->FileName.c_str(), "r");
	FILE *dest_file = fopen("image_compress", "w");
	fgetpos (dest_file, &position);


	usize = get_file_size(source_file);
                        
    sour = new unsigned char[usize];
    dest = new unsigned char[usize];
    usize = (int)fread(sour, 1, usize, source_file);
	huf.encode(dest, csize, sour, usize);

    fwrite(dest, 1, csize, dest_file);
}

int		**videoCodec::decompression()
{
	unsigned char *dest,*sour;
	int usize,csize;
	Huffman huf;
	FILE *dest_file;

	FILE *dest_file2 = fopen("image_decompress", "w");
	FILE *source_file2 = fopen("image_compress", "r");
	csize = get_file_size(source_file2);

    sour = new unsigned char[csize];
    csize = fread(sour, 1, csize, source_file2);
	dest = new unsigned char[huf.get_uncompressed_size(sour)];
		std::cout << "je passe" << std::endl;
	huf.decode(dest, csize, sour);
	fwrite(dest, 1, csize, dest_file2);
	
	int a,width,height,i,j;
	int **imgDec;
	i = j = 0;
	std::ifstream f ("image_decompress", std::ios::in | std::ios::binary);
	f.read ((char *)&width, sizeof(int));
	f.read ((char *)&height, sizeof(int));
	imgDec = new int*[width];
	for(int i=0; i < width; i++)
		imgDec[i] = new int[height];
		
	std::cout << width << "x" << height << std::endl;
	while(!f.eof())
	{
		if (j == (height-1))
		{
			j=0;
			i++;
		}
		f.read ((char *)&a, sizeof(int));
		imgDec[i][j] = a;
		j++;
	}
	return (imgDec);
}