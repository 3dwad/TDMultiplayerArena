// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "WebRequestBase.generated.h"

class IHttpRequest;
class FHttpModule;

DECLARE_LOG_CATEGORY_EXTERN(LogWebRequest,All,All)

UENUM(BlueprintType)
enum class EWebRequestType: uint8
{
	Post,
	Get
};

UCLASS()
class TDMULTIPLAYERARENA_API UWebRequestBase : public UObject
{
	public:
	
	bool CallWebScript(const FString& InScriptURL, TSharedPtr<FJsonObject>& OutJsonRequest,EWebRequestType InRequestType = EWebRequestType::Post);

	TSharedPtr<FJsonObject> CreateJsonRequest();

	virtual void CallJsonResponse(const TSharedPtr<FJsonObject>& InJsonResponse){}

	virtual void CallJSonFail(){}

	virtual void OnResponseReceived(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool InWasSuccessful);

private:

	void InitRequest(TSharedRef<IHttpRequest>& OutRequest, const FString& InRequestType, const FString& InScriptURL);

	FHttpModule* HttpModule;
	FString JsonStream{"JsonStream"};

	bool bUsingSSL{false};
	GENERATED_BODY()
};
