#ifndef PERLIN_TURBULENCE_H
#define PERLIN_TURBULENCE_H

#include <perlin/perlin.h>

#include <vector>

namespace perlin
{

class Turbulence1D
{
public:

	Turbulence1D( std::vector< Noise1D* > levels )
	 : m_levels( levels ) {}

	~Turbulence1D()
	{
		std::vector< Noise1D* >::iterator it = m_levels.begin();
		std::vector< Noise1D* >::iterator end = m_levels.end();

		for ( ; it != end; ++it ) delete *it;
	}

	float generate( float x ) const
	{
		float value = 0.0f;
		float factor = 1.0f;

		std::vector< Noise1D* >::const_iterator it = m_levels.begin();
		std::vector< Noise1D* >::const_iterator end = m_levels.end();

		for ( ; it != end; ++it )
		{
			value += fabs( (*it)->generate( factor * x ) ) / factor;

			factor += 1.0f;
		}

		return value;
	}

private:

	std::vector< Noise1D* > m_levels;

};


class Turbulence2D
{
public:
	Turbulence2D( std::vector< Noise2D* > levels )
	 : m_levels( levels ) {}

	~Turbulence2D()
	{
		std::vector< Noise2D* >::iterator it = m_levels.begin();
		std::vector< Noise2D* >::iterator end = m_levels.end();

		for ( ; it != end; ++it ) delete *it;
	}

	float generate( float x, float y ) const
	{
		float value = 0.0f;
		float factor = 1.0f;

		std::vector< Noise2D* >::const_iterator it = m_levels.begin();
		std::vector< Noise2D* >::const_iterator end = m_levels.end();

		for ( ; it != end; ++it )
		{
			value += fabs( (*it)->generate( factor * x, factor * y ) ) / factor;

			factor += 1.0f;
		}

		return value;
	}

private:

	std::vector< Noise2D* > m_levels;

};


class Turbulence3D
{
public:
	Turbulence3D( std::vector< Noise3D* > levels )
	 : m_levels( levels ) {}

	~Turbulence3D()
	{
		std::vector< Noise3D* >::iterator it = m_levels.begin();
		std::vector< Noise3D* >::iterator end = m_levels.end();

		for ( ; it != end; ++it ) delete *it;
	}

	float generate( float x, float y, float z ) const
	{
		float value = 0.0f;
		float factor = 1.0f;

		std::vector< Noise3D* >::const_iterator it = m_levels.begin();
		std::vector< Noise3D* >::const_iterator end = m_levels.end();

		for ( ; it != end; ++it )
		{
			value += fabs( (*it)->generate( factor * x, factor * y, factor * z ) ) / factor;

			factor += 1.0f;
		}

		return value;
	}

private:

	std::vector< Noise3D* > m_levels;

};


class TurbulenceFactory
{
public:
	TurbulenceFactory( NoiseFactory& factory )
	 : m_factory( factory ) {}


	Turbulence1D* create1D( int numLevels ) const
	{
		int P[ 256 ] = { 62, 211, 5, 167, 9, 20, 189, 30, 224, 93, 176, 110,
			155, 214, 50, 238, 81, 114, 104, 90, 151, 169, 160, 103, 197, 66,
			89, 85, 127, 55, 201, 172, 141, 10, 92, 70, 44, 163, 217, 212, 209,
			7, 125, 57, 36, 237, 254, 142, 97, 153, 227, 61, 27, 8, 146, 115,
			244, 173, 240, 252, 202, 162, 236, 56, 24, 42, 205, 135, 175, 215,
			74, 29, 198, 122, 46, 48, 188, 79, 88, 190, 77, 19, 251, 138, 206,
			63, 1, 133, 233, 140, 32, 28, 170, 53, 38, 45, 180, 43, 59, 25,
			184, 181, 69, 168, 255, 71, 18, 229, 204, 80, 39, 22, 152, 11, 131,
			245, 145, 41, 178, 249, 31, 12, 134, 132, 117, 100, 26, 15, 230,
			124, 2, 4, 154, 148, 52, 78, 83, 239, 220, 177, 248, 129, 82, 6,
			250, 199, 14, 182, 207, 119, 33, 17, 111, 37, 130, 166, 76, 96, 13,
			126, 147, 174, 196, 235, 95, 157, 98, 150, 143, 137, 47, 221, 67,
			94, 161, 226, 241, 164, 156, 136, 203, 86, 120, 191, 34, 35, 54,
			108, 72, 113, 84, 112, 116, 186, 105, 232, 225, 228, 231, 21, 187,
			102, 64, 16, 91, 165, 200, 49, 247, 40, 242, 243, 51, 185, 253, 0,
			246, 222, 87, 158, 3, 121, 179, 58, 194, 107, 219, 208, 139, 99,
			23, 109, 159, 210, 171, 73, 213, 192, 234, 218, 60, 149, 183, 68,
			123, 223, 144, 118, 75, 195, 101, 128, 65, 106, 193, 216 };

		std::vector< Noise1D* > levels( numLevels );

		for ( int i=0; i<numLevels; ++i )
		{
			levels[ i ] = m_factory.create1D( P[ i & 255 ] );
		}
		
		return new Turbulence1D( levels );
	}
	Turbulence2D* create2D( int numLevels ) const
	{
		int P[ 256 ] = { 62, 211, 5, 167, 9, 20, 189, 30, 224, 93, 176, 110,
			155, 214, 50, 238, 81, 114, 104, 90, 151, 169, 160, 103, 197, 66,
			89, 85, 127, 55, 201, 172, 141, 10, 92, 70, 44, 163, 217, 212, 209,
			7, 125, 57, 36, 237, 254, 142, 97, 153, 227, 61, 27, 8, 146, 115,
			244, 173, 240, 252, 202, 162, 236, 56, 24, 42, 205, 135, 175, 215,
			74, 29, 198, 122, 46, 48, 188, 79, 88, 190, 77, 19, 251, 138, 206,
			63, 1, 133, 233, 140, 32, 28, 170, 53, 38, 45, 180, 43, 59, 25,
			184, 181, 69, 168, 255, 71, 18, 229, 204, 80, 39, 22, 152, 11, 131,
			245, 145, 41, 178, 249, 31, 12, 134, 132, 117, 100, 26, 15, 230,
			124, 2, 4, 154, 148, 52, 78, 83, 239, 220, 177, 248, 129, 82, 6,
			250, 199, 14, 182, 207, 119, 33, 17, 111, 37, 130, 166, 76, 96, 13,
			126, 147, 174, 196, 235, 95, 157, 98, 150, 143, 137, 47, 221, 67,
			94, 161, 226, 241, 164, 156, 136, 203, 86, 120, 191, 34, 35, 54,
			108, 72, 113, 84, 112, 116, 186, 105, 232, 225, 228, 231, 21, 187,
			102, 64, 16, 91, 165, 200, 49, 247, 40, 242, 243, 51, 185, 253, 0,
			246, 222, 87, 158, 3, 121, 179, 58, 194, 107, 219, 208, 139, 99,
			23, 109, 159, 210, 171, 73, 213, 192, 234, 218, 60, 149, 183, 68,
			123, 223, 144, 118, 75, 195, 101, 128, 65, 106, 193, 216 };

		std::vector< Noise2D* > levels( numLevels );

		for ( int i=0; i<numLevels; ++i )
		{
			levels[ i ] = m_factory.create2D( P[ i & 255 ] );
		}
		
		return new Turbulence2D( levels );
	}

	Turbulence3D* create3D( int numLevels ) const
	{
		int P[ 256 ] = { 62, 211, 5, 167, 9, 20, 189, 30, 224, 93, 176, 110,
			155, 214, 50, 238, 81, 114, 104, 90, 151, 169, 160, 103, 197, 66,
			89, 85, 127, 55, 201, 172, 141, 10, 92, 70, 44, 163, 217, 212, 209,
			7, 125, 57, 36, 237, 254, 142, 97, 153, 227, 61, 27, 8, 146, 115,
			244, 173, 240, 252, 202, 162, 236, 56, 24, 42, 205, 135, 175, 215,
			74, 29, 198, 122, 46, 48, 188, 79, 88, 190, 77, 19, 251, 138, 206,
			63, 1, 133, 233, 140, 32, 28, 170, 53, 38, 45, 180, 43, 59, 25,
			184, 181, 69, 168, 255, 71, 18, 229, 204, 80, 39, 22, 152, 11, 131,
			245, 145, 41, 178, 249, 31, 12, 134, 132, 117, 100, 26, 15, 230,
			124, 2, 4, 154, 148, 52, 78, 83, 239, 220, 177, 248, 129, 82, 6,
			250, 199, 14, 182, 207, 119, 33, 17, 111, 37, 130, 166, 76, 96, 13,
			126, 147, 174, 196, 235, 95, 157, 98, 150, 143, 137, 47, 221, 67,
			94, 161, 226, 241, 164, 156, 136, 203, 86, 120, 191, 34, 35, 54,
			108, 72, 113, 84, 112, 116, 186, 105, 232, 225, 228, 231, 21, 187,
			102, 64, 16, 91, 165, 200, 49, 247, 40, 242, 243, 51, 185, 253, 0,
			246, 222, 87, 158, 3, 121, 179, 58, 194, 107, 219, 208, 139, 99,
			23, 109, 159, 210, 171, 73, 213, 192, 234, 218, 60, 149, 183, 68,
			123, 223, 144, 118, 75, 195, 101, 128, 65, 106, 193, 216 };

		std::vector< Noise3D* > levels( numLevels );

		for ( int i=0; i<numLevels; ++i )
		{
			levels[ i ] = m_factory.create3D( P[ i & 255 ] );
		}

		return new Turbulence3D( levels );
	}

private:

	NoiseFactory m_factory;

};


}; // end namespace perlin

#endif // PERLIN_TURBULENCE_H
