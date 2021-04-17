#include "tools.h"
#include <unistd.h>

using std::string;


int is_file_exists(const string &path)
{
    return !access(path.c_str(), F_OK);
}


