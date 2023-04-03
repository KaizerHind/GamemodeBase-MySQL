/*
# Credits Source: Dripa | https://sampforum.blast.hk/showthread.php?tid=343128&pid=1867238
# Design Modify by: KaizerHind.
*/

#include <a_samp>
#include <foreach>

new Text:ueberschrift[MAX_PLAYERS];
new Text:insidetext[MAX_PLAYERS];

static bool:fnc[1] = false;

public OnGameModeInit()
{
    fnc[0] = (funcidx("mBox_OnPlayerConnect") != -1);
    CallLocalFunction("mBox_OnGameModeInit", "");
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit mBox_OnGameModeInit
forward mBox_OnGameModeInit();

public OnPlayerConnect(playerid)
{
    if(fnc[0]) CallLocalFunction("mBox_OnPlayerConnect", "i", playerid);
    
    ueberschrift[playerid] = TextDrawCreate(39.599994, 130.266601, "Title");
    TextDrawLetterSize(ueberschrift[playerid], 0.400000, 1.600000);
    TextDrawTextSize(ueberschrift[playerid], 170.000000, 0.000000);
    TextDrawAlignment(ueberschrift[playerid], 1);
    TextDrawColor(ueberschrift[playerid], -1);
    TextDrawUseBox(ueberschrift[playerid], 1);
    TextDrawBoxColor(ueberschrift[playerid], 762614988);
    TextDrawSetShadow(ueberschrift[playerid], 0);
    TextDrawSetOutline(ueberschrift[playerid], 1);
    TextDrawBackgroundColor(ueberschrift[playerid], 255);
    TextDrawFont(ueberschrift[playerid], 1);
    TextDrawSetProportional(ueberschrift[playerid], 1);

    insidetext[playerid] = TextDrawCreate(39.599975, 150.426651, "Descrip");
    TextDrawLetterSize(insidetext[playerid], 0.400000, 1.600000);
    TextDrawTextSize(insidetext[playerid], 170.000000, 0.000000);
    TextDrawAlignment(insidetext[playerid], 1);
    TextDrawColor(insidetext[playerid], -1);
    TextDrawUseBox(insidetext[playerid], 1);
    TextDrawBoxColor(insidetext[playerid], 488447436);
    TextDrawSetShadow(insidetext[playerid], 0);
    TextDrawSetOutline(insidetext[playerid], 1);
    TextDrawBackgroundColor(insidetext[playerid], 255);
    TextDrawFont(insidetext[playerid], 1);
    TextDrawSetProportional(insidetext[playerid], 1);
    return 1;
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect mBox_OnPlayerConnect
forward mBox_OnPlayerConnect(playerid);

stock NotiBox(playerid,header[],text[])
{
    new string[128];

    format(string, sizeof string,"%s",header);
    TextDrawSetString(Text:ueberschrift[playerid],string);
    TextDrawShowForPlayer(playerid,Text:ueberschrift[playerid]);

    format(string, sizeof string,"%s",text);
    TextDrawSetString(Text:insidetext[playerid],string);
    TextDrawShowForPlayer(playerid,Text:insidetext[playerid]);

    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

    SetPVarInt(playerid,"NotiBoxEx",1);
    SetTimerEx("CloseBox", 5000, 0, "i", playerid);
    return 1;
}

forward CloseBox(playerid);
public CloseBox(playerid)
{
    TextDrawHideForPlayer(playerid,Text:ueberschrift[playerid]);
    TextDrawHideForPlayer(playerid,Text:insidetext[playerid]);
    return 1;
}