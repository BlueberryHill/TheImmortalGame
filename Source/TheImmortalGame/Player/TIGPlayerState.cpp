// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGPlayerState.h"

#include "General/Entity.h"

ATIGPlayerState::ATIGPlayerState() :
	APlayerState(),
	UniqueID(EntityUtility::CreateNextUniqueID<ATIGPlayerState>())
{
}
