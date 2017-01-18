//http_req.cpp

#include "http_req.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

HTTP_Req::HTTP_Req(std::string req)
{
    list<string> lines = split(req, '\n');

    list<string>::iterator it;
    int i = 0;
    for(it = lines.begin(); it != lines.end(); it++, i++)
    {
        switch(i)
        {
            case 0:
                if(parse_req_type(*it) == -1)
                    cout << "http_req: bad req type" << endl;
                break;
            case 1:
                if(parse_host(*it) == -1)
                    cout << "http_req: bad host" << endl;
                break;
            case 2:
                if( parse_user_agent(*it) == -1)
                    cout << "http_req: bad user agent" << endl;
                break;
            case 3:
                if( parse_accept(*it) == -1)
                    cout << "http_req: bad accepted types" << endl;
                break;
            case 4:
                if( parse_accept_lang(*it) == -1)
                    cout << "http_req: bad accepted language" << endl;
                break;
            case 5:
                if( parse_accept_encoding(*it) == -1)
                    cout << "http_req: bad encoding" << endl;
                break;
            case 6:
                if( parse_connection(*it) == -1)
                    cout << "http_req: bad connection" << endl;
                break;
            default:
                cout << "HTTP_Req found extra fields." << endl;
        } //switch
    }//for
} //ctor

/*
 *  Ret -1 on fail else 0
 * */
int HTTP_Req::parse_req_type(string h)
{
    list<string> fields = split(h, ' ');
    if(fields.size() != 3) //GET-or-POST, path, http-type
    {
        //cout << "Bad header size" << endl;
        return -1;
    }
    int i = 0;
    for(list<string>::iterator it = fields.begin(); it != fields.end(); it++, i++)
    {
        switch(i)
        {
            case 0: if( *it == "GET" || *it == "POST")
                        req_type = *it;
                    else
                    {
                        cout << "Invalid request type. Got: " << *it << endl; 
                        req_type = "invalid";
                    }
                    break;
            case 1: path = *it;
                    break;
            case 2: version = *it;
                    break;
        }
    }
    return 0;
}

//return -1 on fail
int HTTP_Req::parse_host(string s)
{
    string host_tag = s.substr(0, 6);
    if(host_tag != "Host: ")
        return -1;

    int host_field_length = s.length() - 6;
    host = s.substr(6, host_field_length);
    return 0;

}

int HTTP_Req::parse_user_agent(string s)
{
    int taglen = 12;
    string ua_tag = s.substr(0, taglen);
    if(ua_tag != "User-Agent: ")
        return -1;

    int ua_field_length = s.length() - taglen;
    user_agent = s.substr(taglen, ua_field_length);
    return 0;

}

int HTTP_Req::parse_accept(string s)
{
    accept_html = false;
    int taglen = 8;
    string accept_tag = s.substr(0, taglen);
    if(accept_tag != "Accept: ")
        return -1;
    
    if( s.find("text/html") != string::npos )
        accept_html = true;

    return 0;
}


int HTTP_Req::parse_accept_lang(string s)
{
    int taglen = 17;
    string lang_tag = s.substr(0, taglen);
    if(lang_tag != "Accept-Language: ")
        return -1;

    int lang_field_length = s.length() - taglen;
    accepted_lang = s.substr(taglen, lang_field_length);
    return 0;


}

int HTTP_Req::parse_accept_encoding(string s)
{
    int taglen = 17;
    string enc_tag = s.substr(0, taglen);
    if(enc_tag != "Accept-Encoding: ")
        return -1;

    int enc_field_length = s.length() - taglen;
    accepted_encoding = s.substr(taglen, enc_field_length);
    return 0;


}
int HTTP_Req::parse_connection(string s)
{
    int taglen = 12;
    string conn_tag = s.substr(0, taglen);
    if(conn_tag != "Connection: ")
        return -1;

    int conn_field_length = s.length() - taglen;
    connection = s.substr(taglen, conn_field_length);
    return 0;


}

//getters
string HTTP_Req::get_type()
{
    return req_type;
}

string HTTP_Req::get_path()
{
    return path;
}

string HTTP_Req::get_version()
{ return version; }

string HTTP_Req::get_host()
{ return host; }

string HTTP_Req::get_user_agent()
{ return user_agent; }

bool HTTP_Req::get_accept_html()
{ return accept_html; }

string HTTP_Req::get_lang()
{ return accepted_lang; }

string HTTP_Req::get_encoding()
{ return accepted_encoding; }

string HTTP_Req::get_connection()
{ return connection; }

//note that delim is a char, not a char string, not a std::string
std::list<string> HTTP_Req::split(string str, char delim)
{
    std::stringstream ss;
    ss.str(str);
    std::string token;
    std::list<string> l;
    while(std::getline(ss, token, delim))
    {
        l.push_back(token);
    }
    return l;
}
