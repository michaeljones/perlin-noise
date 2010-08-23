
INCLUDE=-Isrc -I/home/mike/projects/tools/include/OpenEXR

LIBS=-lImath -lIlmImf -lpthread
LIBPATH=-L/home/mike/projects/tools/lib

all: testsuite


test: testsuite
	./testsuite/two_d_image

testsuite: testsuite/two_d_image

testsuite/two_d_image:
	g++ testsuite/two_d_image.cpp -o testsuite/two_d_image $(INCLUDE) $(LIBS) $(LIBPATH) 

