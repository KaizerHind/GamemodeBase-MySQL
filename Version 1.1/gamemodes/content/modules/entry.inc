PlayerName(playerid){
    new name[24 + 1];
    GetPlayerName(playerid, name, MAX_PLAYER_NAME);
    return name;
}

public OnGameModeInit()
{
	/* ======== [ Configuración general ] ======== */
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	ShowNameTags(1);
	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
    SetGameModeText(MODE_SERVER);
	SendRconCommand("hostname "#SERVER_NAME"");
    SendRconCommand("mapname San Andreas");
    SendRconCommand("weburl "#DISCORD_SV"");
 	SendRconCommand("password ");

	/* ############### ini Config File.  ############### */
    DB = mysql_connect_file("mysql.ini");
    if(mysql_errno(DB) == 0){ print("La Conexion con la DB ha sido Exitosa - [MySQL]\n");}
	else {print("La Conexion con la DB ha Fallado - [MySQL]");  SendRconCommand("exit");}
	/* ################################################# */
	/* ## A Partir de aqui puedes agregar codigo ## */
	/* ############################################ */


	/* ############### DON TOUCH ############### */
	#if defined entry_OnGameModeInit
		return entry_OnGameModeInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit entry_OnGameModeInit
#if defined entry_OnGameModeInit
	forward entry_OnGameModeInit();
#endif


public OnGameModeExit()
{
    foreach(new a: Player){
		SavePlayer(a);
    }
    mysql_close(DB);
	/* ############### DON TOUCH ############### */
	#if defined entry_OnGameModeExit
		return entry_OnGameModeExit();
	#else
		return 0;
	#endif
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif

#define OnGameModeExit entry_OnGameModeExit
#if defined entry_OnGameModeExit
	forward entry_OnGameModeExit();
#endif


public OnPlayerSpawn(playerid)
{
    if(GetPVarInt(playerid, "Logueado") == 0) {Kick(playerid);}
	/* ############### DON TOUCH ############### */
	#if defined entry_OnPlayerSpawn
		return entry_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn entry_OnPlayerSpawn
#if defined entry_OnPlayerSpawn
	forward entry_OnPlayerSpawn(playerid);
#endif


public OnPlayerConnect(playerid)
{
	RandomCamera(playerid);
	PreloadAnimLibs(playerid);
	ShowServerNameTD(playerid);
	mysql_format(DB, global_str, sizeof global_str, "SELECT * FROM users WHERE Name = '%e'", PlayerName(playerid));
	mysql_tquery(DB, global_str, "OnPlayerDataCheck", "d", playerid);
	
	/* ############### DON TOUCH ############### */
	#if defined entry_OnPlayerConnect
		return entry_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect entry_OnPlayerConnect
#if defined entry_OnPlayerConnect
	forward entry_OnPlayerConnect(playerid);
#endif

CALLBACK:OnPlayerDataCheck(playerid){
	if (IsPlayerNPC(playerid)) return SpawnPlayer(playerid);
	if (GetPVarInt(playerid, "Logueado"))
	{
	 	Kick(playerid);
	 	return 1;
	}

	if(cache_num_rows() > 0){
		ClearChat(playerid, 100);
		cache_get_value_name(0, "Password", hash);
		format(PlayerData[playerid][jPass], 65, "%s", hash);
		
		format(global_str, sizeof(global_str), "\n\n\t\t¡Bienvenido de nuevo %s!.\n____________________________________\n\tTu ultima conexion fue el ><.\n\nIngresa tu contraseña para entrar al Servidor. Sino eres el propietario de dicha cuenta, te invitamos a reloguear con otro nombre que este disponible.", PlayerName(playerid));
		ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_PASSWORD, mHeader, global_str, ""#CBLANCO"Aceptar", ""#CBLANCO"Salir");
	}else{
		ClearChat(playerid, 100);
		format(global_str, sizeof(global_str), ""#CBLANCO"Bienvenido a "#CNAMESV""#SERVER_NAME" "#CBLANCO"%s!\n\nAl Finalizar realizaras un pequeño Test para determinar tu nivel de Rol.\nEsperamos te diviertas dentro de la Comunidad, no olvides respetar las Reglas\ny jugar de manera sana, cualquier falta puede conllevar a una sancion.\n\nSin nada mas que decir; Procedamos a tomar tus datos.\n\nIngresa una contraseña para registrar tu cuenta.", PlayerName(playerid));
		ShowPlayerDialog(playerid, dRegistro, DIALOG_STYLE_PASSWORD, mHeader, global_str, ""#CBLANCO"Aceptar", ""#CBLANCO"Salir");
	}
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{

	/* ############### DON TOUCH ############### */
	#if defined entry_OnPlayerEnterCheckpoint
		return entry_OnPlayerEnterCheckpoint(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerEnterCheckpoint
	#undef OnPlayerEnterCheckpoint
#else
	#define _ALS_OnPlayerEnterCheckpoint
#endif

#define OnPlayerEnterCheckpoint entry_OnPlayerEnterCheckpoint
#if defined entry_OnPlayerEnterCheckpoint
	forward entry_OnPlayerEnterCheckpoint(playerid);
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new VarAge = strval(inputtext);

	switch(dialogid){
		case dLogin:
		{
			if(!response)
			{
				new megahash[64 + 1];
				SHA256_PassHash(inputtext, "123h1h23hh", megahash, 64);
				if(strcmp(PlayerData[playerid][jPass], megahash, false) == 0)
				{
					mysql_tquery(DB, global_str, "PlayerIngreso", "d", playerid);
					SendClientMessage(playerid, -1, "Bienvenido de nuevo, te echabamos de menos.");
				}
				else
				{
					ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_PASSWORD, mHeader, mError,  ""#CBLANCO"Entrar", ""#CBLANCO"Salir");
				}
			}
			else Kick(playerid);
		}
        case dRegistro:{
            if(!response) return Kick(playerid);
            {
				SHA256_PassHash(inputtext, "123h1h23hh", PlayerData[playerid][TempHash], 64);
                ShowPlayerDialog(playerid, dGender, DIALOG_STYLE_MSGBOX, mHeader, ""#CBLANCO"Cuentanos; ¿Eres un Hombre o una Mujer?", "Masculino", "Femenino");
            }
        }
		case dGender:
		{
		    if(response)
			{
				PlayerData[playerid][jSexo] = 1;
				PlayerData[playerid][jRopa] = 46;
			}
		    else if(!response)
		    {
				PlayerData[playerid][jSexo] = 2;
				PlayerData[playerid][jRopa] = 12;
			}
			new strAge[120+1];
			format(strAge, sizeof(strAge), ""#CBLANCO"Muy bien %s!\nAhora cuentanos. ¿Que edad tienes?", PlayerName(playerid), strAge);
			ShowPlayerDialog(playerid, dEdad, DIALOG_STYLE_INPUT, mHeader, strAge, "Aceptar", "Cancelar");
		}
		case dEdad:
		{
			if(!response) return Kick(playerid);
			format(global_str, sizeof(global_str), ""#CNAMESV"%s"#CBLANCO"; Solo puedes ingresar "#CAMARILLO"valores numericos"#CBLANCO".\nLa edad minima es de "#CAMARILLO"<13> "#CBLANCO"y la maxima de "#CAMARILLO"<50>"#CBLANCO".\n\nPor favor ingresa una "#CAMARILLO"Edad Valida"#CBLANCO".\n¿Qué edad tienes? Cuentanos.", PlayerName(playerid), global_str);
		    if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, dEdad, DIALOG_STYLE_INPUT, ""#CBLANCO"A Continuación dinos tu edad.\t", global_str, "Aceptar", "Cancelar");
			if(strval(inputtext) < 13) return ShowPlayerDialog(playerid, dEdad, DIALOG_STYLE_INPUT, ""#CBLANCO"A Continuación dinos tu edad.\t", global_str, "Aceptar", "Cancelar");
			if(VarAge < 13 || VarAge > 50) return ShowPlayerDialog(playerid, dEdad, DIALOG_STYLE_INPUT, ""#CBLANCO"A Continuación dinos tu edad.\t", global_str, "Aceptar", "Cancelar");

			PlayerData[playerid][jEdad] = VarAge;
			format(global_str, sizeof(global_str), ""#CBLANCO"Excelente %s! Ya queda muy poco; A Continuacion deberas escoger\nuna "#CAMARILLO"Nacionalidad"#CBLANCO", de acuerdo a tu personaje, esta puede ser\ntu nacionalidad IC, como OOC.", PlayerName(playerid));
			ShowPlayerDialog(playerid, dAlertCountry, DIALOG_STYLE_MSGBOX, mHeader, global_str, "Aceptar", "Cancelar");
			
		}
		case dAlertCountry:
		{
			if(!response) return Kick(playerid);
			ShowPlayerDialog(playerid, dCountry, DIALOG_STYLE_LIST, mHeader, "America del Sur.\nAmerica Del Norte.", "Aceptar", "Cancelar");
		}

		case dCountry:
		{
		    if(!response) return 0;
		    switch(listitem)
		    {
				case 0:
				{
					ShowPlayerDialog(playerid, dCountryAMS, DIALOG_STYLE_LIST, mHeader, COUNTRY_AMS, "Seleccionar", "");
					printf("Seleccionaste: %s", COUNTRY_AMS);
				}
				case 1:
				{
					ShowPlayerDialog(playerid, dCountryAMS, DIALOG_STYLE_LIST, mHeader, COUNTRY_AMS, "Seleccionar", "");
				}
			}
		}

		case dCountryAMS:
		{
		    if(!response) return 1;
		    ShowPlayerDialog(playerid, dFinish, DIALOG_STYLE_MSGBOX, mHeader, ""#CVERDE"Registro Finalizado; "#CBLANCO"Recuerda cumplir las\nnormas o podrias ser sancionado.", "Continuar", "");
		}
		case dCountryAMN:
		{
		    if(!response) return 1;
		    ShowPlayerDialog(playerid, dFinish, DIALOG_STYLE_MSGBOX, mHeader, ""#CVERDE"Registro Finalizado; "#CBLANCO"Recuerda cumplir las\nnormas o podrias ser sancionado.", "Continuar", "");
		}

		//ShowPlayerDialog(playerid, dFinish, DIALOG_STYLE_MSGBOX, mHeader, ""#CVERDE"Registro Finalizado; "#CBLANCO"Recuerda cumplir las\nnormas o podrias ser sancionado.", "Continuar", "");
		case dFinish:
		{
			if(response)
			{
				mysql_format(DB, global_str, sizeof global_str, "INSERT INTO users (Name, Password, Ropa, Sexo, Edad, Score, Ciudad) VALUES ('%e', '%e', '%i', '%i', '%i', '5', '%e')",
				PlayerName(playerid),
				PlayerData[playerid][TempHash],
				PlayerData[playerid][jSexo],
				PlayerData[playerid][jRopa],
				PlayerData[playerid][jEdad],
				PlayerData[playerid][jScore],
				PlayerData[playerid][jCiudad]);
				mysql_query(DB, global_str);

				printf("- %s Se ha registrado por Primera vez en el Servidor.\nPasara a mirar la Introduccion..", PlayerName(playerid));
				StartIntro(playerid);
			}
			else
			{
				Kick(playerid);
			}
		}
	}
	/* ############### DON TOUCH ############### */
	#if defined entry_OnDialogResponse
		return entry_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif

#define OnDialogResponse entry_OnDialogResponse
#if defined entry_OnDialogResponse
	forward entry_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    /*new bool:cancel = (clickedid == Text:INVALID_TEXT_DRAW);

    if(IsPlayerConnected(playerid))
    {
		if(cancel)
		{
			Kick(playerid);
			return #IgnoredThis#(playerid);
		}
		else if(clickedid == #IgnoredThis#)
		{
			
		}
    }*/
	/* ############### DON TOUCH ############### */
	#if defined entry_OnPlayerClickTextDraw
		return entry_OnPlayerClickTextDraw(playerid, Text:clickedid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif

#define OnPlayerClickTextDraw entry_OnPlayerClickTextDraw
#if defined entry_OnPlayerClickTextDraw
	forward entry_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

forward PlayerIngreso(playerid); public PlayerIngreso(playerid) 
{
    if(cache_num_rows () == 0)
    {
        SendClientMessage(playerid, -1, "Contraseña incorrecta, ingresala nuevamente.");
        ShowPlayerDialog(playerid, dLogin, DIALOG_STYLE_PASSWORD, mHeader, mError,  ""CBLANCO"Entrar", ""CBLANCO"Salir");
    }
    else
    {
        cache_get_value_int(0, "Ropa", PlayerData[playerid][jRopa]);
        cache_get_value_int(0, "Sexo", PlayerData[playerid][jSexo]);
		cache_get_value_int(0, "Score", PlayerData[playerid][jScore]);
		cache_get_value_int(0, "Score", PlayerData[playerid][jCiudad]);

		SetPlayerScore(playerid, PlayerData[playerid][jScore]);

        SetPVarInt(playerid, "Logueado", 1);
        AccountLoaded(playerid);
    }
    return 1;
}

forward AccountLoaded(playerid); public AccountLoaded(playerid){
    TogglePlayerSpectating(playerid, false);

    format(PlayerData[playerid][jName], 25, "%s", PlayerName(playerid));
	SetSpawnInfo(playerid, 0, PlayerData[playerid][jRopa], 1397.3853, -1577.9474, 14.4706, 0.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
    return 1;
}

forward StartingIntro(playerid); public StartingIntro(playerid)
{
	/*# Verificamos que el jugador esta realizado la Introduccion #*/
	MakingTutorial[playerid] = true;
	/*# Cargamos la Cinematica #*/
	LoadCutScene(playerid);
	/*# Inicio de Introduccion | Cada simulacion cambiara cada 5 segundos a la siguiente #*/
	SetTimerEx("StartBox1", 0, false, "d", playerid);
	return 1;
}

forward StartBox1(playerid); public StartBox1(playerid){NotiBox(playerid, PlayerName(playerid), "Oh no! Mierda, Mierda! Se incendia mi casa!"); SetTimerEx("StartBox2", 5000, false, "d", playerid); return 1;}
forward StartBox2(playerid); public StartBox2(playerid){NotiBox(playerid, PlayerName(playerid), "Mis cosas carajo! He perdido mi trabajo hoy.\n\n¿y ahora esto?"); SetTimerEx("StartBox3", 5000, false, "d", playerid); return 1;}

forward StartBox3(playerid); public StartBox3(playerid){
	SetPlayerCameraPos(playerid, 2096.0591, -1126.9547, 32.9660); SetPlayerCameraLookAt(playerid, 2095.1418, -1126.5475, 32.4278);
	NotiBox(playerid, "Historia.", "Debido al incendio has perdido las pertenencias que se encontraban dentro de la casa.");
	SetTimerEx("StartBox4", 5000, false, "d", playerid); return 1;
}

forward StartBox4(playerid); public StartBox4(playerid){
	NotiBox(playerid, "Historia.", "Parece ser que el incendio consumio tus muebles y documentos."); 
	SetTimerEx("StartBox5", 5000, false, "d", playerid); return 1;
}

forward StartBox5(playerid); public StartBox5(playerid){NotiBox(playerid, "Historia", "Debido a que no tienes empleo, deberas buscar uno nuevo."); return 1;}

/*forward FinishedIntro(playerid);
public FinishedIntro(playerid)
{
	//SetTimerEx("FinishedIntro", 30, false, "d", playerid);

	MakingTutorial[playerid] = false;
	TogglePlayerSpectating(playerid, false);
	//Bienvenida
	SendClientMessage(playerid,-1,"- "#CBLANCO"!Felicidades; Bienvenido a "mHeader""#CBLANCO", disfruta tu estancia!");

    //Spawn de Registro
	SetPVarInt(playerid, "Logueado", 1);

	//Stats
	SetPlayerScore(playerid, 1);

	SetSpawnInfo(playerid, 0, PlayerData[playerid][jRopa], 1397.3853, -1577.9474, 14.4706, 0.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}*/

stock SavePlayer(playerid){
    mysql_format(DB, global_str, sizeof(global_str), "UPDATE users SET Score = %d WHERE ID = %d LIMIT 1",
    PlayerData[playerid][jScore],
    PlayerData[playerid][ID]);

    mysql_tquery(DB, global_str);
    return 1;
}

StartIntro(playerid)
{
	PlayerFreeze(playerid, 30);
	SetTimerEx("StartingIntro", 0, false, "d", playerid);
	return 1;
}