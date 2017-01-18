#include "file_fetcher.h"
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iostream>

using namespace std;

bool file_fetcher::exists(string f)
{
    if( f == "/")
        f = "index.html";

    f = get_cwd() + f;

    ifstream ifs(f.c_str());
    bool retval = ifs.good();
    if(!retval)
        cout << f << " doesn't exist"<< endl;
    return ifs.good();
}

string file_fetcher::read(string f)
{
    if( f == "/" )
        f = "index.html";


    if( !exists(f) )
        return "404 not found";

    f = get_cwd() + f;
    ifstream ifs(f.c_str());
    stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

string file_fetcher::get_cwd()
{
    char buf[256];
    return string(getcwd(buf, 256));
}
