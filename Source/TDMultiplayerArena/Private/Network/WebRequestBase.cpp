// Fill out your copyright notice in the Description page of Project Settings.


#include "WebRequestBase.h"

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "HttpModule.h"


DEFINE_LOG_CATEGORY(LogWebRequest)


bool UWebRequestBase::CallWebScript(const FString& InScriptURL, TSharedPtr<FJsonObject>& OutJsonRequest,EWebRequestType InRequestType)
{
	if (!HttpModule)
		HttpModule = &FHttpModule::Get();

	//	Create request
	TSharedRef<IHttpRequest> IHttpRequest = HttpModule->CreateRequest();

	// Get full URL
	FString ResultURL = "http://";
	if (bUsingSSL)
		ResultURL = "https://";
	ResultURL += InScriptURL;

	if (InRequestType == EWebRequestType::Post)
		InitRequest(IHttpRequest, "Post", ResultURL);
	else
		InitRequest(IHttpRequest, "Get", ResultURL);

	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStream);
	FJsonSerializer::Serialize(OutJsonRequest.ToSharedRef(), Writer);
	IHttpRequest->SetContentAsString(JsonStream);

	UE_LOG(LogWebRequest, Warning, TEXT("Request Json data to '%s'"), *ResultURL)

	IHttpRequest->ProcessRequest();

	return true;
}

TSharedPtr<FJsonObject> UWebRequestBase::CreateJsonRequest()
{
	return MakeShareable(new FJsonObject);
}

void UWebRequestBase::OnResponseReceived(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool InWasSuccessful)
{
	if (InWasSuccessful)
	{
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(InResponse->GetContentAsString());

		UE_LOG(LogWebRequest, Warning, TEXT("[OnResponseReceived] Response json: \n'%s'"),*InResponse->GetContentAsString())

		TSharedPtr<FJsonObject> JsonObject;
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			CallJsonResponse(JsonObject);
		}
		else
		{
			UE_LOG(LogWebRequest, Error, TEXT("[OnResponseReceived] Fail to deserialize json!"))
			CallJSonFail();
		}
	}
	else
	{
		CallJSonFail();
	}
}

void UWebRequestBase::InitRequest(TSharedRef<IHttpRequest>& OutRequest, const FString& InRequestType,const FString& InScriptURL)
{
	OutRequest->OnProcessRequestComplete().BindUObject(this, &UWebRequestBase::OnResponseReceived);
	OutRequest->SetURL(InScriptURL);
	OutRequest->SetVerb(InRequestType);
	OutRequest->SetHeader(TEXT("User-Agent"),"X-UnrealEngine-Agent");
	OutRequest->SetHeader("Content-Type", TEXT("application/json"));
}




