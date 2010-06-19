#ifndef						__DCT_H__
#define						__DCT_H__

#include					<iostream>
#include					<cmath>

/**							DEFINES for the dct's operations**/
#define DCT_PI				3.14159265358979323846
#define DCT_RSQRT_2 		0.70710678118654752438
namespace					videoCodec
{
	class					DCT
	{
		public:
		/**					C-TOR				**/
		DCT();
		~DCT();
		
		/**					METHODS				**/
		/**
		* @return true if the productLookupTable have been initialized
		**/
		bool				getIsInitialized();
		/**
		*@return double ** the array of product lookup table
		**/
		double				*getProductLookupTable();
		/**
		*@return true if the initialization was a sucess
		*initialize the lookUptable
		**/
		bool				initialize();
		/**
		* @param unsigned char * the array of raw data
		* @param short int * the array to be returned with the frequency data
		* @warning both array must be initialise with 8 rows and 8 columns
		**/
		void				referenceDCT(unsigned char* data, short int* result);
		
		private:
		/**					METHODS				**/
		
		/**					ATTRIBUTES			**/
		bool				isInitialized;
		double				*productLookupTable;
		double				reciprocalRootTwo;
	};
}
#endif						/* !__DCT_H__*/