// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"


#include "TIGCoreGameState.generated.h"

class UTIGArena;
class TIGLogicalArena;
/**
 * 
 */
UCLASS()
class THEIMMORTALGAME_API ATIGCoreGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void			 Init(UTIGArena& ViewArena, TIGLogicalArena& LogicalArena);

	~ATIGCoreGameState();

	const UTIGArena&       GetArenaView()	 const { return *ArenaView; }
	UTIGArena&			   GetArenaView()		   { return *ArenaView; }
	const TIGLogicalArena& GetLogicalArena() const { return *LogicalArena; }

private:
	UTIGArena*		 ArenaView	  = nullptr;	//#TODO: This shouldn't live here as different players may have different (or no) view of the world
	TIGLogicalArena* LogicalArena = nullptr;
};
