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

## Execute

```
cd ..
cp ressources/* bin
./bin/tetris
```
