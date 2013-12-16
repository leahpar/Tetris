#!/bin/sh

version=`grep "^\*" ChangeLog.md | head -1 | cut -d ' ' -f 2 | tr -d 'v'`
codexe=`date "+%Y%m%d%H%M%S"`
os="linux64"
package="Tetris-${version}"
package2="Tetris-${version}-${os}-${codexe}"

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

cp ressources/* ${package}/

mkdir ${package}/libs 2>/dev/null
ldd bin/${BIN} | grep SDL2 | while read lib x path x
do
   cp ${path} ${package}/libs/${lib}
done

echo "make launcher..."

echo "#!/bin/sh" > ${package}/launch.sh
echo "LD_LIBRARY_PATH=\${LD_LIBRARY_PATH}:`pwd`/libs ./${BIN}" >> ${package}/launch.sh

echo "make tar..."

tar -czf ${package2}.tar.gz ${package}

mv ${package2}.tar.gz bin/

echo "clean..."

rm -rf ${package2}.tar.gz ${package} 

echo ""
echo "done."

ls bin/${package2}.tar.gz

