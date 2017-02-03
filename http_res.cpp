//http_res.cpp

#include <string>
#include <sstream>
#include "http_res.h"



using namespace std;


//because the mingw compiler doesnt have this function even though cpp does.
//this is a known bug
namespace patch
{
    string to_string(int i)
    {
        ostringstream s;
        s << i;
        return s.str();
    }

}

string HTTP_Res::form_header(string http_version, string status_code,
                             string reason_phrase, string content_type,
                             int content_len)
{
    bool valid = true;
    if(status_code == "404" || status_code == "403" || status_code == "415")
        valid = false; //error so the resp pkt is a bit different

    string retval;
    retval += http_version + " ";
    retval += status_code + " ";
    retval += reason_phrase + "\r\n";
    retval += "Connection: close\r\n";
    retval += "Date: Fri, 3 Feb 2017 01:01:01 GMT\r\n";
    retval += "Server: ACK-er Man (Ubuntu)\r\n";

    if(valid)
    {
        retval += "Content-Type: "+ content_type + "\r\n";
        retval += "Content-Length: " + patch::to_string(content_len) + "\r\n";
    }

    retval += "\r\n"; //end of header indicator
    return retval;
}

string HTTP_Res::form_res_pkt(string http_version, string status_code,
                              string reason_phrase, string msg_body,
                              string content_type)
{
    string header = form_header(http_version, status_code, 
            reason_phrase, content_type, msg_body.length());
   return header + msg_body; 

}


