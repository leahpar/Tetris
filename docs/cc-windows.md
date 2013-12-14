# Windows compilation

(cross compilation from Linux)

This example is for a Debian 64 bits. You may easily adapt thoses commands for your distribution.

## Get dependancies

### SDL2

```
cd /tmp
wget http://www.libsdl.org/release/SDL2-devel-2.0.1-mingw.tar.gz
tar -xvf SDL2-devel-2.0.1-mingw.tar.gz
cd SDL2-2.0.1/i686-w64-mingw32
# you can use another place, update Toolchain-mingw32.cmake file consequently
sudo cp -R include lib /usr/i686-w64-mingw32
```

### SDL2 ttf

```
cd /tmp
wget http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.12-mingw.tar.gz
tar -xvf SDL2_ttf-devel-2.0.12-mingw.tar.gz
cd SDL2_ttf-2.0.12/i686-w64-mingw32
# you can use another place, update Toolchain-mingw32.cmake file consequently
sudo cp -R include lib /usr/i686-w64-mingw32
```

### SDL2 image

```
cd /tmp
wget http://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz
tar -xvf SDL2_image-devel-2.0.0-mingw.tar.gz
cd SDL2_image-2.0.0/i686-w64-mingw32
# you can use another place, update Toolchain-mingw32.cmake file consequently
sudo cp -R include lib /usr/i686-w64-mingw32
```

### SDL2 mixer

```
cd /tmp
wget http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.0-mingw.tar.gz
tar -xvf SDL2_mixer-devel-2.0.0-mingw.tar.gz
cd SDL2_mixer-2.0.0/i686-w64-mingw32
# you can use another place, update Toolchain-mingw32.cmake file consequently
sudo cp -R include lib /usr/i686-w64-mingw32
```

## Compile

### get cross compiler

```
apt-get install g++-mingw-w64-i686
```

### Compile

```
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-mingw32.cmake ..
make
```

## Prepare environment

```
cd /path/to/your/Tetris
mkdir Tetris
# ger binary
cp bin/tetris.exe Tetris/
# get ressources
cp ressources/tetris* Tetris/
# get dlls
cp /tmp/SDL2*/bin/*.dll Tetris/
# make a zip
zip -r Tetris.zip Tetris
```

