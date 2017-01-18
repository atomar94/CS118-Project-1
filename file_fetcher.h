//file_fetcher.h
//
#ifndef FILEFETCHER_H
#define FILEFETCHER_H

#include <string>

using namespace std;


//a stateless (slow and simple) file interface
class file_fetcher
{
    public:
        bool exists(string f);
        string read(string f);
        bool valid_type(string f);
    
    private:
        string get_cwd();        
};

#endif
