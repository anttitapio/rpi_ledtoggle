#include <stdio.h>
#include <stdlib.h>



int main (void)
{
    const char* logPath = "/srv/http/cgi-bin/ledToggleCount.log";
    const char* IOPath = "/sys/class/gpio/gpio11/value";
    FILE* gpio;
    FILE* oldCountFile;
    FILE* newCountFile;
    char* state=malloc( sizeof( char ) );
    char* currentCount=malloc( sizeof( char ) );
    char* newCount = NULL;
    size_t n = 0;
    size_t i = 0;

    gpio  = fopen( IOPath, "w+" );
    oldCountFile = fopen( logPath, "r" );
    if (oldCountFile == NULL ) {
        printf("Log file not found\n");
        return EXIT_FAILURE;
    }
    while ( n=fread( &currentCount[i], 1, 1, oldCountFile )) {
        currentCount = realloc( currentCount, sizeof( currentCount)+1 );
        i++;
    }
    printf( "Read %d bytes, result was %s\n", i, currentCount);
    
    newCount = malloc( sizeof( currentCount ) );
    n = sprintf( newCount, "%d", atoi(currentCount)+1 );
    printf( "New count is %s\n", newCount );

    fclose( oldCountFile );
    newCountFile = fopen( logPath, "w");
    fwrite( newCount, 1, n, newCountFile );

    fread( state, 1, 1, gpio );
    if ( atoi( state ))
        fwrite( "0", 1, 1, gpio );
    else
        fwrite( "1", 1, 1, gpio );
    fclose( gpio );
    fclose( newCountFile );

    free( state );
    free( currentCount );

    return EXIT_SUCCESS;
}
