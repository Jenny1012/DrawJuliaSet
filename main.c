#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define FRAME_WIDTH		640
#define FRAME_HEIGHT	480

#define FRAME_BUFFER_DEVICE	"/dev/fb0"



/*************************************************************
 *  <<Julia set相關資料>>
 *  https://en.wikipedia.org/wiki/Julia_set
 *
 *  cX 為 Julia set數學式中複數 "c" 的實部
 *  cY 為 Julia set數學式中複數 "c" 的虛部
 *  調整cX(值域:-1.0~1.0)--->(實部) 與
 		cY(值域:0.0~1.0)--->(虛部) 可得到不同的圖形
 *
*************************************************************/


int main()
{
    char name1[12];
    char name2[12];
    char name3[12];
    char teamname[12];
    int sid[5];

	//RGB16
	int16_t frame[FRAME_HEIGHT][FRAME_WIDTH];

	int max_cX = -700;
	int min_cY = 270;

	int cY_step = -5;
	int cX = -700;	// x = -700~-700
	int cY;			// y = 400~270

	int fd;


	printf( "Function1: Name\n" );

	//Dummy Function. Please refer to the specification of Project 1.
	name(name1, name2, name3, teamname);

	printf( "Function2: ID\n" );

	//Dummy Function. Please refer to the specification of Project 1.
	id( sid );

	//Dummy printout. Please refer to the specification of Project 1.
	printf( "Main Function:\n" );
	printf( "*****Print All*****\n" );
	printf( "%s\n", teamname );
	printf( "%d  ", sid[0] );
	printf( "%s\n", name1 );
	printf( "%d  ", sid[1] );
	printf( "%s\n", name2 );
	printf( "%d  ", sid[2] );
	printf( "%s\n", name3 );
	printf( "ID Summation = %d\n", sid[3]);
	printf( "*****End Print*****\n" );

	printf( "\n***** Please enter p to draw Julia Set animation *****\n" );

	while(getchar()!='p') {}


	system( "clear" );


	fd = open( FRAME_BUFFER_DEVICE, (O_RDWR | O_SYNC) );

	if( fd<0 )
	{	printf( "Frame Buffer Device Open Error!!\n" );	}
	else
	{
		for( cY=400 ; cY>=min_cY; cY = cY + cY_step ) {

			drawJuliaSet( cX, cY, FRAME_WIDTH, FRAME_HEIGHT, frame );

			write( fd, frame, sizeof(int16_t)*FRAME_HEIGHT*FRAME_WIDTH );

			lseek( fd, 0, SEEK_SET );
		}


		//Dummy printout. Please refer to the specification of Project 1.

		printf( ".*.*.*.<:: Happy New Year ::>.*.*.*.\n" );
		printf( "by %s\n", teamname );
		printf( "%d  ", sid[0] );
        printf( "%s\n", name1 );
        printf( "%d  ", sid[1] );
        printf( "%s\n", name2 );
        printf( "%d  ", sid[2] );
        printf( "%s\n", name3 );

		close( fd );
	}


	while(getchar()!='p') {}

	return 0;
}
