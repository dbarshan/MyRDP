#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main(){
	
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if( sockfd < 0){
		std::cout << "Error: opening socket  " << sockfd << std::endl;
		return sockfd;
	}
	
	int port = 5000;
	
	struct sockaddr_in serv_addr;
	
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
	
	int ret = bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
	if(ret < 0){
		std::cout << "Error: on binding" << std::endl;
		return ret;
	}
	
	listen(sockfd,1);
	
	struct sockaddr cli_addr;
	int clilen = sizeof(cli_addr);
	int sockfd2 = accept(sockfd,(struct sockaddr *)&cli_addr, &clilen);
	if( sockfd2 < 0 ){
		std::cout << "Error: on accept " << sockfd2 << std::endl;
		return sockfd2;
	}
	std::cout << "Someone connected to port 5000. Sending message:" << std::endl;
	char buffer[1025];
	int i = 0;
	while(1){
		i++;
		memset(buffer, 0, sizeof(buffer));
		std::string s = std::to_string(i);
		strcpy(buffer,s.c_str());
		//std::cin.getline(buffer,sizeof(buffer));
		ret = write(sockfd2,buffer,strlen(buffer));
		if ( ret < 0 ){
			std::cout << "Error: can not read from socket " << ret << std::endl;
		}
		sleep(1);
	}	
	return 0;
}