// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGCoreGameState.h"

#include "Game Systems/TIGLogicalArena.h"


void ATIGCoreGameState::Init(UTIGArena& ViewArena, TIGLogicalArena& LogicArena)
{
	ArenaView = &ViewArena;
	LogicalArena = &LogicArena;
}

ATIGCoreGameState::~ATIGCoreGameState()
{
	delete LogicalArena;
}
