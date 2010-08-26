
#include <perlin/perlin.h>

#include <ImfRgbaFile.h>

int main( int argv, char** argc )
{
	srand48( 0 );

    perlin::NoiseFactory factory;

    perlin::Noise3D* noise = factory.create3D();

    Imath::V2i resolution( 500, 500 ); 
    Imf::Rgba* pixels = new Imf::Rgba[ resolution.x * resolution.y ];

    for ( int i=0; i<resolution.x; ++i )
    {
        for ( int j=0; j<resolution.y; ++j )
        {
            Imf::Rgba& pixel = pixels[ j * resolution.x + i ];

            float value = noise->generate( i/20.0f, j/20.0f, 5.85f );
            value = value/2.0 + 0.5f;
            pixel.r = value;
            pixel.g = value;
            pixel.b = value;
            pixel.a = 1.0;
        }
    }

    Imf::RgbaOutputFile file( "three_d.exr", resolution.x, resolution.y, Imf::WRITE_RGBA );
    file.setFrameBuffer( pixels, 1, resolution.x );
    file.writePixels( resolution.y );

    delete noise;

    return 0;
}


