#include <stdio.h>
#include <string.h>
#include "../chess.c"

char* showpos( char* s, position p ){
    sprintf( s, "%c%u", fileof(p) + 'a', rankof(p) + 1 );
    return s;
}

int main(){
    char pos[3];
    char* strings[] = {
        "h8"
    };
    char positions[] = { 
        0x3f
    };
    for( int i = 0; i < sizeof( strings ) + 1; i++ ){
        if( 0 != strncmp( strings[i], showpos( pos, positions[i]) , 2) ){
            printf("\033[41mError!\033[0m 0x%02x should have equaled %s", 
                positions+i,
                strings[i]
            );
        }
    }

}
