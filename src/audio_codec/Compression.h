#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>

#include "Node.h"

extern "C"
{
  struct SIZE
  {
    char  car1;
    char  car2;
    char  car3;
    char  car4;
  };
}

class Compression
{
public:
  Compression();
  ~Compression();

  void              setTabOcc(std::map<char, int> tabOcc);
  std::map<char, int>    getTabOcc();
  void              setTabFreq(std::map<char, float> tabFreq);
  std::map<char, float>  getTabFreq();
  void              addSymbol(char symbol);
  void              deleteSymbol(char symbol);
  void              calculateFreq();
  void              readFile(const char *file);
  int               totalSymbols();
  void              affTab();
  void              triToList();
  void              generateTree();
  void              compressedFile(const char *file);
  void              binToChar(std::ofstream *destFile, const char *file);
  void              intToStruct(int val, std::ofstream *destFile);

private:
  std::map<char, int>		_tabOcc;
  std::map<char, float>		_tabFreq;
  std::map<char, std::string>	_tabCode;
  std::list<Node *>		_items;
  int				_fileSize;
};

#endif // !COMPRESSION_H
