// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/LogicalTypes.h"

class TIGLogicalPiece;

enum class EPieceType : uint8;
/**
 * 
 */
class THEIMMORTALGAME_API TIGLogicalPieceManager
{
	using Piece = TIGLogicalPiece;
	using Army = TArray<Piece*>;
	using PieceID = TIG::PieceID;
	using PlayerID = TIG::PlayerID;

	using PlayerIDToArmy = TMap<PieceID, Army>;
	using PieceIDToPiece = TMap<PieceID, TUniquePtr<Piece>>; 
	
public:
	TIGLogicalPieceManager();
	~TIGLogicalPieceManager();

	TIGLogicalPieceManager(const TIGLogicalPieceManager&) = delete;
	TIGLogicalPieceManager& operator=(const TIGLogicalPieceManager&) = delete;

	const TIGLogicalPiece & GetPieceForID(int32 PieceID) const;
	PieceID CreatePiece(PlayerID OwningPlayer, EPieceType Type);
	void AddToPlayerIDMap(TIG::PlayerID &OwningPlayer, TUniquePtr<TIGLogicalPiece> &NewPiece);
private:
	PieceIDToPiece PieceIDMap;
	PlayerIDToArmy PlayerIDMap;
};
