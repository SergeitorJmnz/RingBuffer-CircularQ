//Prototipos de funciones
void Create_Ring_Buffer(BYTE* buffer, unsigned int buffer_size);//Los tipos de variable BYTE pueden ser de cualquier otro tipo. (unsigned char)
unsigned int Data_In(BYTE* data, unsigned int len);
unsigned int Data_Out(BYTE* outData, unsigned int len);//la variable len tambien puede ser unsigned char
unsigned int SkipData( unsigned int len );
unsigned int Free_Space();
unsigned int Buffered_Bytes();
void Update_State();

//Variables internas
unsigned char *m_load_ptr, *m_consume_ptr;
unsigned char *m_buff_end;
unsigned char *m_buff;
int m_max_load, m_max_consume, m_data_in_buffer;

//Funciones públicas
void Create_Ring_Buffer( BYTE* buffer, unsigned int buffer_size )
{
  m_buff = (unsigned char*)buffer;
  m_buff_end = m_buff + buffer_size;
  m_load_ptr = m_consume_ptr = m_buff;
  m_max_load = buffer_size;
  m_max_consume = m_data_in_buffer = 0;
  Update_State();
}

// Try to add data to the buffer. After the call,
// 'len' contains the amount of bytes actually copied.
unsigned int Data_In( BYTE* data, unsigned int len )
{
  if (len > (unsigned int)m_max_load){
    len = (unsigned int)m_max_load;
  }
  memcpy(m_load_ptr, data, len);
  m_load_ptr += len;
  m_data_in_buffer += len;
  Update_State();
  return len;
}

// Request 'len' bytes from the buffer. After the call,
// 'len' contains the amount of bytes actually copied.
unsigned int Data_Out( BYTE* outData, unsigned int len )
{
  if (len > (unsigned int)m_max_consume)
  {
    len = (unsigned int)m_max_consume;
  }
  memcpy(outData, m_consume_ptr, len);
  m_consume_ptr += len;
  m_data_in_buffer -= len;
  Update_State();
  return len;
}

// Tries to skip len bytes. After the call,
// 'len' contains the realized skip.
unsigned int SkipData( unsigned int len )
{
  int i;
  int skip;
  unsigned int requestedSkip = len;
  for (i=0; i<2; ++i) // This may wrap  so try it twice
  {
    skip = (int)len;
    if (skip > m_max_consume)
    {
      skip = m_max_consume;
    }
    m_consume_ptr += skip;
    m_data_in_buffer -= skip;
    len -= skip;
    Update_State();
  }
  len = requestedSkip - len;
  return len;
}

// The amount of data the buffer can currently receive on one Data_In() call.
unsigned int Free_Space()
{ 
  return (unsigned int)m_max_load;
}

// The total amount of data in the buffer. Note that it may not be continuous: you may need
// two successive calls to Get_Data() to get it all.
unsigned int Buffered_Bytes() 
{ 
  return (unsigned int)m_data_in_buffer; 
}

//Funciones privadas
void Update_State()
{
  if (m_consume_ptr == m_buff_end)	
  {
    m_consume_ptr = m_buff;
  }
  if (m_load_ptr == m_buff_end)		
  {
    m_load_ptr = m_buff;
  }
  
  if (m_load_ptr == m_consume_ptr)
  {
    if (m_data_in_buffer > 0)
    {
      m_max_load = 0;
      m_max_consume = m_buff_end - m_consume_ptr;
    }
    else
    {
      m_max_load = m_buff_end - m_load_ptr;
      m_max_consume = 0;
    }
  }
  else if (m_load_ptr > m_consume_ptr)
  {
    m_max_load = m_buff_end - m_load_ptr;
    m_max_consume = m_load_ptr - m_consume_ptr;
  }
  else
  {
    m_max_load = m_consume_ptr - m_load_ptr;
    m_max_consume = m_buff_end - m_consume_ptr;
  }
}