// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Character.h"
#include "Borderlands.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "../Absorber.h"
#include "../DamageHandler.h"
#include "../HealthAbsorber.h"
#include "../weapon/Weapon.h"
#include "../ElectricDamageType.h"


TArray<FString> AAI_Character::features = TArray<FString>();


// Sets default values
AAI_Character::AAI_Character(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("SkeletalMesh'/Game/Borderlands/mobs/hyperion/Skel_BattleDroid.Skel_BattleDroid'"));
	const ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/Borderlands/mobs/hyperion/BattleDroid_Dif_Mat.BattleDroid_Dif_Mat'"));

	const ConstructorHelpers::FObjectFinder<UAnimSequence> hitAnim(TEXT("AnimSequence'/Game/Borderlands/mobs/hyperion/AnimSet/Base_BattleDroid/Melee_Anim.Melee_Anim'"));
	const ConstructorHelpers::FObjectFinder<UAnimSequence> idleAnim(TEXT("AnimSequence'/Game/Borderlands/mobs/hyperion/AnimSet/Base_BattleDroid/Idle_Anim.Idle_Anim'"));
	const ConstructorHelpers::FObjectFinder<UAnimSequence> walkAnim(TEXT("AnimSequence'/Game/Borderlands/mobs/hyperion/AnimSet/Base_BattleDroid/big_run_F_Anim.big_run_F_Anim'"));
	const ConstructorHelpers::FObjectFinder<UAnimSequence> deathAnim(TEXT("AnimSequence'/Game/Borderlands/mobs/hyperion/AnimSet/Base_BattleDroid/Death_Var1_Anim.Death_Var1_Anim'"));
	
	GetMesh()->SetSkeletalMesh(MeshObj.Object);
	GetMesh()->SetMaterial(0, MeshMaterial.Object);
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -85.0));
	
	senses = CreateDefaultSubobject< UPawnSensingComponent >(TEXT("senses"));
	senses->bSeePawns = true;
	senses->SetPeripheralVisionAngle(65.0);
	senses->SightRadius = 2500.0;
	senses->SetSensingUpdatesEnabled(true);
	//senses->SetSensingInterval(0.3); //Unreal crash generator


	state = EB_AIState::idle;
	curState = EAI_FSM::patrouille;
	hit = hitAnim.Object;
	idle = idleAnim.Object;
	walk = walkAnim.Object;
	death = deathAnim.Object;

	currentAnim = idle;
	senses->OnSeePawn.AddDynamic( this, &AAI_Character::onSeePlayer );
	GetCharacterMovement()->MaxWalkSpeed = 275.0; //Vitesse normale -> 400


	DamageHandler = CreateDefaultSubobject<UDamageHandler>(TEXT("DamageHandler"));
	UHealthAbsorber* healthAbsorber = NewObject<UHealthAbsorber>(DamageHandler, UHealthAbsorber::StaticClass());
	DamageHandler->addAbsorber(healthAbsorber);
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
		mouvement();
	}
	GetMesh()->PlayAnimation(currentAnim,true);
}


// Called every frame
void AAI_Character::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

	//Check if the character is dead or not
	if (IsDead()){ BeginDeath(); }

	
	if( state == EB_AIState::dead && currentAnim != death ){
		currentAnim = death;
		GetMesh()->PlayAnimation(currentAnim,false);
		UWorld* World = GetWorld();
		if (World != NULL){
			float animLen = GetMesh()->GetSingleNodeInstance()->GetLength();
			FTimerHandle timerHandler;
			GetWorldTimerManager().SetTimer(timerHandler, this, &AAI_Character::goRagdoll, animLen, false);
		}
	} 
	if( state == EB_AIState::hit && currentAnim != hit ){ currentAnim = hit; GetMesh()->PlayAnimation(currentAnim,false); } 
	if( state == EB_AIState::walk && currentAnim != walk ){ currentAnim = walk; GetMesh()->PlayAnimation(currentAnim,true); }
	if( state == EB_AIState::idle && currentAnim != idle ){ currentAnim = idle; GetMesh()->PlayAnimation(currentAnim,true); } 
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(class UInputComponent* InputComponent){
	Super::SetupPlayerInputComponent(InputComponent);
}


void AAI_Character::onSeePlayer( APawn* seen ){	
	if( controller != NULL && state != EB_AIState::dead ){
		state = EB_AIState::walk;
		controller->MoveToActor(seen);
		
		float dist = FVector::Dist(seen->GetActorLocation(),GetActorLocation());
		if( dist < 200.0 ){ 
		state = EB_AIState::hit; 
		
		FMyDamageEvent dmgEvent;
		dmgEvent.DamageTypeClass = UElectricDamageType::StaticClass();
		dmgEvent.dps = 15;
		dmgEvent.effectChance = 0.8f;

		seen->TakeDamage(20.0,dmgEvent,GetInstigatorController(),this);
		
		}
	}
}

float AAI_Character::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser){
	/*Test pour type de degats*/
	if (DamageHandler) {
		return DamageHandler->Execute_Damage(DamageHandler, DamageAmount, DamageEvent);
	}
	return 0.0f;
}


bool AAI_Character::IsDead(){
	return (DamageHandler->Execute_getAbsorberAmount(DamageHandler, EAbsType::Flesh) <= 0.f);
}

void AAI_Character::BeginDeath(){
	state = EB_AIState::dead;
}



void AAI_Character::EndDeath(){ Destroy(); }

void AAI_Character::goRagdoll(){

	
	controller->StopMovement();
	//Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionProfileName(FName(TEXT("Ragdoll")));
	SetActorEnableCollision(true);
	
	GetMesh()->SetAllBodiesSimulatePhysics(true);
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->WakeAllRigidBodies();
    GetMesh()->bBlendPhysics = true;
    //GetMesh()->AddImpulseAtLocation(Impulse, HitLocation, Bone);
	
	GetCharacterMovement()->StopMovementImmediately();
    GetCharacterMovement()->DisableMovement();
    GetCharacterMovement()->SetComponentTickEnabled(false);
	
	//Pour inverser
	//MeshComp->PutAllRigidBodiesToSleep();
	//MeshComp->SetSimulatePhysics(false);
	
	UWorld* World = GetWorld();
	if (World != NULL){
		float animLen = GetMesh()->GetSingleNodeInstance()->GetLength()*3.0;
	
		FTimerHandle timerHandler;
		GetWorldTimerManager().SetTimer(timerHandler, this, &AAI_Character::EndDeath, animLen, false);
	}
}

void AAI_Character::mouvement(){
	if( state != EB_AIState::dead ){
		float pi = FGenericPlatformMath::Acos(-1.0);
		double radius = 400.0;
		float angle = FMath::RandRange(0,2.0*pi);
		float x = radius * FGenericPlatformMath::Cos(angle);
		float y = radius * FGenericPlatformMath::Sin(angle);
		FVector pos = GetActorLocation();
		pos.X += x; pos.Y+= y;
		
		state = EB_AIState::walk;
		controller->MoveToLocation(pos);
		if( curState == EAI_FSM::recherche ){ 
			controller->StopMovement(); 
			curState = EAI_FSM::patrouille;
			state = EB_AIState::idle;
			
			float delais = 1.5;
			FTimerHandle timerHandler;
			GetWorldTimerManager().SetTimer(timerHandler, this, &AAI_Character::mouvement, delais, false);
		}
	}
}

bool AAI_Character::HasFeature(FString feature){ return AAI_Character::features.Contains(feature); }
