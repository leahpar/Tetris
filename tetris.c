// gcc -o tetris -lrt tetris.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>  /* sleep */
#include <time.h>

#define MATRIX_X (20+1)
#define MATRIX_Y (10+2)

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

#define MOVE_DOWN   0
#define MOVE_LEFT   1
#define MOVE_RIGHT  2
#define ROTATE      3

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
   {{PX_L, PX_V, PX_V, PX_V},
    {PX_L, PX_V, PX_V, PX_V},
    {PX_L, PX_L, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // J  90
   {{PX_V, PX_J, PX_J, PX_V},
    {PX_V, PX_J, PX_V, PX_V},
    {PX_V, PX_J, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // Z  90
   {{PX_V, PX_Z, PX_V, PX_V},
    {PX_Z, PX_Z, PX_V, PX_V},
    {PX_Z, PX_V, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},

   // S  90
   {{PX_S, PX_V, PX_V, PX_V},
    {PX_S, PX_S, PX_V, PX_V},
    {PX_V, PX_S, PX_V, PX_V},
    {PX_V, PX_V, PX_V, PX_V}},
    
    /************************ 180 *****************************/
   // I  0
   {{PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V},
    {PX_V, PX_I, PX_V, PX_V}},

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

/******************************************/
#define ASCII_PX_EV  "    " /* void */
#define ASCII_PX_EL  "  <!" /* left */
#define ASCII_PX_ER  "!>  " /* right */
#define ASCII_PX_EB  "=="   /* bottom */
#define ASCII_PX_EB2 "\\/"  /* bottom2 */

#define ASCII_PX_V  " ."
#define ASCII_PX    "##"
/******************************************/

int g_matrix[MATRIX_X][MATRIX_Y];
int g_tps = 0;
int g_top = 0;

T_PIECE g_piece;


/******************************************************************************/
/* initialize the matrice and create rotated pieces*/
/******************************************************************************/
void initMatrix()
{
   int i, x, y;
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
   
//   // create rotated pieces
//   for (i=0; i<3*NB_PIECE; i++)
//   {
//      // rotate +90
//      for (x=0; x<LG_PIECE; x++)
//      {
//         for(y=0; y<LG_PIECE; y++)
//         {
//            g_pieces[i+NB_PIECE][x][y] = g_pieces[i][LG_PIECE-y-1][x];
//         }
//      }
//   }
}

/******************************************************************************/
/* print matrix on the screen */
/******************************************************************************/
void printMatrix()
{
   int x,y;
   
   system("clear");
   fprintf(stdout, "\n");
   
   for (x=0; x<MATRIX_X-1; x++)
   {
      // fprintf(stdout, ASCII_PX_EL);
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
   
   fprintf(stdout, "tps   : %d\n", g_tps);
   fprintf(stdout, "piece : nb %d ; type %d ; pos [%d ; %d]\n",
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
   int x;
   
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
    return rand()%10;
}

/******************************************************************************/
/* move the current piece */
/******************************************************************************/
int movePiece(int move)
{
// fprintf(stderr, "DBG movePiece %d\n", move);
   int test_pos = 0;
   
   switch(move)
   {
      case MOVE_DOWN:
         g_piece.nx++;
         break;
      case MOVE_LEFT:
         g_piece.ny--;
         break;
      case MOVE_RIGHT:
         g_piece.ny++;
         break;
      case ROTATE:
         g_piece.ntype = (g_piece.ctype+NB_PIECE)%(4*NB_PIECE);
         break;
      default:
         // unknown move
         return 0;
         break;
   }
   
   // delete piece at current position...
   deletePiece();
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
/* MAIN */
/******************************************************************************/
int main()
{
   int piece;
   int res;
   int tps = 0;
   struct timespec tic, tac;
   
   // init piece
   memset(&g_piece, 0, S_PIECE);
   
   // init rand
   srand(time(NULL));
   
   /*
   int i, j, k;
   for(i=0; i<7; i++)
   {
      for (j=0; j<2; j++)
      {
         for (k=0; k<4; k++)
         {
            fprintf(stdout, "%d", g_pieces[i][j][k]);
         }
         fprintf(stdout, "\n");
      }
      fprintf(stdout, "\n");
   }
   */
   
   initMatrix();
   printMatrix();
   
   res = 0;
   while (1)
   {
      piece = getRandomPiece();
      res = addPiece(piece);
      if (res != 0)
      {
         fprintf(stdout, "Can't add piece %d at pos [%d;%d], GAME OVER !\n",
            g_piece.ctype, g_piece.nx, g_piece.ny);
         return 1;
      }
      printMatrix();
   
      // time is running out
      res = 0;
      while (1)
      {
         clock_gettime(CLOCK_REALTIME, &tic);
         
         // player can move the piece
         while (1)
         {
            movePiece(simPlayerAction());
            
            clock_gettime(CLOCK_REALTIME, &tac);
            if (( tac.tv_sec  - tic.tv_sec  ) * 1000000
              + ( tac.tv_nsec - tic.tv_nsec ) / 1000      > 50000)
            {
               break;
            }
            usleep(20000);
         }
         
         res = movePiece(MOVE_DOWN);
         if (res != 0) break;

         printMatrix();
         g_tps++;
      }
   }
   
   fprintf(stdout, "The end, bye !\n");
   return 0;

}











