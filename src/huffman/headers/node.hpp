#ifndef __NODE_H__
  #define __NODE_H__

#include <iostream>
#include <string>
#include <map>
using namespace std;

class Node
{
  private:
    char  _letter;
    int   _freq;
    Node* _leftSon;
    Node* _rightSon;
  public:
    Node(char letter, int freq, Node *left, Node *right);
    ~Node();
    char  getLetter();
    void  setLetter(char letter);
    int   getFreq();
    void  setFreq(int freq);
    Node  *getLeftSon();
    void  setLeftSon(Node &leftNode);
    Node  *getRightSon();
    void  setRightSon(Node &rightNode);
    void  print(string &code, map<char, string> &tabCode);
};

#endif /* !__NODE_H__ */
