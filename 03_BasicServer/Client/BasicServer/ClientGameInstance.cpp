// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientGameInstance.h"

void UClientGameInstance::Init()
{
	Super::Init();

	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UClientGameInstance::Update));

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (SocketSubsystem)
	{
		Server = SocketSubsystem->CreateSocket(NAME_Stream, "SensorConnect", true);

		bool isIPValid;

		auto ServerAddress = SocketSubsystem->CreateInternetAddr();
		// ServerAddress->SetIp(TEXT("127.0.0.1"), isIPValid);
		ServerAddress->SetIp(TEXT("10.0.128.201"), isIPValid);
		ServerAddress->SetPort(3002);

		if (Server && Server->Connect(*ServerAddress))
		{
			Print(TEXT("Server Connected"));

			SendWorker = new NetworkSendThread(Server);
			SendThread = FRunnableThread::Create(SendWorker, TEXT("SendThread"));

			RecvWorker = new NetworkRecvThread(Server);
			RecvThread = FRunnableThread::Create(RecvWorker, TEXT("RecvThread"));

			Print(TEXT("Two Threads Started"));
		}
		else
		{
			Print(TEXT("Failed Connection"));
		}
	}
}

void UClientGameInstance::Shutdown()
{
	Destroy();

	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	Super::Shutdown();
}

void UClientGameInstance::Destroy()
{
	if (Server)
	{
		Server->Close();
		Server = nullptr;

		Print(TEXT("Server Closed"));
	}

	if(SendWorker) SendWorker->Stop(), Print(TEXT("Closed Send Threads"));
	if(RecvWorker) RecvWorker->Stop(), Print(TEXT("Closed Recv Threads"));

	if (SendThread)
	{
		SendThread->Kill();
		delete SendThread;
		SendThread = nullptr;
		if (SendWorker)
		{
			delete SendWorker;
			SendWorker = nullptr;
		}
	}

	if (RecvThread)
	{
		RecvThread->Kill();
		delete RecvThread;
		RecvThread = nullptr;
		if (RecvWorker)
		{
			delete RecvWorker;
			RecvWorker = nullptr;
		}
	}
}

bool UClientGameInstance::Update(float Delta)
{
	if (!RecvWorker) return true;

	auto Next = RecvWorker->NextMessage();

	if (!Next.MessageType) return true;
	
	RecvWorker->PopMessage();

	switch (Next.MessageType)
	{
	
	case 2:
	{
		PLoginRespond LoginRespond;
		LoginRespond.ParseFromArray(Next.Buffer.GetData(), Next.MessageLen);

		if (LoginRespond.allowlogin())
		{
			Print(TEXT("Login Successfully"));

			SelfID = LoginRespond.selfid();
			Print(FString::Printf(TEXT("Player ID: %u"), SelfID));
		}
		else
		{
			Print(TEXT("Login Failed"));
		}

	}break;

	case 4:
	{
		PPlayerAction PlayerAction;
		PlayerAction.ParseFromArray(Next.Buffer.GetData(), Next.MessageLen);
		ActionMessage.Broadcast(PlayerAction.playerid(), PlayerAction.actiontype());
	}break;

	case 6:
	{
		PPlayerMove PlayerMove;
		PlayerMove.ParseFromArray(Next.Buffer.GetData(), Next.MessageLen);
		MoveMessage.Broadcast(PlayerMove.playerid(), PlayerMove.movetype(), PlayerMove.movevalue());
	}break;

	case 8:
	{
		PPlayerTurn PlayerTurn;
		PlayerTurn.ParseFromArray(Next.Buffer.GetData(), Next.MessageLen);
		TurnMessage.Broadcast(PlayerTurn.playerid(), PlayerTurn.turntype(), PlayerTurn.turnvalue());

	}break;

	case 9:
	{
		PGameBegin GameBegin;
		GameBegin.ParseFromArray(Next.Buffer.GetData(), Next.MessageLen);

		Print(TEXT("Game Start"));
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/FirstPersonCPP/Maps/FirstPersonExampleMap"),
			true, TEXT("?game=/Game/FirstPersonCPP/PlayMode.PlayMode_C"));

	}break;

	}

	return true;
}

void UClientGameInstance::SendLoginRequest(const PLoginRequest& Message)
{
	SingleMessageData SendData;
	SendData.MessageType = 1;
	SendData.MessageLen = Message.ByteSizeLong();
	SendData.Buffer.SetNum(SendData.MessageLen);
	Message.SerializeToArray(SendData.Buffer.GetData(), SendData.MessageLen);
	
	if (SendWorker)
	{
		SendWorker->AddMessage(SendData);

		Print("Sending Login Info");
	}
}

void UClientGameInstance::SendAction(const PActionRequest& Message)
{
	SingleMessageData SendData;
	SendData.MessageType = 3;
	SendData.MessageLen = Message.ByteSizeLong();
	SendData.Buffer.SetNum(SendData.MessageLen);
	Message.SerializeToArray(SendData.Buffer.GetData(), SendData.MessageLen);

	if (SendWorker)
	{
		SendWorker->AddMessage(SendData);
	}
}

void UClientGameInstance::SendMove(const PMoveRequest& Message)
{
	SingleMessageData SendData;
	SendData.MessageType = 5;
	SendData.MessageLen = Message.ByteSizeLong();
	SendData.Buffer.SetNum(SendData.MessageLen);
	Message.SerializeToArray(SendData.Buffer.GetData(), SendData.MessageLen);

	if (SendWorker)
	{
		SendWorker->AddMessage(SendData);
	}
}

void UClientGameInstance::SendTurn(const PTurnRequest& Message)
{
	SingleMessageData SendData;
	SendData.MessageType = 7;
	SendData.MessageLen = Message.ByteSizeLong();
	SendData.Buffer.SetNum(SendData.MessageLen);
	Message.SerializeToArray(SendData.Buffer.GetData(), SendData.MessageLen);

	if (SendWorker)
	{
		SendWorker->AddMessage(SendData);
	}
}