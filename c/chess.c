
#include <stdlib.h>

typedef unsigned char piece;
typedef unsigned char position;
typedef char* position_set;

// return file.
unsigned char fileof( position p ){
    return ( 0xF0 & p) >> 4;
}  
// return rank.  
unsigned char rankof( position p ){
    return 0x0F & p;
}

#define EMPTY   0x00
#define PAWN    0x01
#define KNIGHT  0x02
#define BISHOP  0x03
#define ROOK    0x04
#define QUEEN   0x05
#define KING    0x06

#define WHITE   0x00
#define BLACK   0x08

#define WHITE_SHORTCASTLE  1
#define WHITE_LONGCASTLE   2
#define BLACK_SHORTCASTLE  4
#define BLACK_LONGCASTLE   8

typedef unsigned char boardmeta;

typedef struct {    
    unsigned char squares[32];
    boardmeta meta;
} board;


#define EMPTY_BOARD 0x00000000000000000000000000000000;

board* gamestart_board() {
    board* b = (board*)malloc(sizeof(board));
    b->meta = 0xff; // all castling
	 fprintf(stderr, "\033[43;30m%32s\033[0m\n", b->squares);
    b->squares[0] = (( WHITE | ROOK   ) << 4 ) | ( WHITE | KNIGHT ); 
    b->squares[1] = (( WHITE | BISHOP ) << 4 ) | ( WHITE | QUEEN  ); 
    b->squares[2] = (( WHITE | KING   ) << 4 ) | ( WHITE | BISHOP ); 
    b->squares[3] = (( WHITE | KNIGHT ) << 4 ) | ( WHITE | ROOK   );
    b->squares[4] = (( WHITE | PAWN   ) << 4 ) | ( WHITE | PAWN   );
    b->squares[5] = (( WHITE | PAWN   ) << 4 ) | ( WHITE | PAWN   );
    b->squares[6] = (( WHITE | PAWN   ) << 4 ) | ( WHITE | PAWN   );
    b->squares[7] = (( WHITE | PAWN   ) << 4 ) | ( WHITE | PAWN   );
	 for( int i = 8; i < 24 ;i++ ) b->squares[i] = 0x00;
    b->squares[24] = (( BLACK | PAWN   ) << 4 ) | ( BLACK | PAWN   );
    b->squares[25] = (( BLACK | PAWN   ) << 4 ) | ( BLACK | PAWN   );
    b->squares[26] = (( BLACK | PAWN   ) << 4 ) | ( BLACK | PAWN   );
    b->squares[27] = (( BLACK | PAWN   ) << 4 ) | ( BLACK | PAWN   );
    b->squares[28] = (( BLACK | ROOK   ) << 4 ) | ( BLACK | KNIGHT ); 
    b->squares[29] = (( BLACK | BISHOP ) << 4 ) | ( BLACK | QUEEN  ); 
    b->squares[30] = (( BLACK | KING   ) << 4 ) | ( BLACK | BISHOP ); 
    b->squares[31] = (( BLACK | KNIGHT ) << 4 ) | ( BLACK | ROOK   );
	 for( int i = 0; i < 32; i++ ){
		fprintf(stderr, "0x%02x 0x%02x ", (b->squares[i] >> 4) & 15, b->squares[i] & 15 );
		if( (i + 1) % 4 == 0) fprintf(stderr, "\n" );
	 }
   return b;
}

piece piece_at( const board* b, position p ){
    unsigned char offset_bits = ( (rankof(p) * 32) + (fileof(p) * 4) ) ;
	 unsigned char offset = offset_bits / 8;
	 unsigned char shift  = 4 - (offset_bits % 8 );
	 unsigned char pieceat = ( b->squares[offset ] >> shift ) & 15;
	 //fprintf(stderr, "Piece at position %02x is at bit %u, offset %u, shift %u, and is 0x%x\n", 
	// 	p, offset_bits, offset, shift, pieceat);
	return pieceat;
}

