

#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H



void cirBufReset (void);
unsigned int cirBufWrite (unsigned char* data, unsigned char len);
unsigned int cirBufRead (unsigned char* data, unsigned char len);
unsigned int cirBufGetSize(void);

unsigned char* cirBufGetDataPtr(void);

void prueba_buffer_circular();


#endif //_CIRCULAR_BUFFER_H

