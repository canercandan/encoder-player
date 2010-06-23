#include					"Quantizer.h"

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
{
}

Quantizer::Quantizer(const Quantizer & copy)
{
	this->setMatrixType(copy._matrixType);
}

Quantizer					&Quantizer::operator=(const Quantizer & copy)
{
	this->setMatrixType(copy._matrixType);
	return (*this);
}

std::string					Quantizer::getMatrixType()
{
	return (this->_matrixType);
}

void						Quantizer::setMatrixType(std::string type)
{
	if ((this->_matrixType = type) == "standard_jpeg")
		this->_matrixCoeff = jpegStandardQuantizationMatrix;
	else
	{
		this->_matrixType = "standard_jpeg";
		this->_matrixCoeff = jpegStandardQuantizationMatrix;
	}
}

void						Quantizer::quantizeDCTMatrix(short int * bloc)
{
	double					tmp;
	for (int i = 0; i < 64; i++)
	{
		tmp = bloc[i] / this->_matrixCoeff[i];
		bloc[i] = lrint(tmp);
	}
}
