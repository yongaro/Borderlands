// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AI_Character.generated.h"

class AAI_BController;

UENUM()
enum EB_AIState{
	idle,
	hit,
	walk,
	dead
};

UENUM()
enum EAI_FSM{
	patrouille,
	suivre,
	recherche
};

UCLASS()
class BORDERLANDS_API AAI_Character : public ACharacter{
	GENERATED_BODY()
protected:
	class UPawnSensingComponent* senses;
	class AAI_BController* controller;
	//class USkeletalMeshComponent* MeshComp;
	class UDamageHandler* DamageHandler;
	
	class UAnimSequence* hit;
	class UAnimSequence* idle;
	class UAnimSequence* walk;
	class UAnimSequence* death;

	class UAnimSequence* currentAnim;

public:
	static TArray<FString> features;
	EB_AIState state;
	EAI_FSM curState;
	// Sets default values for this character's properties
	AAI_Character();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	UFUNCTION( BlueprintCallable, Category = EnemyFunctions) 
	virtual void onSeePlayer( class APawn* seen );

	virtual float TakeDamage
		(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	virtual bool IsDead();
	virtual void BeginDeath();
	virtual void EndDeath();
	virtual void goRagdoll();
	virtual void mouvement();
	
	virtual bool HasFeature(FString);
};



/*Controller IA qui retablit l animation de base de son proprietaire*/
UCLASS()
class BORDERLANDS_API AAI_BController : public AAIController{
	GENERATED_BODY()
public:	
	AAI_Character* owner;

	AAI_BController( const FObjectInitializer& init ):AAIController(init){}
	AAI_BController( AAI_Character* own ):AAIController(){ owner = own; }

	virtual void OnMoveCompleted( FAIRequestID RequestID, EPathFollowingResult::Type Result ){ 
		if( Result == EPathFollowingResult::Success ){ 
			owner->state = EB_AIState::idle;
			owner->curState = EAI_FSM::recherche;
			owner->mouvement();
		}
		if( Result == EPathFollowingResult::Blocked || Result == EPathFollowingResult::Invalid ){
			//owner->state = EB_AIState::idle;
			owner->curState = EAI_FSM::recherche;
			owner->mouvement();
		}
	}
};
