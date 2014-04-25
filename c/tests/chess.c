#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../chess.c"

char* showpos( char* s, position p ){
    snprintf( s, 3, "%c%u", fileof(p) + 'a', rankof(p) + 1 );
    return s;
}

char* showpiece(char* buf, size_t bufsize, piece p ){
	char* color;
	if( ( p & 8 ) == BLACK )
		color = "\033[30m";
	else
		color = "\033[37m";
	char* pstr;
	switch( p & 0x07 ){
		case PAWN:
			pstr = "Pa";
			break;
		case KNIGHT:
			pstr = "Kn";
			break;
		case BISHOP:
			pstr = "Bi";
			break;
		case ROOK:
			pstr = "Ro";
			break;
		case QUEEN:
			pstr = "Qu";
			break;
		case KING:
			pstr = "Kg";
			break;
		default:
		case EMPTY:
			pstr = "  ";
			break;
	}
	snprintf( buf, bufsize, "%s%s", color, pstr);
	return buf;
}

#define BG_BLACK "\033[41m"
#define BG_WHITE "\033[42m"
#define PIECEBUF 16
void showboard( board* b, char orientation ){
	position p;
	char* bg;
	char piecebuf[PIECEBUF];
	for( int rank = (orientation==WHITE?7:0); 
		(orientation==WHITE?rank >= 0 : rank <= 7); 
		( orientation ==WHITE ? rank-- : rank++) 
	){
		for( int file = 0; file < 8; file++ ){
			p = ( file << 4 ) + rank;
			//fprintf(stderr, "Printing piece at %s ( 0x%x ) \n", showpos( piecebuf, p ), piece_at(b,p ) );
			if(  
				( file % 2 == 0 && rank % 2 == 0 ) ||
				( file % 2 == 1 && rank % 2 == 1 ) 
			){
				bg = BG_BLACK;
			}else{
				bg = BG_WHITE;
			}
			printf( "%s%s\033[0m", bg, showpiece( piecebuf, PIECEBUF, piece_at( b, p ) ) );
		}
		printf("\n");
	}
}

int main(){
    char pos[3];
    char* strings[] = {
        "h8", "a1", "d6"
    };
    char positions[] = { 
        0x77, 0x00, 0x35
    };
    for( int i = 0; i < sizeof( positions ) ; i++ ){
        printf("\033[33mTest: \033[0m 0x%02x should equal %s | ", 
           	positions[i],
            strings[i]
        );
	
        if( 0 != strncmp( strings[i], showpos( pos, positions[i]) , 2) ){
            printf("\033[41mError!\033[0m 0x%02x should have equaled %s, but came out as %s\n", 
                positions[i],
                strings[i],
					 pos
            );
        }
		  else {
				printf( "\033[1;32mOK\033[0m\n" );
		  }
    }
	 board* b = gamestart_board();
	 printf("From white's side:\n");
	 showboard( b, WHITE);
	 printf("\n");
	 printf("From black's side:\n");
	 showboard( b, BLACK);
}
