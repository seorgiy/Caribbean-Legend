#include "scripts\utils.c"

// boal -->
#define CARDS_RULE "Las reglas son simples.  Blackjack. 36 cartas, de seis a ases. El as vale 11 puntos, los reyes - 4, el señor (caballo caballero) - 3, Nobile (soldado de a pie) - 2, el resto tiene el mismo valor que el escrito. Tu objetivo es conseguir 21 puntos. Haz clic en el mazo para coger una carta más. Cada carta es una apuesta. Haz clic en un retrato en la parte superior derecha para terminar tu turno. Necesitas suficiente dinero para al menos tres apuestas si quieres jugar. Presiona esc o una cruz si has terminado."
#define DICE_RULE "Dados. Cinco para cada jugador. Puedes derribar a los cinco o a cualquiera de ellos pero sólo una vez. Cada dado es una apuesta. Tu objetivo es conseguir la máxima puntuación.\nAquí van las combinaciones: dúo (2), dos dúos (2+2), tríada (3), full (3+2), cuadrado (4), calle (dados en fila) y póker (5). \n Haz clic en un recipiente para lanzar, haz clic en un dado para derribar este dado en particular, haz clic en un retrato para terminar tu turno (en caso de que no necesites derribar o no tengas suficiente dinero para hacerlo)."
#define MAX_TITLENEXTRATE 13 // счетчик для званий
#define MAX_TITLE 5
// boal <--

object Address_Form;

void Set_inDialog_Attributes()
{
	ref The_Character_is;

	The_Character_is = GetMainCharacter();
	if (!CheckAttribute(The_Character_is, "sex") || The_Character_is.sex == "man")
	{
		Address_Form.Spa = "señor";
		Address_Form.Fra = "monsieur";
		Address_Form.Eng = "sir";
		Address_Form.Hol = "mynheer";
		Address_Form.Pir = "sir";
	}
	else
	{
		Address_Form.Spa = "señorita";
		Address_Form.Fra = "mademoiselle";
		Address_Form.Eng = "miss";
		Address_Form.Hol = "lady";
		Address_Form.Pir = "miss";
	}
	Address_Form.Spa.Title1 = "Corsario";
	Address_Form.Fra.Title1 = "Privateer";
	Address_Form.Eng.Title1 = "Caper";
	Address_Form.Hol.Title1 = "Filibuster";
	Address_Form.Pir.Title1 = "Pirate";

	Address_Form.Spa.Title2 = "Comandante";
	Address_Form.Fra.Title2 = "Commander";
	Address_Form.Eng.Title2 = "Commander";
	Address_Form.Hol.Title2 = "Commander";
	Address_Form.Pir.Title2 = "Commander";

	Address_Form.Spa.Title3 = "Capitán";
	Address_Form.Fra.Title3 = "Captain";
	Address_Form.Eng.Title3 = "Captain";
	Address_Form.Hol.Title3 = "Captain";
	Address_Form.Pir.Title3 = "Captain";

	Address_Form.Spa.Title4 = "Comodoro";
	Address_Form.Fra.Title4 = "Commodore";
	Address_Form.Eng.Title4 = "Commodore";
	Address_Form.Hol.Title4 = "Commodore";
	Address_Form.Pir.Title4 = "Commodore";

	Address_Form.Spa.Title5 = "Almirante";
	Address_Form.Fra.Title5 = "Admiral";
	Address_Form.Eng.Title5 = "Admiral";
	Address_Form.Hol.Title5 = "Admiral";
	Address_Form.Pir.Title5 = "Admiral";

	Address_Form.Spa.woman = "señora";
	Address_Form.Fra.woman = "madame";
	Address_Form.Eng.woman = "missis";
	Address_Form.Hol.woman = "lady";
	Address_Form.Pir.woman = "missis";

	Address_Form.Spa.man = "señor";
	Address_Form.Fra.man = "monsieur";
	Address_Form.Eng.man = "sir";
	Address_Form.Hol.man = "mynheer";
	Address_Form.Pir.man = "sir";
	/*switch (The_Character_is.id)
	{
		case "Blaze":

			Address_Form.Spa = GlobalStringConvert("Address_Form_Spa");
			Address_Form.Fra = GlobalStringConvert("Address_Form_Fra");
			Address_Form.Eng = GlobalStringConvert("Address_Form_Eng");
			Address_Form.Por = GlobalStringConvert("Address_Form_Por");
			Address_Form.Hol = GlobalStringConvert("Address_Form_Hol");
			return;
		break;

		case "Beatriss":

			Address_Form.Spa = "Señorita";
			Address_Form.Fra = "Mademoiselle";
			Address_Form.Eng = "Miss";
			Address_Form.Por = "Senhorita";
			Address_Form.Hol = "Juffrouw";
			return;
		break;
	}
	trace("ERROR: Player Character is not defined - can't select address form");
	*/
}

// boal -->

string RandSwear()
{
	switch (rand(14))
	{
	case 0:
		return "¡Caramba! ";
		break;

	case 1:
		return "¡Maldita sea! ";
		break;

	case 2:
		return "¡Maldición! ";
		break;

	case 3:
		return "¡Mierda! ";
		break;

	case 4:
		return "No me jodas... ";
		break;

	case 5:
		return "¡Por los malditos tiburones! ";
		break;

	case 6:
		return "¡¡¡Argh!!! ";
		break;

	case 7:
		return "¡¡Qué demonios!! ";
		break;

	case 8:
		return "¡Alle hagel! "; // ñòàíäàðòíîå ïèðàòñêîå "òâîþ ìàòü"
		break;

	case 9:
		return "¡Maldito sea! ";
		break;

	case 10:
		return "¡Mierda! ";
		break;

	case 11:
		return "Maldito seas... ";
		break;

	case 12:
		return "¡Vete a la mierda! ";
		break;

	case 13:
		return "¡Maldita sea! ";
		break;

	case 14:
		return "¡Qué me aspen! ";
		break;
	}
}

// navy --> вынес простые восклицания,
// т.к. "О, Боже!!! Я вырежу тебе сердце" звучит мягко говоря странно :)
string RandExclamation()
{
	switch (rand(2))
	{
	case 0:
		return "¡Oh, Señor! ";
		break;

	case 1:
		return "¡Oh, Cielos! ";
		break;

	case 2:
		return "¡Santa Virgen! ";
		break;
	}
}
// navy <--
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                Выбор фраз для диалога
////////////////////////////////////////////////////////////////////////////////////////////////////////
// boal 13.03.2004 -->
string RandPhraseSimple(string Var1, string Var2);
{
	int RandP;
	RandP = Rand(1);
	switch (RandP)
	{
	case 0:
		return /*"First phrase selected" + */ Var1;
		break;

	case 1:
		return /*"Second phrase selected" + */ Var2;
		break;
	}
	return "ERROR";
}
// выбор фразы из трех
string LinkRandPhrase(string Var1, string Var2, string Var3)
{
	int RandP;
	RandP = Rand(2);
	switch (RandP)
	{
	case 0:

		return /*"First phrase selected" + */ Var1;

		break;

	case 1:

		return /*"Second phrase selected" + */ Var2;

		break;

	case 2:

		return /*"Third phrase selected" + */ Var3;

		break;
	}
	return "ERROR";
}

string NationKingsCrown(ref Character)
{
	switch (sti(Character.nation))
	{
	case ENGLAND:
		return "trono inglés";
		break;
	case FRANCE:
		return "corona francesa";
		break;
	case SPAIN:
		return "corona española";
		break;
	case HOLLAND:
		return "Reino de Holanda";
		break;
	case PIRATE:
		return "Hermanos de la Costa";
		break;
	}
}
string NationKingsName(ref NPChar)
{
	switch (sti(NPChar.nation))
	{
	case ENGLAND:
		return "Su Majestad Charles II de Inglaterra";
		break;
	case FRANCE:
		return "Su Majestad Louis XIV de Francia";
		break;
	case SPAIN:
		return "Su Católica Majestad Carlos II de España";
		break;
	case HOLLAND:
		return "Su Majestad William III de Holanda";
		break;
	case PIRATE:
		return "Los Hermanos de la Costa";
		break;
	}
}

string NationNameMan(int pNation)
{
	switch (pNation)
	{
	case ENGLAND:
		return "Inglés";
		break;
	case FRANCE:
		return "Francés";
		break;
	case SPAIN:
		return "Español";
		break;
	case HOLLAND:
		return "Holandés";
		break;
	case PIRATE:
		return "un pirata";
		break;
	}
}
// boal 13.03.2004 <--
string NationNamePeople(int pNation)
{
	switch (pNation)
	{
	case ENGLAND:
		return "Ingleses";
		break;
	case FRANCE:
		return "Franceses";
		break;
	case SPAIN:
		return "Españoles";
		break;
	case HOLLAND:
		return "Holandeses";
		break;
	case PIRATE:
		return "piratas";
		break;
	}
}

string NationNamePeopleAcc(int pNation)
{
	switch (pNation)
	{
	case ENGLAND:
		return "Ingleses";
		break;
	case FRANCE:
		return "Franceses";
		break;
	case SPAIN:
		return "Españoles";
		break;
	case HOLLAND:
		return "Holandeses";
		break;
	case PIRATE:
		return "piratas";
		break;
	}
}

string NationNameAblative(int iNation) // творительный падеж
{
	switch (iNation)
	{
	case ENGLAND:
		return "Inglaterra";
		break;
	case FRANCE:
		return "Francia";
		break;
	case SPAIN:
		return "España";
		break;
	case HOLLAND:
		return "Holanda";
		break;
	case PIRATE:
		return "los piratas";
		break;
	}
}

string NationNameNominative(int iNation) // именительный падеж
{
	switch (iNation)
	{
	case ENGLAND:
		return "Inglaterra";
		break;
	case FRANCE:
		return "Francia";
		break;
	case SPAIN:
		return "España";
		break;
	case HOLLAND:
		return "Holanda";
		break;
	case PIRATE:
		return "Hermanos de la Costa";
		break;
	}
}

string NationNameGenitive(int iNation) // родительный падеж
{
	switch (iNation)
	{
	case ENGLAND:
		return "Inglaterra";
		break;
	case FRANCE:
		return "Francia";
		break;
	case SPAIN:
		return "España";
		break;
	case HOLLAND:
		return "Holanda";
		break;
	case PIRATE:
		return "los piratas";
		break;
	}
}

///////Часто будет использоваться поэтому заношу сюда
string NationEuropaTown(int iNation)
{
	switch (iNation)
	{
	case ENGLAND:
		return "London";
		break;
	case FRANCE:
		return "Le Roshele";
		break;
	case SPAIN:
		return "Sevilla";
		break;
	case PIRATE:
		return "Tortuga";
		break;
	case HOLLAND:
		return "Amsterdam";
		break;
	}
}
string GetCityName(string city) // имена городов по аттрибуту char.city
{
	string ret;
	int nFile = LanguageOpenFile("LocLables.txt");

	ret = LanguageConvertString(nFile, city + " Town")
		LanguageCloseFile(nFile);

	return ret;
}

string GetPortByCityName(string city) // имена портов по городов по аттрибуту char.city
{
	switch (city)
	{
	case "Bridgetown":
		return "Bridgetown_town";
		break;
	case "SanJuan":
		return "SanJuan_town";
		break;
	case "Santiago":
		return "Santiago_town";
		break;
	case "PuertoPrincipe":
		return "PuertoPrincipe_port";
		break;
	case "SentJons":
		return "SentJons_town";
		break;
	case "PortRoyal":
		return "PortRoyal_town";
		break;
	case "FortOrange":
		return "Shore35";
		break;
	case "Villemstad":
		return "Villemstad_town";
		break;
	case "BasTer":
		return "BasTer_town";
		break;
	case "LaVega":
		return "LaVega_port";
		break;
	case "Bridgetown":
		return "Bridgetown_town";
		break;
	case "SantoDomingo":
		return "SantoDomingo_town";
		break;
	case "PortPax":
		return "PortPax_town";
		break;
	case "Pirates":
		return "Pirates_town";
		break;
	case "FortFrance":
		return "FortFrance_town";
		break;
	case "LeFransua":
		return "LeFransua_town";
		break;
	case "Havana":
		return "Havana_town";
		break;
	case "Charles":
		return "Charles_town";
		break;
	case "PortoBello":
		return "PortoBello_town";
		break;
	case "PortSpein":
		return "PortSpein_town";
		break;
	case "Tortuga":
		return "Tortuga_town";
		break;
	case "Marigo":
		return "Marigo_town";
		break;
	case "Panama":
		return "Panama_town";
		break;
	case "Cartahena":
		return "Cartahena_town";
		break;
	case "Maracaibo":
		return "Maracaibo_town";
		break;
	case "Caracas":
		return "Caracas_town";
		break;
	case "Cumana":
		return "Cumana_town";
		break;
	case "SantaCatalina":
		return "SantaCatalina_town";
		break;
	case "Beliz":
		return "Beliz_town";
		break;
	case "LosTeques":
        return "Shore20";
		break;
	}
	return "";
}

string GetMayakByCityName(string city) // получить id маяка по названию города
{
	switch (city)
	{
	case "Bridgetown":
		return "Mayak2";
		break;
	case "Santiago":
		return "Mayak9";
		break;
	case "PortRoyal":
		return "Mayak3";
		break;
	case "BasTer":
		return "Mayak4";
		break;
	case "SantoDomingo":
		return "Mayak8";
		break;
	case "PortPax":
		return "Mayak7";
		break;
	case "Havana":
		return "Mayak10";
		break;
	case "Charles":
		return "Mayak5";
		break;
	case "PortSpein":
		return "Mayak1";
		break;
	case "Tortuga":
		return "Mayak6";
		break;
	case "Cartahena":
		return "Mayak11";
		break;
	}
	return "";
}

string GetCityNameByMayak(string mayak) // получить id города по маяку
{
	switch (mayak)
	{
	case "Mayak1":
		return "PortSpein";
		break;
	case "Mayak2":
		return "Bridgetown";
		break;
	case "Mayak3":
		return "PortRoyal";
		break;
	case "Mayak4":
		return "BasTer";
		break;
	case "Mayak5":
		return "Charles";
		break;
	case "Mayak6":
		return "Tortuga";
		break;
	case "Mayak7":
		return "PortPax";
		break;
	case "Mayak8":
		return "SantoDomingo";
		break;
	case "Mayak9":
		return "Santiago";
		break;
	case "Mayak10":
		return "Havana";
		break;
	case "Mayak11":
		return "Cartahena";
		break;
	}
	return "";
}

string GetIslandByArealName(string areal)
{
	string sAreal = areal;
	if (areal == "PortoBello" || areal == "Panama" || areal == "Cartahena" ||
		areal == "Maracaibo" || areal == "Caracas" || areal == "Cumana" || areal == "SantaCatalina" ||
		areal == "Beliz" || areal == "Tenotchitlan")
	{
		sAreal = "Mein";
	}
	return sAreal;
}

string GetIslandByCityName(string city) // имена острова по городу по аттрибуту char.city
{
	switch (city)
	{
	case "Bridgetown":
		return "Barbados";
		break;
	case "SanJuan":
		return "PuertoRico";
		break;
	case "Santiago":
		return "Cuba";
		break;
	case "PuertoPrincipe":
		return "Cuba";
		break;
	case "SentJons":
		return "Antigua";
		break;
	case "PortRoyal":
		return "Jamaica";
		break;
	case "FortOrange":
		return "Jamaica";
		break;
	case "Villemstad":
		return "Curacao";
		break;
	case "BasTer":
		return "Guadeloupe";
		break;
	case "LaVega":
		return "Hispaniola";
		break;
	case "SantoDomingo":
		return "Hispaniola";
		break;
	case "PortPax":
		return "Hispaniola";
		break;
	case "Pirates":
		return "Bermudes";
		break;
	case "FortFrance":
		return "Martinique";
		break;
	case "LeFransua":
		return "Martinique";
		break;
	case "Havana":
		return "Cuba";
		break;
	case "Charles":
		return "Nevis";
		break;
	case "PortoBello":
		return "Mein";
		break;
	case "PortSpein":
		return "Trinidad";
		break;
	case "Tortuga":
		return "Tortuga";
		break;
	case "Marigo":
		return "SentMartin";
		break;
	case "Panama":
		return "Mein";
		break;
	case "Cartahena":
		return "Mein";
		break;
	case "Maracaibo":
		return "Mein";
		break;
	case "Caracas":
		return "Mein";
		break;
	case "Cumana":
		return "Mein";
		break;
	case "SantaCatalina":
		return "Mein";
		break;
	case "Beliz":
		return "Mein";
		break;
	case "Tenotchitlan":
		return "Mein";
		break;
	case "LosTeques":
        return "Mein";
		break;
	case "IslaMona":
		return "IslaMona";
		break;
	}
	return "";
}

string GetArealByCityName(string city) // ареал по городу по аттрибуту char.city
{
	switch (city)
	{
	case "Bridgetown":
		return "Barbados";
		break;
	case "SanJuan":
		return "PuertoRico";
		break;
	case "Santiago":
		return "Cuba1";
		break;
	case "PuertoPrincipe":
		return "Cuba1";
		break;
	case "SentJons":
		return "Antigua";
		break;
	case "PortRoyal":
		return "Jamaica";
		break;
	case "FortOrange":
		return "Jamaica";
		break;
	case "Villemstad":
		return "Curacao";
		break;
	case "BasTer":
		return "Guadeloupe";
		break;
	case "LaVega":
		return "Hispaniola1";
		break;
	case "SantoDomingo":
		return "Hispaniola1";
		break;
	case "PortPax":
		return "Hispaniola2";
		break;
	case "Pirates":
		return "Bermudes";
		break;
	case "FortFrance":
		return "Martinique";
		break;
	case "LeFransua":
		return "Martinique";
		break;
	case "Havana":
		return "Cuba2";
		break;
	case "Charles":
		return "Nevis";
		break;
	case "PortoBello":
		return "PortoBello";
		break;
	case "PortSpein":
		return "Trinidad";
		break;
	case "Tortuga":
		return "Tortuga";
		break;
	case "Marigo":
		return "SentMartin";
		break;
	case "Panama":
		return "Panama";
		break;
	case "Cartahena":
		return "Cartahena";
		break;
	case "Maracaibo":
		return "Maracaibo";
		break;
	case "Caracas":
		return "Caracas";
		break;
	case "Cumana":
		return "Cumana";
		break;
	case "SantaCatalina":
		return "SantaCatalina";
		break;
	case "Beliz":
		return "Beliz";
		break;
	case "Tenotchitlan":
		return "Tenotchitlan";
		break;
	case "IslaMona":
		return "IslaMona";
		break;
	case "LosTeques":
        return "LosTeques";
		break;
	}
	return "";
}

string GiveArealByLocation(ref location)
{
	string sAreal;
	if (CheckAttribute(location, "MustSetReloadBack"))
		return "none";
	if (CheckAttribute(location, "fastreload"))
	{
		sAreal = GetArealByCityName(location.fastreload);
		return sAreal;
	}
	if (CheckAttribute(location, "parent_colony"))
	{
		sAreal = GetArealByCityName(location.parent_colony);
		return sAreal;
	}
	if (!CheckAttribute(location, "islandId"))
		return "none";
	if (location.islandId == "Cuba" || location.islandId == "Hispaniola" || location.islandId == "Mein")
	{
		if (!CheckAttribute(location, "islandIdAreal"))
			return "none";
		sAreal = location.islandIdAreal;
	}
	else
		sAreal = location.islandId;
	return sAreal;
}

// выбор куда идти  по острову даем город (главный город острова с портом)
string GetCityNameByIsland(string CurIslandId)
{
	string TargetLocation;

	TargetLocation = "None";

	switch (CurIslandId)
	{
	case "Antigua":
		TargetLocation = "SentJons";
		break;
	case "Bermudes":
		TargetLocation = "Pirates";
		break;
	case "Barbados":
		TargetLocation = "Bridgetown";
		break;
	case "Beliz":
		TargetLocation = "Beliz";
		break;
	case "Cuba1":
		TargetLocation = "Santiago";
		break;
	case "Cuba2":
		TargetLocation = "Havana";
		break;
	case "Cumana":
		TargetLocation = "Cumana";
		break;
	case "Caracas":
		TargetLocation = "Caracas";
		break;
	case "Curacao":
		TargetLocation = "Villemstad";
		break;
	case "Cartahena":
		TargetLocation = "Cartahena";
		break;
	case "Guadeloupe":
		TargetLocation = "BasTer";
		break;
	case "Hispaniola1":
		TargetLocation = "SantoDomingo";
		break;
	case "Hispaniola2":
		TargetLocation = "PortPax";
		break;
	case "Jamaica":
		TargetLocation = "PortRoyal";
		break;
	case "Maracaibo":
		TargetLocation = "Maracaibo";
		break;
	case "Martinique":
		TargetLocation = "FortFrance";
		break;
	case "SentMartin":
		TargetLocation = "Marigo";
		break;
	case "Nevis":
		TargetLocation = "Charles";
		break;
	case "PuertoRico":
		TargetLocation = "SanJuan";
		break;
	case "PortoBello":
		TargetLocation = "PortoBello";
		break;
	case "Pearl":
		TargetLocation = "none";
		break;
	case "Panama":
		TargetLocation = "Panama";
		break;
	case "SantaCatalina":
		TargetLocation = "SantaCatalina";
		break;
	case "Terks":
		TargetLocation = "none";
		break;
	case "Dominica":
		TargetLocation = "none";
		break;
	case "Caiman":
		TargetLocation = "none";
		break;
	case "Tortuga":
		TargetLocation = "Tortuga";
		break;
	case "Trinidad":
		TargetLocation = "PortSpein";
		break;
	case "Tenotchitlan":
		TargetLocation = "none";
		break;
	case "IslaMona":
		TargetLocation = "IslaMona";
		break;
	}
	return TargetLocation;
}

string TimeGreeting()
{
	if (GetHour() >= 18 && GetHour() < 23)
	{
		return "Buenas tardes";
	}
	if (GetHour() >= 6 && GetHour() < 12)
	{
		return "Buenos dias";
	}
	if (GetHour() >= 12 && GetHour() < 18)
	{
		return "Buena mañana";
	}
	if (GetHour() >= 23 || GetHour() < 6)
	{
		return "Buenas noches";
	}
	return "¡Hola!";
}

string Greeting()
{
	return "Hola";
}

string Goodbye()
{
	if (GetHour() >= 23 || GetHour() < 6)
	{
	   return "Buenas noches";
	}
	return RandPhraseSimple("Adiós", "Hasta la vista");
}

// выбор фразы от репутации
string PCharRepPhrase(string bad, string good)
{
	if (makeint(pchar.reputation.nobility) < 41)
	{
		return bad;
	}
	else
	{
		return good;
	}
}
// boal для НПС
string NPCharRepPhrase(ref _pchar, string bad, string good)
{
	if (makeint(_pchar.reputation) < 41)
	{
		return bad;
	}
	else
	{
		return good;
	}
}

////////// поиск нужного перса для диалога
string GetCharIDByParam(string attrPresent1, string attr2, string val2)
{
	ref rCharacter; // ищем
	int n = GetCharIDXByParam(attrPresent1, attr2, val2);

	if (n > 0)
	{
		makeref(rCharacter, Characters[n]);
		return rCharacter.id;
	}
	return "";
}
int GetCharIDXByParam(string attrPresent1, string attr2, string val2)
{
	ref rCharacter; // ищем
	int n;

	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, attrPresent1))
		{
			if (rCharacter.(attr2) == val2)
				return n;
		}
	}
	return -1;
}
int GetCharIDXForTownAttack(string attrPresent1)
{
	ref rColony; // ищем
	int n;
	bool ok;

	for (n = 0; n < MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		ok = false;
		if (CheckAttribute(rColony, "Default.BoardLocation2") && rColony.Default.BoardLocation2 == attrPresent1)
		{
			ok = true;
		}
		if (rColony.Default.BoardLocation == attrPresent1 || ok)
		{
			if (rColony.HeroOwn == true)
			{
				return -1;
			}

			return GetFortCommanderIdx(rColony.id);
		}
	}
	return -1;
}
// обращение НПС к ГГ, зависит от нации НПС
string GetAddress_Form(ref NPChar)
{
	string attr = NationShortName(sti(NPChar.nation));
	return address_form.(attr);
}
// обращение ГГ к НПС, зависит от нации НПС и его пола
string GetAddress_FormToNPC(ref NPChar)
{
	string attr = NationShortName(sti(NPChar.nation));
	string attr2 = NPChar.sex;
	// проверка на скелетов
	if (attr2 != "woman")
	{
		attr2 = "man";
	}
	return address_form.(attr).(attr2);
}
string GetAddress_FormTitle(int nation, int num)
{
	string attr = NationShortName(nation);
	string attr2 = "Title" + num;
	string ret = XI_ConvertString("NoTitle");
	if (CheckAttribute(address_form, attr + "." + attr2))
	{
		ret = address_form.(attr).(attr2);
	}
	return ret;
}

bool isCityHasFort(string _city)
{
	int iTest = FindColony(_city); // город
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		if (!CheckAttribute(rColony, "HasNoFort"))
			return true;
	}
	return false;
}

string GetCityFrom_Sea(string _city)
{
	int iTest = FindColony(_city); // город
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		return rColony.from_sea;
	}
	return "";
}
// boal <--

// eddy. кто по профессии (только для типовых статиков, не фантомов). sPrefix - приставка для падежей: Gen, Dat..
string GetWorkTypeOfMan(ref NPChar, string sPrefix)
{
	string sCity, sTemp;
	sTemp = "desconocido";
	if (CheckAttribute(NPChar, "City"))
	{
		sCity = NPChar.City;
		sTemp = NPChar.id;
		sTemp = strcut(sTemp, strlen(sCity) + 1, strlen(sTemp) - 1);
	}
	return XI_ConvertString("Qué" + sTemp + sPrefix);
}

// Warship 07.08.09 -->
// Количество имен в группе
int GetNamesCount(String _nameType)
{
	aref typeNames;
	makearef(typeNames, Names.Pirates.(_nameType));

	return GetAttributesNum(typeNames);
}

// Случайное имя из определённой группы в определённом падеже
String GetRandName(String _nameType, String _case)
{
	String nameId;

	nameId = "l" + rand(GetNamesCount(_nameType) - 1);

	return GetName(_nameType, nameId, _case);
}

// Вернет имя из группы с указаным Id и в указанном падеже
String GetName(String _nameType, String _nameId, String _nameCase)
{
	return Names.Pirates.(_nameType).(_nameId).(_nameCase);
}

// Вернет указанное имя в другом падеже, поиск по именам группы _nameType
String ChangeNameCaseEx(String _nameType, String _name, String _fromCase, String _toCase)
{
	aref typeNames;
	String nameId;

	makearef(typeNames, Names.Pirates.(_nameType));

	for (int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;

		if (GetName(_nameType, nameId, _fromCase) == _name)
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}

	return "";
}

// Тоже самое, что и выше, только меньше параметров - ищет само
String ChangeNameCase(String _nameType, String _name, String _toCase)
{
	aref typeNames;
	String nameId;

	makearef(typeNames, Names.Pirates.(_nameType));

	for (int i = 0; i < GetAttributesNum(typeNames); i++)
	{
		nameId = "l" + i;

		if (GetName(_nameType, nameId, NAME_NOM) == _name || GetName(_nameType, nameId, NAME_GEN) || GetName(_nameType, nameId, NAME_DAT) ||
			GetName(_nameType, nameId, NAME_ACC) == _name || GetName(_nameType, nameId, NAME_ABL) || GetName(_nameType, nameId, NAME_VOC))
		{
			return GetName(_nameType, nameId, _toCase);
		}
	}

	return "";
}
// <-- Warship 07.08.09
string GetIndianName(int Sex) // Jason имена индейцев
{
	string nameid;

	if (Sex == MAN)
		nameid = "l" + rand(99);
	else
		nameid = "l" + (100 + rand(68));

	return Names.Indian.(nameId);
}
