#!/bin/bash
# This script builds the project as a Windows binary, and then copies
# the required librares to the path
# This is currently not functional.  This will be done through wine
# next.

if [ "$1" = "clean" ]
then
    rm -r ./win
fi

mkdir -p ./win

i486-mingw32-g++ ./*xx -o ./win/Game.exe -mwindows -lmingw32 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lBox2D -I/home/taylor/.wine/drive_c/SFML/include -I/home/taylor/.wine/drive_c/Box2D -L/home/taylor/.wine/drive_c/SFML/lib -L/home/taylor/.wine/drive_c/Box2D/Box2D -static-libstdc++ -static-libgcc

cp /home/taylor/.wine/drive_c/windows/system32/OpenAL32.dll ./win
cp /home/taylor/.wine/drive_c/SFML/lib/sfml-{audio,graphics,system,window}-2.dll ./win
cp /home/taylor/.wine/drive_c/Box2D/Box2D/libBox2D.dll ./win
cp /home/taylor/.wine/drive_c/MinGW/bin/{libgcc_s_dw2-1.dll,libstdc++-6.dll,libsndfile-1.dll} ./win
cp -r ./img ./win
cp -r ./audio ./win
exit

