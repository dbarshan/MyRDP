#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <error.h>


int main(){
	
	int port = 5000;
	
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if ( sockfd < 0 ){
		std::cout << "Error: opening socket " <<sockfd << std::endl;
		return sockfd;
	}
	
	struct hostent *server = gethostbyname("127.0.0.1");
	if( server == NULL ){
		std::cout << "Error: host not found" << std::endl;
		return -1;
	}
	
	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);
	int ret = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if ( ret < 0 ){
		std::cout << "Error "<< ret <<": Can not connect to socket " << std::endl;
		std::cout << errno << " " << strerror(errno) ;
		return ret;
	}
	
	char buffer[1025];
	std::cout << "Connection Established. Start receiving message:" << std::endl;
	while(1){
		memset(buffer, 0, sizeof(buffer));
		int n = read(sockfd,buffer,1024);
		if ( n < 0 ){
			std::cout << "Error: reading from socket "<< n <<  std::endl;
		}
		else{
			std::cout << buffer << std::endl;
		}
	}		
	return 0;
}