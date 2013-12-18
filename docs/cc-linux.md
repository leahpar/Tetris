# Linux compilation

This example is for Debian based distributions. You may easily adapt thoses commands for your distribution.

## Get dependancies


```
# install SDL2
apt-get install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-ttf-2.0-0 libsdl2-mixer-2.0-0
# install SDL2 dev
apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

## Compile

```
git clone https://github.com/leahpar/Tetris.git
cd Tetris
cd build
cmake ..
make
```

Or you can use the all-in-one command line

```
git clone https://github.com/leahpar/Tetris.git
cd Tetris
gcc src/tetris.c -o bin/tetris -Iinclude -I/usr/include/SDL2 -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
```

## Execute

```
cd ..
cp ressources/* bin
./bin/tetris
```
