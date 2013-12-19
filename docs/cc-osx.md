# OSX compilation

I'm not using Xcode, but GCC via [homebrew](http://brew.sh)

## Homebrew & Compiler

### Homebrew

```
ruby -e "$(curl -fsSL https://raw.github.com/mxcl/homebrew/go/install)"
```

### GCC

This take a while to compile GCC, have a cofee !

```
brew tap homebrew/versions
brew install gcc48
```

### Cmake

```
brew install cmake
```

## Get dependancies

### SDL2

```
brew install sdl2 sdl2_ttf sdl2_image sdl2_mixer
```

## Compile

```
git clone https://github.com/leahpar/Tetris.git
cd Tetris
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-macos.cmake ..
make
```
## Execute

```
cd ..
cp -r ressources bin/
./bin/tetris
```

