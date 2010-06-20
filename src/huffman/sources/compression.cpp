#include "headers/node.hpp"
#include "headers/compression.hpp"
#include "headers/common.hpp"

Compression::Compression()
{
  this->_fileSize = 0;
}

Compression::~Compression() {}

void  Compression::setTabOcc(map<char, int> tabOcc)
{
  this->_tabOcc = tabOcc;
}

map<char, int>  Compression::getTabOcc()
{
  return (this->_tabOcc);
}

void  Compression::setTabFreq(map<char, float> tabFreq)
{
  this->_tabFreq = tabFreq;
}

map<char, float>  Compression::getTabFreq()
{
  return (this->_tabFreq);
}

void  Compression::addSymbol(char symbol)
{
  this->_tabOcc[symbol] += 1;
}

void  Compression::deleteSymbol(char symbol)
{
  map<char, int>::iterator it;
  if (this->_tabOcc[symbol])
  {
    it = this->_tabOcc.find(symbol);
    this->_tabOcc.erase(it);
  }
}

void  Compression::readFile(const char *file)
{
  FILE  *pFile;
  char  c;

  pFile = fopen(file , "r");
  if (pFile == NULL) 
    cerr << "Error opening file" << endl;
  else
  {
    while ((c = fgetc(pFile)) != EOF)
    {
      this->addSymbol(c);
      this->_fileSize += 1;
    }
    fclose(pFile);
  }
}

int Compression::totalSymbols()
{
  int total = 0;
  map<char, int>::iterator it;

  for (it = this->_tabOcc.begin(); it != this->_tabOcc.end(); it++)
    total += (*it).second;

  return (total);
}

void  Compression::calculateFreq()
{
  int totalSymbols = this->totalSymbols();
  map<char, int>::iterator it;
  float freq;

  for (it = this->_tabOcc.begin(); it != this->_tabOcc.end(); it++)
  {
    freq = (100 * (*it).second) / totalSymbols;
    this->_tabFreq[(*it).first] = freq;
  }
}

void  Compression::affTab()
{
  map<char, string>::iterator it;

  for (it = this->_tabCode.begin(); it != this->_tabCode.end(); ++it)
    std::cout << (*it).first << " - " << (*it).second << std::endl;
}

void  Compression::triToList()
{
    map<char, int>::iterator it;

    for (it = this->_tabOcc.begin(); it != this->_tabOcc.end(); it++)
    {
      Node *node = new Node((*it).first, (*it).second, NULL, NULL);
      this->_items.push_back(node);
    }
    this->_items.sort(compare_weight);
}

void  Compression::generateTree()
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
  firstIt->print(code, _tabCode);
}

void  Compression::binToChar(ofstream *destFile, const char *file)
{
  int   stock = 0;
  int   taille = 0;
  char  new_car;
  string code;
  FILE  *pFile;
  ifstream basicFile;
  char  c;
  int   i;
  int   size;

  basicFile.open (file, ios::binary | ios::in);
  basicFile.seekg(0, ios::end);
  size = basicFile.tellg();

  pFile = fopen(file , "r");
  if (pFile == NULL)
    cerr << "Error opening file" << endl;
  else if (basicFile.bad())
    cerr << "Error opening file" << endl;
  else
  {
    while (size > 0 && (c = fgetc(pFile)))
    {
      code = this->_tabCode[c];
      for (i = 0; i < (int)code.length(); i++)
      {
        if (code[i] == '1')
        {
          stock = stock << 1;
          stock += 1;
        }
        else if (code[i] == '0')
        {
          stock = stock << 1;
        }
        taille += 1;

        if (taille == 8)
        {
          taille = 0;
          new_car = stock;
          *destFile << new_car;
          stock = 0;
        }
      }
      size--;
    }
    if (taille != 0)
    {
      stock = stock << (8 - taille);
      new_car = stock;
      *destFile << new_car;
    }
  }
  fclose(pFile);
  basicFile.close();
}

/*
 * Conversion de la taille du fichier sur 4 caracteres
 */
void  Compression::intToStruct(int val, ofstream *destFile)
{
  SIZE *s;
  int *si = &val;
  s = (SIZE*)si;

  *destFile << s->car1 << s->car2 << s->car3 << s->car4;
}

void  Compression::compressedFile(const char *file)
{
  ofstream                    destFile;
  string                      destFileName(file);
  map<char, string>::iterator it;
  map<char, int>::iterator    it2;

  destFileName += ".tar.gz";
  destFile.open(destFileName.c_str());
  if (destFile.bad())
    cerr << "Error creating compressed file" << std::endl;
  else
  {
    // Taille du fichier
    intToStruct(this->_fileSize, &destFile);
    // Nombre de caracteres differents
    intToStruct(this->_tabCode.size(), &destFile);
    // Table des occurences
    for (it2 = this->_tabOcc.begin(); it2 != this->_tabOcc.end(); ++it2)
    {
      destFile << (*it2).first;
      intToStruct((*it2).second, &destFile);
    }

    binToChar(&destFile, file);
  }
  destFile.close();
}
