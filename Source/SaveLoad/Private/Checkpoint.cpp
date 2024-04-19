// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "../MyCharacter.h"
#include "Components/SphereComponent.h"
#include  "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	CollisionMesh->SetupAttachment(CollisionSphere);

}


void ACheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("OVERLAPPING!!"));
	if (OtherActor->IsA(AMyCharacter::StaticClass())) {
		Cast<AMyCharacter>(OtherActor)->SaveGame();
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere = this->FindComponentByClass<USphereComponent>();
	if (CollisionSphere) {
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlap);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}
	
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

