#include "Quantizer.h"

int Quantizer::jpegStandardQuantizationMatrix[64] =
    {
	16, 11, 10, 16, 24, 40, 51, 61,
	12, 12, 14, 19, 26, 58, 60, 55,
	14, 13, 16, 24, 40, 57, 69, 56,
	14, 17, 22, 29, 51, 87, 80, 62,
	18, 22, 37, 56, 68, 109, 103, 77,
	24, 35, 55, 64, 81, 104, 113, 92,
	49, 64, 78, 87, 103, 121, 120, 101,
	72, 92, 95, 98, 112, 100, 103, 99
    };

Quantizer::Quantizer(std::string type)
{
    if ((this->_matrixType = type) == "standard_jpeg")
	this->_matrixCoeff = jpegStandardQuantizationMatrix;
    else
	{
	    this->_matrixType = "standard_jpeg";
	    this->_matrixCoeff = jpegStandardQuantizationMatrix;
	}
}

Quantizer::~Quantizer()
{}

Quantizer::Quantizer(const Quantizer & copy)
{
    this->setMatrixType(copy._matrixType);
}

Quantizer &Quantizer::operator=(const Quantizer & copy)
{
    this->setMatrixType(copy._matrixType);
    return (*this);
}

std::string Quantizer::getMatrixType()
{
    return (this->_matrixType);
}

void Quantizer::setMatrixType(std::string type)
{
    if ((this->_matrixType = type) == "standard_jpeg")
	{
	    this->_matrixCoeff = jpegStandardQuantizationMatrix;
	}
    else
	{
	    this->_matrixType = "standard_jpeg";
	    this->_matrixCoeff = jpegStandardQuantizationMatrix;
	}
}

void Quantizer::quantizeDCTMatrix(short int * bloc)
{
    double tmp;

    for (int i = 0; i < 64; i++)
	{
	    tmp = bloc[i] / this->_matrixCoeff[i];
	    bloc[i] = lrint(tmp);
	}
}

void Quantizer::unquantizeDCTMatrix(short int * bloc)
{
    double tmp;

    for (int i = 0; i < 64; i++)
	{
	    tmp = bloc[i] * this->_matrixCoeff[i];
	    bloc[i] = lrint(tmp);
	}
}
