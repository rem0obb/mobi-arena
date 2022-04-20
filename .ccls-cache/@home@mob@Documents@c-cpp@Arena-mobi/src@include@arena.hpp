#pragma once

#include <unistd.h>
#include <string.h>

class Arena
{
 private:
  char *m_mem;
  unsigned int m_size;
  unsigned int m_amount;
  const char* m_ptr;

 public:
  ~Arena();
  Arena ( unsigned int = sysconf(_SC_PAGESIZE) );
  Arena(const Arena& fast);  
  Arena operator=(const Arena &fast);

  void mmem(unsigned int );
  void *req ( unsigned int );
  void dell();
  //void remove ( void *p_mem );
  unsigned int afree();
  

};
