# Voc Demo

A realtime demo of [Voc](https://www.github.com/paulbatchelor/voc), a vocal 
tract physical model.

![Screenshot of Voc Demo](voc_demo.png)

This is a simple voc demo using 
[RtAudio](https://github.com/thestk/rtaudio)
and 
[Nuklear](https://github.com/vurtun/nuklear).

## Setup

First compile 
[Voc](https://www.github.com/paulbatchelor/voc)
from source. CWEB and 
[Soundpipe](https://www.github.com/paulbatchelor/soundpipe) will
need to be installed beforehand.

This demo relies on the GLFW OpenGL2 backend for Nuklear, so make sure that
is properly configured and installed. 

After Voc is compiled, copy "libvoc.a" and
"voc.h" to the folder "voc".

Then, compile the demo with:
    make

To run, run:
    ./voc_demo

