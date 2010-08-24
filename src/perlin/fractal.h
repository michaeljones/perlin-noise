#ifndef PERLIN_FRACTAL_H
#define PERLIN_FRACTAL_H

#include <perlin/perlin.h>

namespace perlin
{

class Fractal1D
{
public:
	Fractal1D( Noise1D* noise, int numLevels ) 
	 : m_numLevels( numLevels ), m_noise( noise ) {}

	~Fractal1D()
	{
		delete m_noise;
	}

	float generate( float x ) const
	{
		float value = 0.0f;

		float factor = 1.0f;
		for ( int i=0; i<m_numLevels; ++i )
		{
			value += m_noise->generate( factor * x ) / factor;

			factor += 1.0f;
		}

		return value;
	}

private:

	int m_numLevels;
	Noise1D* m_noise;

};

class Fractal2D
{
public:
	Fractal2D( Noise2D* noise, int numLevels ) 
	 : m_numLevels( numLevels ), m_noise( noise ) {}

	~Fractal2D()
	{
		delete m_noise;
	}

	float generate( float x, float y ) const
	{
		float value = 0.0f;

		float factor = 1.0f;
		for ( int i=0; i<m_numLevels; ++i )
		{
			value += m_noise->generate( factor * x, factor * y ) / factor;

			factor += 1.0f;
		}

		return value;
	}

private:

	int m_numLevels;
	Noise2D* m_noise;

};


class Fractal3D
{
public:
	Fractal3D( Noise3D* noise, int numLevels ) 
	 : m_numLevels( numLevels ), m_noise( noise ) {}

	~Fractal3D()
	{
		delete m_noise;
	}

	float generate( float x, float y, float z ) const
	{
		float value = 0.0f;

		float factor = 1.0f;
		for ( int i=0; i<m_numLevels; ++i )
		{
			value += m_noise->generate( factor * x, factor * y, factor * z ) / factor;

			factor += 1.0f;
		}

		return value;
	}

private:

	int m_numLevels;
	Noise3D* m_noise;

};

class FractalFactory
{
public:
	FractalFactory( NoiseFactory& factory )
	 : m_factory( factory ) {}

	Fractal2D* create2D( int numLevels ) const
	{
		return new Fractal2D( m_factory.create2D(), numLevels );
	}

	Fractal3D* create3D( int numLevels ) const
	{
		return new Fractal3D( m_factory.create3D(), numLevels );
	}

private:

	NoiseFactory m_factory;

};

}; // end namespace perlin

#endif // PERLIN_FRACTAL_H
