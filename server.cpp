/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <stdlib.h>
#include <strings.h>
#include <sys/wait.h>	/* for the waitpid() system call */
#include <signal.h>	/* signal name macros, and the kill() prototype */

#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>

#include "http_req.h"
#include "file_fetcher.h"
#include "http_res.h"


void error(std::string msg)
{
    perror(msg.c_str());
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, pid;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);	//create socket
     if (sockfd < 0) 
        error("ERROR opening socket");
     memset((char *) &serv_addr, 0, sizeof(serv_addr));	//reset memory
     //fill in address info
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
     listen(sockfd,5);	//5 simultaneous connection at most



    file_fetcher ff;
    HTTP_Res res;
    int counter = 0;
    while(true) {

         //accept connections
         newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
         
        if (newsockfd < 0) 
           error("ERROR on accept");
         
        int n;
   	    char buffer[512];
   			 
   	    memset(buffer, 0, 512);	//reset memory
      
 		 //read client's message
   	    n = read(newsockfd,buffer,511);
   	    if (n < 0) error("ERROR reading from socket");

        string stdstr = buffer;
        HTTP_Req req(stdstr);
        //printf("Message Begins:\n");
        //printf("%s\n",buffer);

        cout << " ----- ----- ----- " << endl;

        cout << "Request " << counter << endl;
        cout << "Parser Identified Fields:" << endl;
        cout << "Type:\t" << req.get_type() << endl;
        cout << "Path:\t" << req.get_path() << endl;
        cout << "Version\t" << req.get_version() << endl;
        cout << "User Agent:\t" << req.get_user_agent() << endl;
        cout << "Accepts HTML?\t" << (req.get_accept_html() ? "True" : "False") << endl;
        cout << "Language\t" << req.get_lang() << endl;
        cout << "Encoding\t" << req.get_encoding() << endl;
        cout << "Conn.\t" << req.get_connection() << endl;

        cout << " ----- ----- -----" << endl;

        //Form Response
        string msg_body;
        string status_code;
        string reason_phrase;
        string response;

        if( ff.exists( req.get_path() ) )
        {
            msg_body = ff.read(req.get_path());
            status_code = "202"; //accepted
            reason_phrase = "Accepted";
        }
        else
        {
            msg_body = "";
            status_code = "404";
            reason_phrase = "Not Found";
        }
        
        response = res.form_res_pkt(req.get_version(), status_code, 
                reason_phrase, msg_body, req.mime());

        //reply to client
   	    n = write(newsockfd, response.c_str(), response.length());
   	    if (n < 0) error("ERROR writing to socket");
         
        counter++;     
        close(newsockfd);//close connection 
    } 
    close(sockfd);
 
    return 0; 
}

