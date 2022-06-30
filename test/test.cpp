#include <gtest/gtest.h>
#include "src/include/arena.hpp"

#define req_char( length ) static_cast<char*>(m_fast->req(length));

class T_Arena : public testing::Test
{
public:
    Arena *m_fast;

    T_Arena() {}
    ~T_Arena() {}
};

TEST_F(T_Arena, Fast)
{
    const char length = sizeof(char);
    const unsigned int size = 4*length;

    m_fast = new Arena(size);

    EXPECT_EQ(size, m_fast->fquantity());

    // requests blocks
    char* t_one  = req_char(length);
    char* t_two  = req_char(length);
    char* t_tree = req_char(length);
    char* t_four = req_char(length);

    // usage blocks
    *t_one  = 0x4d; // M
    *t_two  = 0x4f; // O
    *t_tree = 0x42; // B
    *t_four = 0x49; // I

    EXPECT_EQ(0x4d, *t_one);
    EXPECT_EQ(0x4f, *t_two);
    EXPECT_EQ(0x42, *t_tree);
    EXPECT_EQ(0x49, *t_four);

    EXPECT_EQ(0, m_fast->fquantity());

    // overwrite 
    char* t_five =  req_char(length);
    char* t_six =  req_char(length);
    
    *t_five = 0x41; // A
    *t_six = 0x56; // V

    EXPECT_EQ(0x41, *t_one);
    EXPECT_EQ(0x56, *t_two);

    delete m_fast;
}

TEST_F(T_Arena, CopyFast)
{
    const char length = sizeof(char);
    const unsigned int size = 4*length;

    m_fast = new Arena(size);
    char *name = req_char(size);

    Arena fast2(*m_fast);
    char* name2 = static_cast<char*>(fast2.req(size));

    EXPECT_EQ(*name2, *name);  

    delete m_fast;
}