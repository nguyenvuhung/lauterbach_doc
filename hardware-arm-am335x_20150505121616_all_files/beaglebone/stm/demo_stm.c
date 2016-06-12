
#define TRUE 1
#define FALSE 0
#define SIZE 18

const char cstr1[] = "Constant String1";

#define STM_BASE 0x4b000000

// Address space 0
#define STP_TRACE0_D8(   _channel_,_data_) {*((volatile unsigned char *)  (STM_BASE + 0x1000 * _channel_)) = _data_;}
#define STP_TRACE0_D8TS( _channel_,_data_) {*((volatile unsigned char *)  (STM_BASE + 0x1000 * _channel_ + 0x0800)) = _data_;}
#define STP_TRACE0_D16(  _channel_,_data_) {*((volatile unsigned short *) (STM_BASE + 0x1000 * _channel_)) = _data_;}
#define STP_TRACE0_D16TS(_channel_,_data_) {*((volatile unsigned short *) (STM_BASE + 0x1000 * _channel_ + 0x0800)) = _data_;}
#define STP_TRACE0_D32(  _channel_,_data_) {*((volatile unsigned int *)   (STM_BASE + 0x1000 * _channel_)) = _data_;}
#define STP_TRACE0_D32TS(_channel_,_data_) {*((volatile unsigned int *)   (STM_BASE + 0x1000 * _channel_ + 0x0800)) = _data_;}

// Address space 1
#define STP_TRACE1_D8(   _channel_,_data_) {*((volatile unsigned char *)  (STM_BASE + 0x0400 * _channel_)) = _data_;}
#define STP_TRACE1_D8TS( _channel_,_data_) {*((volatile unsigned char *)  (STM_BASE + 0x0400 * _channel_ + 0x0200)) = _data_;}
#define STP_TRACE1_D16(  _channel_,_data_) {*((volatile unsigned short *) (STM_BASE + 0x0400 * _channel_)) = _data_;}
#define STP_TRACE1_D16TS(_channel_,_data_) {*((volatile unsigned short *) (STM_BASE + 0x0400 * _channel_ + 0x0200)) = _data_;}
#define STP_TRACE1_D32(  _channel_,_data_) {*((volatile unsigned int *)   (STM_BASE + 0x0400 * _channel_)) = _data_;}
#define STP_TRACE1_D32TS(_channel_,_data_) {*((volatile unsigned int *)   (STM_BASE + 0x0400 * _channel_ + 0x0200)) = _data_;}


void wait(void)
{
	int i;
	for(i = 50000; i>0; i--);  /* wait to ensure that FiFo does not overflow */
}


char flags[SIZE+1];

int sieve(void)				/* sieve of erathostenes */
{
	register int i, prime, k;
	int count;

	count = 0;

	for ( i = 0 ; i <= SIZE ; flags[ i++ ] = TRUE ) ;

	for ( i = 0 ; i <= SIZE ; i++ )
	{
		if ( flags[ i ] )
		{
			prime = i + i + 3;
			k = i + prime;
			while ( k <= SIZE )
			{
				flags[ k ] = FALSE;
				k += prime;
			}
			count++;
			if (count % 4 == 0)
				wait();
			STP_TRACE0_D8(1, prime);
		}
	}

	return count;
}


int main(void)
{
	unsigned int i = 0;
	while ( TRUE )
	{
		STP_TRACE0_D8(0, 'H');
		STP_TRACE0_D8(0, 'e');
		STP_TRACE0_D8(0, 'l');
		STP_TRACE0_D8(0, 'l');
		wait();
		STP_TRACE0_D8(0, 'o');
		STP_TRACE0_D8(0, ' ');
		STP_TRACE0_D8(0, 'w');
		STP_TRACE0_D8(0, 'o');
		wait();
		STP_TRACE0_D8(0, 'r');
		STP_TRACE0_D8(0, 'l');
		STP_TRACE0_D8(0, 'd');
		STP_TRACE0_D8TS(0, '!');
		wait();

		sieve();
		wait();

		i++;
		if ((i % 7) == 0){
			STP_TRACE0_D32(2, i;);
			wait();
		}
	}
}


