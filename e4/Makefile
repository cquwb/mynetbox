all:
	cd test && g++ -std=c++11 t_server.cpp address.cpp socket.cpp acceptor.cpp connect.cpp pollLoop.cpp EventHandler.cpp TcpServer.cpp -o t_server && g++ -std=c++11 t_client.cpp address.cpp socket.cpp -o t_client
clean:
	cd test && rm t_server && rm t_client
    	
