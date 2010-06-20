#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>

#include "Node.h"

class	Decompression
{
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

private:
  std::map<char, int>		_tabOcc;
  std::map<char, std::string>	_tabCode;
  std::list<Node *>		_items;
  unsigned int			_fileSize;

};

#endif // !DECOMPRESSION_H
