// Fill out your copyright notice in the Description page of Project Settings.


#include "TIGLogicalTile.h"
#include "General/Entity.h"

#include "TileUtility.h"

TIGLogicalTile::TIGLogicalTile(TIG::TileID ID) 
	: UniqueID(ID)
	, State(TileUtility::ETileState::NUM)
{
}

TIGLogicalTile::TIGLogicalTile() :
	TIGLogicalTile(EntityUtility::CreateNextUniqueID<TIGLogicalTile>())
{
}

TIGLogicalTile::~TIGLogicalTile()
{
}

const TIGLogicalTile & TIGLogicalTile::GetInvalidTile()
{
	static TIGLogicalTile InvalidTile(TIG::INVALID_TILE_ID);
	return InvalidTile;
}
