# Voc Demo

A realtime demo [Voc](https://www.github.com/paulbatchelor/voc), a vocal tract 
physical model.

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

After Voc is compiled, copy "libvoc.a" and
"voc.h" to the folder "voc".

In this directory, run make. 

To run:

    ./voc_demo

