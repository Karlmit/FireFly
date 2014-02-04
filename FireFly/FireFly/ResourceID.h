#pragma once

// IDs for resources

enum class TexturesID
{
	Zid,
	Moth,
	ROOM1_Background,
	ROOM1_Foreground,
	ROOM1_Coat1,
	ROOM1_Coat2,
	ROOM1_Coat3,
	ROOM1_Coat4,
	ROOM1_Coat5,
	ROOM1_JAR,
	Spider,
	SIZE_OF_ENUM,	// Keep last
};

// A replica of enum but with strings for the LevelEditor conversion of string to id
static const char* TexturesIDNames[TexturesID::SIZE_OF_ENUM] = 
{ 
	"Zid",
	"Moth",
	"ROOM1_Background",
	"ROOM1_Foreground",
	"ROOM1_Coat1",
	"ROOM1_Coat2",
	"ROOM1_Coat3",
	"ROOM1_Coat4",
	"ROOM1_Coat5",
	"ROOM1_JAR",
	"Spider",
};

enum class SoundEffectsID
{
	Fly,
	Moth,
};