// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <queue>

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Character.h"

#include "Sockets.h"
#include "IPAddress.h"
#include "SocketTypes.h"
#include "SocketSubsystem.h"

#include "GameMessage.pb.h"

#include "ClientGameInstance.generated.h"

#define GI Cast<UClientGameInstance>(GetGameInstance())

inline void Print(const FString& Content)
{
	if (GEngine)
	{
		GEngine -> AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *Content);
	}
}

class SingleMessageData
{
public:
	uint32_t MessageType;
	uint32_t MessageLen;
	
	TArray<uint8_t> Buffer;
};

class NetworkSendThread : public FRunnable
{
public:
    NetworkSendThread() = default;
	NetworkSendThread(FSocket* Server) : Server(Server) {}
	virtual ~NetworkSendThread() = default;

private:
    FSocket* Server;

    std::queue<SingleMessageData> WillSend;
    FCriticalSection QueueMutex;

protected:
    FCriticalSection stop_mutex;
    bool _should_stop;
    bool ShouldStop(bool flag = false)
    {
        FScopeLock Lock(&stop_mutex);

        if (flag) _should_stop = true;
        return _should_stop;
    }

public:
    virtual uint32 Run() override
    {
        uint8_t Buffer[40960]; // DANGER
        uint32_t Index = 0, Size = 0;

        while (true)
        {
            if (!ShouldStop())
            {
                if (!Server) break;

                if (Size)
                {
                    int Sended;
                    Server->Send(Buffer + Index, Size - Index, Sended);
                    Index += Sended;
                    if (Index >= Size)
                    {
                        Index = Size = 0;
                    }
                }
                else
                {
                    FScopeLock Lock(&QueueMutex);

                    if (!WillSend.empty())
                    {
                        const SingleMessageData& Message = WillSend.front();
                        memcpy(Buffer + 0, &Message.MessageType, 4);
                        memcpy(Buffer + 4, &Message.MessageLen, 4);
                        memcpy(Buffer + 8, Message.Buffer.GetData(), Message.MessageLen);
                        
                        Index = 0;
                        Size = 8 + Message.MessageLen;

                        WillSend.pop();
                    }
                }
            }
            else break;
        }
        return (uint32)0;
    }

    virtual bool Init() override
    {
        _should_stop = false;
        return true;
    }

    virtual void Stop() override
    {
        ShouldStop(true);
    }

    virtual void Exit() override
    {

    }

public:
    void AddMessage(const SingleMessageData& Message)
    {
        FScopeLock Lock(&QueueMutex);

        WillSend.push(Message);
    }
};

class NetworkRecvThread : public FRunnable
{
public:
    NetworkRecvThread() = default;
    NetworkRecvThread(FSocket* Server) : Server(Server) {}
	virtual ~NetworkRecvThread() = default;

private:
    FSocket* Server;

    std::queue<SingleMessageData> HaveRecved;
    FCriticalSection QueueMutex;

protected:
    FCriticalSection stop_mutex;
    bool _should_stop;
    bool ShouldStop(bool flag = false)
    {
        FScopeLock Lock(&stop_mutex);

        if (flag) _should_stop = true;
        return _should_stop;
    }

public:
    virtual uint32 Run() override
    {
        uint8_t Buffer[40960]; // DANGER
        uint32_t Size = 0;

        uint32_t MessageType = 0, MessageLen = 0;

        while (true)
        {
            if (!ShouldStop())
            {
                if (!Server) break;

                if (!MessageType)
                {
                    int Readed;
                    Server->Recv(Buffer + Size, 4 - Size, Readed);
                    Size += Readed;
                    if (Size >= 4)
                    {
                        memcpy(&MessageType, Buffer, 4);
                        Size = 0;
                    }
                }
                else if (!MessageLen)
                {
                    int Readed;
                    Server->Recv(Buffer + Size, 4 - Size, Readed);
                    Size += Readed;
                    if (Size >= 4)
                    {
                        memcpy(&MessageLen, Buffer, 4);
                        Size = 0;
                    }
                }
                else
                {
                    int Readed;
                    Server->Recv(Buffer + Size, MessageLen - Size, Readed);
                    Size += Readed;
                    if (Size >= MessageLen)
                    {
                        SingleMessageData ComplateMessage;
                        ComplateMessage.MessageType = MessageType;
                        ComplateMessage.MessageLen = MessageLen;
                        ComplateMessage.Buffer.SetNum(MessageLen);
                        memcpy(ComplateMessage.Buffer.GetData(), Buffer, MessageLen);

                        {
                            FScopeLock Lock(&QueueMutex);
                            HaveRecved.push(ComplateMessage);
                        }

                        MessageType = 0;
                        MessageLen = 0;

                        Size = 0;
                    }
                }
            }
            else break;
        }
        return (uint32)0;
    }

    virtual bool Init() override
    {
        _should_stop = false;
        return true;
    }

    virtual void Stop() override
    {
        ShouldStop(true);
    }

    virtual void Exit() override
    {

    }

public:
    SingleMessageData NextMessage()
    {
        FScopeLock Lock(&QueueMutex);

        if (HaveRecved.empty())
        {
            SingleMessageData Empty;
            Empty.MessageType = 0;
            return Empty;
        }

        return HaveRecved.front();
    }

    void PopMessage()
    {
        FScopeLock Lock(&QueueMutex);

        HaveRecved.pop();
    }
};

/*

Message Type:

0 Not Allow / None / Empty / Network Error

1 LoginRequest
2 LoginRespond
3 ActionRequest : 1 For Jump, 2 For Fire
4 PlayerAction
5 MoveRequest : 1 For Forward, 2 For Right
6 PlayerMove
7 TurnRequest : 1 For Turn, 2 For Lookup
8 PlayerTurn
9 GameBegin

*/

DECLARE_MULTICAST_DELEGATE_TwoParams(ActionDelegate, uint32_t, uint32_t)
DECLARE_MULTICAST_DELEGATE_ThreeParams(MoveDelegate, uint32_t, uint32_t, float)
DECLARE_MULTICAST_DELEGATE_ThreeParams(TurnDelegate, uint32_t, uint32_t, float)

/**
 * 
 */
UCLASS()
class BASICSERVER_API UClientGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    ActionDelegate ActionMessage;

    MoveDelegate MoveMessage;

    TurnDelegate TurnMessage;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

private:
    FDelegateHandle TickDelegateHandle;

public:
    bool Update(float Delta);
    void Destroy();

public:
	void SendLoginRequest(const PLoginRequest& Message);
    void SendAction(const PActionRequest& Message);
    void SendMove(const PMoveRequest& Message);
    void SendTurn(const PTurnRequest& Message);

protected:
    NetworkSendThread* SendWorker = nullptr;
    NetworkRecvThread* RecvWorker = nullptr;

    FRunnableThread* SendThread = nullptr;
    FRunnableThread* RecvThread = nullptr;

protected:
	FSocket* Server = nullptr;

public:
    UPROPERTY(BlueprintReadwrite)
    int SelfID = 0;
};