#include "headers/node.hpp"

bool  compare_weight(Node *first, Node *second)
{
  if (first->getFreq() == second->getFreq())
    return (first->getLetter() < second->getLetter());
  return (first->getFreq() < second->getFreq());
}