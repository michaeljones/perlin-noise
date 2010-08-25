
INCLUDE=-Isrc -I/home/mike/projects/tools/include/OpenEXR

LIBS=-lImath -lIlmImf -lpthread
LIBPATH=-L/home/mike/projects/tools/lib

CPPFLAGS=-pg -Wall

all: testsuite


test: testsuite
	./testsuite/three_d_slice_image
	./testsuite/two_d_image
	./testsuite/one_d_image

testsuite: testsuite/two_d_image testsuite/one_d_image testsuite/three_d_slice_image testsuite/viewer testsuite/two_d_fractal_image testsuite/two_d_turbulence_image

testsuite/one_d_image: testsuite/one_d_image.cpp
	g++ $(CPPFLAGS) testsuite/one_d_image.cpp -o testsuite/one_d_image $(INCLUDE) $(LIBS) $(LIBPATH)

testsuite/two_d_image: testsuite/two_d_image.cpp
	g++ $(CPPFLAGS) testsuite/two_d_image.cpp -o testsuite/two_d_image $(INCLUDE) $(LIBS) $(LIBPATH) 

testsuite/two_d_fractal_image: testsuite/two_d_fractal_image.cpp
	g++ $(CPPFLAGS) testsuite/two_d_fractal_image.cpp -o testsuite/two_d_fractal_image $(INCLUDE) $(LIBS) $(LIBPATH) 

testsuite/two_d_turbulence_image: testsuite/two_d_turbulence_image.cpp
	g++ $(CPPFLAGS) testsuite/two_d_turbulence_image.cpp -o testsuite/two_d_turbulence_image $(INCLUDE) $(LIBS) $(LIBPATH) 

testsuite/three_d_slice_image: testsuite/three_d_slice_image.cpp
	g++ $(CPPFLAGS) testsuite/three_d_slice_image.cpp -o testsuite/three_d_slice_image $(INCLUDE) $(LIBS) $(LIBPATH) 

testsuite/viewer: testsuite/viewer.cpp
	g++ $(CPPFLAGS) testsuite/viewer.cpp -o testsuite/viewer $(INCLUDE) $(LIBS) $(LIBPATH) -lglut -lGL -lGLU

clean:
	rm -f testsuite/*image
	rm -f testsuite/viewer

