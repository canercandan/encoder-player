#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>

class Node
{
public:
  Node(char letter, int freq, Node *left, Node *right);
  ~Node();

  friend bool	operator<(Node&, Node&);

  char  getLetter();
  void  setLetter(char letter);
  int   getFreq();
  void  setFreq(int freq);
  Node  *getLeftSon();
  void  setLeftSon(Node &leftNode);
  Node  *getRightSon();
  void  setRightSon(Node &rightNode);
  void  print(std::string &code, std::map<char, std::string> &tabCode);
private:
  char  _letter;
  int   _freq;
  Node* _leftSon;
  Node* _rightSon;
};

#endif // !NODE_H
