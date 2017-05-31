BIN = voc_demo

CFLAGS = -std=c99 -pedantic -O2 -Inuklear -Ivoc
CXXFLAGS = -D__UNIX_JACK__ -Irtaudio -Ivoc

OBJ = main.o rtaudio/RtAudio.o audio.o

LIBS = -lglfw -lGL -lm -lGLU 
LIBS += -lstdc++ -ljack -Lvoc -lvoc -lsoundpipe -lsndfile

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(BIN) $(LIBS)

clean:
	rm -rf $(BIN)
	rm -rf $(OBJ)
