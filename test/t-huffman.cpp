#include <cstring>

#include <iostream>

#include "Compression.h"
#include "Decompression.h"

int main (int argc, char** argv)
{
  Compression*		myComp = new Compression();
  Decompression*	myDecomp = new Decompression();

  if (argc == 3)
    {
      const char* myFile = argv[2];
      int test = ::strcmp(argv[1], "-c");

      if (test == 0)
	{
	  myComp->readFile(myFile);
	  myComp->triToList();
	  myComp->generateTree();
	  myComp->compressedFile(myFile);
	}
      else
	{
	  myDecomp->readFile(myFile);
	}

      return 0;
    }

  std::cout << "USAGE: ./huffman [options] filename" << std::endl
	    << "Options:" << std::endl
	    << "\t-c, \tCompress a file" << std::endl
	    << "\t-d, \tDecompress a file" << std::endl;

  return 1;
}
