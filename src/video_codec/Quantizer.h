#ifndef __QUANTIZER_H_
#define __QUANTIZER_H_

#include <cmath>
#include <string>

class Quantizer
{
public:
    /**							C-TOR					**/

    Quantizer(std::string type = "standard_jpeg");
    ~Quantizer();
    Quantizer(const Quantizer &);
    Quantizer& operator=(const Quantizer &);

    /**							METHOD					**/

    /**
     *@return String the current type of matrix use for the quantization
     **/
    std::string					getMatrixType();
    /**
     *@param String the new matrix type
     **/
    void						setMatrixType(std::string);
    /**
     *@param short int * the array of DCT frequencies to be quantized
     *the size of the param has to be 8*8
     **/
    void						quantizeDCTMatrix(short int *);
    /**
     *@param short int * the array of DCT frequencies to be unquantized
     *the size of the param has to be 8*8
     **/
    void						unquantizeDCTMatrix(short int *);

private:
    /**						ATTRIBUTES					**/

    std::string	_matrixType;
    int*	_matrixCoeff;

    static int jpegStandardQuantizationMatrix[64];
};

#endif // !__QUANTIZER_H_
