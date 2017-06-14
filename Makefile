BIN = voc_demo

CFLAGS += -std=c99 -pedantic -O2 -Inuklear -g
CXXFLAGS += -Irtaudio 
CONFIG ?=

include $(CONFIG)

OBJ = main.o rtaudio/RtAudio.o audio.o 
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CXX=clang++
CXXFLAGS+=-D__MACOSX_CORE__ 
CFLAGS+=-D__MACOSX_CORE__ 
LIBS +=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation \
	-framework IOKit -framework Carbon  -framework OpenGL \
	-framework GLUT -framework Foundation \
	-framework AppKit -lstdc++ -lm -L/usr/local/lib
LIBS += -lglfw -framework Cocoa -framework CoreVideo -lm -lsoundpipe -lsndfile
CXXFLAGS += -I/usr/local/include
CFLAGS += -I/usr/local/include

# Header files needed for MacPorts installations
CFLAGS += -I/opt/local/include -L/opt/local/lib
else
CXX=g++
CXXFLAGS += -D__UNIX_JACK__ 
LIBS += -lstdc++ -ljack -lsoundpipe -lsndfile
LIBS += -lglfw -lGL -lm -lGLU -lpthread
endif


%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(BIN) $(LIBS)

clean:
	rm -rf $(BIN)
	rm -rf $(OBJ)
