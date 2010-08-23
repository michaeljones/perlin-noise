
#include <stdlib.h>
#include <math.h>

namespace perlin
{


class Noise1D
{

};


template< typename T >
class Point2
{
public:

	Point2() {};
	Point2( T _x, T _y ) : x( _x ), y( _y ) {}

    T dot( Point2< T > other )
	{
		return x * other.x + y * other.y;
	}

	T x;
	T y;
};

typedef Point2< int > IntPoint2;
typedef Point2< float > FloatPoint2;

class Noise2D
{
public:

	Noise2D( FloatPoint2* gradients )
	 : m_gradients( gradients ) {} 

	~Noise2D()
	{
		delete m_gradients;
	}


	float generate( float x, float y )
	{
		int xCoord = floor( x );
		int yCoord = floor( y );

		/*
		Using:
			
			   d ---------- c
			   |            |
			   |  . (x,y)   |
		 y	   |            |
		 ^	   |            |
	     |     a ---------- b
	     |
		  ---> x
		 
		 */

		IntPoint2 a( xCoord, yCoord );
		IntPoint2 b( xCoord + 1, yCoord );
		IntPoint2 c( xCoord + 1, yCoord + 1 );
		IntPoint2 d( xCoord, yCoord + 1 );

		FloatPoint2 aGrad = getGradient( a );
		FloatPoint2 bGrad = getGradient( b );
		FloatPoint2 cGrad = getGradient( c );
		FloatPoint2 dGrad = getGradient( d );

		float xOffset = x - xCoord;
		float yOffset = y - yCoord;

		FloatPoint2 aOffset( xOffset, yOffset );
		FloatPoint2 bOffset( xOffset - 1, yOffset );
		FloatPoint2 cOffset( xOffset - 1, yOffset - 1 );
		FloatPoint2 dOffset( xOffset, yOffset - 1 );

		float aContrib = aGrad.dot( aOffset );
		float bContrib = bGrad.dot( bOffset );
		float cContrib = cGrad.dot( cOffset );
		float dContrib = dGrad.dot( dOffset );

		float xParam = 3 * xOffset * xOffset - 2 * xOffset * xOffset * xOffset;
		float yParam = 3 * yOffset * yOffset - 2 * yOffset * yOffset * yOffset;

		float abContrib = ( 1 - xParam ) * aContrib + xParam * bContrib;
		float dcContrib = ( 1 - xParam ) * dContrib + xParam * cContrib;

		return ( 1 - yParam ) * abContrib + yParam * dcContrib;
	}

	FloatPoint2 getGradient( IntPoint2 point )
	{
		/*
		Offsets as generated by the following python code:

			import random

			values = [ str( x ) for x in range( 0, 256 ) ]

			random.seed( 0 )
			random.shuffle( values )

			print "{ %s }" % ", ".join( values )

		*/
		char P[ 256 ] = { 62, 211, 5, 167, 9, 20, 189, 30, 224, 93, 176, 110,
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
		
		int index = point.y & 255;
		index = ( point.x + P[ index ] ) & 255;

		return m_gradients[ index ];
	}

private:

	FloatPoint2* m_gradients;

};


class Noise3D
{

};


class GeneratorFactory
{
public:

	GeneratorFactory() {};

	Noise2D* create2D()
	{
		FloatPoint2* gradients = new FloatPoint2[ 256 ];

		srand48( 0 );

		for ( int i=0; i<256; ++i )
		{
			gradients[ i ].x = drand48() * 2.0 - 1.0;
			gradients[ i ].y = drand48() * 2.0 - 1.0;

			float lengthSq = gradients[ i ].x * gradients[ i ].x + gradients[ i ].y * gradients[ i ].y;
			float length = sqrt( lengthSq );

			gradients[ i ].x /= length;
			gradients[ i ].y /= length;
		}

		return new Noise2D( gradients );
	}
};


}; // end namespace perlin 

