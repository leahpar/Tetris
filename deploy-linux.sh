#!/bin/sh

version=`grep "^\*" ChangeLog.md | head -1 | cut -d ' ' -f 2 | tr -d 'v'`
codexe=`git log -1 --format=%ci | sed "s/[^0-9]//g" | cut -b1-12`
os="linux64"
project="Tetris"
package="${project}-${version}"
package2="${project}-${version}-${os}-${codexe}"

PRJ=`pwd`
BIN=tetris

# colors
gri="\033[0m"
red="\033[31m"
gre="\033[32m"
ore="\033[33m"
 

cd build

rm -rf *

cmake ..

make

cd ..

mkdir ${package} 2>/dev/null

cp bin/${BIN} ${package}/

cp -r ressources ${package}/

mkdir ${package}/libs 2>/dev/null
ldd bin/${BIN} | grep SDL2 | while read lib x path x
do
   cp ${path} ${package}/libs/${lib}
done

echo "make launcher..."

echo "#!/bin/sh" > ${package}/launch.sh
echo "LD_LIBRARY_PATH=\${LD_LIBRARY_PATH}:\`pwd\`/libs ./${BIN}" >> ${package}/launch.sh
chmod 755 ${package}/launch.sh

echo "make tar..."

tar -czf ${package2}.tar.gz ${package}

rm -f bin/${package2}.tar.gz 2>/dev/null
mv ${package2}.tar.gz bin/

echo "clean..."

rm -rf ${package2}.tar.gz ${package} 

echo ""
echo "done."

ls bin/${package2}.tar.gz

