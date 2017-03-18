#include "server.h"
#include "client.h"

#include <utility>
#include <string>

using namespace std;

int main()
{
    Server s;
    Client c;

    pair<string, string> retval = s.read_request(8000);

    string method = retval.first;
    string path = retval.second;
    
}
