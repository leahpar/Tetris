# Tetris

## Dependancies

### SDL2 library

http://www.libsdl.org

SDL + SDL_ttf + SDL_image

```
# install SDL2
apt-get install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-ttf-2.0-0 libsdl2-mixer-2.0-0
# install SDL2 dev
apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

## Compilation

### Linux

```
cd build
cmake ..
make
```

### Windows (cross compilation)

Get dependancies

```
# get SDL2
cd /tmp
wget http://www.libsdl.org/release/SDL2-devel-2.0.1-mingw.tar.gz
tar -xvf SDL2-devel-2.0.1-mingw.tar.gz
cd SDL2-2.0.1/i686-w64-mingw32
# you can use another place, update Toolchain-mingw32.cmake file consequently
sudo cp -R include lib /usr/i686-w64-mingw32

# get SDL2 TTF
cd /tmp
wget http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.12-mingw.tar.gz
tar -xvf SDL2_ttf-devel-2.0.12-mingw.tar.gz
cd SDL2_ttf-2.0.12/i686-w64-mingw32
# you can use another place, update Toolchain-mingw32.cmake file consequently
sudo cp -R include lib /usr/i686-w64-mingw32

# get SDL2 Image
cd /tmp
wget http://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.0-mingw.tar.gz
tar -xvf SDL2_image-devel-2.0.0-mingw.tar.gz
cd SDL2_image-2.0.0/i686-w64-mingw32
# you can use another place, update Toolchain-mingw32.cmake file consequently
sudo cp -R include lib /usr/i686-w64-mingw32

# get SDL2 Mixer
cd /tmp
wget http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.0-mingw.tar.gz
tar -xvf SDL2_mixer-devel-2.0.0-mingw.tar.gz
cd SDL2_mixer-2.0.0/i686-w64-mingw32
# you can use another place, update Toolchain-mingw32.cmake file consequently
sudo cp -R include lib /usr/i686-w64-mingw32
```

Compile

```
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-mingw32.cmake ..
make
```

### Mac OSX

Soon...


