#include "tcpServer.h"
#include <thread>
#include <unistd.h>
#include <queue>

std::queue<char> queBuff;

void threadFunc(tcpServer *echoServer)
{
    char recvBuff[BUFSIZ];
    int recvLen;
    while (echoServer->waitAccpet() > 0)
    {
        echoServer->setClientState(true);
        while ((recvLen = echoServer->recvData(recvBuff, sizeof(recvBuff))) > 0)
        {
            recvBuff[recvLen] = '\0';
            echoServer->sendData(recvBuff, recvLen);
            for (int i=0; i <recvLen; i++)
            {
                queBuff.push(recvBuff[i]);  // 추가
                printf("check1\n");
            }
            printf("received : %s\n", recvBuff);
        }
        echoServer->closeSocket(echoServer->getClientSocket());
        echoServer->setClientState(false);

        printf("close client socket\n");
    }
}

int main()
{
    int counter=0;
    char inBuff[BUFSIZ];
    tcpServer echoServer(5100);
    std::thread f1(threadFunc, &echoServer);  // 5: 매개변수(counter)

    while(1)
    {
        if (!queBuff.empty())
        {
            printf("%c", queBuff.front());  // 가장 앞 자료
            queBuff.pop();  // front queue 제거
            printf("check2\n");
        }

        sprintf(inBuff,"%d", counter++);
        echoServer.sendData(inBuff, strlen(inBuff));
        sleep(1);

        // if (echoServer.getClientSocket() >= 3)
        // {
        //     sprintf(inBuff, "%d", counter++);
        //     echoServer.sendData(inBuff, strlen(inBuff));
        //     printf("check3\n");
        // }
        // sleep(1);

        // memset(inBuff, 0, sizeof(inBuff));
        // fgets(inBuff, strlen(inBuff), stdin);
        // if (echoServer.getClientSocket() > 0)
        // {
        //     echoServer.sendData(inBuff, sizeof(inBuff));
        // }
    }
    f1.join();

    echoServer.closeSocket(echoServer.getClientSocket());   

    return 0;
}