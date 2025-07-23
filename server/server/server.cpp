#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<errno.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<cstdio>
#include<sys/socket.h>
#include<netinet/in.h>


static void die(const char *msg){
	int err=errno;
	fprintf(stderr,"[%d] %s\n" , err,msg);
	abort();
}
static void msg(const char *msg){
	fprintf(stderr,"%s\n",msg);
}
 
static void do_something(int connfd){
	char buff[1024]={};
	ssize_t n = read(connfd , buff ,sizeof(buff) - 1);
	if(n<0){
		msg("read() error");
		return ;
	}
	std::cerr << "client says: " << buff << std::endl;
	/* 
	or
	fprintf(stderr, "client says: %s\n", rbuf); */

	char wbuf[]="Ok,da...";
	//write(connfd,wbuf,strlen(wbuf));
    ssize_t written = write(connfd, wbuf, strlen(wbuf));
	if (written < 0) {
		 perror("write");
	}


}
	int main(){
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0){
		die("socket()");
	}
	std::cout<<"socket() was created"<<std::endl;
	// This needed for most server applications

	int val=1;
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val)); // reuse socket addr

	// Bind
	struct sockaddr_in addr{}; // creates a structure for addr & port we want to bind
	addr.sin_family=AF_INET; // address family for IPV4
	addr.sin_port=htons(5467); // 16 bit network byte order to local host
	addr.sin_addr.s_addr=htonl(0); //IP address 32 bits
	int rv = bind(fd,(const struct sockaddr *)&addr ,sizeof(addr));
	if(rv<0){
		die("bind()");
	}
        std::cout<<"bind() was successfull"<<std::endl;
	
	//listen
	rv=listen(fd,SOMAXCONN);

	if(rv<0){
		die("listen()");
	}
        std::cout<<"waiting for connection"<<std::endl;
        
	while(true){
	// accept
		struct sockaddr_in client_addr={};
		socklen_t addrlen = sizeof(client_addr);
		int connfd=accept(fd,(struct sockaddr*)&client_addr,&addrlen);
		if(connfd<0){
			continue;
		}
	std::cout<<"connection was successfull"<<std::endl;
	do_something(connfd);
	close(connfd);
	}
	return 0 ;
	}
