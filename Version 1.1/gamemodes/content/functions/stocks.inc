CALLBACK: Descongelar(playerid) return TogglePlayerControllable(playerid,true);

stock PlayerFreeze(playerid,segundos=0)
{
	if(!segundos) return TogglePlayerControllable(playerid,false);

	else if(segundos)
	{
		TogglePlayerControllable(playerid,false);
		SetTimerEx("Descongelar",segundos*1000,false,"i",playerid);
	}
	return 1;
}

stock ClearChat(playerid,lineas)
{
	Loop(i,lineas,0) SendClientMessage(playerid,-1,"");
 	return 1;
}

stock RandomCamera(playerid)
{
  new RandMovement;
  RandMovement = random(3);
  TogglePlayerSpectating(playerid, true);
  switch(RandMovement)
  {
	case 0:
  	{
		InterpolateCameraPos(playerid, 1821.641113, -1920.931152, 13.405388, 1821.379272, -1665.030517, 14.498521, 45000);
		InterpolateCameraLookAt(playerid, 1821.657226, -1915.932739, 13.531604, 1821.308349, -1660.035522, 14.711844, 22500);
	}
	case 1:
  	{
		InterpolateCameraPos(playerid, 1565.513305, -1733.132446, 14.356844, 1578.185058, -1729.579711, 71.607223, 45000);
		InterpolateCameraLookAt(playerid, 1561.613769, -1736.157714, 15.157655, 1574.273071, -1732.688232, 71.423744, 45000);
	}
	case 2:
  	{
		InterpolateCameraPos(playerid, 1308.438964, -1403.570190, 14.576297, 990.262329, -1416.168090, 56.591018, 45000);
		InterpolateCameraLookAt(playerid, 1303.439819, -1403.628540, 14.645874, 993.421386, -1413.238647, 54.053543, 22500);
	}
  }
  return 1;
}

forward PreloadAnimLibs(playerid);
public PreloadAnimLibs(playerid) {
  for(new i = 0; i < sizeof(AnimLibs); i++) {
      ApplyAnimation(playerid, AnimLibs[i], "null", 4.0, 0, 0, 0, 0, 0, 1);
  }
  return 1;
}

stock LoadCutScene(playerid)
{
	/*# Posicionamiento de Vista hacia el Incendio #*/
	SetPlayerCameraPos(playerid, 2070.1780, -1127.1179, 24.1296);
	SetPlayerCameraLookAt(playerid, 2071.0688, -1126.6582, 24.1964);
	/*# Actores de Simulacion en la Introduccion #*/
	ActorIntro[0] = CreateActor(7, 2077.9656, -1123.2223, 24.2170, -90.0);
	ActorIntro[1] = CreateActor(279, 2086.35620, -1119.58069, 26.32540, -120.0);
	ActorIntro[2] = CreateActor(279, 2086.50854, -1125.49023, 25.81730, -60.0);
	ApplyAnimation(ActorIntro[0], "MISC", "null", 0.0, 0, 0, 0, 0, 0); ApplyActorAnimation(ActorIntro[0], "MISC", "PLYR_SHKHEAD", 4.1, 1, 0, 0, 0, 0);
	ApplyAnimation(ActorIntro[1], "PED", "null", 0.0, 0, 0, 0, 0, 0); ApplyActorAnimation(ActorIntro[1], "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 0);
	ApplyAnimation(ActorIntro[2], "PED", "null", 0.0, 0, 0, 0, 0, 0); ApplyActorAnimation(ActorIntro[2], "PED", "ARRESTgun", 4.1, 0, 1, 1, 1, 0);
	/*# Fuego Animado en la casa #*/
	FireObj[0] = CreateObject(18691, 2094.531250, -1120.134887, 822.818237, 0.0, 0.07, 0.0);
	FireObj[1] = CreateObject(18691, 2092.469726, -1119.442871, 819.035400, 0.0, 0.07, 0.0);
	FireObj[2] = CreateObject(18691, 2093.576660, -1123.130615, 819.035400, 0.0, 0.07, 0.0);
	FireObj[3] = CreateObject(18691, 2092.883056, -1127.110961, 819.035400, 0.0, 0.07, 0.0);
	FireObj[4] = CreateObject(18691, 2095.645996, -1126.088623, 822.412231, 0.0, 0.07, 0.0);
	/*# Escalera, Barricada y tubo de agua, fuera y dentro de la casa #*/
	fExtra[0] = CreateObject(1211, 2077.1470, -1121.3151, 23.5567,   0.0, 0.0, 0.0);
	fExtra[1] = CreateObject(1459, 2084.36426, -1123.13074, 24.74886,   0.0, -4.0, 90.0);
	fExtra[2] = CreateObject(1437, 2090.55054, -1123.87634, 25.07072,   -10.0, 0.0, -90.0);
    /*# Simulacion de Extinguidores en mano [1] #*/
    FireObj[5] = CreateObject(366, 2086.34570, -1119.63647, 26.09930, 0.0, 10.0, -26.0);
    FireObj[6] = CreateObject(18687, 2086.7922, -1119.7451, 26.1624, 0.0, 0.0, 0.0);
    /*# Simulacion de Extinguidores en mano [2] #*/
	FireObj[7] = CreateObject(366, 2086.67163, -1125.47974, 25.99930, 0.0, 10.0, 26.0);
	FireObj[8] = CreateObject(18687, 2087.04077, -1125.19336, 26.06380, 0.0, 0.0, 0.0);
	/*# Unidad de bombero en el incendio [2] #*/
	VehEngine[0] = CreateVehicle(407, 2076.9529, -1115.2106, 24.2980, 180.0, 3, 1, -1);
	return 1;
}

stock ShowServerNameTD(playerid)
{
	TextDrawShowForPlayer(playerid, tdSVName[0]);
	TextDrawShowForPlayer(playerid, tdSVName[1]);
	return 1;
}

stock CommandError(playerid)
{
	TextDrawShowForPlayer(playerid, tdError[0]); TextDrawShowForPlayer(playerid, tdError[1]); TextDrawShowForPlayer(playerid, tdError[2]); return 1;
}

stock IsNumeric(const string[])
{
    new length=strlen(string);
    if (length==0) return false;
    for (new i = 0; i < length; i++) {
        if (
        (string[i] > '9' || string[i] < '0' && string[i]!='-' && string[i]!='+')
        || (string[i]=='-' && i!=0)                                             //
        || (string[i]=='+' && i!=0)                                             //
        ) return false;
    }
    if (length==1 && (string[0]=='-' || string[0]=='+')) return false;
	return true;
}