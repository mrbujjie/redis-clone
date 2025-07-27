#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <thread>
using namespace std;

const size_t k_max_msg = 4096;

static void msg(const char *msg) {
    cerr << msg << endl;
}

static void die(const char *msg) {
    int err = errno;
    cerr << "[" << err << "] " << msg << endl;
    exit(1);
}

static int32_t read_full(int fd, char *buf, size_t n) {
    while (n > 0) {
        ssize_t rv = read(fd, buf, n);
        if (rv <= 0) {
            return -1;  // error or EOF
        }
        assert((size_t)rv <= n);
        n -= (size_t)rv;
        buf += rv;
    }
    return 0;
}

static int32_t write_all(int fd, const char *buf, size_t n) {
    while (n > 0) {
        ssize_t rv = write(fd, buf, n);
        if (rv <= 0) {
            return -1;  // error
        }
        assert((size_t)rv <= n);
        n -= (size_t)rv;
        buf += rv;
    }
    return 0;
}

static int32_t one_request(int connfd) {
    char rbuf[4 + k_max_msg];
    errno = 0;
    int32_t err = read_full(connfd, rbuf, 4);
    if (err) {
        msg(errno == 0 ? "EOF" : "read() error");
        return err;
    }

    uint32_t len = 0;
    memcpy(&len, rbuf, 4);  // assuming little-endian
    if (len > k_max_msg) {
        msg("message too long");
        return -1;
    }

    err = read_full(connfd, &rbuf[4], len);
    if (err) {
        msg("read() error while reading body");
        return err;
    }

    cerr << "client says: " << string(&rbuf[4], len) << endl;

    // Send reply
    const char reply[] = "Okay!!!No problem , we'll come up with a plan";
    char wbuf[4 + sizeof(reply)];
    len = (uint32_t)strlen(reply);
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], reply, len);
    return write_all(connfd, wbuf, 4 + len);
	close(connfd);
}

int main() {
    cerr << "Starting server..." << endl;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        die("socket()");
    }
    cerr << "Socket created." << endl;

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5467);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv != 0) {
        die("bind()");
    }
    cerr << "Bind successful." << endl;

    rv = listen(fd, SOMAXCONN);
    if (rv != 0) {
        die("listen()");
    }
    cerr << "Listening on port 5467..." << endl;

    while (true) {
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        cerr << "Waiting for connection..." << endl;
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            msg("accept() failed, continuing...");
            continue;
        }
        cerr << "Client connected." << endl;

       /* while (true) {
            int32_t err = one_request(connfd);
            if (err) {
                cerr << "Closing connection." << endl;
                break;
            }
        } */
		
		// Thread-based concurrency
		
		thread t(one_request,connfd);
		t.join();
		cout<<"Main thread continues after join"<<endl;
		
		
       // close(connfd);
    }

    return 0;
}

