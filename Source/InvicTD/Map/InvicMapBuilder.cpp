// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicMapBuilder.h"
#include "MapDataAsset.h"

// Sets default values
AInvicMapBuilder::AInvicMapBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UMapDataAsset* AInvicMapBuilder::GetAsset() const
{
	return MapAsset;
}

float AInvicMapBuilder::GetTileDistance() const
{
	return TileDistance;
}

FVector AInvicMapBuilder::ConvertGridToWorld(FIntPoint point) const
{
	FIntPoint TopLeft = FIntPoint();
	FIntPoint Size = FIntPoint();
	if (MapAsset)
	{
		Size = MapAsset->GetSize();
		TopLeft = FIntPoint(-Size.X / 2, -Size.Y / 2);
	}
	int x = point.X, y = point.Y;

	int TX = TopLeft.X + (Size.X - x);
	int TY = TopLeft.Y + y;
	FVector Position = FVector(TileDistance * TX - 0.5f * TileDistance, TileDistance * TY + 0.5f * TileDistance, ConvertZ);
	return Position;
}

// Called when the game starts or when spawned
void AInvicMapBuilder::BeginPlay()
{
	Super::BeginPlay();
	
	BuildMapFromMapAsset();
	//BuildMapFromString(FIntPoint(12, 22), "114411111117116111151111400011115111111171111144101161100000111611111120155510222011111115111011111015101171711300002100001110117111130311110211111011511113032221011114101161111300000001111410271441111115511111144000004111611116115171111114411111151161111111611111");
}

void AInvicMapBuilder::BuildMapFromMapAsset()
{
	if (MapAsset)
	{
		FIntPoint Size = MapAsset->GetSize();
		FIntPoint TopLeft = FIntPoint(-Size.X / 2, -Size.Y / 2);
		for (int x = 0; x < Size.X; x++)
		{
			for (int y = 0; y < Size.Y; y++)
			{
				int TX = TopLeft.X + (Size.X - x);
				int TY = TopLeft.Y + y;
				FVector Position = FVector(TileDistance * TX - 0.5f * TileDistance, TileDistance * TY + 0.5f * TileDistance, 0);
				AActor* Object = nullptr;

				switch (MapAsset->GetTile(FIntPoint(x, y)))
				{
				case EMB_TileType::Path:
					Object = GetWorld()->SpawnActor<AActor>(MapAsset->PathObject, Position, FRotator());
					break;
				case EMB_TileType::High:
					Object = GetWorld()->SpawnActor<AActor>(MapAsset->HighObject, Position, FRotator());
					break;
				case EMB_TileType::PathScenery:
					if(MapAsset->PathScenery.Num() > 0)
						Object = GetWorld()->SpawnActor<AActor>(MapAsset->PathScenery[0], Position, FRotator());
					break;
				case EMB_TileType::PathScenery2:
					if (MapAsset->PathScenery.Num() > 1)
						Object = GetWorld()->SpawnActor<AActor>(MapAsset->PathScenery[1], Position, FRotator());
					break;
				case EMB_TileType::PathScenery3:
					if (MapAsset->PathScenery.Num() > 2)
						Object = GetWorld()->SpawnActor<AActor>(MapAsset->PathScenery[2], Position, FRotator());
					break;
				case EMB_TileType::HighScenery:
					if (MapAsset->HighScenery.Num() > 0)
						Object = GetWorld()->SpawnActor<AActor>(MapAsset->HighScenery[0], Position, FRotator());
					break;
				case EMB_TileType::HighScenery2:
					if (MapAsset->HighScenery.Num() > 1)
						Object = GetWorld()->SpawnActor<AActor>(MapAsset->HighScenery[1], Position, FRotator());
					break;
				case EMB_TileType::HighScenery3:
					if (MapAsset->HighScenery.Num() > 2)
						Object = GetWorld()->SpawnActor<AActor>(MapAsset->HighScenery[2], Position, FRotator());
					break;
				}

				if(!Object)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Failed to spawn at %d|%d"),x,y));
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Built From Asset yeahhh")));
}

void AInvicMapBuilder::BuildMapFromString(FIntPoint Size, char* String)
{
	size_t Len = strlen(String);
	FIntPoint TopLeft = FIntPoint(-Size.X / 2, -Size.Y / 2);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Length is %d"), Len));
	//Keep in mind: X is Y, Y is X
	if (MapAsset && Len >= Size.X * Size.Y)
	{
		MapAsset->SetSize(Size);
		for (int x = 0; x < Size.X; x++)
		{
			for (int y = 0; y < Size.Y; y++)
			{
				int TX = TopLeft.X + (Size.X-x);
				int TY = TopLeft.Y + y;
				char c = String[x * Size.Y + y];
				if (c == '0')
				{
					MapAsset->SetTile(FIntPoint(x, y), EMB_TileType::Path);
					FVector Position = FVector(TileDistance * TX - 0.5f*TileDistance, TileDistance * TY + 0.5f * TileDistance, 0);
					AActor* Object = GetWorld()->SpawnActor<AActor>(MapAsset->PathObject, Position, FRotator());
					if(Object)
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d|%d is %c"), x, y, c));
				}
				else if (c == '1')
				{
					MapAsset->SetTile(FIntPoint(x, y), EMB_TileType::High);
					FVector Position = FVector(TileDistance * TX - 0.5f * TileDistance, TileDistance * TY + 0.5f * TileDistance, 0);
					AActor* Object = GetWorld()->SpawnActor<AActor>(MapAsset->HighObject, Position, FRotator());
					if (Object)
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d|%d is %c"), x, y, c));
				}
				else if (c <= '4')
				{
					if(c == '2')
						MapAsset->SetTile(FIntPoint(x, y), EMB_TileType::PathScenery);
					else if (c == '3')
						MapAsset->SetTile(FIntPoint(x, y), EMB_TileType::PathScenery2);
					else if (c == '4')
						MapAsset->SetTile(FIntPoint(x, y), EMB_TileType::PathScenery3);

					FVector Position = FVector(TileDistance * TX - 0.5f * TileDistance, TileDistance * TY + 0.5f * TileDistance, 0);
					AActor* Object = GetWorld()->SpawnActor<AActor>(MapAsset->PathScenery[c - '2'], Position, FRotator());
					if (Object)
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d|%d is %c"), x, y, c));
				}
				else if (c <= '7')
				{
					if (c == '5')
						MapAsset->SetTile(FIntPoint(x, y), EMB_TileType::HighScenery);
					else if (c == '6')
						MapAsset->SetTile(FIntPoint(x, y), EMB_TileType::HighScenery2);
					else if (c == '7')
						MapAsset->SetTile(FIntPoint(x, y), EMB_TileType::HighScenery3);

					FVector Position = FVector(TileDistance * TX - 0.5f * TileDistance, TileDistance * TY + 0.5f * TileDistance, 0);
					AActor* Object = GetWorld()->SpawnActor<AActor>(MapAsset->HighScenery[c - '5'], Position, FRotator());
					if (Object)
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d|%d is %c"), x, y, c));
				}
			}
		}
	}
}

// Called every frame
void AInvicMapBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

