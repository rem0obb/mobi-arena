#include "arena.hpp"
#include <iostream>


Arena::Arena ( unsigned int p_size ) : m_size ( p_size ), m_amount ( m_size )
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
  jmp:
    block = ( char * ) m_ptr;
    m_ptr += p_amount;
    m_amount -= p_amount;
  }
  else
  {
    dell();
    mmem ( p_amount );
    goto jmp;
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
  m_amount = p_amount;
}
