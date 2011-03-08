target:mapper.o all

include Makefile.CoordinateMapper

LDFLAGS+= `pkg-config --libs openhrp3.1`
CXXFLAGS+= `pkg-config --cflags openhrp3.1`
OBJS+=mapper.o

mapper.o:mapper.cpp
	g++ -c $< -I. `pkg-config --cflags openhrp3.1`

