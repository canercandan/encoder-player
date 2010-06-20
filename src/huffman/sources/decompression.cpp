#include "headers/node.hpp"
#include "headers/decompression.hpp"
#include "headers/common.hpp"

Decompression::Decompression() {}

Decompression::~Decompression() {}

void  Decompression::readFile(const char *file)
{
  ofstream  destFile;
  //string  destFileName(file);
  string  destFileName("decompressedFile.txt");
  FILE  *pFile;
  Node  *firstIt;
  char  c;
  unsigned short  res;
  unsigned int mask;

  //destFileName = destFileName.substr(0, destFileName.size() - 7);
  destFile.open(destFileName.c_str());
  if (destFile.bad())
    cerr << "Error creating decompressed file" << std::endl;
  else
  {
    pFile = fopen(file, "r");
    if (pFile == NULL)
      cerr << "Error opening file" << endl;
    else
    {
      fileSize(pFile);
      createTabOcc(pFile);

      triToList();
      generateTree();
      firstIt = this->_items.front();

      res = (fgetc(pFile));
      res = res << 8;
      c = fgetc(pFile);
      mask = 32768;
      res += (unsigned char)c;
      while (this->_fileSize > 0)
      {
        destFile << getChar(firstIt, res, mask);
        this->_fileSize--;
        if (mask < 256)
        {
          mask = mask * 256;
          res = res << 8;
          c = fgetc(pFile);
          res += (unsigned char)c;
        }
      }
      fclose(pFile);
    }
    destFile.close();
  }
}

char  Decompression::getChar(Node *firstIt, unsigned short c, unsigned int &mask)
{
  if (firstIt->getLetter())
  {
    return (firstIt->getLetter());
  }
  else
  {
    if (c & mask)
    {
      mask = mask / 2;
      return (getChar(firstIt->getRightSon(), c, mask));
    }
    else
    {
      mask = mask / 2;
      return (getChar(firstIt->getLeftSon(), c, mask));
    }
  }
}

void  Decompression::fileSize(FILE *file)
{
  fread(&this->_fileSize, 4, 1, file);
}

void  Decompression::createTabOcc(FILE *file)
{
  int  nbCar;
  char  test;
  int   nbOcc;

  fread(&nbCar, 4, 1, file);
  for (int i = 0; i < nbCar; i++)
  {
    fread(&test, 1, 1, file);
    fread(&nbOcc, 4, 1, file);
    this->_tabOcc[test] = nbOcc;
  }
}

void  Decompression::affTab()
{
  map<char, string>::iterator it;

  for (it = this->_tabCode.begin(); it != this->_tabCode.end(); ++it)
    std::cout << (*it).first << " - " << (*it).second << std::endl;
}

void  Decompression::triToList()
{
    map<char, int>::iterator it;

    for (it = this->_tabOcc.begin(); it != this->_tabOcc.end(); it++)
    {
      Node *node = new Node((*it).first, (*it).second, NULL, NULL);
      this->_items.push_back(node);
    }
    this->_items.sort(compare_weight);
}

void  Decompression::generateTree()
{
  Node *firstIt;
  Node *secondIt;
  int weight;

  while (this->_items.size() > 1)
  {
    firstIt = this->_items.front();
    this->_items.pop_front();
    secondIt = this->_items.front();
    this->_items.pop_front();
    weight = firstIt->getFreq() + secondIt->getFreq();
    Node *node = new Node(0, weight, firstIt, secondIt);
    this->_items.push_back(node);
    this->_items.sort(compare_weight);
  }
  firstIt = this->_items.front();
  string code("");
  firstIt->print(code, this->_tabCode);
}
