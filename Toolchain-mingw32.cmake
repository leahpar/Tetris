# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)
SET(CMAKE_WIN32_EXECUTABLE ON)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER i686-w64-mingw32-windres)

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH
  /usr/i686-w64-mingw32
)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# DLLs
# This section is used by deploy-win.sh to get dlls
# libfreetype-6.dll
# libogg-0.dll
# libvorbis-0.dll
# libvorbisfile-3.dll
# SDL2.dll
# SDL2_image.dll
# SDL2_ttf.dll
# SDL2_mixer.dll

