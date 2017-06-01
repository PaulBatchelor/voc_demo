BIN = voc_demo

CFLAGS = -std=c99 -pedantic -O2 -Inuklear -Ivoc -g
CXXFLAGS = -D__UNIX_JACK__ -Irtaudio -Ivoc -g
CONFIG ?=

include $(CONFIG)

OBJ = main.o rtaudio/RtAudio.o audio.o voc/voc.o

ifeq ($(system), Darwin)
CXX=clang++
CXXFLAGS=-D__MACOSX_CORE__ -c
CFLAGS=-D__MACOSX_CORE__ -c
LIBS=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation \
	-framework IOKit -framework Carbon  -framework OpenGL \
	-framework GLUT -framework Foundation \
	-framework AppKit -lstdc++ -lm -L/usr/local/lib
LIBS += -lglfw3 -framework Cocoa -framework CoreVideo -lm -lGLEW 
CXXFLAGS += -I/usr/local/include
CFLAGS += -I/usr/local/include
else
CXX=g++
CXXFLAGS=-D__UNIX_JACK__ -c
LIBS += -lstdc++ -ljack -lsoundpipe -lsndfile
LIBS += -lglfw -lGL -lm -lGLU 
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
