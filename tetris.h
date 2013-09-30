#ifndef TETRIS_SDL_H_INCLUDED
#define TETRIS_SDL_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_Mixer.h>


/**** PIXELS ******************************/
#define PX_I   0
#define PX_O   1
#define PX_T   2
#define PX_L   3
#define PX_J   4
#define PX_Z   5
#define PX_S   6
#define PX_V   7   /* void pixel */
#define PX_ET  8   /* edge top pixel */
#define PX_EB  9   /* edge bottom pixel */
#define PX_ER  10  /* edge right pixel */
#define PX_EL  11  /* edge left pixel */
#define PX_FX  12  /* FX complete line */
#define NB_PX  13

/**** ASCII ART ***************************/
#define ASCII_PX_EV  "    " /* void       */
#define ASCII_PX_EL  "  <!" /* left       */
#define ASCII_PX_ER  "!>  " /* right      */
#define ASCII_PX_EB  "=="   /* bottom     */
#define ASCII_PX_EB2 "\\/"  /* bottom2    */
#define ASCII_PX_V   " ."
#define ASCII_PX     "##"
#define ASCII_PX_FX  "**"


/**** USER ACTIONS ************************/
#define ACTION_NONE        -1
#define ACTION_QUIT        99
#define ACTION_PAUSE       98
#define ACTION_MOVE_DOWN    0
#define ACTION_MOVE_LEFT    1
#define ACTION_MOVE_RIGHT   2
#define ACTION_ROTATE       3
#define ACTION_DROP         4

typedef struct
{
   // current type
   int ctype;
   // new position
   int ntype;
   // current position
   int cx;
   int cy;
   // new position
   int nx;
   int ny;
} T_PIECE;
#define S_PIECE sizeof(T_PIECE)

typedef struct
{
   int tps;
   int lines;
   int key;
   int level;
   int nextPiece;
   int score;
   int pieces;
   int drop;
   int highScore[NB_HIGHSCORE];
} T_SCORE;
#define S_SCORE sizeof(T_SCORE)

// SCREEN
typedef struct
{
    SDL_Rect R;
    int type;
} TileProp;
typedef struct
{
    SDL_Window* screen;
    SDL_Renderer *renderer;
    // textures
    SDL_Texture* tileset;
    TileProp* props;
    // font
    TTF_Font *font;
    // audio
    Mix_Music *sound;
    int pause;
} T_SCREEN;
#define S_SCREEN sizeof(T_SCREEN)


#endif // TETRIS_SDL_H_INCLUDED
