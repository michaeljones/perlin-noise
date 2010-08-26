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

			factor *= 2.0f;
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

			factor *= 2.0f;
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

			factor *= 2.0f;
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
		std::vector< Noise1D* > levels( numLevels );

		for ( int i=0; i<numLevels; ++i )
		{
			levels[ i ] = m_factory.create1D();
		}
		
		return new Turbulence1D( levels );
	}

	Turbulence2D* create2D( int numLevels ) const
	{
		std::vector< Noise2D* > levels( numLevels );

		for ( int i=0; i<numLevels; ++i )
		{
			levels[ i ] = m_factory.create2D();
		}
		
		return new Turbulence2D( levels );
	}

	Turbulence3D* create3D( int numLevels ) const
	{
		std::vector< Noise3D* > levels( numLevels );

		for ( int i=0; i<numLevels; ++i )
		{
			levels[ i ] = m_factory.create3D();
		}

		return new Turbulence3D( levels );
	}

private:

	NoiseFactory m_factory;

};


}; // end namespace perlin

#endif // PERLIN_TURBULENCE_H
