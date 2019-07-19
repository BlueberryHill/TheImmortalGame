// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGLogicalPieceManager.h"

#include "TIGLogicalPiece.h"


TIGLogicalPieceManager::TIGLogicalPieceManager()
{
}

TIGLogicalPieceManager::~TIGLogicalPieceManager()
{
}

TIGLogicalPieceManager::PieceID TIGLogicalPieceManager::CreatePiece(PlayerID OwningPlayer, EPieceType Type)
{
	TUniquePtr<Piece> NewPiece = MakeUnique<TIGLogicalPiece>(Type);

	AddToPlayerIDMap(OwningPlayer, NewPiece);

	PieceID NewPieceID = NewPiece->GetUniqueID();
	PieceIDMap.Emplace(NewPieceID, std::move(NewPiece));

	return NewPieceID;
}

void TIGLogicalPieceManager::AddToPlayerIDMap(TIG::PlayerID& OwningPlayer, TUniquePtr<TIGLogicalPiece>& NewPiece)
{
	if (PlayerIDMap.Contains(OwningPlayer) == false)
	{
		PlayerIDMap.Emplace(OwningPlayer, Army{});
	}
	PlayerIDMap[OwningPlayer].Emplace(NewPiece.Get());
}

const TIGLogicalPiece & TIGLogicalPieceManager::GetPieceForID(PieceID PieceID) const
{
	check(PieceIDMap.Contains(PieceID) && "GetPieceForID - Requesting an ID not in the map");
	return *(PieceIDMap.Find(PieceID)->Get());
}