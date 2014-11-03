#ifndef MANAGEFILENAME_H
#define MANAGEFILENAME_H

#include <string>
#include <iostream>



class ManageFilename {

public:
    static std::string GetFileExtension(const std::string& FileName);

    static std::string GetFileName(const std::string& FileName);


};






#endif // MANAGEFILENAME_H
