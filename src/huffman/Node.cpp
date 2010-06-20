#include "Node.h"

Node::Node(char letter, int freq, Node *left, Node *right)
{
  this->_letter   = letter;
  this->_freq     = freq;
  this->_leftSon  = left;
  this->_rightSon = right;
}

Node::~Node()
{}

bool	Node::operator<(Node& first, Node& second)
{
  if (first.getFreq() == second.getFreq())
    return (first.getLetter() < second.getLetter());
  return (first.getFreq() < second.getFreq());
}

char  Node::getLetter()
{
  return this->_letter;
}

void  Node::setLetter(char letter)
{
  this->_letter = letter;
}

int Node::getFreq()
{
  return (this->_freq);
}

void  Node::setFreq(int freq)
{
  this->_freq = freq;
}

Node *Node::getLeftSon()
{
  return (this->_leftSon);
}

void  Node::setLeftSon(Node &leftNode)
{
  this->_leftSon->setLetter(leftNode.getLetter());
  this->_leftSon->setFreq(leftNode.getFreq());
  this->_leftSon->_leftSon  = leftNode.getLeftSon();
  this->_leftSon->_rightSon = leftNode.getRightSon();
}

Node *Node::getRightSon()
{
    return (this->_rightSon);
}

void  Node::setRightSon(Node &rightNode)
{
  this->_rightSon->setLetter(rightNode.getLetter());
  this->_rightSon->setFreq(rightNode.getFreq());
  this->_rightSon->_leftSon  = rightNode.getLeftSon();
  this->_rightSon->_rightSon = rightNode.getRightSon();
}


void  Node::print(std::string &code, std::map<char, std::string> &tabCode)
{
  std::string::iterator it;

  if ((this->_leftSon != NULL) && (this->_rightSon != NULL))
  {
    code += '0';
    this->_leftSon->print(code, tabCode);
    if (!code.empty())
    {
      it = code.begin() + (code.size() - 1);
      code.erase(it);
    }
    code += '1';
    this->_rightSon->print(code, tabCode);
    if (!code.empty())
    {
      it = code.begin() + (code.size() - 1);
      code.erase(it);
    }
  }
  else
    tabCode[this->_letter] = code;
}
