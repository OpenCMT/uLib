#include <iostream>
#include "Test.h"


using namespace std;

void TestFilename::PrintName()
{
    cout << "Filename is: ";
    cout << ManageFilename::GetFileName(this->m_string) << "\n";
}

void TestFilename::PrintExtension()
{
    cout << "Fileexten is: ";
    cout << ManageFilename::GetFileExtension(this->m_string) << "\n";
}
