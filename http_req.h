//http_req.h
//

#include <string>
#include <list>

using namespace std;

class HTTP_Req
{
    public:
        HTTP_Req(std::string request);

        string get_type(); //get or post
        string get_path(); //what page
        string get_version(); //http1.1, 1.0, etc.
        string get_host();
        string get_user_agent();
        bool get_accept_html();
        string get_lang();
        string get_encoding();
        string get_connection();


    private:

        string req_type;
        string path;
        string version;
        string host;
        string user_agent;

        bool accept_html;

        string accepted_lang;
        string accepted_encoding;
        string connection;


        std::list<string> split(string str, char delim);

        int parse_req_type(string h);
        int parse_host(string s);
        int parse_user_agent(string s);
        int parse_accept(string s);
        int parse_accept_lang(string s);
        int parse_accept_encoding(string s);
        int parse_connection(string s);

};
