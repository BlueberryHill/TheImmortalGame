// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGLogicalPiece.h"

#include "General/Entity.h"

#include "Game Systems/Movement/TIGMovementBase.h"
#include "Game Systems/Movement/TIGMovementManager.h"


TIGLogicalPiece::TIGLogicalPiece(EPieceType Type) :
	UniqueID(EntityUtility::CreateNextUniqueID<TIGLogicalPiece>()),
	BaseType(Type)
{
}

TIGLogicalPiece::~TIGLogicalPiece()
{
}
