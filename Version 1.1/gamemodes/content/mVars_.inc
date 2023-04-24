/*# Informacion del Jugador #*/
enum jInfo 
{
    ID,
    jName[25],
    jPass[64 + 1],
    TempHash[64 + 1],
    jRopa,
    jSexo,
    jEdad,
    jScore,
    jCiudad,
    Float:jHealth,
    Float:jArmour
}

new	/*# Global Vars #*/
	MySQL:DB,
	global_str[1024],
    global_str2[1024],
	hash[64 + 1];

new PlayerData[MAX_PLAYERS][jInfo];

new 
    bool:MakingTutorial[MAX_PLAYERS];

new /*# Vars - Introduccion #*/
    ActorIntro[3], FireObj[9], fExtra[3], VehEngine[1],
    Text:tdError[3], Text:tdSVName[2];

new const AnimLibs[][] = {
  "AIRPORT",      "ATTRACTORS",   "BAR",          "BASEBALL",     "BD_FIRE",
  "BEACH",        "BENCHPRESS",   "BF_INJECTION", "BIKE_DBZ",     "BIKED",
  "BIKEH",        "BIKELEAP",     "BIKES",        "BIKEV",        "BLOWJOBZ",
  "BMX",          "BOMBER",       "BOX",          "BSKTBALL",     "BUDDY",
  "BUS",          "CAMERA",       "CAR",          "CAR_CHAT",     "CARRY",
  "CASINO",       "CHAINSAW",     "CHOPPA",       "CLOTHES",      "COACH",
  "COLT45",       "COP_AMBIENT",  "COP_DVBYZ",    "CRACK",        "CRIB",
  "DAM_JUMP",     "DANCING",      "DEALER",       "DILDO",        "DODGE",
  "DOZER",        "DRIVEBYS",     "FAT",          "FIGHT_B",      "FIGHT_C",
  "FIGHT_D",      "FIGHT_E",      "FINALE",       "FINALE2",      "FLAME",
  "FLOWERS",      "FOOD",         "FREEWEIGHTS",  "GANGS",        "GFUNK",
  "GHANDS",       "GHETTO_DB",    "GOGGLES",      "GRAFFITI",     "GRAVEYARD",
  "GRENADE",      "GYMNASIUM",    "HAIRCUTS",     "HEIST9",       "INT_HOUSE",
  "INT_OFFICE",   "INT_SHOP",     "JST_BUISNESS", "KART",         "KISSING",
  "KNIFE",        "LAPDAN1",      "LAPDAN2",      "LAPDAN3",      "LOWRIDER",
  "MD_CHASE",     "MD_END",       "MEDIC",        "MISC",         "MTB",
  "MUSCULAR",     "NEVADA",       "ON_LOOKERS",   "OTB",          "PARACHUTE",
  "PARK",         "PAULNMAC",     "PED",          "PLAYER_DVBYS", "PLAYIDLES",
  "POLICE",       "POOL",         "POOR",         "PYTHON",       "QUAD",
  "QUAD_DBZ",     "RAPPING",      "RIFLE",        "RIOT",         "ROB_BANK",
  "ROCKET",       "RUNNINGMAN",   "RUSTLER",      "RYDER",        "SCRATCHING",
  "SEX",          "SHAMAL",       "SHOP",         "SHOTGUN",      "SILENCED",
  "SKATE",        "SMOKING",      "SNIPER",       "SNM",          "SPRAYCAN",
  "STRIP",        "SUNBATHE",     "SWAT",         "SWEET",        "SWIM",
  "SWORD",        "TANK",         "TATTOOS",      "TEC",          "TRAIN",
  "TRUCK",        "UZI",          "VAN",          "VENDING",      "VORTEX",
  "WAYFARER",     "WEAPONS",      "WOP",          "WUZI"
};

#define COUNTRY_AMS "Argentina\nBolivia\nBrasil\nChile\nColombia\nEcuador\nParaguay\nPerú\nUruguay\nVenezuela"
#define COUNTRY_AMN "Canada\nCosta Rica\nCuba\nEl Salvador\nEstados Unidos\nGuatemala\nHonduras\nMexico\nNicaragua\nPanama\nPuerto Rico\nRepublica Dominicana"


/*======================================================================*/

/* Macros */
#define CALLBACK:%0(%1)     forward %0(%1); public %0(%1)
#define Loop(%0,%1,%2)  	for(new %0 = %2; %0 < %1; %0++)

/* Configuracion Manual Server.cfg */
#define DISCORD_SV          "https://discord.gg/CODIGO"
#define SERVER_NAME         "Redsands - Juego de Rol"
#define MODE_SERVER         "Roleplay/Rol"
#define LANGUAGE_SERVER     "Español/Spanish"

/* Mensajes Predeterminados */
#define mHeader             "\t"#CNAMESV""#SERVER_NAME""
#define mError				""#CERROR"La contraseña ingresada no corresponde\na la registrada en la "#CBLANCO"Base de datos.\n\nIntenta nuevamente."
/*======================================================================*/

main() {   
    print("========================================");
    print("|*- index.pwn Cargado correctamente.   |");
    print("========================================");
    print("|*- Creditos:                          |");
    print("========================================");
    print("|*- KaizerHind - Developer.            |");
    print("|*- D13G0 - Doubts about MySql.        |");
    print("|*- root - Hash password solution.     |");
    print("|*- Galasso - Hash password solution.  |");
    print("========================================");
}