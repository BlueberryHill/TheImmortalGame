// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGPlayerState.h"

#include "ThreadSafeCounter.h"

namespace {
	int CreateNextUniqueID() {
		static FThreadSafeCounter ID{ 0 }; 
		return ID.Increment();
	}

}

ATIGPlayerState::ATIGPlayerState() :
	APlayerState(),
	UniqueID(CreateNextUniqueID())
{
}
