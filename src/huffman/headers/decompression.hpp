#ifndef __DECOMPRESSION_H__
  #define __DECOMPRESSION_H__

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "node.hpp"
using namespace std;

class Decompression
{
  private:
    map<char, int>    _tabOcc;
    map<char, string> _tabCode;
    list<Node *>      _items;
    unsigned int      _fileSize;
  public:
    Decompression();
    ~Decompression();
    void  readFile(const char *file);
    void  fileSize(FILE *file);
    void  createTabOcc(FILE *file);
    void  affTab();
    void  triToList();
    void  generateTree();
    char  getChar(Node *firstIt, unsigned short c, unsigned int &mask);
};

#endif /* !__DECOMPRESSION_H__ */
