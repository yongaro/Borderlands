// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AI_Character.h"


// Sets default values
AAI_Character::AAI_Character(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("SkeletalMesh'/Game/Borderlands/mobs/hyperion/Skel_BattleDroid.Skel_BattleDroid'"));
	const ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/Borderlands/mobs/hyperion/BattleDroid_Dif_Mat.BattleDroid_Dif_Mat'"));

	const ConstructorHelpers::FObjectFinder<UAnimSequence> hitAnim(TEXT("AnimSequence'/Game/Borderlands/mobs/hyperion/AnimSet/Base_BattleDroid/Melee_Anim.Melee_Anim'"));
	const ConstructorHelpers::FObjectFinder<UAnimSequence> idleAnim(TEXT("AnimSequence'/Game/Borderlands/mobs/hyperion/AnimSet/Base_BattleDroid/Idle_Anim.Idle_Anim'"));
	const ConstructorHelpers::FObjectFinder<UAnimSequence> walkAnim(TEXT("AnimSequence'/Game/Borderlands/mobs/hyperion/AnimSet/Base_BattleDroid/big_run_F_Anim.big_run_F_Anim'"));

	MeshComp = CreateDefaultSubobject< USkeletalMeshComponent >(TEXT("AI_PawnMesh"));
	FVector offset = FVector(0.0,0.0,-85.0);
	MeshComp->SetSkeletalMesh(MeshObj.Object);
	MeshComp->SetMaterial(0, MeshMaterial.Object);	
	MeshComp->ApplyWorldOffset(offset,false);	
	MeshComp->AttachTo(RootComponent);


	senses = CreateDefaultSubobject< UPawnSensingComponent >(TEXT("senses"));
	senses->bSeePawns = true;
	senses->SetPeripheralVisionAngle(55.0);
	senses->SightRadius = 1500.0;
	senses->SetSensingUpdatesEnabled(true);
	//senses->SetSensingInterval(0.3); //Unreal crash generator


	state = EB_AIState::idle;
	hit = hitAnim.Object;
	idle = idleAnim.Object;
	walk = walkAnim.Object;

	currentAnim = idle;
	senses->OnSeePawn.AddDynamic( this, &AAI_Character::onSeePlayer );
	GetCharacterMovement()->MaxWalkSpeed = 250.0; //Vitesse normale -> 400
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay(){
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if(World != NULL){
		FVector NewLocation = GetActorLocation();
		FRotator NewRotation = GetActorRotation();
		controller = World->SpawnActor<AAI_BController>(AAI_BController::StaticClass(), NewLocation, NewRotation);
		controller->SetPawn(this);
		controller->owner = this;
	}
	MeshComp->PlayAnimation(currentAnim,true);
}


// Called every frame
void AAI_Character::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );
	//swapIdleWalk();
	if( state == EB_AIState::hit && currentAnim != hit ){ currentAnim = hit; MeshComp->PlayAnimation(currentAnim,false); } 
	if( state == EB_AIState::walk  && currentAnim != walk ){ currentAnim = walk; MeshComp->PlayAnimation(currentAnim,true); }
	if( state == EB_AIState::idle && currentAnim != idle ){ currentAnim = idle; MeshComp->PlayAnimation(currentAnim,true); } 
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(class UInputComponent* InputComponent){
	Super::SetupPlayerInputComponent(InputComponent);

}


void AAI_Character::onSeePlayer( APawn* seen ){	
	if( controller != NULL){
		state = EB_AIState::walk;
		controller->MoveToActor(seen);
		
		float dist = FVector::Dist(seen->GetActorLocation(),GetActorLocation());
	
		if( dist < 200.0 ){ state = EB_AIState::hit; }//hitAnim(); }
	}
	else{ UE_LOG(LogTemp, Warning, TEXT("AAI_Character::onSeePlayer -- pas de AIController")); }
}
