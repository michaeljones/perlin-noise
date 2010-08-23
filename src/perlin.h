
namespace perlin
{


class Noise1D
{

};


template< typename T >
class Point2
{
public:

	Point2( T _x, T _y ) : x( _x ), y( _y ) {}

	T x;
	T y;
};

typedef Point2< int > IntPoint2;

class Noise2D
{
public:

	Noise2D();

	float generate( float x, float y )
	{
		int xCoord = floor( x );
		int yCoord = floor( y );

		FloatPoint2 a( x - xCoord, y - yCoord );
		FloatPoint2 b( x - ( xCoord + 1 ), y - yCoord );
		FloatPoint2 c( x - ( xCoord + 1 ), y - ( yCoord + 1 ) );
		FloatPoint2 d( x - xCoord, y - ( yCoord + 1 ) );

		FloatPoint2 aGrad = getGradient( a );
		FloatPoint2 bGrad = getGradient( b );
		FloatPoint2 cGrad = getGradient( c );
		FloatPoint2 dGrad = getGradient( d );

		float aContrib = aGrad.dot( a )
		float bContrib = bGrad.dot( b )
		float cContrib = cGrad.dot( c )
		float dContrib = dGrad.dot( d )

	}

};


class Noise3D
{

};


class GeneratorFactory
{
public:

	GeneratorFactory();



};


}; // end namespace perlin 

