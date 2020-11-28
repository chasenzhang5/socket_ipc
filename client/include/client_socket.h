#ifndef _AUTO_SOCKET_H_
#define _AUTO_SOCKET_H_

#include <stdio.h>
#include <iostream>
#include <thread>

#include "pkg_define.h"
#include "mem_pool.h"

using namespace std;

#define BLOCK_SIZE 1024 * 40  //40K

class IpcClientBase
{
public:
    IpcClientBase();
    virtual ~IpcClientBase();

    int connectServer(string ip = "127.0.0.1", int port = 10500);
    int disConnect();

    int send(PkgHeader *header, const char *data, int len);
    virtual int onRecv(char *data, int len) = 0;

private:
    static int recvLoop(IpcClientBase *pthis);

    string m_ip;
    int m_port;
    int m_sockfd;
    int m_efd_thread;
    bool is_running_thread;

    thread thread_recv;
    MemPool m_mem_pool;
};

#endif
