#include <cstdlib>

#include		<iostream>
#include		"video_codec/VideoCodec.h"
#include		"video_codec/DCT.h"
#include		"video_codec/Quantizer.h"
#include		"video_codec/Image.h"

int **oneD_twoD(short int * src, int height, int width)
{
    int			**res;

    res = new int *[height];
    for (int i = 0; i < height; i++)
	res[i] = new int[width];
    for (int i = 0; i < height; i++)
	for (int j = 0; j < width; j++)
	    res[i][j] = (int) src[i * width + j];
    return (res);
}

short int		*twoD_oneD(int **src, int height, int width)
{
	short int	*res;

	res = new short int[height * width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			res[i * width + j] = (short int) src[i][j];
	return (res);
}

int				main ()
{
    char			c;
    unsigned char 	*tab;
    VideoCodec		vc;
    DCT				dct;
    short int		*tabDct;
    Quantizer		quantizer;
    int				**tab2;
    int				height;
    int				width;
    Image			infos;

    srand (time(NULL));
    std::cout << "choose activity" << std::endl;
    std::cout << "1 : compress" << std::endl;
    std::cout << "2 : uncompress" << std::endl;
    std::cin >> c;
    if (c == '1')
	{
	    /*création et initialisation d'un tableau*/
	    std::cout << "** initiate arrays. **" << std::endl;
	    tab = new unsigned char [64];
	    tabDct = new short int [64];
	    std::cout << "** array initiation complete **" << std::endl;
	    /*insertion de valeur dans le tableau entre 0 et 255*/
	    std::cout << "** affect values to array's cells. **" << std::endl;
	    for (int i = 0; i < 64; i++)
		{
		    if (!(i % 8))
			std::cout << "\t";
		    std::cout << "|";
		    tab[i] = rand() % 255;
		    std::cout << tab[i];
		    if ((i % 8) == 7)
			std::cout << std::endl;
		}
	    std::cout << "** affectation to array's cells complete. **" << std::endl;
	    /*Apply dct*/
	    std::cout << "** apply dct. **" << std::endl;
	    dct.referenceDCT(tab, tabDct);
	    for (int i = 0; i < 64; i++)
		{
		    if (!(i % 8))
			std::cout << "\t";
		    std::cout << "|";
		    std::cout << tabDct[i];
		    if ((i % 8) == 7)
			std::cout << std::endl;
		}
	    std::cout << "** dct applied. **" << std::endl;
	    /*Apply quantization*/
	    std::cout << "** apply quantization. **" << std::endl;
	    quantizer.quantizeDCTMatrix(tabDct);
	    for (int i = 0; i < 64; i++)
		{
		    if (!(i % 8))
			std::cout << "\t";
		    std::cout << "|";
		    std::cout << tabDct[i];
		    if ((i % 8) == 7)
			std::cout << std::endl;
		}
	    std::cout << "** quantization applied. **" << std::endl;
	    /*building the array to be saved*/
	    std::cout << "** changing array dimension. **" << std::endl;
	    tab2 = oneD_twoD(tabDct, 8, 8);
	    std::cout << "** array dimension changed. **" << std::endl;
	    vc.SaveImgInList(tab2, 8, 8);
	    vc.createFile("mtemp.file");
	    vc.SaveFlux();
	    /*Cleaning every inch of memory allocated*/
	    std::cout << "** Cleaning allocated memory. **" << std::endl;
	    delete [] tab;
	    delete [] tabDct;
	    for (int i = 0; i < 8; i++)
		delete [] tab2[i];
	    delete [] tab2;
	    std::cout << "** Cleaning done. **" << std::endl;
	}
    else if (c == '2')
	{
	    std::cout << "** video codec decompression. **" << std::endl;
	    vc.decompression();
	    std::cout << "** video codec decompression done.**" << std::endl;
	    std::cout << "** file reading. **" << std::endl;
	    infos = vc.lectureFichier();
	    std::cout << "** reading done. **" << std::endl;
	    height = infos.getHeight(); /*recuperation de la heuteur*/
	    width = infos.getWidth(); /*recuperation de la largeur*/
	    /*Saved array*/
	    std::cout << "** Quantized array **" << std::endl;
	    tabDct = twoD_oneD(infos.getTab(), height, width);
	    for (int i = 0; i < 64; i++)
		{
		    if (!(i % 8))
			std::cout << "\t";
		    std::cout << "|";
		    std::cout << tabDct[i];
		    if ((i % 8) == 7)
			std::cout << std::endl;
		}
	    std::cout << "** Unquantization **" << std::endl;
	    quantizer.unquantizeDCTMatrix(tabDct);
	    for (int i = 0; i < 64; i++)
		{
		    if (!(i % 8))
			std::cout << "\t";
		    std::cout << "|";
		    std::cout << tabDct[i];
		    if ((i % 8) == 7)
			std::cout << std::endl;
		}
	    std::cout << "** Unquantization done. **" << std::endl;
	    std::cout << "** IDCT. **" << std::endl;
	    tab = new unsigned char [64];
	    dct.referenceIDCT(tabDct, tab);
	    for (int i = 0; i < 64; i++)
		{
		    if (!(i % 8))
			std::cout << "\t";
		    std::cout << "|";
		    tab[i] = rand() % 255;
		    std::cout << tab[i];
		    if ((i % 8) == 7)
			std::cout << std::endl;
		}
	    std::cout << "** IDCT done. **" << std::endl;
	    /*Cleaning every inch of memory allocated*/
	    std::cout << "** Cleaning allocated memory. **" << std::endl;
	    delete [] tabDct;
	    delete [] tab;
	    std::cout << "** Cleaning done. **" << std::endl;
	}
    return (0);
}
