// Fill out your copyright notice in the Description page of Project Settings.


#include "MapDataAsset.h"

FIntPoint UMapDataAsset::GetSize() const
{
    return Size;
}

void UMapDataAsset::SetSize(FIntPoint size)
{
    Size = size;
    Tiles.Empty();
    Tiles.Reserve(size.X * size.Y);

    for (int i = 0; i < size.X * size.Y; i++)
        Tiles.Add(EMB_TileType::None);
}

EMB_TileType UMapDataAsset::GetTile(FIntPoint point) const
{
    return Tiles[point.Y * Size.X + point.X];
}

void UMapDataAsset::SetTile(FIntPoint point, EMB_TileType Tile)
{
    Tiles[point.Y * Size.X + point.X] = Tile;
}

int UMapDataAsset::GetEnemyCount() const
{
    return TotalEnemyCount;
}

void UMapDataAsset::SetEnemyCount(int enemyCount)
{
    TotalEnemyCount = enemyCount;
}

float UMapDataAsset::GetSpawnGap() const
{
    return SpawnGap;
}

void UMapDataAsset::SetSpawnGap(float spawnGap)
{
    SpawnGap = spawnGap;
}

FIntPoint UMapDataAsset::GetPathPoint(int index) const
{
    return Path[index];
}

void UMapDataAsset::AddPathPoint(FIntPoint pathPoint)
{
    Path.Add(pathPoint);
}

void UMapDataAsset::SetPathPoint(int index, FIntPoint pathPoint)
{
    Path[index] = pathPoint;
}

TArray<FIntPoint>* UMapDataAsset::GetPath()
{
    return &Path;
}
