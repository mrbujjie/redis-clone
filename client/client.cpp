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
#include<vector>


using namespace std ;

static void msg(const char *msg){
	fprintf(stderr,"%s\n",msg);
}

const size_t k_max_msg = 32 << 20 ; // larger than the kernel buffer

static int32_t write_all(int fd , char *buf , ssize_t n){
	while(n>0){
		ssize_t rv = write(fd,buf,n);
		if(rv<=0){
			return -1 ;
			}
        assert((size_t)rv <= n);
	n-=(size_t)rv;
	buf+=rv;
	}
	return 0;
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

// append to the back 

static void buf_append(vector<uint8_t> &buf, const uint8_t *data, size_t len){
	buf.insert(buf.end(),data,data+len);
}

// the previous multiple task or query func was splited into 'send_req' and 'read_res'.

static int32_t send_req(int fd , const uint8_t * text,size_t len){
	if(len>k_max_msg){
		return -1 ;
	}
	
	vector<uint8_t> wbuf;
	buf_append(wbuf,(const uint8_t *)&len,4);
	buf_append(wbuf,text,len);
	return write_all(fd,reinterpret_cast<char*>(wbuf.data()),wbuf.size());
}

static  int32_t read_res(int fd){
	// 4 bytes header
	vector<uint8_t> rbuf;
	rbuf.resize(4);
	errno = 0;
	int32_t err = read_full(fd,reinterpret_cast<char*>(&rbuf[0]),4);
	if(err){
		if(errno==0){
			msg("EOF");
		}else{
			msg("read() error");
			
		}return err;
	}
	
	uint32_t len=0;
	memcpy(&len, rbuf.data(),4);
	if(len>k_max_msg){
		msg("too long");
		return -1;
	}
	
	// reply body 
	rbuf.resize(4+len);
	err=read_full(fd,reinterpret_cast<char*>(&rbuf[4]),len);
	if(err){
		msg("read() error");
		return err;
	}
	// do something
	
	printf("len : %u data : %.s\n",len,len<100?len:100,reinterpret_cast<char*>(&rbuf[4]));
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
	addr.sin_port=htons(1740);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	int rv=connect(fd,(const struct sockaddr*)&addr,sizeof(addr));
	if(rv<0){
		cerr<<"connction() failed"<<endl;
		abort();

	}
	// multiple pipeliened requests 
	
	vector<string> query_list={"hey there 1" , "hey there 2", "hey there 3",
	// large msg requiress multiple loop events
	string(k_max_msg,'z'),"hey there 5",};
	
	for(const string &s : query_list){
		int32_t err =send_req(fd,(uint8_t*)s.data(),s.size());
		if(err){
			goto L_DONE;
		}
	}
	for(size_t i=0; i<query_list.size();++i){
		int32_t err = read_res(fd);
		if(err){
			goto L_DONE;
		}
	}
	
L_DONE:
	close(fd);
	return 0;
}
