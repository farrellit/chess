
typedef char piece;
typedef char position;
typedef char* position_set;

// return file.
char fileof( position p ){
    return ( 0xF0 & p) >> 4;
}  
// return rank.  
char rankof( position p ){
    return 0x0F & p;
}

#define EMPTY   0x00
#define PAWN    0x01
#define KNIGHT  0X02
#define BISHOP  0X03
#define ROOK    0X04
#define QUEEN   0X05
#define KING    0X06

#define WHITE   0x00
#define BLACK   0x08

#define WHITE_CASTLABLE  0x01
#define BLACK_CASTLABLE  0x02

#define EMPTY_BOARD 0x00000000000000000000000000000000;

char[] gamestart_board() {
    return { 
    (( WHITE & ROOK   ) << 4 ) & ( WHITE & KNIGHT ), 
    (( WHITE & BISHOP ) << 4 ) & ( WHITE & QUEEN  ), 
    (( WHITE & KING   ) << 4 ) & ( WHITE & BISHOP ), 
    (( WHITE & KNIGHT ) << 4 ) & ( WHITE & ROOK   ), 
    (( WHITE & PAWN   ) << 4 ) & ( WHITE & PAWN   ),
    (( WHITE & PAWN   ) << 4 ) & ( WHITE & PAWN   ),
    (( WHITE & PAWN   ) << 4 ) & ( WHITE & PAWN   ),
    (( WHITE & PAWN   ) << 4 ) & ( WHITE & PAWN   ),
    0x00, 0x00, 0x00, 0x00, // empty row
    0x00, 0x00, 0x00, 0x00, // empty row
    0x00, 0x00, 0x00, 0x00, // empty row
    0x00, 0x00, 0x00, 0x00, // empty row
    (( WHITE & PAWN   ) << 4 ) & ( WHITE & PAWN   ),
    (( WHITE & PAWN   ) << 4 ) & ( WHITE & PAWN   ),
    (( WHITE & PAWN   ) << 4 ) & ( WHITE & PAWN   ),
    (( WHITE & PAWN   ) << 4 ) & ( WHITE & PAWN   ),
    (( WHITE & ROOK   ) << 4 ) & ( WHITE & KNIGHT ), 
    (( WHITE & BISHOP ) << 4 ) & ( WHITE & QUEEN  ), 
    (( WHITE & KING   ) << 4 ) & ( WHITE & BISHOP ), 
    (( WHITE & KNIGHT ) << 4 ) & ( WHITE & ROOK   ) 
    }
}


typedef char boardmeta;

typedef struct {    
    char squares[32];
    boardmeta meta;
} board;

piece piece_at( const board* b, position p ){
    return ( 
      *(b->squares) >>  
        ( ( fileof( p ) * 4 ) + 
          ( fileof( p ) * 8 )  )  
        ) & 0X0F;
}


