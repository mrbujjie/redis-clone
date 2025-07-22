#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include<errno.h>

#include<iostream>
#include<cstdio>

#include<sys/socket.h>
#include<unistd.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std ;

void do_something(int fd){
  	char wbuff[]="theni la irunthu!...conncetion success";
	int wn=write(fd,wbuff,strlen(wbuff));
	if(wn<0){
		cerr<<"message was not sent successfull"<<endl;
	}
	
	
	char buff[1024]={};
    ssize_t n=read(fd,buff,sizeof(buff)-1);
	if(n<0){
		cerr<<"msg() error"<<endl;
	}
	cout<<"server says: "<<buff<<endl;
}
int main(){
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0){
		cerr<<"socket() creaton is failed"<<endl;
		abort();
	}
	cout<<"socket() was created"<<endl;

        struct sockaddr_in addr={};
	addr.sin_family=AF_INET;
	addr.sin_port=htons(5467);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	int rv=connect(fd,(const struct sockaddr*)&addr,sizeof(addr));
	if(rv<0){
		cerr<<"connction() failed"<<endl;
		abort();

	}
	do_something(fd);
	close(fd);
	return 0;
}
