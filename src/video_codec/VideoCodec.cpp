#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

#include "Huffman.h"
#include "DCT.h"
#include "Quantizer.h"
#include "VideoCodec.h"

VideoCodec::VideoCodec()
{}

void	VideoCodec::SaveImgInList(int **tab, int width, int height)
{
    Image 	img;
    img.setHeight(height);
    img.setWidth(width);
    img.setTab(tab,width,height);

    this->ListImage.push_back(img);
}

void		VideoCodec::createFile(std::string filename) //creation du fichier de sortie avec le nom que tu veu
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

void		VideoCodec::SaveFlux() //enregistrement de la liste remplie des datas images dans le flux de sortie en binaire
{
    FILE *file = fopen(this->FileName.c_str(), "w");
    std::list<Image>::iterator	it;
    int width=0,height=0;

    it = this->ListImage.begin();
    if (file == NULL)
    	std::cout << "Impossible d'ouvrir le fichier en lecture !" << std::endl;
    else
  	{
	    for (it = this->ListImage.begin(); it != this->ListImage.end(); it++) //parcours de chaq image stocker dans la list
		{
		    int **tab = it->getTab();
		    width = it->getWidth();
		    height = it->getHeight();//data de l'image restocker dans un tableau a deux dimension

		    fprintf(file, "%d",width);
		    fprintf(file, "%c", '/');
		    fprintf(file, "%d",height);
		    fprintf(file, "%c", '/');
		    std::cout << width << "/" << height << std::endl;
		    for(int i = 0; i < width; i++)
			for(int j=0; j < height; j++)
			    {
				fprintf(file, "%d",tab[i][j]);
				fprintf(file, "%c", '/');
			    }
		    fprintf(file, "%c", 'O');
		    fclose(file);
		    this->compression(width,height);
		    /*::sleep(1000);*/
		    /*this->decompression();
		    int **Endtab = this->lectureFichier();
		    (void)Endtab;*/
		}
	}
}

void		VideoCodec::compression(int width, int height)
{
    std::cout << "Starting compressing image" << std::endl;
    unsigned char *dest,*sour;
    int usize,csize;
    Huffman huf;
    fpos_t position;

    FILE *source_file = fopen(this->FileName.c_str(), "r");
    FILE *dest_file = fopen("image_compress", "w");
    usize = get_file_size(source_file);

    sour = new unsigned char[usize];
    dest = new unsigned char[usize];
    usize = (int)fread(sour, 1, usize, source_file);
    huf.encode(dest, csize, sour, usize);
    fwrite(dest, 1, csize, dest_file);

    fclose(source_file);
    fclose(dest_file);
    remove(this->FileName.c_str());
    std::cout << "Deleting source file" << std::endl;
}

void	VideoCodec::decompression()
{
    std::cout << "Starting decompressing image" << std::endl;
    unsigned char *dest,*sour;
    int usize,csize;
    Huffman huf;

    FILE *dest_file = fopen("image_decompress", "w");
    FILE *source_file = fopen("image_compress", "r");
    if (source_file == NULL || dest_file == NULL)
	std::cout << "impossible d'ouvrir le fichier" << std::endl;

    csize = get_file_size(source_file);

    sour = new unsigned char[csize];
    csize = fread(sour, 1, csize, source_file);
    dest = new unsigned char[huf.get_uncompressed_size(sour)];

    huf.decode(dest, csize, sour);
    fwrite(dest, 1, csize, dest_file);

    fclose(source_file);
    fclose(dest_file);
    std::cout << "decompressing finish" << std::endl;
}

std::pair<int *, int **>	VideoCodec::lectureFichier()
{
    std::cout << "Starting reading file" << std::endl;
    int				height,width,i,j,flag;
    int				**imgDec;
    std::string		str;
    char			c = 'a';
    char			a = 'a';
    int				count = 0;
    i = j = flag=0;

    FILE			*f = fopen("image_decompress", "r");
    while (flag != 3)
	{
	    if (flag == 1)
		str = "";
	    fscanf(f,"%c",&c);
	    if (c != '/')
		{
		    flag = 0;
		    str += c;
		}
	    else
		{
		    flag=1;
		    fscanf(f,"%a", &a);
		    if ( a == 'O')
			flag = 3;
		    count++;
		    if (count == 1)
			width = atoi(str.c_str());
		    if (count == 2)
			{
			    height = atoi(str.c_str());
			    break;
			}
		}
	}

    std::cout << width << "x" << height << std::endl;
    imgDec = new int*[width];
    for(int i=0; i <= width; i++)
	imgDec[i] = new int[height];

    while ( i != width && j != height)
	{
	    if (flag == 1)
		str = "";
	    fscanf(f,"%c",&c);
	    if (c != '/')
		{
		    flag = 0;
		    str += c;
		}
	    else
		{
		    flag=1;
		    if ( i == width && j == height)
			break;
		    if (j == (height-1))
			{
			    j = 0;
			    i++;
			}
		    imgDec[i][j] = atoi(str.c_str());
		    j++;
		}
	}
    std::cout << "Tableau created" << std::endl;
	std::pair<int *, int **>	res;
	int							dimensions[2];
	dimensions[0] = height;
	dimensions[1] = width;
	res.first = dimensions;
	res.second = imgDec;
    return (res);
}
