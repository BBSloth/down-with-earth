
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravitySource.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DE_API AGravitySource : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gravity, meta = (AllowPrivateAccess = "true"))
	float GravityScale;

public:	
	AGravitySource();


protected:
	virtual void BeginPlay() override;

public:	
	float GetGravityScale();
		
};
