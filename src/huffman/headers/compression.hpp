#ifndef __COMPRESSION_H__
  #define __COMPRESSION_H__

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"
using namespace std;

struct SIZE {
  char  car1;
  char  car2;
  char  car3;
  char  car4;
};

class Compression
{
  private:
    map<char, int>    _tabOcc;
    map<char, float>  _tabFreq;
    map<char, string> _tabCode;
    list<Node *>      _items;
    int               _fileSize;
  public:
    Compression();
    ~Compression();
    void              setTabOcc(map<char, int> tabOcc);
    map<char, int>    getTabOcc();
    void              setTabFreq(map<char, float> tabFreq);
    map<char, float>  getTabFreq();
    void              addSymbol(char symbol);
    void              deleteSymbol(char symbol);
    void              calculateFreq();
    void              readFile(const char *file);
    int               totalSymbols();
    void              affTab();
    void              triToList();
    void              generateTree();
    void              compressedFile(const char *file);
    void              binToChar(ofstream *destFile, const char *file);
    void              intToStruct(int val, ofstream *destFile);
};

#endif /* !__COMPRESSION_H__ */
