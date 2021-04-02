#include "tools.h"
#include <random>
#include <ctime>
#include <unistd.h>
#include <dirent.h>
#include <ctime>

using std::istringstream;
using std::string;


int is_file_exists(const string &path)
{
    return !access(path.c_str(), F_OK);
}

int is_folder_exist(const string &path)
{
    DIR *dp;
    if ((dp = opendir(path.c_str())) == NULL)
    {
        return 0;
    }

    closedir(dp);
    return -1;
}
