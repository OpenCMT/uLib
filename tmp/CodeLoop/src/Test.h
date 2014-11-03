#ifndef TEST_H
#define TEST_H

#include <string>

#include "ManageFilename.h"

class TestFilename {

public:
    TestFilename( const char *str)
        : m_string(str)
    {}

    void PrintName();

    void PrintExtension();


    std::string m_string;
};


#endif // TEST_H
