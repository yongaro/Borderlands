// Fill out your= copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "SpawnActor.h"
#include "TestMeshSocket/TestSocket.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));//
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	Mesh->SetStaticMesh(MeshObj.Object);
	SetActorHiddenInGame(true);
	FVector scale; scale.X = scale.Y = scale.Z = 0.5f;
	Mesh->SetWorldScale3D(scale);
	bCanBeDamaged = false;
	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ASpawnActor::spawn() {
	if (whatToSpawn != NULL) {
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters params;
			params.Owner = this;
			params.bNoCollisionFail = true;
			FVector loc = GetActorLocation()+offset;
			FRotator rotation = FRotator::ZeroRotator;
			rotation.Yaw = 90.f;
			AActor *a = world->SpawnActor<AActor>(whatToSpawn, loc, rotation, params);
		}
		if (bDestroyWhenFinished)
			Destroy();
	}
}
