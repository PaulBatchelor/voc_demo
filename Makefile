BIN = voc_demo

CFLAGS = -std=c99 -pedantic -O2 -Inuklear -Ivoc -g
CXXFLAGS = -D__UNIX_JACK__ -Irtaudio -Ivoc -g
CONFIG ?=

include $(CONFIG)

OBJ = main.o rtaudio/RtAudio.o audio.o voc/voc.o

LIBS += -lglfw -lGL -lm -lGLU 
LIBS += -lstdc++ -ljack -lsoundpipe -lsndfile

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(BIN) $(LIBS)

clean:
	rm -rf $(BIN)
	rm -rf $(OBJ)
