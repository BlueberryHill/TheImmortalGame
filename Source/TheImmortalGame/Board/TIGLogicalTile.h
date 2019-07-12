// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/LogicalTypes.h"

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
private:
	TIG::TileID UniqueID = 0;
};
