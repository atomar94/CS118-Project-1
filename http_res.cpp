//http_res.cpp

#include <string>
#include "http_res.h"

using namespace std;

string HTTP_Res::form_header(string http_version, string status_code,
                             string reason_phrase)
{
    string retval;
    retval += http_version + " ";
    retval += status_code + " ";
    retval += reason_phrase + "\r\n";
    return retval;
}

string HTTP_Res::form_res_pkt(string http_version, string status_code,
                              string reason_phrase, string msg_body)
{
    string header = form_header(http_version, status_code, reason_phrase);
   return header + "\r\n" + msg_body; 

}


