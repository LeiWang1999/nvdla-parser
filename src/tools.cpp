#include "tools.h"
#include <random>
#include <ctime>
#include <unistd.h>
#include <dirent.h>
#include <ctime>

using std::istringstream;
using std::string;

std::string get_random_name()
{
    const std::string char_set = "0a1b2c3d4e5f6g7h_8i9jAkBlCmDnEoFpGqHrI~sJtKuLvMwNxOyPzQ9R8S7T6U5V4W3X2Y1Z0";
    std::random_device random_generator;
    std::default_random_engine random_engine(random_generator());
    std::uniform_int_distribution<> uni_int_dist(0, char_set.size() - 1);

    int string_lens = (uni_int_dist(random_engine) + 12) / 3; // length [4, 32]
    std::string result;
    result.resize(string_lens);
    for (auto &x : result)
        x = char_set[uni_int_dist(random_engine)];

    return result;
}

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
