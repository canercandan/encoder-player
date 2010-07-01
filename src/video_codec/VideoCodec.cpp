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

void	VideoCodec::SaveImgInList(int *tab, int width, int height)
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
    int count = 0;

    it = this->ListImage.begin();
    if (file == NULL)
    	std::cout << "Impossible d'ouvrir le fichier en lecture !" << std::endl;
    else
  	{
	    for (it = this->ListImage.begin(); it != this->ListImage.end(); it++)
		{
		    std::cout << "Enregistrement de la :" << count+1 << std::endl;
		    int *tab = it->getTab();
		    width = it->getWidth();
		    height = it->getHeight();
		    if (count == 0)
			{
			    fprintf(file, "%d",width);
			    fprintf(file, "%c", '/');
			    fprintf(file, "%d",height);
			    fprintf(file, "%c", '/');
			    std::cout << width << "/" << height << std::endl;
			}

		    for(int i = 0; i < height; i++)
			for(int j=0; j < width; j++)
			    {
				fprintf(file, "%d",tab[i * width +j]);
				fprintf(file, "%c", '/');
			    }
		    fprintf(file, "%c", 'N');
		    count++;
		}
	    fprintf(file, "%c", 'Q');
	    fclose(file);
	    //this->compression(width,height);
	}
}

void		VideoCodec::compression()
{
    std::cout << "Starting compressing image" << std::endl;
    unsigned char *dest,*sour;
    int usize,csize;
    Huffman huf;
    //fpos_t position; // not used

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
    //    remove(this->FileName.c_str());
    std::cout << "Deleting source file" << std::endl;
}

void	VideoCodec::decompression()
{
    std::cout << "Starting decompressing image" << std::endl;
    unsigned char *dest,*sour;
    //int usize; // not used
    int csize;
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

std::list<Image>		VideoCodec::lectureFichier()
{
    std::cout << "Starting reading file" << std::endl;
    int				height,width,i,j,flag;
    int				*imgDec;
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
    imgDec = new int[height * width * 3];
   
    while (c != 'Q')
	{
	    if (flag == 1)
		str = "";
	    fscanf(f,"%c",&c);
	    if (c != '/' && c != 'N')
		{
		    flag = 0;
		    str += c;
		}
	    else if (c == 'N')
		{
		    i = j = 0;
		    this->SaveImgInList(imgDec,width,height);
		}
	    else
		{
		    flag=1;
		    if (j == (height-1))
			{
			    j = 0;
			    i++;
			}
		    imgDec[i*width+j] = atoi(str.c_str());

		    j++;
		}
	}
    fclose(f);
    return (this->ListImage);
}
