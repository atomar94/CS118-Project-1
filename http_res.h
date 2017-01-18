//http_res.h

#ifndef HTTP_RES_H
#define HTTP_RES_H

#include <string>

using namespace std;

class HTTP_Res
{
    public:
        string form_header(string http_version, string status_code,
                          string reason_phrase, string content_type,
                          int content_len);
        string form_res_pkt(string http_version, string status_code,
                            string reason_phrase, string msg_body,
                            string content_type);


};

#endif

