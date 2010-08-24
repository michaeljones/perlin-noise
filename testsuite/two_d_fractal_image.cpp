
#include <perlin/fractal.h>

#include <ImfRgbaFile.h>

int main( int argv, char** argc )
{
	perlin::NoiseFactory noiseFactory;
	perlin::FractalFactory factory( noiseFactory );

	perlin::Fractal2D* noise = factory.create2D( 50 );

	Imath::V2i resolution( 500, 500 ); 
	Imf::Rgba* pixels = new Imf::Rgba[ resolution.x * resolution.y ];

	for ( int i=0; i<resolution.x; ++i )
	{
		for ( int j=0; j<resolution.y; ++j )
		{
			Imf::Rgba& pixel = pixels[ j * resolution.x + i ];

			float value = noise->generate( i/200.0f, j/200.0f );
			value = value/2.0 + 0.5f;
			pixel.r = value;
			pixel.g = value;
			pixel.b = value;
			pixel.a = 1.0;
		}
	}

	Imf::RgbaOutputFile file( "two_d.exr", resolution.x, resolution.y, Imf::WRITE_RGBA );
	file.setFrameBuffer( pixels, 1, resolution.x );
	file.writePixels( resolution.y );

	delete noise;

	return 0;
}


