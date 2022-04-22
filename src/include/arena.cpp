#include "arena.hpp"

#include <stdexcept>

Arena::Arena ( unsigned int p_size, bool p_overwrite ) : m_size ( p_size ),
  m_amount ( m_size ),
  m_overwrite ( p_overwrite )
{
  m_mem = new char[m_size];
  m_ptr = m_mem;
}

Arena Arena::operator= ( const Arena &fast )
{
  delete [] m_mem;

  m_mem = new char[fast.m_size];
  memcpy ( m_mem, fast.m_mem, fast.m_size );
  m_size = fast.m_size;
  m_ptr = fast.m_ptr;
  m_amount = fast.m_amount;
  return *this;
}

Arena::Arena ( const Arena &fast )
{
  m_mem = new char[fast.m_size];
  memcpy ( m_mem, fast.m_mem, fast.m_size );
  m_size = fast.m_size;
  m_ptr = fast.m_ptr;
  m_amount = fast.m_amount;
}

Arena::~Arena()
{
  delete [] m_mem;
  m_ptr = m_mem;
  m_mem = nullptr;
}

void *Arena::req ( unsigned int p_amount )
{
  char *block = nullptr;

  if ( p_amount <= m_amount )
  {
    block = ( char * ) m_ptr;
    m_ptr += p_amount;
    m_amount -= p_amount;
  }
  else if ( p_amount > m_size )
  {
    dell();
    mmem ( p_amount );
    block = ( char * ) m_ptr;
    m_ptr += p_amount;
    m_amount -= p_amount;
  }
  else
  {
    if ( m_overwrite )
    {
      dell();
      block = ( char * ) m_ptr;
      m_ptr += p_amount;
      m_amount -= p_amount;

    }
    else
      throw std::runtime_error ( "Arena full" );
  }

  return block;
}

void Arena::dell()
{
  m_ptr = m_mem;
  m_amount = m_size;
}

unsigned int Arena::afree()
{
  return m_amount;
}

void Arena::mmem ( unsigned int p_amount )
{
  if ( m_mem == nullptr )
    return;

  delete [] m_mem;
  m_mem = new char[p_amount];
  m_ptr = m_mem;
  m_size = p_amount;
  m_amount = m_size;
}
