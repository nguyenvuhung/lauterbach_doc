
#define TRUE 1
#define FALSE 0
#define SIZE 18

#include "MidiDemo.h"

static int mstatic1, mstatic2, mcount;
const char cstr1[] = "Constant String1";

char vdblarray[5][6];
char vtriplearray[2][3][4];

typedef struct struct1 {
	char * word;
	int count;
	struct struct1 * left;
	struct struct1 * right;
	int field1:2;
	unsigned field2:3;
} strtype1 ;

strtype1 ast;

struct abc
{
	int x;
	int y;
};

struct abc def;

static void func1( intptr )		/* static function */
int * intptr;
{
	(*intptr)++;
}

void func2()
{
	int autovar;
	register int regvar;
	static int fstatic = 44;	/* initialized static variable */
	static int fstatic2;		/* not initialized static variable */

	autovar = regvar = fstatic;
	autovar++;

	func1( &autovar );	/* to force autovar as stack-scope */

	func1( &fstatic );	/* to force fstatic as static-scope */

	for ( regvar = 0; regvar < 5 ; regvar++ )
		mstatic1 += regvar*autovar;

	fstatic += mstatic1;

	fstatic2 = 2*fstatic;

	func1( &fstatic2 );
}

static int * func9()			/* nested local variables */
{
	static stat1 = 0;
	register reg1;
	auto auto1;

	auto1 = stat1;

	for ( reg1 = 0 ; reg1 < 2 ; reg1++ )
	{
		static stat2 = 0;
		register reg2;
		auto auto2;

		auto2 = stat2;

		for ( reg2 = 0 ; reg2 < reg1 ; reg2++ )
		{
			func1( &stat1 );
			func1( &auto1 );
			func1( &stat2 );
			func1( &auto2 );
		}
	}

	return &stat1;
}

int int_sin(unsigned int x)
{
	int sign=1;
	if (x&0x20)
		sign=-1;
	x=x&0x1f;
	if ((x&0x10)&&(x&0xf))
		x=0x10-(x&0xf);

	// sin(x) -Pi/2 <= x <= Pi/2 = x-x^3/3!+x^5/5!-...
	return sign*((120*10*10*10*10*x - (20*10*10*x*x*x) + (x*x*x*x*x))>>9);
}

static short sinewave[630];

static void func_sin()
{
	int x;
	for (x = 0; x < 628; x++) 
		sinewave[x] = int_sin(x)/(x/32+1);
}

int func13( a, c, e )			/* arguments and locals stack-tracking */
int a, c, e;
{
	int b, d, f;

	b = a+c+e;
	f = b+a;
	d = f*b;

	if ( e > 0 )
		c += func13( b, f, e-1 );

	return c+e+d;
}

int sieve();

int main()
{
	func_sin();

	while(TRUE)
	{
		mstatic1 = 12;
		mstatic2 = 34;
		mcount++;

		vtriplearray[0][0][0] = 1;
		vtriplearray[1][0][0] = 2;
		vtriplearray[0][1][0] = 3;
		vtriplearray[0][0][1] = 4;
		
		func2();
		
		func9();
		
		func13( 1, 2, 3 );
		
		sieve();
	}
}

char flags[SIZE+1];

int sieve()				/* sieve of erathostenes */
{
        register int i, primz, k;
	int anzahl;

	anzahl = 0;

        for ( i = 0 ; i <= SIZE ; flags[ i++ ] = TRUE ) ;

        for ( i = 0 ; i <= SIZE ; i++ )
        {
                if ( flags[ i ] )
                {
                        primz = i + i + 3;
                        k = i + primz;
                        while ( k <= SIZE )
                        {
                                flags[ k ] = FALSE;
                                k += primz;
                        }
                        anzahl++;
                }
        }

	return anzahl;
}

int background()			/* job for background-demo */
{
	register long count1, count2;

	count1 = count2 = 0;

	while ( TRUE )
	{
		while ( ++count1 ) ;
		count2++;
	}

	return TRUE;
}
