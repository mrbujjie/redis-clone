#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include<errno.h>

#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstdint>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<arpa/inet.h>


using namespace std ;

const size_t k_max_msg =4096 ;

static int32_t write_all(int fd , char *buf , ssize_t n){
	while(n>0){
		ssize_t rv = write(fd,buf,n);
		if(rv<=0){
			return -1 ;
			}
        assert((size_t)rv <= n);
	n-=(size_t)rv;
	buf+=rv;
	}return 0;
}

static int32_t read_full(int fd ,char *buf , size_t n){
	while(n>0){
		ssize_t rv = read(fd,buf,n);
		if(rv<=0){
			return -1;
			}
	assert((size_t)rv <=n);
	n-=(size_t)rv;
	buf+=rv;
	}
	return 0;
}


static int32_t multiple_tasks(int fd , const char* message){
	// sending message : 
	uint32_t wlen=0;
	
	//const char message[] = "hi server, it's new code with multiple requests from a single client";
	char wbuf[4+strlen(message)];
	wlen=(uint32_t)strlen(message);
	memcpy(wbuf,&wlen ,4);
	memcpy(&wbuf[4],message,wlen);
	int err= write_all(fd,wbuf,4+wlen);
	if(err<0){
		cerr<<"writing() error"<<endl;
		return err;
	}
	
	// read from server : 
	
	char rbuf[4+k_max_msg];
	errno =0 ;
	int rerr= read_full(fd ,rbuf,4);
	if(rerr){
		cout<<(errno==0 ? "EOF" : "read error ()")<<endl;
		return rerr;
	}
	uint32_t len =0 ;
	memcpy(&len , rbuf ,4); // assuming this is little endian
	if(len>k_max_msg){
		cout<<"message too long"<<endl;
		return -1;
	}
	rerr = read_full(fd,&rbuf[4],len);
	if(rerr<0){
		cout<<"read() error while reading body"<<endl;
		return rerr;
		}
	cerr<<"server says : "<< string(&rbuf[4],len)<<endl;
	
	return 0;
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
	int err =0 ;
	err = multiple_tasks(fd , "first message");
	if(err){
		goto L_DONE;
	}
	err=multiple_tasks(fd , "second message");
	if(err){
		goto L_DONE;
	}
	err=multiple_tasks(fd ,"third message");
	if(err){
		goto L_DONE;
	}
L_DONE:
	close(fd);
	return 0;
}

