#include "../headers/compression.hpp"
#include "../headers/decompression.hpp"

int main (int argc, char const *argv[])
{
  Compression *myComp = new Compression();
  Decompression *myDecomp = new Decompression();

  if (argc == 3)
  {
    const char *myFile = argv[2];
    int test = strcmp(argv[1], "-c");
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
  }
  else
  {
    cerr << "USAGE: ./huffman [options] filename" << std::endl;
    cerr << "Options:" << endl;
    cerr << "\t-c, \tCompress a file" << endl;
    cerr << "\t-d, \tDecompress a file" << endl;
  }
  return 0;
}