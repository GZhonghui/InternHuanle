#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>

#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "GameMessage.pb.h"

#define IMPORT_USER
#include "User.h"

int fd[4];

uint8_t Buffer[4][40960];

uint32_t Size[4];
uint32_t MessageType[4];
uint32_t MessageLen[4];

uint32_t NowPlayerID = 0;
uint32_t PlayerID[4];

struct epoll_event event;
struct epoll_event wait_events[16];

inline void Init()
{
    InitUserInfo();

    memset(fd, -1, sizeof(fd));

    memset(Size, 0, sizeof(Size));
    memset(MessageType, 0, sizeof(MessageType));
    memset(MessageLen, 0, sizeof(MessageLen));

    memset(PlayerID, 0, sizeof(PlayerID));

    puts("Init Done");
}

inline void SendAll(int i, uint32_t SumLen)
{
    if(fd[1] >= 0)
    {
        auto SendLen = send(fd[1], Buffer[i], SumLen, 0);
    }
    if(fd[2] >= 0)
    {
        auto SendLen = send(fd[2], Buffer[i], SumLen, 0);
    }
}

inline void ProcessEvent(int i)
{
    switch(MessageType[i])
    {
    case 1:
    {
        PLoginRequest LoginRequest;
        LoginRequest.ParseFromArray(Buffer[i], Size[i]);

        if(UserLoginInfo.count(LoginRequest.username()) &&
            UserLoginInfo[LoginRequest.username()] == LoginRequest.password())
        {
            ++NowPlayerID;
            PlayerID[i] = NowPlayerID;

            PLoginRespond LoginRespond;
            LoginRespond.set_allowlogin(1);
            LoginRespond.set_playernumber(1); // HARD CODE
            LoginRespond.set_selfid(NowPlayerID);
                                    
            uint32_t SingleMessageType = 2;
            uint32_t SingleMessageLen = LoginRespond.ByteSizeLong();

            memcpy(Buffer[i] + 0, &SingleMessageType, 4);
            memcpy(Buffer[i] + 4, &SingleMessageLen, 4);
            LoginRespond.SerializeToArray(Buffer[i] + 8, SingleMessageLen);
            uint32_t sendLen = send(fd[i], Buffer[i], SingleMessageLen + 8, 0); // DANGER

            printf("New Client (%d)\n", NowPlayerID);

            PGameBegin GameBegin;
            GameBegin.set_selfid(1); // HARD CODE

            SingleMessageType = 9;
            SingleMessageLen = GameBegin.ByteSizeLong();

            memcpy(Buffer[i] + 0, &SingleMessageType, 4);
            memcpy(Buffer[i] + 4, &SingleMessageLen, 4);
            GameBegin.SerializeToArray(Buffer[i] + 8, SingleMessageLen);

            if(NowPlayerID >= 2) // HARD CODE
            {
                SendAll(i, SingleMessageLen + 8);
            }

        }
        else
        {
            PLoginRespond LoginRespond;
            LoginRespond.set_allowlogin(0);
            LoginRespond.set_playernumber(1); // HARD CODE
            LoginRespond.set_selfid(1); // HARD CODE
                                    
            uint32_t SingleMessageType = 2;
            uint32_t SingleMessageLen = LoginRespond.ByteSizeLong();

            memcpy(Buffer[i] + 0, &SingleMessageType, 4);
            memcpy(Buffer[i] + 4, &SingleMessageLen, 4);
            LoginRespond.SerializeToArray(Buffer[i] + 8, SingleMessageLen);
            uint32_t sendLen = send(fd[i], Buffer[i], SingleMessageLen + 8, 0); // DANGER
        }
    }break;

    case 3:
    {
        PActionRequest ActionRequest;
        ActionRequest.ParseFromArray(Buffer[i], Size[i]);

        uint32_t ActionPlayerID = PlayerID[i]; // DANGER

        PPlayerAction PlayerAction;
        PlayerAction.set_playerid(ActionPlayerID);
        PlayerAction.set_actiontype(ActionRequest.actiontype());

        uint32_t SingleMessageType = 4;
        uint32_t SingleMessageLen = PlayerAction.ByteSizeLong();

        memcpy(Buffer[i] + 0, &SingleMessageType, 4);
        memcpy(Buffer[i] + 4, &SingleMessageLen, 4);
        PlayerAction.SerializeToArray(Buffer[i] + 8, SingleMessageLen);

        SendAll(i, SingleMessageLen + 8);

        // uint32_t sendLen = send(fd[i], Buffer[i], SingleMessageLen + 8, 0); // DANGER
    }break;

    case 5:
    {
        PMoveRequest MoveRequest;
        MoveRequest.ParseFromArray(Buffer[i], Size[i]);

        uint32_t MovePlayerID = PlayerID[i];

        PPlayerMove PlayerMove;
        PlayerMove.set_playerid(MovePlayerID);
        PlayerMove.set_movetype(MoveRequest.movetype());
        PlayerMove.set_movevalue(MoveRequest.movevalue());

        uint32_t SingleMessageType = 6;
        uint32_t SingleMessageLen = PlayerMove.ByteSizeLong();

        memcpy(Buffer[i] + 0, &SingleMessageType, 4);
        memcpy(Buffer[i] + 4, &SingleMessageLen, 4);
        PlayerMove.SerializeToArray(Buffer[i] + 8, SingleMessageLen);
        
        SendAll(i, SingleMessageLen + 8);

        // uint32_t sendLen = send(fd[i], Buffer[i], SingleMessageLen + 8, 0); // DANGER
    }break;

    case 7:
    {
        PTurnRequest TurnRequest;
        TurnRequest.ParseFromArray(Buffer[i], Size[i]);

        uint32_t TurnPlayerID = PlayerID[i];

        PPlayerTurn PlayerTurn;
        PlayerTurn.set_playerid(TurnPlayerID);
        PlayerTurn.set_turntype(TurnRequest.turntype());
        PlayerTurn.set_turnvalue(TurnRequest.turnvalue());

        uint32_t SingleMessageType = 8;
        uint32_t SingleMessageLen = PlayerTurn.ByteSizeLong();

        memcpy(Buffer[i] + 0, &SingleMessageType, 4);
        memcpy(Buffer[i] + 4, &SingleMessageLen, 4);
        PlayerTurn.SerializeToArray(Buffer[i] + 8, SingleMessageLen);

        SendAll(i, SingleMessageLen + 8);

        // uint32_t sendLen = send(fd[i], Buffer[i], SingleMessageLen + 8, 0); // DANGER
    }break;
    }
}

inline void Recv(int i, const epoll_event& wait_event)
{
    if(fd[i] < 0) return;

    if((fd[i] == wait_event.data.fd) && (EPOLLIN == wait_event.events & EPOLLIN))
    {
        int len = 0;

        if(!MessageType[i])
        {
            len = recv(fd[i], Buffer[i]+Size[i], 4-Size[i], 0);
            Size[i] += len;
            if(Size[i] >= 4)
            {
                memcpy(&MessageType[i], Buffer[i], 4);
                Size[i] = 0;
            }
        }else if(!MessageLen[i])
        {
            len = recv(fd[i], Buffer[i]+Size[i], 4-Size[i], 0);
            Size[i] += len;
            if(Size[i] >= 4)
            {
                memcpy(&MessageLen[i], Buffer[i], 4);
                Size[i] = 0;
            }
        }else
        {
            len = recv(fd[i], Buffer[i]+Size[i], MessageLen[i]-Size[i], 0);
            Size[i] += len;
            if(Size[i] >= MessageLen[i])
            {
                ProcessEvent(i);

                MessageType[i] = 0;
                MessageLen[i] = 0;

                Size[i] = 0;
            }
        }
    }
}

int main()
{
    Init();

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(3002);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

    listen(sockfd, 10);

    fd[0] = sockfd;

    int epfd = epoll_create(10);
    if(-1 == epfd)
    {
        puts("error in creating epfd");
        return -1;
    }

    event.data.fd = sockfd;
    event.events = EPOLLIN;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);

    if(-1 == ret)
    {
        puts("error in adding server");
        return -1;
    }

    while(true)
    {
        ret = epoll_wait(epfd, wait_events, 3, -1);

        for(int i=0; i<ret; i+=1)
        {
            const epoll_event& wait_event = wait_events[i];

            if((sockfd == wait_event.data.fd) && (EPOLLIN == wait_event.events & EPOLLIN))
            {
                struct sockaddr_in cli_addr;
                unsigned int clilen = sizeof(cli_addr);

                int connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

                fd[fd[1] < 0 ? 1 : 2] = connfd;

                event.data.fd = connfd;
                event.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
            }
            Recv(1, wait_event);
            Recv(2, wait_event);
        }
    }

    return 0;
}