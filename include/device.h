#ifdef WIN32
#include <windows.h>
#define Alert(a,b,c,d) MessageBox(a,b,c,d)
// SDL2+WIN bug ?
#undef main
#endif

#ifdef __linux__
#define Alert(a,b,c,d)
#endif

#ifdef APPLE
#define Alert(a,b,c,d)
#endif
