#ifndef TCPSERVER_H
#define TCPSERVER_H

#pragma once

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class tcpServer
{
private:
    int serverSock_fd;
    int clientSock_fd;
    int portNum;
    bool clientState;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t clnt_addr_size;

public:
    tcpServer(int port);
    virtual ~tcpServer();
    bool getClientState();
    void setClientState(bool state);
    int getClientSocket();
    int getServerSocket();
    void creatSocket();
    int waitAccpet();
    int recvData(char *recvBuff, size_t size);
    int sendData(char *sendBuff, size_t size);
    void closeSocket(int socket);

};

#endif