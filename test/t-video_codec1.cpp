#include		<cstdlib>

#include		<iostream>
#include		"video_codec/Mcodec.h"

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
	Mcodec		test;
	char		c;

	std::cout << "**\tChoisir le mode : **" << std::endl;
	std::cout << "\t1. compress" << std::endl;
	std::cout << "\t2. uncompress" << std::endl;
	std::cin >> c;
	if (c == '1')
		test.compressImage("C:\\Documents and Settings\\EPITECH\\Bureau\\epitech.jpg");
	else if (c == '2')
		test.uncompressImage();
	return 0;
    return (0);
}
