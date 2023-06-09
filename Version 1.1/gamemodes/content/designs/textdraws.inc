public OnGameModeInit()
{
    /*# Nombre del Servidor #*/
    tdSVName[0] = TextDrawCreate(71.600036, 304.986785, "Redsands");
    TextDrawLetterSize(tdSVName[0], 0.363599, 1.400889);
    TextDrawTextSize(tdSVName[0], 0.000000, 272.000000);
    TextDrawAlignment(tdSVName[0], 2);
    TextDrawColor(tdSVName[0], -1);
    TextDrawSetShadow(tdSVName[0], 0);
    TextDrawSetOutline(tdSVName[0], -1);
    TextDrawBackgroundColor(tdSVName[0], 255);
    TextDrawFont(tdSVName[0], 3);
    TextDrawSetProportional(tdSVName[0], 1);

    tdSVName[1] = TextDrawCreate(70.000038, 318.887634, "Juego de Rol");
    TextDrawLetterSize(tdSVName[1], 0.363599, 1.400889);
    TextDrawTextSize(tdSVName[1], 0.000000, 272.000000);
    TextDrawAlignment(tdSVName[1], 2);
    TextDrawColor(tdSVName[1], -1);
    TextDrawSetShadow(tdSVName[1], 0);
    TextDrawSetOutline(tdSVName[1], -1);
    TextDrawBackgroundColor(tdSVName[1], 255);
    TextDrawFont(tdSVName[1], 3);
    TextDrawSetProportional(tdSVName[1], 1);

    /*# Mensaje que se mostrara al Errar un comando. #*/
    tdError[0] = TextDrawCreate(114.899940, 359.144378, "RedBox");
    TextDrawLetterSize(tdError[0], 0.000000, 3.000003);
    TextDrawTextSize(tdError[0], 122.699943, 0.000000);
    TextDrawAlignment(tdError[0], 1);
    TextDrawColor(tdError[0], -1);
    TextDrawUseBox(tdError[0], 1);
    TextDrawBoxColor(tdError[0], -1237303066);
    TextDrawSetShadow(tdError[0], 0);
    TextDrawBackgroundColor(tdError[0], 255);
    TextDrawFont(tdError[0], 1);
    TextDrawSetProportional(tdError[0], 1);

    tdError[1] = TextDrawCreate(125.299774, 359.144378, "BlackBox");
    TextDrawLetterSize(tdError[1], 0.000000, 3.000003);
    TextDrawTextSize(tdError[1], 250.000000, 0.000000);
    TextDrawAlignment(tdError[1], 1);
    TextDrawColor(tdError[1], -1);
    TextDrawUseBox(tdError[1], 1);
    TextDrawBoxColor(tdError[1], 230);
    TextDrawSetShadow(tdError[1], 0);
    TextDrawBackgroundColor(tdError[1], 255);
    TextDrawFont(tdError[1], 1);
    TextDrawSetProportional(tdError[1], 1);

    tdError[2] = TextDrawCreate(127.599998, 363.226745, "Comando incorrecto; Usa /Ayuda para mas informacion.");
    TextDrawLetterSize(tdError[2], 0.217200, 1.027555);
    TextDrawTextSize(tdError[2], 246.000000, 0.000000);
    TextDrawAlignment(tdError[2], 1);
    TextDrawColor(tdError[2], -1);
    TextDrawSetShadow(tdError[2], 0);
    TextDrawBackgroundColor(tdError[2], 255);
    TextDrawFont(tdError[2], 1);
    TextDrawSetProportional(tdError[2], 1);

    /* ############### DON TOUCH ############### */
    #if defined ongame_td_OnGameModeInit
        return ongame_td_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit ongame_td_OnGameModeInit
#if defined ongame_td_OnGameModeInit
    forward ongame_td_OnGameModeInit();
#endif

stock LoadPlayerTextdraw(i)
{
	return 1;
}