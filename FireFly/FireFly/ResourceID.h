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
	ROOM1_Jar,
	Spider,
	ZidDash,
	ROOM1_Byra,
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
	"ROOM1_Jar",
	"Spider",
	"SpiderDash",
	"ROOM1_Byra",
};

enum class SoundEffectsID
{
	Fly,
	Moth,
};