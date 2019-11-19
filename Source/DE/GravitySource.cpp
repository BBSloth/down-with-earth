
#include "GravitySource.h"

AGravitySource::AGravitySource()
{
}

void AGravitySource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Accessors

float AGravitySource::GetGravityScale()
{
	return GravityScale;
}
