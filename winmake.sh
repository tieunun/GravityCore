#!/bin/bash
# This script builds the project as a Windows binary, and then copies
# the required librares to the path
# This is currently not functional.  This will be done through wine
# next.

mkdir -p win

i486-mingw32-g++ *xx -o ./win/Game.exe -l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l Box2D -B /usr/local -L /usr/local/lib

cp /usr/local/bin/sfml-{audio,graphics,system,window}-2.dll ./win
cp /usr/i486-mingw32/bin/{OpenAL32.dll,zlib1.dll,libFLAC-8.dll,libjpeg-8.dll,libstdc++-6.dll,libfreetype-6.dll,libogg-0.dll,libvorbis-0.dll,libgcc_s_sjlj-1.dll,libsndfile-1.dll,libvorbisenc-2.dll} ./win
