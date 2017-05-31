# voc Demo

This is a simple voc demo using RtAudio and Nuklear.

## Setup

First compile Voc from source, then copy "libvoc.a" and
"voc.h" to the folder "voc".

In this directory, run make. 

To run:

    ./voc_demo

By default, it will run at a samplerate of 44.1kHz. To run with a different
samplerate, run:

    ./voc_demo 44100
