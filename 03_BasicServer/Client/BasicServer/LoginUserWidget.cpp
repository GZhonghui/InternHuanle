// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUserWidget.h"

void ULoginUserWidget::Login()
{
	std::string UserNameStr = TCHAR_TO_UTF8(*UserName->GetText().ToString());
	std::string PasswordStr = TCHAR_TO_UTF8(*Password->GetText().ToString());

	if (UserNameStr.length() && PasswordStr.length() && GI)
	{
		PLoginRequest LoginRequestMessage;
		LoginRequestMessage.set_username(UserNameStr);
		LoginRequestMessage.set_password(PasswordStr);

		GI->SendLoginRequest(LoginRequestMessage);
	}
}

void ULoginUserWidget::QuitThread()
{
	if (GI)
	{
		GI->Destroy();
	}
}