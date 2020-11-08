// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/WebRequestBase.h"
#include "WebRequestForBP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateResultTest, const FString&, InStringValue, const float&,InFloatValue);

USTRUCT()
struct FKeyNumber
{
	FKeyNumber(): Key(""), Value(-1){}
	FKeyNumber(const FString& InKey, const float& InValue): Key(InKey), Value(InValue){}

	UPROPERTY()
	FString Key;
	
	UPROPERTY()
	float Value;

	GENERATED_BODY()
};

USTRUCT()
struct FKeyString
{
	FKeyString(): Key(""), Value(""){}
	FKeyString(const FString& InKey, const FString& InValue): Key(InKey), Value(InValue){}

	UPROPERTY()
	FString Key;
	
	UPROPERTY()
	FString Value;

	GENERATED_BODY()
};

UCLASS(BlueprintType)
class TDMULTIPLAYERARENA_API UWebRequestForBP : public UWebRequestBase
{
public:

	UPROPERTY(BlueprintAssignable, Category = "WebRequest")
	FDelegateResultTest DelegateResultTest;

	UFUNCTION(BlueprintCallable, Category = "WebRequest", meta = (DisplayName = "Add Number (BP)"))
	void AddNumber(const FString& InKey, const float& InValue)
	{
		Numbers.Add(FKeyNumber(InKey, InValue));
	}

	UFUNCTION(BlueprintCallable, Category = "WebRequest", meta = (DisplayName = "Add String (BP)"))
	void AddString(const FString& InKey, const FString& InValue)
	{
		Strings.Add(FKeyString(InKey, InValue));
	}

	UFUNCTION(BlueprintCallable, Category = "WebRequest", meta = (DisplayName = "Call Web Script (BP)"))
	void CallScript(const FString& InScriptURL);

protected:

	virtual void CallJsonResponse(const TSharedPtr<FJsonObject>& InJsonResponse) override;

private:

	TArray<FKeyNumber> Numbers;
	TArray<FKeyString> Strings;


	GENERATED_BODY()
};
