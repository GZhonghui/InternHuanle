// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/EditableTextBox.h"

#include "ClientGameInstance.h"

#include "LoginUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASICSERVER_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* UserName;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* Password;

public:
	UFUNCTION(BlueprintCallable)
	void Login();

	UFUNCTION(BlueprintCallable)
	void QuitThread();
};
