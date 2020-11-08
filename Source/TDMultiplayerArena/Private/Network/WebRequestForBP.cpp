// Fill out your copyright notice in the Description page of Project Settings.


#include "WebRequestForBP.h"

void UWebRequestForBP::CallScript(const FString& InScriptURL)
{
	TSharedPtr<FJsonObject> JsonObject = CreateJsonRequest();

	if (Numbers.Num())
	{
		for (const FKeyNumber& Number : Numbers)
		{
			JsonObject->SetNumberField(Number.Key, Number.Value);
		}
	}

	if (Strings.Num())
	{
		for (const FKeyString& String : Strings)
		{
			JsonObject->SetStringField(String.Key, String.Value);
		}
	}

	CallWebScript(InScriptURL, JsonObject);
}

void UWebRequestForBP::CallJsonResponse(const TSharedPtr<FJsonObject>& InJsonResponse)
{
	if (!InJsonResponse->HasField("resultText"))
		return;

	const double ResultNumber = InJsonResponse->GetNumberField("resultNumber");
	const FString ResultString = InJsonResponse->GetStringField("resultText");

	const float ResultFloat = static_cast<float>(ResultNumber);

	UE_LOG(LogTemp, Warning, TEXT("Web response: string = '%s', number = '%f'"), *ResultString, ResultFloat)

	DelegateResultTest.Broadcast(ResultString, ResultFloat);
}
