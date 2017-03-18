
server:
	g++ -g main.cpp server.cpp client.cpp http_req.cpp http_res.cpp -o mserver

client:
	g++ -g main.cpp server.cpp client.cpp http_req.cpp http_res.cpp -o mserver

all:
	server,	client

