#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>  /* sleep */
#include <time.h>

/* http://www.libsdl.org */
#include <SDL2/SDL.h>

/* http://www.libsdl.org/projects/SDL_ttf */
#include <SDL2/SDL_ttf.h>

/* http://www.libsdl.org/projects/SDL_mixer */
/* http://www.kekkai.org/roger/sdl/mixer */
#include <SDL2/SDL_mixer.h>

/*
use SDL 2.0
http://www.siteduzero.com/forum/sujet/installation-sdl-2-code-blocks
*/

#include "device.h"
#include "config.h"
#include "tetris.h"
#include "data.h"

#define DISPLAY_MODE_SDL
#ifdef DISPLAY_MODE_SDL
#define printMatrix(a) printMatrix_SDL(a)
#endif
#ifndef DISPLAY_MODE_SDL
#define printMatrix(a) printMatrix_CLI(a)
#endif


int g_matrix[MATRIX_X][MATRIX_Y];
T_PIECE g_piece;
T_SCORE g_score;
T_SCREEN g_screen;


void levelUp()
{
   g_score.level++;
}

void printText(char * str)
{
   SDL_Surface * surface;
   SDL_Texture * texture;
   SDL_Rect      rect;

   // make texture
   surface = TTF_RenderText_Solid(g_screen.font, str, FONT_COLOR);
   texture = SDL_CreateTextureFromSurface(g_screen.renderer, surface);

   // display texture
   rect.h = surface->h;
   rect.w = surface->w;
   rect.y = TILE_S * MATRIX_X/2;
   rect.x = TILE_S * MATRIX_Y/2 - surface->w/2;
   SDL_RenderCopy(g_screen.renderer,
                  texture,
                  NULL,
                  &rect);

   SDL_FreeSurface(surface);
   SDL_DestroyTexture(texture);
}


void printScore()
{
   SDL_Surface * surface;
   SDL_Texture * texture;
   SDL_Rect      rect;
   int i,j;

   // score
   // level
   // lines
   // next piece


   sprintf(g_display[DISPLAY_SCORE][1], "%d", g_score.score);
   sprintf(g_display[DISPLAY_LEVEL][1], "%d", g_score.level);
   sprintf(g_display[DISPLAY_LINES][1], "%d", g_score.lines);
   sprintf(g_display[DISPLAY_PIECS][1], "%d", g_score.pieces);
   if (g_screen.pause == 0)
      sprintf(g_display[DISPLAY_MUSIC][1], "on");
   else
      sprintf(g_display[DISPLAY_MUSIC][1], "off");
   for (i=0; i<NB_HIGHSCORE; i++)
   {
      sprintf(g_display[DISPLAY_HIGH+1+i][0], "%d", g_score.highScore[i]);
      sprintf(g_display[DISPLAY_HIGH+1+i][1], " ");
   }

   for (i=0; i<DISPLAY_COUNT; i++)
   {
      for (j=0; j<2; j++)
      {
         // make texture
         surface = TTF_RenderText_Solid(g_screen.font, (char*)(g_display[i][j]), FONT_COLOR);
         texture = SDL_CreateTextureFromSurface(g_screen.renderer, surface);

         // display texture
         rect.h = surface->h;
         rect.w = surface->w;
         rect.y = SCORE_DISPLAY_X + i * TILE_S;
         rect.x = SCORE_DISPLAY_Y + j * 7 * TILE_S;
         SDL_RenderCopy(g_screen.renderer,
                        texture,
                        NULL,
                        &rect);
         SDL_FreeSurface(surface);
         SDL_DestroyTexture(texture);
      }
   }


}

/******************************************************************************/
/* print matrix on the screen */
/******************************************************************************/
void printMatrix_SDL(char * str)
{
   int x, y;
   SDL_Rect rect;

   // clean screen
   /* SDL 1.2
   SDL_FillRect(g_screen.screen, NULL, 0);
   */
   SDL_SetRenderDrawColor(g_screen.renderer, 0, 0, 0, 255);
   SDL_RenderClear(g_screen.renderer);

   // display matrix
   for(x=0; x<MATRIX_X; x++)
   {
      for(y=0; y<MATRIX_Y; y++)
      {
         rect.h = TILE_S;
         rect.w = TILE_S;
         rect.y = x * TILE_S;
         rect.x = y * TILE_S;
         /* SDL 1.2
         SDL_BlitSurface(g_screen.tileset,
                         &(g_screen.props[g_matrix[x][y]].R),
                         g_screen.screen,
                         &rect);
         */
         SDL_RenderCopy(g_screen.renderer,
                        g_screen.tileset,
                        &(g_screen.props[g_matrix[x][y]].R),
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
         rect.y = SCORE_DISPLAY_X + (x+DISPLAY_COUNT-NB_HIGHSCORE-1-4) * TILE_S;
         rect.x = y * TILE_S + SCORE_DISPLAY_Y;
         /* SDL 1.2
         SDL_BlitSurface(g_screen.tileset,
                         &(g_screen.props[g_pieces[g_score.nextPiece][x][y]].R),
                         g_screen.screen,
                         &rect);
         */
         SDL_RenderCopy(g_screen.renderer,
                        g_screen.tileset,
                        &(g_screen.props[g_pieces[g_score.nextPiece][x][y]].R),
                        &rect);
      }
   }

   // Print score
   printScore();

   // print text
   if (str != NULL)
   {
      printText(str);
   }


   /* SDL 1.2
   SDL_Flip(g_screen.screen);
   */
   SDL_RenderPresent(g_screen.renderer);
}


void printMatrix_CLI(char * str)
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
      g_score.pieces, g_piece.ctype, g_piece.cx, g_piece.cy);

}

/******************************************************************************/
/* get a random piece */
/******************************************************************************/
int getRandomPiece()
{
   return (rand() % NB_PIECE);
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
   printMatrix(NULL);
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
   int lines = 1;

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
         g_score.score += SCORE_LINE * lines;
         lines++;
      }
   }
   // if line(s) deleted, level up
   if (lines > 1)
   {
      levelUp();
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

   g_score.score += SCORE_PIECE;
   // create piece
   g_score.pieces++;
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
/* pause */
/******************************************************************************/
int gamePause(char * str)
{
   fprintf(stderr, "__PAUSE");
   int action = ACTION_NONE;
   SDL_Event event;

   // purge events in queue
   while(SDL_PollEvent(&event));

   // wait for end pause or quit
   while(action == ACTION_NONE)
   {
      SDL_WaitEvent(&event);
      switch(event.type)
      {
         case SDL_QUIT:
            action = ACTION_QUIT;
            break;
         case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
               case SDLK_ESCAPE:
                  action = ACTION_QUIT;
                  break;
               case SDLK_p:
                  action = ACTION_PAUSE;
                  break;
               case SDLK_m:
                  /* pause music */
                  if (g_screen.pause == 1)
                  {
                     Mix_PlayMusic(g_screen.sound, -1);
                     g_screen.pause = 0;
                  }
                  /* resume music */
                  else
                  {
                     Mix_HaltMusic();
                     g_screen.pause = 1;
                  }
                  action = ACTION_NONE;
                  break;
               default:
                  action = ACTION_NONE;
                  break;
            }
            break;
      }
      printMatrix(str);
   }
   return action;
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
         case SDL_WINDOWEVENT:
            // Set pause on focus lost
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
               ret = gamePause("Pause...");
            }
            break;
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
            case SDLK_m:
               /* pause music */
               if (g_screen.pause == 1)
               {
                  Mix_PlayMusic(g_screen.sound, -1);
                  g_screen.pause = 0;
               }
               /* resume music */
               else
               {
                  Mix_HaltMusic();
                  g_screen.pause = 1;
               }
               ret = ACTION_NONE;
               break;
            case SDLK_p:
            case SDLK_LALT:
               ret = gamePause("Pause...");
               break;
            default:
               ret = ACTION_NONE;
               break;
            }
            break;
      }
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
         g_score.score += SCORE_DROP * (g_piece.nx - g_piece.cx);
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


int LoadTileSet()
{
   int i;
   SDL_Surface* img;

   // load texture

   if (access(TILESET_FILE, F_OK) != 0)
   {
      Alert(NULL, "File %s not found !", NULL, 0);
      return 1;
   }

   img = SDL_LoadBMP(TILESET_FILE);
   if (img == NULL)
   {
      Alert(NULL, SDL_GetError(), NULL, 0);
      return 1;
   }
   /* SDL 1.2
   g_screen.tileset = (SDL_Surface*) SDL_DisplayFormat(img);
   */
   g_screen.tileset = SDL_CreateTextureFromSurface(g_screen.renderer, img);
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
/* initialize libs SDL & co */
/******************************************************************************/
int initTetris()
{
   FILE * f;

   // init piece
   memset(&g_piece, 0, S_PIECE);

   // init score
   memset(&g_score, 0, S_SCORE);
   g_score.nextPiece = getRandomPiece();

   // init screen
   memset(&g_screen, 0, S_SCREEN);
   g_screen.props = (TileProp*)malloc(sizeof(TileProp)*NB_PX);
   g_screen.pause = 1;

   // init rand
   srand(time(NULL));

   // Init SDL
   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
   g_screen.screen = SDL_CreateWindow(WINDOW_TITLE,
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      MATRIX_Y*TILE_S + MATRIX_Y*TILE_S,
                                      MATRIX_X*TILE_S,
                                      0);
   g_screen.renderer = SDL_CreateRenderer(g_screen.screen, -1, 0);

   // Init SDL ttf
   TTF_Init();
   g_screen.font  = TTF_OpenFont(FONT_FILE, FONT_SIZE);

   // Init audio
   if (Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS))
   {
      Alert(NULL, Mix_GetError(), NULL, 0);
      return 1;
   }
   g_screen.sound = Mix_LoadMUS(AUDIO_FILE);
   if(g_screen.sound == NULL) {
      Alert(NULL, Mix_GetError(), NULL, 0);
      return 1;
   }
   //Mix_PlayMusic(g_screen.sound, -1);

   // load textures
   if (LoadTileSet() != 0)
   {
      Alert(NULL, SDL_GetError(), NULL, 0);
      return 1;
   }

   //get high scores
   f = fopen(SCORE_FILENAME, "r");
   if (f != NULL)
   {
      fread(g_score.highScore, sizeof(g_score.highScore), 1, f);
      fclose(f);
   }

   return 0;
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
/* MAIN */
/******************************************************************************/
int main(int argc, char **argv)
{
   int res;
   long tic;
   int umove;
   FILE * f;
   int i, tmp;

   // Init SDL & co
   if (initTetris() != 0)
   {
      return 1;
   }

   // Init display
   initMatrix();
   printMatrix(NULL);

   res = 0;
   while (1)
   {
      res = addPiece(g_score.nextPiece);
      g_score.nextPiece = getRandomPiece();
      // can't add piece, game over
      if (res != 0)
      {
         break;
      }
      printMatrix(NULL);

      // time is running out
      res = 0;
      while (1)
      {
         tic = 100 - 2*g_score.level;
         g_score.drop = 0;
         // player can move the piece
         while (1)
         {
            usleep(10000);
            umove = simPlayerAction();
            // Quit game
            if (umove == ACTION_QUIT) return 1;
            // Reset tic counter so player can move piece
            if (umove == ACTION_DROP && g_score.drop == 0)
            {
               tic = 30;
               g_score.drop = 1;
            }
            else if (umove == ACTION_DROP)
            {
               tic = 0;
            }
            movePiece(umove);
            printMatrix(NULL);

            tic--;
            if (tic <= 0)
            {
               break;
            }
         }

         res = movePiece(ACTION_MOVE_DOWN);
         printMatrix(NULL);

         if (res != 0)
         {
            // check if there is some complete lines
            checkLine();
            break;
         }

         printMatrix(NULL);
         g_score.tps++;
      }
   }

   gamePause("GAME OVER");

   // save high scores
   f = fopen(SCORE_FILENAME, "w");
   for (i=0; i<NB_HIGHSCORE; i++)
   {
      if (g_score.score > g_score.highScore[i])
      {
         tmp = g_score.highScore[i];
         g_score.highScore[i] = g_score.score;
         g_score.score = tmp;
      }
   }
   if (f != NULL)
   {
      fwrite(g_score.highScore, sizeof(g_score.highScore), 1, f);
      fclose(f);
   }

   TTF_CloseFont(g_screen.font);
   TTF_Quit();

   Mix_HaltMusic();
   Mix_FreeMusic(g_screen.sound);

   SDL_DestroyTexture(g_screen.tileset);
   SDL_DestroyRenderer(g_screen.renderer);
   SDL_DestroyWindow(g_screen.screen);
   SDL_Quit();

   return 0;

}

