#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>  /* sleep */
#include <time.h>
#include <SDL/SDL.h>
//#include <SDL/SDL_ttf.h>

#define DT_USLEEP  30000

#define DISPLAY_MODE_SDL
#ifdef DISPLAY_MODE_SDL
#define printMatrix() printMatrix_SDL()
#endif
#ifndef DISPLAY_MODE_SDL
#define printMatrix() printMatrix_CLI()
#endif



#ifdef LINUX
#define clear() system("clear")
long getTicTime() {
{
   struct timespec time;

   clock_gettime(CLOCK_REALTIME, &time);
   return time.tv_sec * 1000000 + time.tv_nsec / 1000;
}
#endif
#ifdef WIN32
#include <Windows.h>
#define clear() system("cls")
/* linux : usleep(usec) / Windows : Sleep(ms) */
#define usleep(x) Sleep(x/1000)
long getTicTime() {
    static LARGE_INTEGER s_frequency;
    static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
    if (s_use_qpc) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / s_frequency.QuadPart;
    } else {
        return GetTickCount();
    }
}
#endif

#define MATRIX_X (20+1)
#define MATRIX_Y (10+2)

#define SCORE_DISPLAY_Y (MATRIX_Y*(TILE_S+2))

#define TILESET_FILE "texture.bmp"
#define TILE_S 30

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

#define ACTION_NONE        -1
#define ACTION_QUIT        99
#define ACTION_MOVE_DOWN    0
#define ACTION_MOVE_LEFT    1
#define ACTION_MOVE_RIGHT   2
#define ACTION_ROTATE       3
#define ACTION_DROP         4


// fucking coordinate !
// #define x y
// #define y x

#define LG_PIECE   4
#define NB_PIECE   7

int g_pieces[NB_PIECE*4][LG_PIECE][LG_PIECE] =
{
   /************************ 0 *****************************/
   // I  0
   {{PX_V, PX_V, PX_V, PX_V},
    {PX_I, PX_I, PX_I, PX_I},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // O  0
   {{PX_O, PX_O, PX_V, PX_V},
    {PX_O, PX_O, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // T  0
   {{PX_V, PX_T, PX_V, PX_V},
    {PX_T, PX_T, PX_T, PX_V},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // L  0
   {{PX_V, PX_V, PX_V, PX_V},
    {PX_L, PX_L, PX_L, PX_V},
    {PX_L, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // J  0
   {{PX_J, PX_V, PX_V, PX_V},
    {PX_J, PX_J, PX_J, PX_V},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // Z  0
   {{PX_V, PX_V, PX_V, PX_V},
    {PX_Z, PX_Z, PX_V, PX_V},
    {PX_V, PX_Z, PX_Z, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // S  0
   {{PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_S, PX_S, PX_V},
    {PX_S, PX_S, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   /************************ 90 *****************************/
   // I  90
   {{PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V}},

   // O  90
   {{PX_O, PX_O, PX_V, PX_V},
    {PX_O, PX_O, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // T  90
   {{PX_V, PX_T, PX_V, PX_V},
    {PX_V, PX_T, PX_T, PX_V},
    {PX_V, PX_T, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // L  90
   {{PX_L, PX_L, PX_V, PX_V},
    {PX_V, PX_L, PX_V, PX_V},
    {PX_V, PX_L, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // J  90
   {{PX_V, PX_J, PX_J, PX_V},
    {PX_V, PX_J, PX_V, PX_V},
    {PX_V, PX_J, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // Z  90
   {{PX_V, PX_V, PX_Z, PX_V},
    {PX_V, PX_Z, PX_Z, PX_V},
    {PX_V, PX_Z, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // S  90
   {{PX_V, PX_S, PX_V, PX_V},
    {PX_V, PX_S, PX_S, PX_V},
    {PX_V, PX_V, PX_S, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

    /************************ 180 *****************************/
   // I  0
   {{PX_V, PX_V, PX_V, PX_V},
    {PX_I, PX_I, PX_I, PX_I},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // O  0
   {{PX_O, PX_O, PX_V, PX_V},
    {PX_O, PX_O, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // T  0
   {{PX_T, PX_T, PX_T, PX_V},
    {PX_V, PX_T, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // L  0
   {{PX_V, PX_V, PX_L, PX_V},
    {PX_L, PX_L, PX_L, PX_V},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // J  0
   {{PX_V, PX_V, PX_V, PX_V},
    {PX_J, PX_J, PX_J, PX_V},
    {PX_V, PX_V, PX_J, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // Z  0
   {{PX_V, PX_V, PX_V, PX_V},
    {PX_Z, PX_Z, PX_V, PX_V},
    {PX_V, PX_Z, PX_Z, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // S  0
   {{PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_S, PX_S, PX_V},
    {PX_S, PX_S, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   /************************ 270 *****************************/
   // I  270
   {{PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V}},

   // O  270
   {{PX_O, PX_O, PX_V, PX_V},
    {PX_O, PX_O, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // T  270
   {{PX_V, PX_T, PX_V, PX_V},
    {PX_T, PX_T, PX_V, PX_V},
    {PX_V, PX_T, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // L  270
   {{PX_V, PX_L, PX_V, PX_V},
    {PX_V, PX_L, PX_V, PX_V},
    {PX_V, PX_L, PX_L, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // J  270
   {{PX_V, PX_J, PX_V, PX_V},
    {PX_V, PX_J, PX_V, PX_V},
    {PX_J, PX_J, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // Z  270
   {{PX_V, PX_V, PX_Z, PX_V},
    {PX_V, PX_Z, PX_Z, PX_V},
    {PX_V, PX_Z, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // S  270
   {{PX_V, PX_S, PX_V, PX_V},
    {PX_V, PX_S, PX_S, PX_V},
    {PX_V, PX_V, PX_S, PX_V},
    {PX_V, PX_V, PX_V, PX_V}}
};

typedef struct
{
   int nb;
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
    SDL_Surface* tileset;
    TileProp* props;
    SDL_Surface* screen;
} T_SCREEN;
#define S_SCREEN sizeof(T_SCREEN)

/******************************************/
#define ASCII_PX_EV  "    " /* void */
#define ASCII_PX_EL  "  <!" /* left */
#define ASCII_PX_ER  "!>  " /* right */
#define ASCII_PX_EB  "=="   /* bottom */
#define ASCII_PX_EB2 "\\/"  /* bottom2 */

#define ASCII_PX_V  " ."
#define ASCII_PX    "##"
#define ASCII_PX_FX "**"

/******************************************/

int g_matrix[MATRIX_X][MATRIX_Y];
T_PIECE g_piece;
T_SCORE g_score;
T_SCREEN g_screen;

void levelUp()
{
   g_score.level /= 1.1;
}

/******************************************************************************/
/* initialize the matrice and create rotated pieces*/
/******************************************************************************/
void initMatrix()
{
   int x, y;
   // empty the matrix
   for (x=0; x<MATRIX_X; x++)
      for (y=0; y<MATRIX_Y; y++)
         g_matrix[x][y] = PX_V;

   // create edges
   for (x=0; x<MATRIX_X; x++)
   {
      g_matrix[x][0]          = PX_EL;
      g_matrix[x][MATRIX_Y-1] = PX_ER;
   }
   for (y=0; y<MATRIX_Y; y++)
   {
      g_matrix[MATRIX_X-1][y]  = PX_EB;
   }
}

/******************************************************************************/
/* print matrix on the screen */
/******************************************************************************/
void printMatrix_SDL()
{
   int x, y;
   SDL_Rect rect;

   // clean screen
   SDL_FillRect(g_screen.screen, NULL, 0);

   // display matrix
   for(x=0; x<MATRIX_X; x++)
   {
      for(y=0; y<MATRIX_Y; y++)
      {
         rect.h = TILE_S;
         rect.w = TILE_S;
         rect.y = x * TILE_S;
         rect.x = y * TILE_S;
         SDL_BlitSurface(g_screen.tileset,
                         &(g_screen.props[g_matrix[x][y]].R),
                         g_screen.screen,
                         &rect);
      }
   }

   // display next piece
   for(x=0; x<LG_PIECE; x++)
   {
      for(y=0; y<LG_PIECE; y++)
      {
         rect.h = TILE_S;
         rect.w = TILE_S;
         rect.y = x * TILE_S + TILE_S;
         rect.x = y * TILE_S + SCORE_DISPLAY_Y;
         SDL_BlitSurface(g_screen.tileset,
                         &(g_screen.props[g_pieces[g_score.nextPiece][x][y]].R),
                         g_screen.screen,
                         &rect);
      }
   }


   SDL_Flip(g_screen.screen);
}

void printMatrix_CLI()
{
   int x,y;

   //clear(); // clear console
   fprintf(stdout, "\n");

   for (x=0; x<MATRIX_X-1; x++)
   {
      //fprintf(stdout, "%.2d", x);
      for (y=0; y<MATRIX_Y; y++)
      {
         switch (g_matrix[x][y])
         {
            case PX_EB:
                  fprintf(stdout, ASCII_PX_EB);
               break;
            case PX_ER:
                  fprintf(stdout, ASCII_PX_ER);
               break;
            case PX_EL:
                  fprintf(stdout, ASCII_PX_EL);
               break;
            case PX_V:
               fprintf(stdout, ASCII_PX_V);
               break;
            case PX_FX:
               fprintf(stdout, ASCII_PX_FX);
               break;
            case PX_I:
            case PX_O:
            case PX_T:
            case PX_L:
            case PX_J:
            case PX_Z:
            case PX_S:
               fprintf(stdout, ASCII_PX);
               break;
         }
      }
      // fprintf(stdout, ASCII_PX_ER);
      fprintf(stdout, "\n");
   }

   // bottom edge
   fprintf(stdout, ASCII_PX_EL);
   for (y=1; y<MATRIX_Y-1; y++)
   {
      fprintf(stdout, ASCII_PX_EB);
   }
   fprintf(stdout, ASCII_PX_ER);
   fprintf(stdout, "\n");
   fprintf(stdout, ASCII_PX_EV);
   for (y=1; y<MATRIX_Y-1; y++)
   {
      fprintf(stdout, ASCII_PX_EB2);
   }
   fprintf(stdout, ASCII_PX_EV);
   fprintf(stdout, "\n");

   fprintf(stdout, "tps    : %d\n", g_score.tps);
   fprintf(stdout, "lines  : %d\n", g_score.lines);
   fprintf(stdout, "piece  : nb %d ; type %d ; pos [%d ; %d]\n",
      g_piece.nb, g_piece.ctype, g_piece.cx, g_piece.cy);

}

/******************************************************************************/
/* get a random piece */
/******************************************************************************/
int getRandomPiece()
{
   return rand() % (NB_PIECE * 4);
}

/******************************************************************************/
/* test if new position is busy */
/******************************************************************************/
int testPosition()
{
// fprintf(stderr, "DBG testPosition\n");
   int x,y;

   // collision
   for (x=0; x<LG_PIECE; x++)
   {
      for(y=0; y<LG_PIECE; y++)
      {
         if (g_pieces[g_piece.ntype][x][y]            != PX_V
          && g_matrix[g_piece.nx + x][g_piece.ny + y] != PX_V)
         {
            return 1;
         }
      }
   }
   return 0;
}

/******************************************************************************/
/* delete the current piece at its current position */
/******************************************************************************/
void deletePiece()
{
// fprintf(stderr, "DBG deletePiece\n");
   int x,y;
   for (x=0; x<LG_PIECE; x++)
   {
      for(y=0; y<LG_PIECE; y++)
      {
         if (g_pieces[g_piece.ctype][x][y] != PX_V)
         {
            g_matrix[g_piece.cx + x][g_piece.cy + y] = PX_V;
         }
      }
   }
}

/******************************************************************************/
/* delete a line and move all upper lines */
/******************************************************************************/
void deleteLine(int line)
{
   int x, y;

   // FX complete line
   for (y=1; y<MATRIX_Y-1; y++)
   {
      g_matrix[line][y] = PX_FX;
   }
   printMatrix();
   usleep(300000);

   // move upper
   for (x=line; x>0; x--)
   {
      memcpy(g_matrix[x], g_matrix[x-1], MATRIX_Y*sizeof(int));
   }
   // empty 0th line
   for (y=1; y<MATRIX_Y-1; y++)
   {
      g_matrix[0][y] = PX_V;
   }
}

/******************************************************************************/
/* check if there is some complete line */
/******************************************************************************/
void checkLine()
{
   int c = 0;
   int x,y;
   for (x=0; x<MATRIX_X-1; x++)
   {
      c = 0;
      for(y=1; y<MATRIX_Y-1; y++)
      {
         if (g_matrix[x][y] != PX_V) c++;
      }
      if (c == MATRIX_Y-2)
      {
         deleteLine(x);
         g_score.lines++;
         levelUp();
      }
   }
}

/******************************************************************************/
/* draw the current piece at its new position */
/******************************************************************************/
void drawPiece()
{
// fprintf(stderr, "DBG drawPiece\n");
   int x,y;
   // draw piece
   for (x=0; x<LG_PIECE; x++)
   {
      for(y=0; y<LG_PIECE; y++)
      {
         if (g_pieces[g_piece.ntype][x][y] != PX_V)
         {
            g_matrix[g_piece.nx + x][g_piece.ny + y]
                                               = g_pieces[g_piece.ntype][x][y];
         }
      }
   }
   // set new posision
   g_piece.cx = g_piece.nx;
   g_piece.cy = g_piece.ny;
   g_piece.ctype = g_piece.ntype;
}

/******************************************************************************/
/* add a piece into the matrix */
/******************************************************************************/
int addPiece(int piece)
{
// fprintf(stderr, "DBG addPiece %d\n", piece);

   // create piece
   g_piece.nb++;
   g_piece.ntype = piece;
   g_piece.ctype = g_piece.ntype;
   g_piece.nx    = 0;
   g_piece.ny    = MATRIX_Y/2-2;
   g_piece.cx    = g_piece.nx;
   g_piece.cy    = g_piece.ny;

   // test the new position
   if (testPosition() == 1) return 1;

   // draw the piece
   drawPiece();

   return 0;
   // if impossible, return 1, game over
}

/******************************************************************************/
/* DEV : simulate player action */
/******************************************************************************/
int simPlayerAction()
{
   /* dev  return rand()%10; */
   int ret = ACTION_NONE;
   SDL_Event event;

   if (SDL_PollEvent(&event))
   {
      switch(event.type)
      {
         case SDL_QUIT:
            ret = ACTION_QUIT;
            break;
         case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
               ret = ACTION_QUIT;
               break;
            case SDLK_UP:
               ret = ACTION_ROTATE;
               break;
            case SDLK_DOWN:
               ret = ACTION_MOVE_DOWN;
               break;
            case SDLK_RIGHT:
               ret = ACTION_MOVE_RIGHT;
               break;
            case SDLK_LEFT:
               ret = ACTION_MOVE_LEFT;
               break;
            case SDLK_SPACE:
               ret = ACTION_DROP;
               break;
            default:
               break;
            }
            break;
      }
      g_score.key = event.key.keysym.sym;
   }

   // purge events in queue
   while(SDL_PollEvent(&event));
   return ret;
}

/******************************************************************************/
/* move the current piece */
/******************************************************************************/
int movePiece(int move)
{
// fprintf(stderr, "DBG movePiece %d\n", move);
   int test_pos = 0;

   // delete piece at current position...
   deletePiece();

   switch(move)
   {
      case ACTION_MOVE_DOWN:
         g_piece.nx++;
         break;
      case ACTION_MOVE_LEFT:
         g_piece.ny--;
         break;
      case ACTION_MOVE_RIGHT:
         g_piece.ny++;
         break;
      case ACTION_ROTATE:
         g_piece.ntype = (g_piece.ctype+NB_PIECE)%(4*NB_PIECE);
         break;
      case ACTION_DROP:
         while (testPosition() == 0)
         {
            g_piece.nx++;
         }
         g_piece.nx--;
         break;
      default:
         // unknown move
         drawPiece();
         return 0;
         break;
   }

   // test new/bottom position
   test_pos = testPosition();
   if (test_pos != 0)
   {
      // redraw piece, sorry
      g_piece.nx = g_piece.cx;
      g_piece.ny = g_piece.cy;
      g_piece.ntype = g_piece.ctype;
      drawPiece();
      return test_pos;
   }
   // ...and draw it at new position
   drawPiece();
   return 0;
   // if can't move, return 1;
}

/******************************************************************************/
/* pause */
/******************************************************************************/
void pause()
{
   fprintf(stderr, "__PAUSE");
   int stop = 0;
   SDL_Event event;
   while(!stop)
   {
      SDL_WaitEvent(&event);
      switch(event.type){
         case SDL_QUIT:
            stop = 1;
            break;
      }
   }
}

int LoadTileSet()
{
   int i;
   SDL_Surface* img;

   // load texture

   if (access(TILESET_FILE, F_OK) != 0)
   {
      fprintf(stderr, "File %s not found !\n", TILESET_FILE);
      return 1;
   }

   img = SDL_LoadBMP(TILESET_FILE);
   if (img == NULL)
   {
      fprintf(stderr, "%s\n", SDL_GetError());
      return 1;
   }
   g_screen.tileset = SDL_DisplayFormat(img);
   SDL_FreeSurface(img);

   for(i=0; i<NB_PX; i++)
   {
         g_screen.props[i].R.h  = TILE_S;
         g_screen.props[i].R.w  = TILE_S;
         g_screen.props[i].R.y  = 0;
         g_screen.props[i].R.x  = TILE_S * i;
         g_screen.props[i].type = i;
      }
   return 0;
}

/******************************************************************************/
/* MAIN */
/******************************************************************************/
int main(int argc, char **argv)
{
   int res;
   long tic;
   int umove;
   int key;
   Uint8* keyboardmap;

fprintf(stderr, "__TETRIS OK\n");

   // init piece
   memset(&g_piece, 0, S_PIECE);

   // init score
   memset(&g_score, 0, S_SCORE);
   g_score.level     = 100;
   g_score.nextPiece = getRandomPiece();

   // init screen
   memset(&g_screen, 0, S_SCREEN);
   g_screen.props = (TileProp*)malloc(sizeof(TileProp)*NB_PX);

   // init rand
   srand(time(NULL));

fprintf(stderr, "__INIT OK\n");

   // Init SDL
   SDL_Init(SDL_INIT_VIDEO);
   g_screen.screen = SDL_SetVideoMode(MATRIX_Y*TILE_S + MATRIX_Y*TILE_S,
                                      MATRIX_X*TILE_S,
                                      32,
                                      SDL_HWSURFACE|SDL_DOUBLEBUF);
   if (LoadTileSet() != 0)
   {
      fprintf(stderr, "__INIT_SDL ERREUR\n");
      return 1;
   }

fprintf(stderr, "__INIT_SDL OK\n");

   initMatrix();
   printMatrix(); //SDL_Flip(g_screen.screen);

fprintf(stderr, "__START...\n");

   res = 0;
   while (1)
   {
fprintf(stderr, "__NEW PIECE\n");
      res = addPiece(g_score.nextPiece);
      g_score.nextPiece = getRandomPiece();
      if (res != 0)
      {
         fprintf(stdout, "Can't add piece %d at pos [%d;%d], GAME OVER !\n",
            g_piece.ctype, g_piece.nx, g_piece.ny);
         break;
      }
      printMatrix();

      // time is running out
      res = 0;
      while (1)
      {

         // player can move the piece
         tic = 0;
         key = 0;
         while (1)
         {
            usleep(10000);
            umove = simPlayerAction();
            // Quit game
            if (umove == ACTION_QUIT) return 1;
            // Reset tic counter so player can move piece
            if (umove == ACTION_DROP) tic = g_score.level/2;
            movePiece(umove);
            printMatrix();

            // action long press
            keyboardmap = SDL_GetKeyState(NULL);
            if (keyboardmap[key]) continue;
            key = g_score.key;

            tic++;
            if (tic > g_score.level)
            {
               break;
            }
         }

         res = movePiece(ACTION_MOVE_DOWN);
         printMatrix();

         if (res != 0)
         {
            // check if there is some complete lines
            checkLine();
            break;
         }

         printMatrix();
         g_score.tps++;
      }
   }

   pause();
   fprintf(stdout, "The end, bye !\n");
   SDL_Quit();
   return 0;

}











