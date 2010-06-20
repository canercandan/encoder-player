#include "DCT.h"

DCT::DCT()
{
  this->isInitialized = false;
}

DCT::~DCT()
{
  if (this->isInitialized)
    delete [] this->productLookupTable;
}

bool	DCT::getIsInitialized()
{
  return (this->isInitialized);
}

double*	DCT::getProductLookupTable()
{
  return (this->productLookupTable);
}

bool	DCT::initialize()
{
  std::cout << "starting initialization." << std::endl;
  this->productLookupTable = new double[4096];
  this->reciprocalRootTwo = 1.0 / sqrt(2.0);
  for (int index = 0, v = 0; v < 8; v++)
    {
      for (int u = 0; u < 8; u++)
	{
	  for (int y = 0; y < 8; y++)
	    {
	      for (int x = 0; x < 8; x++, index++)
		{
		  this->productLookupTable[index] =
		    cos(((2.0 * (double)x + 1.0) * (double)u * DCT_PI) / 16.0) *
		    cos(((2.0 * (double)y + 1.0) * (double)v * DCT_PI) / 16.0);
		}
	    }
	}
    }
  this->isInitialized = true;
  std::cout << "Initialization complete." << std::endl;
}

void	DCT::referenceDCT(unsigned char* data, short int* result)
{
  double	temp;
  int		index;

  index = 0;
  for (int outerIndex = 0; outerIndex < 64; outerIndex++)
    {
      temp = 0.0;
      for (int i = 0; i < 64; i++, index++)
	{
	  temp += ((double)data[i] * this->productLookupTable[index]);
	}
      temp *= this->reciprocalRootTwo *
	(outerIndex < 8 ? this->reciprocalRootTwo : 1.0) *
	((outerIndex % 8) == 0 ? this->reciprocalRootTwo : 1.0);
      result[outerIndex] = lrintf(temp);
    }
}
