/******************************************************************************
	INCLUSIONES
******************************************************************************/

#include "circular_buffer.h"



/******************************************************************************
	VARIABLES GLOBALES
******************************************************************************/

#define BUFFER_SIZE 		64

static unsigned char buffer[BUFFER_SIZE];
static unsigned int WP;		// Write Pointer
static unsigned int RP;		// Read Pointer
static unsigned int SIZE;	// Tamaño ocupado en el buffer



/************************************************************************/

//Inicializacion buffer
void cirBufReset (void)
{
	WP = 0;
	RP = 0;
	SIZE = 0;
}

//Escribir datos en el buffer
unsigned int cirBufWrite (unsigned char* data, unsigned char len)
{
	unsigned int aux;
	
	if(!data) return 0;
	
	if(len > (BUFFER_SIZE-SIZE))
	{
		len = (BUFFER_SIZE-SIZE);
	}
	
	aux = len;
	
	while(aux--)
	{
		buffer[WP++] = *data++;
		if(WP >= BUFFER_SIZE) WP = 0;
	}
	
	SIZE += len;
	
	return len;
}

unsigned int cirBufRead (unsigned char* data, unsigned char len)
{
	unsigned int aux;
	
	if(!data) return 0;
	
	if(len > SIZE)
	{
		len = SIZE;
	}
	
	aux = len;
	
	while(aux--)
	{
		*data++ = buffer[RP++];
		if(RP >= BUFFER_SIZE) RP = 0;
	}
	
	SIZE -= len;
	
	return len;
}


unsigned int cirBufGetSize(void)
{
	return SIZE;
}

unsigned char* cirBufGetDataPtr(void)
{
	return &buffer [RP];
}



void prueba_buffer_circular()
{
	
	unsigned char test_data_in [] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	unsigned char test_data_out [20];
	
	cirBufReset();
	
	cirBufWrite(&test_data_in[0], 3);
	cirBufWrite(&test_data_in[3], 4);
	cirBufWrite(&test_data_in[7], 5);
	cirBufRead(&test_data_out[0], 10);  
	cirBufWrite(&test_data_in[12], 3);
	cirBufWrite(&test_data_in[15], 10);
	//cirBufRead(&test_data_in[0], sizeof(test_data_in));
	
	cirBufRead(&test_data_out[0], sizeof(test_data_out)/2);  
	cirBufRead(&test_data_out[sizeof(test_data_out)/2], sizeof(test_data_out)/2);
}


