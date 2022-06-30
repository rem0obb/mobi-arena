#include "arena.hpp"
#include <stdexcept>

#if DEBUG
#include <fmt/core.h>
#endif

/**
 * if p_overwrite = true (default) Arena overwrite spaces alocated
 *
 * */
Arena::Arena(unsigned int p_size, unsigned int p_limit, bool p_overwrite) : m_size(p_size), 
                                                                            m_amount(m_size),
                                                                            m_limit(p_limit),
                                                                            m_overwrite(p_overwrite)
{
  m_mem = new char[m_size];
  m_head = m_mem;
#if DEBUG
  fmt::print("[{}][DEBUG]\n\t Creating Arena\n\t Arena Size: {}\n\t Free quantity Arena: {}\n\t", __FUNCTION__, m_size, m_amount);
#endif
}

Arena::Arena() : m_mem(nullptr),
                 m_size(0),
                 m_amount(0),
                 m_limit(0),
                 m_head(nullptr),
                 m_overwrite(0)
{
}

/*
 * avoid copy arena, greater than the heap, but it loses performance
 * */
Arena Arena::operator=(const Arena &fast)
{
  delete[] m_mem;

  m_mem = new char[fast.m_size];
  memcpy(m_mem, fast.m_mem, fast.m_size);
  m_size = fast.m_size;
  m_head = fast.m_head;
  m_amount = fast.m_amount;
  m_overwrite = fast.m_overwrite;
  m_limit = m_amount;

  return *this;
}

/*
 * avoid copy arena, greater than the heap, but it loses performance
 */
Arena::Arena(const Arena &fast)
{
  m_mem = new char[fast.m_size];
  memcpy(m_mem, fast.m_mem, fast.m_size);
  m_size = fast.m_size;
  m_head = fast.m_head;
  m_amount = fast.m_amount;
  m_overwrite = fast.m_overwrite;
  m_limit = m_amount;
}

Arena::~Arena()
{
  delete[] m_mem;
  m_mem = nullptr;
  m_head = m_mem;
}

/*
 * requestes block in arena passing desired size
 * */
void *Arena::req(unsigned int p_amount)
{
  if (p_amount <= m_amount)
  {
    if (p_amount < m_limit && m_overwrite && m_size > m_limit)
    {
#if DEBUG
      fmt::print("[{}][DEBUG]\n\t Dominating Arena\n\t Limit: {}\n\t Arena Size: {}\n\t", __FUNCTION__, m_limit, m_size);
#endif
      realloc(m_limit);
      goto new_block;
    }
    else
      goto new_block;
  }
  else if (p_amount > m_size)
  {
#if DEBUG
    fmt::print("[{}][DEBUG]\n\t Increasing arena\n\t Arena Size: {}\n\t Requested: {}\n\t", __FUNCTION__, m_size, p_amount);
#endif
    realloc(p_amount);
    goto new_block;
  }
  else
  {
    if (m_overwrite)
    {
      dell();
      goto new_block;
    }
    else
      throw std::runtime_error("Arena : Arena is full");
  }

new_block:
  char *block = const_cast<char*>(m_head);
  m_head += p_amount;
  m_amount -= p_amount;

#if DEBUG
  fmt::print("[{}][DEBUG]\n\t New Block\n\t Size: {}\n\t Free quantity Arena:\n\t", __FUNCTION__, p_amount, m_amount);
#endif

  return block;
}

/* (m_head)
 *   ↓
 * (m_mem) -> [   ][   ][   ][   ] ...
 * return pointer head for initial memory
 * */
void Arena::dell()
{
  m_head = m_mem;
  m_amount = m_size;
}

/*
 * Delete memory
 * */
void Arena::erase()
{
#if DEBUG
  fmt::print("\n[{}][DEBUG]\n\t Erase Arena\n\t Arena Size: {}\n\t Free quantity Arena:", __FUNCTION__, m_size, m_amount);
#endif
  delete[] m_mem;
  m_mem = nullptr;
  m_head = m_mem;
  m_size = 0;
  m_amount = m_size;
  m_overwrite = true;
}

/*
 * return amount free space in arena
 * */
unsigned int Arena::fquantity()
{
  return m_amount;
}

/*
 * ... [  ][  ][  ] <- [delete] - [alocate more] -> [  ][  ][  ][  ] +++
 * */
void Arena::realloc(unsigned int p_amount)
{
  if (m_mem != nullptr)
    delete[] m_mem;
  else if(p_amount == 0 || p_amount == m_size)
    return;

  m_mem = new char[p_amount];
  m_head = m_mem;
  m_size = p_amount;
  m_amount = m_size;
}