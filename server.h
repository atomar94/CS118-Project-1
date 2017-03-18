//server.h

#include "string"
#include "utility"

using namespace std;

class Server
{
    public:
        //returns the http method as
        // <method-type> <path>
        pair<string, string> read_request();
        void send_response(string msg);

    private:
        int sockfd; 
        int newsockfd;
};

