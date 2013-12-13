#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#define LG_PIECE   4
#define NB_PIECE   7


#define DISPLAY_TITLE 0
//      DISPLAY_BLANK 1
#define DISPLAY_SCORE 2
#define DISPLAY_LEVEL 3
#define DISPLAY_LINES 4
#define DISPLAY_PIECS 5
#define DISPLAY_MUSIC 6
//      DISPLAY_BLANK 7
#define DISPLAY_NEXT  8
//      DISPLAY_BLANK 9
//      DISPLAY_BLANK 10
//      DISPLAY_BLANK 11
//      DISPLAY_BLANK 12
#define DISPLAY_HIGH  13
#define DISPLAY_COUNT 14 + NB_HIGHSCORE
char g_display[DISPLAY_COUNT][2][20] =
{
   {"TETRIS " ,  " "},
   {" ", " "},
   {"Score  :", "123"},
   {"Level  :", "123"},
   {"Lines  :", "123"},
   {"Pieces :", "123"},
   {"Music  :", "off"},
   {" ", " "},
   {"Next Piece", " "},
   {" ", " "},
   {" ", " "},
   {" ", " "},
   {" ", " "},
   {"High scores", " "}

};

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


#endif // DATA_H_INCLUDED
