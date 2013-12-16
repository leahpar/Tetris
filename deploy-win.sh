#!/bin/sh

version=`grep "^\*" ChangeLog.md | head -1 | cut -d ' ' -f 2 | tr -d 'v'`
codexe=`date "+%Y%m%d%H%M%S"`
package="Tetris-${version}-${codexe}"

PRJ=`pwd`


# colors
gri="\033[0m"
red="\033[31m"
gre="\033[32m"
ore="\033[33m"
 

# check dlls
echo "Check dlls..."

mkdir /tmp/SDL2 2>/dev/null

if [ ! -e /tmp/SDL2/SDL2.dll ]; then
   echo "${red}SDL2 missing...${gri}"
   echo "downloading SDL2..."
   echo "   http://www.libsdl.org/release/SDL2-2.0.1-win32-x86.zip"
   cd /tmp/SDL2
   wget -q http://www.libsdl.org/release/SDL2-2.0.1-win32-x86.zip
   unzip -o -qq SDL2-2.0.1-win32-x86.zip
fi
echo "${gre}SDL2 OK${gri}"

if [ ! -e /tmp/SDL2/SDL2_image.dll ]; then
   echo "${red}SDL2-image missing...${gri}"
   echo "downloading SDL2-image..."A
   echo "   http://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0-win32-x86.zip"
   cd /tmp/SDL2
   wget -q http://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0-win32-x86.zip
   unzip -o -qq SDL2_image-2.0.0-win32-x86.zip
fi
echo "${gre}SDL2-image OK${gri}"

if [ ! -e /tmp/SDL2/SDL2_ttf.dll ]; then
   echo "${red}SDL2-ttf missing...${gri}"
   echo "downloading SDL2-ttf..."
   echo "   http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12-win32-x86.zip"
   cd /tmp/SDL2
   wget -q http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12-win32-x86.zip
   unzip -o -qq SDL2_ttf-2.0.12-win32-x86.zip
fi
echo "${gre}SDL2-ttf OK${gri}"

if [ ! -e /tmp/SDL2/SDL2_mixer.dll ]; then
   echo "${red}SDL2-mixer missing...${gri}"
   echo "downloading SDL2-mixer..."
   echo "   http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.0-win32-x86.zip"
   cd /tmp/SDL2
   wget -q http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.0-win32-x86.zip
   unzip -o -qq SDL2_mixer-2.0.0-win32-x86.zip
fi
echo "${gre}SDL2-mixer OK${gri}"


cd ${PRJ}

cd build

rm -rf *

cmake -DCMAKE_TOOLCHAIN_FILE=../Toolchain-mingw32.cmake ..

make

cd ..

mkdir ${package}

cp bin/tetris.exe ${package}/

cp ressources/* ${package}/

cp /tmp/SDL2/*.dll ${package}/

echo "making zip..."

zip -q -r ${package}.zip ${package}

mv ${package}.zip bin/

echo "clean..."

rm -rf ${package}.zip ${package} 

echo ""
echo "done."

ls bin/${package}.zip

