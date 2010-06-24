#ifndef							__QUANTIZER_H_
# define						__QUANTIZER_H_

#include						<cmath>
#include						<string>

static int						jpegStandardQuantizationMatrix[64] =
{16, 11, 10, 16, 24, 40, 51, 61,
 12, 12, 14, 19, 26, 58, 60, 55,
 14, 13, 16, 24, 40, 57, 69, 56,
 14, 17, 22, 29, 51, 87, 80, 62,
 18, 22, 37, 56, 68, 109, 103, 77,
 24, 35, 55, 64, 81, 104, 113, 92,
 49, 64, 78, 87, 103, 121, 120, 101,
 72, 92, 95, 98,   112, 100, 103, 99};
 
 class							Quantizer
 {
	public:
	/**							C-TOR					**/
	Quantizer(std::string type = "standard_jpeg");
	~Quantizer();
	Quantizer(const Quantizer &);
	Quantizer					&operator=(const Quantizer &);
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
	/**							C-TOR					**/
	/**						ATTRIBUTES					**/
	std::string					_matrixType;
	int							*_matrixCoeff;
 };

#endif							/* !__QUANTIZER_H_ */
