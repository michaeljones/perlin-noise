
#include <perlin/perlin.h>

#include <ImfRgbaFile.h>

int main( int argv, char** argc )
{
	perlin::NoiseFactory factory;

	perlin::Noise1D* noise = factory.create1D();

	Imath::V2i resolution( 500, 100 ); 
	Imf::Rgba* pixels = new Imf::Rgba[ resolution.x * resolution.y ];

	for ( int i=0; i<resolution.x; ++i )
	{
		float value = noise->generate( i/20.0f );
		value = value/2.0 + 0.5f;

		for ( int j=0; j<resolution.y; ++j )
		{
			Imf::Rgba& pixel = pixels[ j * resolution.x + i ];

			pixel.r = value;
			pixel.g = value;
			pixel.b = value;
			pixel.a = 1.0;
		}
	}

	Imf::RgbaOutputFile file( "one_d.exr", resolution.x, resolution.y, Imf::WRITE_RGBA );
	file.setFrameBuffer( pixels, 1, resolution.x );
	file.writePixels( resolution.y );

	delete noise;

	return 0;
}


