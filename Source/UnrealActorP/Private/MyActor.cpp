// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"
float intervalTime = 1.0f;
float currentTime = 0.f;
int count = 0;
float dist = 0;
// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Test Text1!"));
	//FVector ActorLocation = GetActorLocation();
	//SetActorLocation(FVector(0, 0, 0));
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("ActorÀ§Ä¡: ")) + GetActorLocation().ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Actor: %s"), ActorLocation.ToString()));
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime += DeltaTime;
	if (intervalTime <= currentTime) {
		currentTime = 0;
		RandomMove();
		count++;
		if (count == 10) {
			count = 0;
			TriggerEventWithProbability(50.0f);
		}
	}
}

void AMyActor::RandomMove()
{
	int32 lx = FMath::RandRange(1, 100);
	int32 ly = FMath::RandRange(1, 100);
	int32 lz = FMath::RandRange(1, 100);
	FVector movevec = FVector(lx, ly, lz);
	dist += distance(GetActorLocation(), movevec);
	SetActorLocation(movevec);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Actor Location: ")) + GetActorLocation().ToString());

	int32 rx = FMath::RandRange(1, 360);
	int32 ry = FMath::RandRange(1, 360);
	int32 rz = FMath::RandRange(1, 360);
	SetActorRotation(FRotator(rx, ry, rz));
}


float AMyActor::distance(FVector first, FVector second) {
	float dx = first.X - second.X;
	float dy = first.Y - second.Y;
	return FMath::Sqrt(dx*dx + dy*dy);
}

void AMyActor::TriggerEventWithProbability(float Probability) {
	int32 value = FMath::RandRange(1, 100);

	if (value <= Probability) {
		UE_LOG(LogTemp, Log, TEXT("Event Triggered"));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("distance: ")) + FString::SanitizeFloat(dist));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Event not Triggered"));
	}
}