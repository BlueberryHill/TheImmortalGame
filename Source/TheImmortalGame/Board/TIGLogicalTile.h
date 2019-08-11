// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/LogicalTypes.h"


namespace TileUtility
{
	enum class ETileState : uint8;
}
/**
 * 
 */
class THEIMMORTALGAME_API TIGLogicalTile
{
public:
	explicit TIGLogicalTile(TIG::TileID UniqueID);
	TIGLogicalTile();
	~TIGLogicalTile();

	static const TIGLogicalTile& GetInvalidTile();

	int32 GetUniqueID() const { return UniqueID; }

	TileUtility::ETileState CurrentState() const							  { return State; }
	void					SetCurrentState(TileUtility::ETileState NewState) { State = NewState; }

private:
	TIG::TileID UniqueID = 0;

	TileUtility::ETileState  State;
};
