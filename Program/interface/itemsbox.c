// Warship 06.09.08 Переделка интерфейса обыска трупов, обмена с офами и сундука
// Большая часть интерфейса - это интерфейс покупки/продажи предметов
// Sith переделка
#event_handler("Control Activation","ProcessInterfaceControls");// гуляем по вкладкам
#define INTERFACETYPE_EXCHANGE_ITEMS		"ExchangeItems"
#define INTERFACETYPE_CHEST					"Chest"
#define INTERFACETYPE_DEADMAN				"Deadman"
#define INTERFACETYPE_BARREL				"Barrel"
#define INTERFACE_ITEMSBOX_CHAR_ARROYSIZE	10

int nCurScrollNum = 0;
int iCharCapacity, iCharQty, iStoreQty, iCurGoodsIdx;
float fCharWeight, fStoreWeight, fWeight;
bool bShowChangeWin = false;
int  BuyOrSell = 0;
string sChrId, sFaceID;
string CurTable, CurRow;
ref refCharacter;
bool bBoxUsed = false; // Сундук-ли?
aref refToChar, arChest, arDeadChar;
string sCharactersArroy[INTERFACE_ITEMSBOX_CHAR_ARROYSIZE] = {"", "", "", "", "", "", "", "", "", ""};

int iTableAddAllBtnX = 570;
int iTableAddAllBtnY = 357;
int iTableAddBtnX = 600;
int iTableAddBtnY = 357;

int iTableRemoveBtnX = 775;
int iTableRemoveBtnY = 357;
int iTableRemoveAllBtnX = 800;
int iTableRemoveAllBtnY = 357;

int iTableAddAllBtnX2 = 1010;
int iTableAddAllBtnY2 = 357;
int iTableAddBtnX2 = 1040;
int iTableAddBtnY2 = 357;

int iTableRemoveBtnX2 = 1215;
int iTableRemoveBtnY2 = 357;
int iTableRemoveAllBtnX2 = 1240;
int iTableRemoveAllBtnY2 = 357;

int iTableInfoX1 = 960;
int iTableInfoY1 = 400;
int iTableInfoX2 = 1450;
int iTableInfoY2 = 860;

int currentTab = 0;// текущий режим сортировки
int iLinesCount = 0;
int iLinesCount2 = 0;
bool validLineClicked = false; // клик ПКМ на существующей строке таблицы, false - строка не выбрана

void InitInterface_RS(string iniName, ref itemsRef, string faceID)
{
	CheckAdmiralMaps(itemsRef); // mitrokosta проверить отличные карты
	sFaceID = faceID;
	String sInterfaceType = sGetInterfaceType();
	if(sInterfaceType == INTERFACETYPE_BARREL)
	{
		StartAboveForm(true);
	}
	else
	{
		StartAboveForm(false); // Warship fix 17.04.09 паузить или нет игру. Если false - не паузить. Нужно для обысков сундуков - кражи
	}	
	string OtherTableCaption;
	refCharacter = GetMainCharacter();
	makearef(refToChar, itemsRef);
	
	if(CheckAttribute(itemsRef, "Money"))
	{
		// Log_TestInfo("Денег - "+itemsRef.money);
	}
	
	LAi_SetActorTypeNoGroup(PChar); // Тип актера - чтоб с нами могли побазарить, если увидели в сундуке
	
	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL) // Если сундук или бочка
	{
		if(!LAi_boarding_process) 
		{
			QuestCheckTakeBoxes(itemsRef); // Перехват
		}
		
		makearef(arChest, itemsRef);
		bBoxUsed = true;
	}
		
	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS || sInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if(sInterfaceType == INTERFACETYPE_DEADMAN) // Если обыск трупа
		{
			makearef(arDeadChar, itemsRef);
		}
		
		iSetCharIDToCharactersArroy(itemsRef); // Не нужно это, но и не помешает
		bBoxUsed = false;
		
		// boal -->
		bool bOk = CheckAttribute(itemsRef, "CanTakeMushket") && CheckAttribute(itemsRef, "IsMushketer");
		if(!CheckAttribute(itemsRef, "HoldEquip") && CheckAttribute(itemsRef, "rank") && !bOk)
		{
			if(sti(itemsRef.rank) < sti(refCharacter.rank)) // только, если ранг больше
			{
				RemoveCharacterEquip(itemsRef, GUN_ITEM_TYPE);
				if(!IsEquipCharacterByItem(itemsRef, "unarmed"))
				{
					RemoveCharacterEquip(itemsRef, BLADE_ITEM_TYPE);
				}
				
				RemoveCharacterEquip(itemsRef, CIRASS_ITEM_TYPE); //броня 081004 boal
			}
		}
		// boal <--
	}
	
	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_DEADMAN) // проверка квестовых ситуаций в каюте кэпа если сундук или обыск трупа
	{
		ShipSituation_SetQuestSituation(ShipSituation_0);
	}
	
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("ItemsName");
	GameInterface.TABLE_LIST.hr.td1.textoffset = "70, 0";
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("Weight");
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("ItemsQty");

	GameInterface.TABLE_LIST2.hr.td1.str = XI_ConvertString("ItemsName");
	GameInterface.TABLE_LIST2.hr.td1.textoffset = "70, 0";
	GameInterface.TABLE_LIST2.hr.td2.str = XI_ConvertString("Weight");
	GameInterface.TABLE_LIST2.hr.td3.str = XI_ConvertString("ItemsQty");
	
	FillCharactersScroll();
	
	if(sInterfaceType == INTERFACETYPE_DEADMAN) SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,"RESOURCE\INI\INTERFACES\itemsboxd.ini");
	else SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	if(sInterfaceType != INTERFACETYPE_DEADMAN){
		CreateString(true, "CharName", "", FONT_NORMAL, COLOR_MONEY, 960, 250, SCRIPT_ALIGN_CENTER, 1.5);
		CreateString(true, "CharJob", "", FONT_NORMAL, COLOR_NORMAL, 960, 125, SCRIPT_ALIGN_CENTER, 1.3);
	}
	
	InterfaceInitButtons(refCharacter);
	
	// Сброс стрелок на первую позицию
	SetTableArrowsInit();
	
	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL) // Только если сундук - у него никаких кнопок нету
	{
		if(sInterfaceType == INTERFACETYPE_CHEST)	OtherTableCaption = XI_ConvertString("OtherTableItemsChest"));
		if(sInterfaceType == INTERFACETYPE_BARREL)	OtherTableCaption = XI_ConvertString("OtherTableItemsBarrel"));
	}
	
	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) // Установим строки с именами
	{

		GameInterface.strings.CharName = GetFullName(refToChar);
		GameInterface.strings.CharJob = GetOfficerPosition(GetCharacterIndex(refToChar.ID));
		OtherTableCaption = XI_ConvertString("OtherTableItemsOfficer"));
	}
	else
	{
		GameInterface.strings.CharName = GetFullName(refCharacter);
		GameInterface.strings.CharJob = "";
	}
	SetControlsTabMode(1); // вкладка по умолчанию
	SetCharWeight();
	SetDescription();
	
	SetCharacterMoneyToGold(refCharacter); // Переводим деньги ГГ в золото
	SetCharacterMoneyToGold(itemsRef);
	iSetCharIDToCharactersArroy(refCharacter); // Заносим в список ГГ
	
	AddToTable(itemsRef);

	FillCharactersImages();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	SetEventHandler("MouseRClickUP","EndTooltip",0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("ShowBoxMove", "ShowBoxMove", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("eTabControlPress", "procTabChange", 0);

	SetFormatedText("STORECAPTION", XI_ConvertString(sGetInterfaceTypeStr("titleExchangeItems", "titleItemsBox", "titleDeadItems","titleBarrel")));
	SetFormatedText("OTHER_TABLE_CAPTION", OtherTableCaption);
	if(sInterfaceType == INTERFACETYPE_DEADMAN && CheckAttribute(&GameInterface, "TABLE_LIST2.tr1.index"))	
	{
		iCurGoodsIdx = sti(GameInterface.TABLE_LIST2.tr1.index);
	}
}

// метод переключает вкладки таблицы
void ProcessInterfaceControls() 
{
    string controlName = GetEventData();
	if (controlName == "InterfaceGoRight") {
		currentTab = currentTab % 5;
		SetControlsTabMode(currentTab + 1);
	}
	if (controlName == "InterfaceGoLeft") {
		currentTab = (5 + currentTab - 2) % 5;
		SetControlsTabMode(currentTab + 1);
	}
}

void InterfaceInitButtons(ref _refCharacter)
{
	String sInterfaceType = sGetInterfaceType();
	
	SetNodeUsing("GET_BUTTON", false);
	SetNodeUsing("GETALL_BUTTON", false);
	SetNodeUsing("CLOSE_BUTTON", false);
	SetNodeUsing("DELBODY_BUTTON", false);
	SetNodeUsing("SKULL_BUTTON", false);

	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			SetNodeUsing("GETALL_BUTTON", true);
		break;
		
		case INTERFACETYPE_DEADMAN:
			SetNodeUsing("GET_BUTTON", true);
			SetNodeUsing("GETALL_BUTTON", true);
			SetNodeUsing("CLOSE_BUTTON", true);
			SetNodeUsing("DELBODY_BUTTON", true);
		break;
		
		case INTERFACETYPE_CHEST:
			SetNodeUsing("GETALL_BUTTON", true); // всем сундукам
		break;
		
		case INTERFACETYPE_BARREL:
			SetNodeUsing("GETALL_BUTTON", true);
		break;
	}
	if(bShowChangeWin)
	{
		SetSelectable("GET_BUTTON", false);
		SetSelectable("GETALL_BUTTON", false);
		SetSelectable("CLOSE_BUTTON", false);
		SetSelectable("DELBODY_BUTTON", false);
	}
	else
	{
		SetSelectable("GET_BUTTON", true);
		SetSelectable("GETALL_BUTTON", true);
		SetSelectable("CLOSE_BUTTON", true);
		SetSelectable("DELBODY_BUTTON", true);
	}
}

void SetTableArrowsInit()
{
	SetNodeUsing("TABLE_REMOVE_BUTTON",false);
	SetNodeUsing("TABLE_REMOVE_ALL_BUTTON",false);
	SetNodeUsing("TABLE_ADD_BUTTON",false);
	SetNodeUsing("TABLE_ADD_ALL_BUTTON",false);
	SetNodeUsing("TABLE_REMOVE_BUTTON2",false);
	SetNodeUsing("TABLE_REMOVE_ALL_BUTTON2",false);
	SetNodeUsing("TABLE_ADD_BUTTON2",false);
	SetNodeUsing("TABLE_ADD_ALL_BUTTON2",false);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 35, iTableAddAllBtnY + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON", 0, iTableAddBtnX, iTableAddBtnY, iTableAddBtnX + 30, iTableAddBtnY + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON", 0, iTableRemoveBtnX, iTableRemoveBtnY, iTableRemoveBtnX + 30, iTableRemoveBtnY + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 35, iTableRemoveAllBtnY + 45, 0);	
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON2", 0, iTableAddAllBtnX2, iTableAddAllBtnY2, iTableAddAllBtnX2 + 35, iTableAddAllBtnY2 + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON2", 0, iTableAddBtnX2, iTableAddBtnY2, iTableAddBtnX2 + 30, iTableAddBtnY2 + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON2", 0, iTableRemoveBtnX2, iTableRemoveBtnY2, iTableRemoveBtnX2 + 30, iTableRemoveBtnY2 + 45, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON2", 0, iTableRemoveAllBtnX2, iTableRemoveAllBtnY2, iTableRemoveAllBtnX2 + 35, iTableRemoveAllBtnY2 + 45, 0);
}

void SetCharacterMoneyToGold(aref rChar) // В интерфейсе оперируем с деньгами как с предметом "gold"
{
	string sInterfaceType = sGetInterfaceType();
	bool bOk = sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL;
	if(bOk && !CheckAttribute(rChar, "ID"))
	{				
		if(!CheckAttribute(rChar, "Items.Gold")) rChar.Items.Gold = 0;
		rChar.items.gold = sti(rChar.items.gold)+sti(GetAttrValue(rChar, "money")); // По квестам ложится сразу золото, а не деньги		
	}
	else
	{
		rChar.items.gold = sti(GetAttrValue(rChar, "money"));
	}
}

int iSetCharIDToCharactersArroy(ref _rChar)
{
	string sCurArroyID;
	string sCharID = _rChar.id;
	for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE; i++)
	{
		sCurArroyID = sCharactersArroy[i];
		if(sCurArroyID == sCharID) return i;
		
		if(sCurArroyID == "")
		{
			sCharactersArroy[i] = sCharID;
			return i;
		}
	}
	
	// Не знаю, возможна ли нехватка свободных, ведь define INTERFACE_ITEMSBOX_CHAR_ARROYSIZE 10
	sCharactersArroy[0] = sCharID; // Свободных нету, но поставить-то нужно
	return 0;
}

void MakeMoneyFromGoldWithowtChest()
{
	string sCurArroyID;
	ref arCurChar;
	for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE, i++)
	{
		sCurArroyID = sCharactersArroy[i];
		if(sCurArroyID != "")
		{
			arCurChar = CharacterFromID(sCurArroyID);
			arCurChar.money = GetCharacterItem(arCurChar, "Gold");
			DeleteAttribute(arCurChar, "items.gold");
		}
	}
}

void MakeMoneyFromGoldWithChest(aref arChest)
{
	arChest.money = GetCharacterItem(arChest, "Gold");
	DeleteAttribute(arChest, "items.gold");
	MakeMoneyFromGoldWithowtChest();
}

void MakeMoneyFromGoldWithDeadMan(aref arDeadChar)
{
	arDeadChar.money = GetCharacterItem(arDeadChar, "Gold");
	DeleteAttribute(arDeadChar, "items.gold");
	MakeMoneyFromGoldWithowtChest();
}

string sGetInterfaceType()
{
	string sRetStr = INTERFACETYPE_EXCHANGE_ITEMS;
	if(sFaceID == "") // Сундук
	{
		sRetStr = INTERFACETYPE_CHEST;
	}
	
	if(sFaceID == "Barrel") // Бочонок
	{
		sRetStr = INTERFACETYPE_BARREL;
	}
	
	if(sFaceID == "666") // Мертвец
	{
		sRetStr = INTERFACETYPE_DEADMAN;
	}
	
	return sRetStr;
}

string sGetInterfaceTypeStr(string sExchangeItems, string sChest, string sDeadMan, string sBarrel)
{
	string sType = sGetInterfaceType();
	string sRetStr="";
	
	switch(sType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			sRetStr = sExchangeItems;
		break;
		
		case INTERFACETYPE_CHEST:
			sRetStr = sChest;
		break;
		
		case INTERFACETYPE_BARREL:
			sRetStr = sBarrel;
		break;
		
		case INTERFACETYPE_DEADMAN:
			sRetStr = sDeadMan;
		break;
	}
	
	return sRetStr;
}

void SetCharactersMoneyOnExit() // Выставим деньги
{
	string sInterfaceType = sGetInterfaceType();
	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			MakeMoneyFromGoldWithowtChest();
		break;
		
		case INTERFACETYPE_CHEST:
			MakeMoneyFromGoldWithChest(arChest);
		break;
		
		case INTERFACETYPE_BARREL:
			MakeMoneyFromGoldWithChest(arChest);
		break;		
		
		case INTERFACETYPE_DEADMAN:
			MakeMoneyFromGoldWithDeadMan(arDeadChar);
		break;
	}
}

void ShowItemsWeight()
{
	string sInterfaceType = sGetInterfaceType();
	int iWeight, iMaxWeight;
	string sText1,sText2;
	sText1 =  FloatToString(GetItemsWeight(refCharacter), 1) + " / " + GetMaxItemsWeight(refCharacter);

	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS)
	{
		sText2 =  FloatToString(GetItemsWeight(refToChar), 1) + " / " + GetMaxItemsWeight(refToChar);
		SetNodeUsing("WEIGHT_ICON2",true);
	}
	else
	{
		sText2 = "";
		SetNodeUsing("WEIGHT_ICON2",false);
	}
	SetFormatedText("MAIN_CHARACTER_WEIGHT", sText1);
	SetFormatedText("OTHER_WEIGHT", sText2);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
}

void ProcessCancelExit()
{
	if(bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
        // Корректное удаление трупа
        if(sGetInterfaceType() == INTERFACETYPE_DEADMAN && !CheckLastItemOnDead())
			Dead_DelLoginedCharacter(refToChar);
		IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
	}
}

void IDoExit(int exitCode)
{
	ref arCurChar;
	string sCurArroyID;
	// boal проверка на перегруз 21.01.2004 -->
	CheckAndSetOverloadMode(GetMainCharacter());
	// boal 21.01.2004 <--
	SetCharactersMoneyOnExit(); // Переводим монеты "gold" в деньгиъ
	RefreshEquippedMaps(GetMainCharacter()); // рефрешим карты, если купили
	ref sld;
	
	if(!bBoxUsed)
	{
		for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE, i++)
		{
			sCurArroyID = sCharactersArroy[i];
			if(sCurArroyID != "")
			{
				arCurChar = CharacterFromID(sCurArroyID);
				if(IsMainCharacter(arCurChar)) continue;
				if(LAi_CheckFightMode(arCurChar)) continue;		// если перс дерется то некогда ему обменом заниматься
				
				if (CheckAttribute(arCurChar, "CanTakeMushket") && CheckAttribute(arCurChar, "IsMushketer")) continue;
				
				if(CheckAttribute(arCurChar, "skill.FencingS")) //boal fix иначе не берут саблю при перегрузе
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar,BLADE_ITEM_TYPE));
				}
		
				if(CheckAttribute(arCurChar, "skill.FencingS") &&  GetCharacterSkill(arCurChar, "FencingS") > 0.1)
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar, CIRASS_ITEM_TYPE)); // boal 08.10.04 броню офицерам
				}

				if(CheckAttribute(arCurChar, "skill.Pistol") && GetCharacterSkill(arCurChar,"Pistol") > 0.1 )
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar, GUN_ITEM_TYPE));
				}
		
				if(CheckAttribute(arCurChar, "RealCompanionIdx")) // 1.2.4 обмен с компаньоном
				{
					sld = GetCharacter(sti(arCurChar.RealCompanionIdx));
					ChangeAttributesFromCharacter(sld, arCurChar, false); //тут предметы и деньги
				}			
			}
		}
	}
	else
	{
		bMainCharacterInBox = false; // снимаем флаг 'в боксе'
		if(!GetAchievement("ach_CL_125"))
		{
			if(pchar.location == Get_My_Cabin() && CheckItemMyCabin("gold_dublon") > 29999)
				Achievment_Set("ach_CL_125");
		}
		if(CheckAttribute(pchar, "systeminfo.tutorial.OverLoad") && GetCharacterFreeItem(refToChar, "BoxOfBalls"))
		{
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("BoxOfBalls")].weight) > GetMaxItemsWeight(pchar))
			{
				DeleteAttribute(pchar, "systeminfo.tutorial.OverLoad");
				DoQuestFunctionDelay("Tutorial_Overload", 1.0);
			}
		}
	}
	
	EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("ShowBoxMove", "ShowBoxMove");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("eTabControlPress", "procTabChange");
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	
	LAi_SetPlayerType(PChar); // Возвращаем тип игрока
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	String sInterfaceType = sGetInterfaceType();

	switch(nodName)
	{
		case "TABLE_REMOVE_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				if(bShowChangeWin) REMOVE_BUTTON();
				else onTableRemoveBtnClick();
			}
		break;

		case "TABLE_REMOVE_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				if(bShowChangeWin) REMOVE_ALL_BUTTON();
				else onTableRemoveAllBtnClick();
			}
		break;

		case "TABLE_ADD_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				if(bShowChangeWin) ADD_ALL_BUTTON();
				else onTableAddAllBtnClick();
			}
		break;

		case "TABLE_ADD_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				if(bShowChangeWin) ADD_BUTTON();
				else onTableAddBtnClick();
			}
		break;
		
		case "TABLE_LIST":
			if(comName=="rightstep")
			{
				if(bShowChangeWin) REMOVE_BUTTON();
				else onTableRemoveBtnClick();
			}
			if(comName=="speedright")
			{
				if(bShowChangeWin) REMOVE_ALL_BUTTON();
				else onTableRemoveAllBtnClick();
			}
			if(comName=="leftstep")
			{
				if(bShowChangeWin) ADD_BUTTON();
				else onTableAddBtnClick();
			}
			if(comName=="speedleft")
			{
				if(bShowChangeWin) ADD_ALL_BUTTON();
				else onTableAddAllBtnClick();
			}
			if(comName=="click")
			{
				validLineClicked = false; // убираем валидность клика для подсказок, если нажали ЛКМ
			}
		break;

		case "TABLE_REMOVE_BUTTON2":
			if(comName == "activate" || comName == "click")
			{
				if(bShowChangeWin) REMOVE_BUTTON();
				else onTableRemoveBtnClick();
			}
		break;

		case "TABLE_REMOVE_ALL_BUTTON2":
			if(comName == "activate" || comName == "click")
			{
				if(bShowChangeWin) REMOVE_ALL_BUTTON();
				else onTableRemoveAllBtnClick();
			}
		break;

		case "TABLE_ADD_ALL_BUTTON2":
			if(comName == "activate" || comName == "click")
			{
				if(bShowChangeWin) ADD_ALL_BUTTON();
				else onTableAddAllBtnClick();
			}
		break;

		case "TABLE_ADD_BUTTON2":
			if(comName == "activate" || comName == "click")
			{
				if(bShowChangeWin) ADD_BUTTON();
				else onTableAddBtnClick();
			}
		break;
		
		case "TABLE_LIST2":
			if(comName=="rightstep")
			{
				if(bShowChangeWin) REMOVE_BUTTON();
				else onTableRemoveBtnClick();
			}
			if(comName=="speedright")
			{
				if(bShowChangeWin) REMOVE_ALL_BUTTON();
				else onTableRemoveAllBtnClick();
			}
			if(comName=="leftstep")
			{
				if(bShowChangeWin) ADD_BUTTON();
				else onTableAddBtnClick();
			}
			if(comName=="speedleft")
			{
				if(bShowChangeWin) ADD_ALL_BUTTON();
				else onTableAddAllBtnClick();
			}
			if(comName=="click")
			{
				validLineClicked = false;
			}
		break;
		
		case "QTY_OK_BUTTON":
			if(comName=="leftstep")
			{
				ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
				REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;

		case "QTY_CANCEL_BUTTON":
			if(comName=="leftstep")
			{
				ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
				REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;

		case "GET_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onTableAddAllBtnClick();
			}
		break;

		case "GETALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onGetAllBtnClick();
				if(sInterfaceType == INTERFACETYPE_DEADMAN && !CheckLastItemOnDead())
				{
					Dead_DelLoginedCharacter(refToChar);
					IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
				}
			}
		break;
		
		//navy --> Убрать тело
		case "DELBODY_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				Dead_DelLoginedCharacter(refToChar);
				ProcessCancelExit();
			}
		break;

		case "CLOSE_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				ProcessCancelExit();
			}
		break;
		//navy <--
		
		case "SKULL_BUTTON":
			if(comName=="upstep")
			{
				SetCurrentNode("CLOSE_BUTTON");
			}
			
			if(comName=="activate" || comName=="click")
			{
				SetNPCQuestDate(refCharacter, "AztecSkull"); //запомним день
				OfficerReincarnation(&characters[sti(refToChar.index)]);
				Dead_DelLoginedCharacter(refToChar);
				ProcessCancelExit();
			}
		break;
	}
}

void procTabChange()
{
	int comIndex = GetEventData();
	String nodName = GetEventData();
	
	switch(nodName)
	{
		case "TABBTN_1":
			SetControlsTabModeManual(1)
		break;
		
		case "TABBTN_2":
			SetControlsTabModeManual(2)
		break;
		
		case "TABBTN_3":
			SetControlsTabModeManual(3)
		break;
		
		case "TABBTN_4":
			SetControlsTabModeManual(4)
		break;
		case "TABBTN_5":
			SetControlsTabModeManual(5)
		break;
	}
}

// метод переключает вкладки таблицы
void SetControlsTabModeManual(int mode) 
{
    currentTab = mode - 1;
    SetControlsTabMode(mode);
}

void SetControlsTabMode(int _mode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;
	int nColor5 = nColor1;

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;

	string sPic6 = sPic1;
	string sPic7 = sPic1;
	string sPic8 = sPic1;
	string sPic9 = sPic1;
	string sPic10 = sPic1;

	switch (_mode)
	{
		case 1:
			sPic1 = "TabSelected";
			sPic6 = "TabSelectedMark";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabSelected";
			sPic7 = "TabSelectedMark";
			nColor2 = argb(255,255,255,255);
		break;
		case 3:
			sPic3 = "TabSelected";
			sPic8 = "TabSelectedMark";
			nColor3 = argb(255,255,255,255);
		break;
		case 4:
			sPic4 = "TabSelected";
			sPic9 = "TabSelectedMark";
			nColor4 = argb(255,255,255,255);
		break;
		case 5:
			sPic5 = "TabSelected";
			sPic10 = "TabSelectedMark";
			nColor5 = argb(255,255,255,255);
		break;
	}
	   
	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS", sPic4);
	SetNewGroupPicture("TABBTN_5", "TABS", sPic5);
	SetNewGroupPicture("TABBTN_1_MARK", "TABS", sPic6);
	SetNewGroupPicture("TABBTN_2_MARK", "TABS", sPic7);
	SetNewGroupPicture("TABBTN_3_MARK", "TABS", sPic8);
	SetNewGroupPicture("TABBTN_4_MARK", "TABS", sPic9);
	SetNewGroupPicture("TABBTN_5_MARK", "TABS", sPic10);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_3", 8,0,nColor3);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_4", 8,0,nColor4);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_5", 8,0,nColor5);
	
	currentTab = _mode;
	
	// Выставим таблицы в начало
	GameInterface.TABLE_LIST.select = 1;
	GameInterface.TABLE_LIST.top = 0;
	GameInterface.TABLE_LIST2.select = 1;
	GameInterface.TABLE_LIST2.top = 0;
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST2",0);
	
	// Тут идёт рефреш предметов
	AddToTable(refToChar);
	
	// Сброс стрелок на первую позицию
	SetTableArrowsInit();

	bShowChangeWin = false;
	EndTooltip();
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void FillCharactersScroll()
{
	int i;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool bOk;
	string sInterfaceType = sGetInterfaceType();
	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetNotQuestPassengersQuantity(pchar);

	GameInterface.CHARACTERS_SCROLL.NotUsed = 6;
	GameInterface.CHARACTERS_SCROLL.ListSize = nListSizeFree + 2;

	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 2); // passengers

	GameInterface.CHARACTERS_SCROLL.BadTex1 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic1 = "emptyface";
	
	string sCharID = "";
	int iCharIDX;

	int m = 0;
	if(sInterfaceType != INTERFACETYPE_EXCHANGE_ITEMS)
	{
		attributeName = "pic" + (m + 1);
		GameInterface.CHARACTERS_SCROLL.(attributeName).character = nMainCharacterIndex;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(pchar);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + pchar.FaceID);
		m++;
	}
	else // При обмене предметами с офом первая картинка - собсно офф
	{
		sCharID = refToChar.ID;
		iCharIDX = GetCharacterIndex(sCharID);
		attributeName = "pic" + (m + 1);
		
		SetCharacterMoneyToGold(refToChar);
		iSetCharIDToCharactersArroy(refToChar); // Пометим его для удаления золота и дачи денег
		
		GameInterface.CHARACTERS_SCROLL.(attributeName).character = iCharIDX;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(refToChar);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + refToChar.FaceID);
		m++;
	}

	for(i = 0; i < nListSize; i++)
	{
		_curCharIdx = GetPassenger(pchar, i);
		bOk = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
		if(_curCharIdx != -1  && !CheckAttribute(&characters[_curCharIdx], "isquest") && !bOk)
		{
			if(pchar.location == Get_My_Cabin()) // belamour заколебешься к ним бегать
			{
				if(sCharID == characters[_curCharIdx].ID) continue;
				if(!isOfficerInShip(GetCharacter(_curCharIdx), true)) continue;
				SetCharacterMoneyToGold(GetCharacter(_curCharIdx));
				iSetCharIDToCharactersArroy(GetCharacter(_curCharIdx)); // Пометим его для удаления золота и дачи денег
				attributeName = "pic" + (m + 1);
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
			else
			{	
				if(IsOfficer(&characters[_curCharIdx]) && PChar.location == Characters[_curCharIdx].location)  // boal // fix - ГГ и офы должны быть в одной локации
				{
					if(sCharID == characters[_curCharIdx].ID) continue;
					
					SetCharacterMoneyToGold(GetCharacter(_curCharIdx));
					iSetCharIDToCharactersArroy(GetCharacter(_curCharIdx)); // Пометим его для удаления золота и дачи денег
					attributeName = "pic" + (m + 1);
					GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
					GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
					GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
					m++;
				}
			}
		}
	}
}

bool FilterItems(ref Item)
{
	bool items1, items2, items3, items4, items5;
	string groupID, itemType, sItem;
	sItem = Item.id;
	
	if(!CheckAttribute(Item, "ID")) return false;

	if(CheckAttribute(Item,"groupID")) 	groupID = Item.groupID;
	if(CheckAttribute(Item,"itemType")) itemType = Item.itemType;	
	if(sItem == "Gold") return false; // Золото выше
		
	items2 = (groupID == BLADE_ITEM_TYPE) || 	// холодное оружие
			 (groupID == GUN_ITEM_TYPE)	||		// огнестрел
			 (groupID == MUSKET_ITEM_TYPE)	||	// мушкеты
			 (groupID == SPYGLASS_ITEM_TYPE) || // трубы
			 (groupID == CIRASS_ITEM_TYPE) ||   // костюмы и доспехи
			 (groupID == TOOL_ITEM_TYPE) ||     // навигационные приборы котороые можно экипировать в спецслот
			 (groupID == LANTERN_ITEM_TYPE) ||  // фонарь
			 (groupID == HAT_ITEM_TYPE) ||  	// шляпы
			 (groupID == AMMO_ITEM_TYPE);		// расходники для огнестрела

	items4 = (groupID == ITEM_SLOT_TYPE) 	|| 	// амулеты
			 (groupID == TALISMAN_ITEM_TYPE)|| 	// талисманы
			 (itemType == "ARTEFACT");			// артефакты
	
	items5 = (groupID == PATENT_ITEM_TYPE)	||	// патенты
			 (groupID == MAPS_ITEM_TYPE) ||		// карты
			 (groupID == SPECIAL_ITEM_TYPE) || 	// спецпредметы
			 (itemType == "QUESTITEMS"); 	    // квестовые предметы			  
	
	if(currentTab == 2)
	{
		if (!items2) return false;
		if (HasSubStr(sItem, "potion"))  return false;
		if (HasSubStr(sItem, "mineral"))  return false;
	}
	if(currentTab == 3 && !HasSubStr(sItem, "potion"))  return false;
	if(currentTab == 4)
	{
		if (!items4) return false;
		if (HasSubStr(sItem, "chest"))  return false;
		if (HasSubStr(sItem, "jewelry"))  return false;
		if (HasSubStr(sItem, "dublon"))  return false;
		if (HasSubStr(sItem, "gold"))  return false;
		if (HasSubStr(sItem, "collect"))  return false;
		if (CheckAttribute(Item,"Price") && sti(Item.price) == 0) return false;
	}
	if(currentTab == 5)
	{
		if (!items5) return false;
		if (HasSubStr(sItem, "potion"))  return false;
		if (HasSubStr(sItem, "cannabis"))  return false;
		if (HasSubStr(sItem, "icollection"))  return false;
	}
	return true;
}

void AddToTable(ref rChar)
{
	string sList, sList2, sItem;
	int i, iLeftQty, iRightQty, goldIndex;
	ref rItem;
	bool items1, items2, items3, items4, items5;
	string groupID,itemType;

	int prevLineCountChar = iLinesCount;
	int prevLineCountChest = iLinesCount2;
	
	iLinesCount = 1;
	iLinesCount2 = 1;
	
	Table_Clear("TABLE_LIST", false, true, false);
	Table_Clear("TABLE_LIST2", false, true, false);
	
	iLeftQty  = GetCharacterFreeItem(refCharacter, "Gold");
	iRightQty = GetCharacterFreeItem(rChar, "Gold");	

	if(currentTab == 1) // деньги только для вкладки все
	{
		sList = "tr" + iLinesCount;
		sList2 = "tr" + iLinesCount2;
		goldIndex = FindItem("Gold");
		rItem = &Items[goldIndex];
		sItem = rItem.id;
		// Персонаж
		if (iLeftQty > 0)
		{
			GameInterface.TABLE_LIST.(sList).td1.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST.(sList).td1.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST.(sList).td1.icon.offset = "0, 0";
			GameInterface.TABLE_LIST.(sList).td1.icon.width = 50;
			GameInterface.TABLE_LIST.(sList).td1.icon.height = 50;
			GameInterface.TABLE_LIST.(sList).td1.textoffset = "70, 0";
			GameInterface.TABLE_LIST.(sList).td1.line_space_modifier = 0.8;
			GameInterface.TABLE_LIST.(sList).td1.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			GameInterface.TABLE_LIST.(sList).index = goldIndex;
			GameInterface.TABLE_LIST.(sList).td2.str = "-";
			GameInterface.TABLE_LIST.(sList).td3.str = iLeftQty;
			iLinesCount++;
		}
		// Сундук
		if (iRightQty > 0)
		{
			GameInterface.TABLE_LIST2.(sList2).td1.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST2.(sList2).td1.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST2.(sList2).td1.icon.offset = "0, 0";
			GameInterface.TABLE_LIST2.(sList2).td1.icon.width = 50;
			GameInterface.TABLE_LIST2.(sList2).td1.icon.height = 50;
			GameInterface.TABLE_LIST2.(sList2).td1.textoffset = "70, 0";
			GameInterface.TABLE_LIST2.(sList2).td1.line_space_modifier = 0.8;
			GameInterface.TABLE_LIST2.(sList2).td1.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			GameInterface.TABLE_LIST2.(sList2).index = goldIndex;
			GameInterface.TABLE_LIST2.(sList2).td2.str = "-";
			GameInterface.TABLE_LIST2.(sList2).td3.str = iRightQty;
			iLinesCount2++;
		}
	}
	
	// Сначала заполняем рандомящимся оружием
	for (i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
    {
        sList = "tr" + iLinesCount;
        sList2 = "tr" + iLinesCount2;
        rItem = &Items[i];
        sItem = rItem.id;

        // Проверка на экипировку
        if (!FilterItems(rItem)) continue;

        iLeftQty = GetCharacterFreeItem(refCharacter, sItem);
        iRightQty = GetCharacterFreeItem(rChar, sItem);

        // Персонаж
        if (iLeftQty > 0)
        {
			GameInterface.TABLE_LIST.(sList).td1.icon.group = rItem.picTexture;
            GameInterface.TABLE_LIST.(sList).td1.icon.image = "itm" + rItem.picIndex;
            GameInterface.TABLE_LIST.(sList).td1.icon.offset = "0, 0";
            GameInterface.TABLE_LIST.(sList).td1.icon.width = 50;
            GameInterface.TABLE_LIST.(sList).td1.icon.height = 50;
            GameInterface.TABLE_LIST.(sList).td1.textoffset = "70, 0";
            GameInterface.TABLE_LIST.(sList).td1.line_space_modifier = 0.9;
            GameInterface.TABLE_LIST.(sList).td1.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
            GameInterface.TABLE_LIST.(sList).index = i;
            GameInterface.TABLE_LIST.(sList).td2.str = FloatToString(stf(rItem.Weight) * iLeftQty, 1);
            GameInterface.TABLE_LIST.(sList).td3.str = iLeftQty;
            iLinesCount++;
        }
        // Сундук
        if (iRightQty > 0)
        {
            GameInterface.TABLE_LIST2.(sList2).UserData.ID = rItem.name;
            GameInterface.TABLE_LIST2.(sList2).UserData.IDX = i;
			
			GameInterface.TABLE_LIST2.(sList2).td1.icon.group = rItem.picTexture;
            GameInterface.TABLE_LIST2.(sList2).td1.icon.image = "itm" + rItem.picIndex;
            GameInterface.TABLE_LIST2.(sList2).td1.icon.offset = "0, 0";
            GameInterface.TABLE_LIST2.(sList2).td1.icon.width = 50;
            GameInterface.TABLE_LIST2.(sList2).td1.icon.height = 50;
            GameInterface.TABLE_LIST2.(sList2).td1.textoffset = "70, 0";
            GameInterface.TABLE_LIST2.(sList2).td1.line_space_modifier = 0.9;
            GameInterface.TABLE_LIST2.(sList2).td1.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
            GameInterface.TABLE_LIST2.(sList2).index = i;
            GameInterface.TABLE_LIST2.(sList2).td2.str = FloatToString(stf(rItem.Weight) * iRightQty, 1);
            GameInterface.TABLE_LIST2.(sList2).td3.str = iRightQty;
            iLinesCount2++;
        }
    }
	// for(i = 0; i < TOTAL_ITEMS; i++) //  
	for(i = 0; i < ITEMS_QUANTITY; i++)
	{
		sList = "tr" + iLinesCount;
		sList2 = "tr" + iLinesCount2;
		rItem = &Items[i];
		sItem = rItem.id;

		// Проверка на экипировку
		if(!FilterItems(rItem)) continue;

		iLeftQty  = GetCharacterFreeItem(refCharacter, sItem);
		iRightQty = GetCharacterFreeItem(rChar, sItem);
		
		// Персонаж
		if(iLeftQty > 0)
		{
			GameInterface.TABLE_LIST.(sList).td1.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST.(sList).td1.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST.(sList).td1.icon.offset = "0, 0";
			GameInterface.TABLE_LIST.(sList).td1.icon.width = 50;
			GameInterface.TABLE_LIST.(sList).td1.icon.height = 50;
			GameInterface.TABLE_LIST.(sList).td1.textoffset = "70, 0";
			GameInterface.TABLE_LIST.(sList).td1.line_space_modifier = 0.9;
			GameInterface.TABLE_LIST.(sList).td1.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			GameInterface.TABLE_LIST.(sList).index = i;
			GameInterface.TABLE_LIST.(sList).td2.str = FloatToString(stf(rItem.Weight) * iLeftQty, 1);
			GameInterface.TABLE_LIST.(sList).td3.str = iLeftQty;
			iLinesCount++;
		}
		// Сундук
		if(iRightQty > 0)
		{
			GameInterface.TABLE_LIST2.(sList2).td1.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST2.(sList2).td1.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST2.(sList2).td1.icon.offset = "0, 0";
			GameInterface.TABLE_LIST2.(sList2).td1.icon.width = 50;
			GameInterface.TABLE_LIST2.(sList2).td1.icon.height = 50;
			GameInterface.TABLE_LIST2.(sList2).td1.textoffset = "70, 0";
			GameInterface.TABLE_LIST2.(sList2).td1.line_space_modifier = 0.9;
			GameInterface.TABLE_LIST2.(sList2).td1.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			GameInterface.TABLE_LIST2.(sList2).index = i;
			GameInterface.TABLE_LIST2.(sList2).td2.str = FloatToString(stf(rItem.Weight) * iRightQty, 1);
			GameInterface.TABLE_LIST2.(sList2).td3.str = iRightQty;
			iLinesCount2++;
		}
	}

	int currentSelect = 0;
	int targetSelect = 0;
	int targetButtonsLine = 0;

	// На случай если количество предметов изменилось у персонажа
	if(iLinesCount > 1)
	{
		if (iLinesCount < prevLineCountChar)
		{
			currentSelect = sti(GameInterface.TABLE_LIST.select);
			if (currentSelect == iLinesCount)
			{
				targetSelect = currentSelect - 1;
				GameInterface.TABLE_LIST.select = targetSelect;
				sList = "tr" + targetSelect;

				targetButtonsLine = targetSelect - 1 - sti(GameInterface.TABLE_LIST.top);
				SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY + 50 * targetButtonsLine, iTableAddAllBtnX + 35, iTableAddAllBtnY + 50 * targetButtonsLine + 45, 0);
				SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON", 0, iTableAddBtnX, iTableAddBtnY + 50 * targetButtonsLine, iTableAddBtnX + 30, iTableAddBtnY + 50 * targetButtonsLine + 45, 0);
				SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON", 0, iTableRemoveBtnX, iTableRemoveBtnY + 50 * targetButtonsLine, iTableRemoveBtnX + 30, iTableRemoveBtnY + 50 * targetButtonsLine + 45, 0);
				SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY + 50 * targetButtonsLine, iTableRemoveAllBtnX + 35, iTableRemoveAllBtnY + 50 * targetButtonsLine + 45, 0);
			}
			else
			{
				targetSelect = sti(GameInterface.TABLE_LIST.select);
				GameInterface.TABLE_LIST.select = targetSelect;
				sList = "tr" + targetSelect;
			}

			if (CheckAttribute(&GameInterface, "TABLE_LIST." + sList + ".index"))
			{
				iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
				ShowGoodsInfo(iCurGoodsIdx);
			}
		}
	}
	else 
	{
		SetNodeUsing ("TABLE_ADD_ALL_BUTTON", false);
		SetNodeUsing ("TABLE_ADD_BUTTON", false);
		SetNodeUsing ("TABLE_REMOVE_BUTTON", false);
		SetNodeUsing ("TABLE_REMOVE_ALL_BUTTON", false);
	}
	// На случай если количество предметов изменилось в сундуке
	if(iLinesCount2 > 1)
	{
		if (iLinesCount2 < prevLineCountChest)
		{
			currentSelect = sti(GameInterface.TABLE_LIST2.select);
			if (currentSelect == iLinesCount2)
			{
				targetSelect = currentSelect - 1;
				GameInterface.TABLE_LIST2.select = targetSelect;
				sList2 = "tr" + targetSelect;

				targetButtonsLine = targetSelect - 1 - sti(GameInterface.TABLE_LIST2.top);			
				SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON2", 0, iTableAddAllBtnX2, iTableAddAllBtnY2 + 50 * targetButtonsLine, iTableAddAllBtnX2 + 35, iTableAddAllBtnY2 + 50 * targetButtonsLine + 45, 0);
				SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON2", 0, iTableAddBtnX2, iTableAddBtnY2 + 50 * targetButtonsLine, iTableAddBtnX2 + 30, iTableAddBtnY2 + 50 * targetButtonsLine + 45, 0);
				SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON2", 0, iTableRemoveBtnX2, iTableRemoveBtnY2 + 50 * targetButtonsLine, iTableRemoveBtnX2 + 30, iTableRemoveBtnY2 + 50 * targetButtonsLine + 45, 0);
				SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON2", 0, iTableRemoveAllBtnX2, iTableRemoveAllBtnY2 + 50 * targetButtonsLine, iTableRemoveAllBtnX2 + 35, iTableRemoveAllBtnY2 + 50 * targetButtonsLine + 45, 0);
			}
			else
			{
				targetSelect = sti(GameInterface.TABLE_LIST2.select);
				GameInterface.TABLE_LIST2.select = targetSelect;
				sList2 = "tr" + targetSelect;
			}

			if (CheckAttribute(&GameInterface, "TABLE_LIST2." + sList2 + ".index"))
			{
				iCurGoodsIdx = sti(GameInterface.TABLE_LIST2.(sList2).index);
				ShowGoodsInfo(iCurGoodsIdx);
			}
		}
	} 
	else 
	{
		SetNodeUsing ("TABLE_ADD_ALL_BUTTON2", false);
		SetNodeUsing ("TABLE_ADD_BUTTON2", false);
		SetNodeUsing ("TABLE_REMOVE_BUTTON2", false);
		SetNodeUsing ("TABLE_REMOVE_ALL_BUTTON2", false);
	}
	
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST2", 0 );
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();
	
	string sRow = "tr" + (iRow + 1);
	Table_UpdateWindow(sControl);
}

void OnHeaderClick()
{
	string sNode = GetEventData();
	int iCol = GetEventData();
}

void ChangePosTable()
{

}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
	GameInterface.qty_edit.str = 0;
	SetCharWeight();
	SetVariable();
	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	HideItemInfo();
	bShowChangeWin = false;
	SetCurrentNode(CurTable);
	InterfaceInitButtons(refCharacter);
}

void HideItemInfo()
{
	XI_WindowDisable("INFO_WINDOW", true);
	XI_WindowShow("INFO_WINDOW", false);
}

void ShowItemInfo()
{
	string sInterfaceType = sGetInterfaceType();
	string sCaption = "";
    string describeStr = "";
	int offx = -488;
    if (validLineClicked && iCurGoodsIdx > 0)
    {
        int lngFileID = LanguageOpenFile("ItemsDescribe.txt");

        if (bBettaTestMode)
        {
            describeStr += "id = " + Items[iCurGoodsIdx].id + NewStr();
        }
        describeStr += GetItemDescribe(iCurGoodsIdx);
		SetNewGroupPicture("INFO_ITEMS_PICTURE", Items[iCurGoodsIdx].picTexture, "itm" + Items[iCurGoodsIdx].picIndex);
        sCaption = LanguageConvertString(lngFileID, Items[iCurGoodsIdx].name);
		SetFormatedText("INFO_CAPTION", sCaption);
		SetFormatedText("INFO_ITEMS_TEXT", describeStr);
        LanguageCloseFile(lngFileID);
		XI_WindowDisable("INFO_WINDOW", false);
		XI_WindowShow("INFO_WINDOW", true);
		bShowChangeWin = true;
        validLineClicked = false;
		if (CurTable == "TABLE_LIST") {
		SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"INFO_FRAME", -1, 4, iTableInfoX1, iTableInfoY1, iTableInfoX2, iTableInfoY2);
		SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"V_INFO_CAPTION", -1, 4, iTableInfoX1, iTableInfoY1+3, iTableInfoX2, iTableInfoY2-404);
		SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"INFO_CAPTION", -1, 4, iTableInfoX1, iTableInfoY1+12, iTableInfoX2, iTableInfoY2-413);
		SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"INFO_ITEMS_PICTURE", -1, 4, iTableInfoX1+181, iTableInfoY1+75, iTableInfoX2-181, iTableInfoY2-257);
		SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"INFO_ITEMS_TEXT", -1, 4, iTableInfoX1+10, iTableInfoY1+215, iTableInfoX2-10, iTableInfoY2-65);
		} else {
			if(sInterfaceType != INTERFACETYPE_DEADMAN){
				SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"INFO_FRAME", -1, 4, iTableInfoX1+offx, iTableInfoY1, iTableInfoX2+offx, iTableInfoY2);
				SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"V_INFO_CAPTION", -1, 4, iTableInfoX1+offx, iTableInfoY1+3, iTableInfoX2+offx, iTableInfoY2-404);
				SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"INFO_CAPTION", -1, 4, iTableInfoX1+offx, iTableInfoY1+12, iTableInfoX2+offx, iTableInfoY2-413);
				SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"INFO_ITEMS_PICTURE", -1, 4, iTableInfoX1+181+offx, iTableInfoY1+75, iTableInfoX2-181+offx, iTableInfoY2-257);
				SendMessage(&GameInterface,"lsllllll",MSG_INTERFACE_MSG_TO_NODE,"INFO_ITEMS_TEXT", -1, 4, iTableInfoX1+10+offx, iTableInfoY1+215, iTableInfoX2-10+offx, iTableInfoY2-65);
			}
		}
    }
}

void ShowBoxMove()
{
	if(bShowChangeWin) // жмем окей, когда курсор на таблице
	{
		SetCurrentNode("QTY_OK_BUTTON");
		// TransactionOK();
	}
	else
	{
		GameInterface.qty_edit.str = "0";
		BuyOrSell = 0;
		ChangeQTY_EDIT();
		
		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
	}
	InterfaceInitButtons(refCharacter);
}

void CS_TableSelectChange()
{
	String sControl = GetEventData();
	int iSelected = GetEventData();
	int iCol = GetEventData();
    CurTable = sControl;
	NullSelectTable("TABLE_LIST");
    NullSelectTable("TABLE_LIST2");	
	// Warship 26.04.09 fix - при прокрутке можно вылазить за экран, неправильно определялась текущая линия
	int iSelLine = iSelected;
	
	if(CheckAttribute(&GameInterface, "TABLE_LIST.top"))
	{
		iSelLine = iSelected - sti(GameInterface.TABLE_LIST.top);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY + 50 * (iSelLine - 1), iTableAddAllBtnX + 35, iTableAddAllBtnY + 50 * (iSelLine - 1) + 45, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON", 0, iTableAddBtnX, iTableAddBtnY + 50 * (iSelLine - 1), iTableAddBtnX + 30, iTableAddBtnY + 50 * (iSelLine - 1) + 45, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON", 0, iTableRemoveBtnX, iTableRemoveBtnY + 50 * (iSelLine - 1), iTableRemoveBtnX + 30, iTableRemoveBtnY + 50 * (iSelLine - 1) + 45, 0);		
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY + 50 * (iSelLine - 1), iTableRemoveAllBtnX + 35, iTableRemoveAllBtnY + 50 * (iSelLine - 1) + 45, 0);
	}
	if(CheckAttribute(&GameInterface, "TABLE_LIST2.top"))
	{
		iSelLine = iSelected - sti(GameInterface.TABLE_LIST2.top);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON2", 0, iTableAddAllBtnX2, iTableAddAllBtnY2 + 50 * (iSelLine - 1), iTableAddAllBtnX2 + 35, iTableAddAllBtnY + 50 * (iSelLine - 1) + 45, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_BUTTON2", 0, iTableAddBtnX2, iTableAddBtnY2 + 50 * (iSelLine - 1), iTableAddBtnX2 + 30, iTableAddBtnY2 + 50 * (iSelLine - 1) + 45, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_BUTTON2", 0, iTableRemoveBtnX2, iTableRemoveBtnY2 + 50 * (iSelLine - 1), iTableRemoveBtnX2 + 30, iTableRemoveBtnY2 + 50 * (iSelLine - 1) + 45, 0);		
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON2", 0, iTableRemoveAllBtnX2, iTableRemoveAllBtnY2 + 50 * (iSelLine - 1), iTableRemoveAllBtnX2 + 35, iTableRemoveAllBtnY2 + 50 * (iSelLine - 1) + 45, 0);
	}
	
	String sList = "tr" + iSelected;
	CurRow = sList;
	SetCharWeight();
	SetVariable();
	validLineClicked = true;
	if (CurTable == "TABLE_LIST") ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sList).index));
    else ShowGoodsInfo(sti(GameInterface.TABLE_LIST2.(sList).index));
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
		if (CurTable != "TABLE_LIST")
		{
			SetNodeUsing("TABLE_ADD_ALL_BUTTON",false);
			SetNodeUsing("TABLE_ADD_BUTTON",false);
			SetNodeUsing("TABLE_REMOVE_BUTTON",false);
			SetNodeUsing("TABLE_REMOVE_ALL_BUTTON",false);
			SetNodeUsing("TABLE_ADD_ALL_BUTTON2",true);
			SetNodeUsing("TABLE_ADD_BUTTON2",true);
			SetNodeUsing("TABLE_REMOVE_BUTTON2",true);
			SetNodeUsing("TABLE_REMOVE_ALL_BUTTON2",true);
		} else {
			SetNodeUsing("TABLE_ADD_ALL_BUTTON",true);
			SetNodeUsing("TABLE_ADD_BUTTON",true);
			SetNodeUsing("TABLE_REMOVE_BUTTON",true);
			SetNodeUsing("TABLE_REMOVE_ALL_BUTTON",true);
			SetNodeUsing("TABLE_ADD_ALL_BUTTON2",false);
			SetNodeUsing("TABLE_ADD_BUTTON2",false);
			SetNodeUsing("TABLE_REMOVE_BUTTON2",false);
			SetNodeUsing("TABLE_REMOVE_ALL_BUTTON2",false);
		}
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	ShowItemsWeight(); // Переделка
}

void SetCharacterName()
{
	string sInterfaceType = sGetInterfaceType();
	
	aref arChar;
	ref rChar;
	
	string sAttr = "pic" + (nCurScrollNum + 1);
	int iCurCharImageIndex = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);
	string sCharacter = iCurCharImageIndex;
	string sFullName = GetFullName(&characters[iCurCharImageIndex]);
	string sJob = GetOfficerPosition(sCharacter);
	
	GameInterface.strings.CharName = sFullName;
	if(iCurCharImageIndex == 1) GameInterface.strings.CharJob = "";
	else GameInterface.strings.CharJob = sJob;
}

void ProcessFrame()
{	
	aref arCurCharFromImage;
	string sInterfaceType = sGetInterfaceType();
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		int iCurCharImageIndex = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);
		
		switch(sInterfaceType)
		{
			case INTERFACETYPE_EXCHANGE_ITEMS:
				makearef(refToChar, characters[iCurCharImageIndex]);
			break;
			
			case INTERFACETYPE_CHEST:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;
			
			case INTERFACETYPE_BARREL:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;
			
			case INTERFACETYPE_DEADMAN:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;
		}
		SetDescription();
		AddToTable(refToChar);

		FillCharactersImages();
		// Выставим таблицы в начало
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
		GameInterface.TABLE_LIST2.select = 1;
		GameInterface.TABLE_LIST2.top = 0;
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
		SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST2",0);

		SetCharacterName();
		
		// Сброс стрелок на первую позицию
		SetTableArrowsInit();
	}
}

void FillCharactersImages()
{
	string sInterfaceType = sGetInterfaceType();
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\le\portraits\256\face_" + refCharacter.FaceId + ".tga");
	
	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			SetNewPicture("OTHER_PICTURE", "interfaces\le\portraits\256\face_" + refToChar.FaceId + ".tga");
		break;
		
		case INTERFACETYPE_CHEST:
			SetNewPicture("OTHER_PICTURE", "interfaces\le\portraits\Search.tga");
		break;
		
		case INTERFACETYPE_BARREL:
			SetNewGroupPicture("OTHER_PICTURE", "BARREL_IMAGE", "BarrelImage");
		break;
		
		case INTERFACETYPE_DEADMAN:
			SetNewPicture("OTHER_PICTURE", "interfaces\le\portraits\Corpse.tga");
		break;
	}
}

void SetDescription()
{
	SetVariable();
}

void SetCharWeight()
{
    fCharWeight  = GetItemsWeight(refCharacter);
    fStoreWeight = GetItemsWeight(refToChar);
}

// Жмакнули по кнопке "взять все"
void onGetAllBtnClick()
{
	int iItemsQty;
	String itemID;
	
	int maxItemsToAdd;
	float weight;
	bool bOk = false;
	
	for(int i=0; i<TOTAL_ITEMS; i++)
	{
		if(CheckAttribute(&Items[i], "ID"))
		{
			itemID = Items[i].id;
			iItemsQty = GetCharacterFreeItem(refToChar, itemID);
			if(iItemsQty < 1) continue;
			
			// Учет перегруза -->
			maxItemsToAdd = GetMaxItemsToTake(true, itemID)
			
			if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
			// <-- Учет перегруза
			
			// if(iItemsQty < 1) continue;
			if(iItemsQty < 1) Log_Info(XI_ConvertString("CharacterOverload"));
			
			RemoveItems(refToChar, itemID, iItemsQty);
			AddItems(refCharacter, itemID, iItemsQty);
			
			bOk = true;
				
			weight = iItemsQty * stf(Items[i].weight);
			fCharWeight += weight; // Тут обновляем для метода GetMaxItemsToTake, иначе тормоза
			fStoreWeight -= weight;
		}
	}
	
	//if(bOk && !CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("", 0, 0, 0, 0, 1);
	
	// Warship fix 10.06.09 -->
	// Обновление текущего веса и т.д.
	SetCharWeight();
	SetVariable();
	
	GameInterface.TABLE_LIST.select = 1;
	GameInterface.TABLE_LIST.top = 0;
	GameInterface.TABLE_LIST2.select = 1;
	GameInterface.TABLE_LIST2.top = 0;
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST",0);
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"SCROLL_LIST2",0);
	
	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.tr1.index);
	ShowGoodsInfo(iCurGoodsIdx);
	
	AddToTable(refToChar); // Рефреш таблицы

	// Сброс стрелок на первую позицию
	SetTableArrowsInit();

	// <-- Warship fix 10.06.09
}
// Нажали на табличной стрелочке "взять 1 ед. предмета одного типа"
void onTableAddBtnClick()
{
	string item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refToChar, item);
	
	// Учет перегруза
	int maxItemsToAdd = GetMaxItemsToTake(true, item);
	if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
	if (iItemsQty > 1) iItemsQty = 1;// лок на 1 ед.	
	if(iItemsQty > 0) // fix
	{
		RemoveItems(refToChar, item, iItemsQty);
		AddItems(refCharacter, item, iItemsQty);
		//if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("", 0, 0, 0, 0, 1);
		
		AddToTable(refToChar);
		
		// Обновление текущего веса и т.д.
		SetCharWeight();
		SetVariable();
		
		item = Items[iCurGoodsIdx].id;  // fix
		
		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(refToChar, item);	
	}
}

// Нажали на табличной стрелочке "взять все предметы одного типа"
void onTableAddAllBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refToChar, item);
	
	// Учет перегруза
	int maxItemsToAdd = GetMaxItemsToTake(true, item);
	
	if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
	if(iItemsQty < 1) Log_Info(XI_ConvertString("CharacterOverload"));
	
	if(iItemsQty > 0) // fix
	{
		RemoveItems(refToChar, item, iItemsQty);
		AddItems(refCharacter, item, iItemsQty);
		//if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("", 0, 0, 0, 0, 1);
		
		AddToTable(refToChar);
		
		// Обновление текущего веса и т.д.
		SetCharWeight();
		SetVariable();
		
		item = Items[iCurGoodsIdx].id;  // fix
		
		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(refToChar, item);	
	}
}

// Нажали на табличной стрелочке "отдать все предметы одного типа"
void onTableRemoveAllBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refCharacter, item);
	
	if(IsQuestUsedItem(item) && item != "Gold") return; // Квестовые не отдать, только золото
	
	// Учет перегруза (в сундуки и трупы можно ложить сколько угодно)
	int maxItemsToAdd = GetMaxItemsToTake(false, item);
	
	if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
	//if(maxItems < 0) return 0;
	
	if(iItemsQty > 0) // fix
	{
		RemoveItems(refCharacter, item, iItemsQty);
		AddItems(refToChar, item, iItemsQty);
		//if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("", 0, 0, 0, 0, 1);
		
		AddToTable(refToChar);
		
		// Обновление текущего веса и т.д.
		SetCharWeight();
		SetVariable();
		
		item = Items[iCurGoodsIdx].id;	// fix
		
		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(refToChar, item);	
	}
}

// Нажали на табличной стрелочке "отдать 1 ед. предмета одного типа"
void onTableRemoveBtnClick()
{
	String item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refCharacter, item);
	
	if(IsQuestUsedItem(item) && item != "Gold") return; // Квестовые не отдать, только золото
	
	// Учет перегруза (в сундуки и трупы можно ложить сколько угодно)
	int maxItemsToAdd = GetMaxItemsToTake(false, item);
	
	if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
	if (iItemsQty > 1) iItemsQty = 1;// лок на 1 ед.	
	if(iItemsQty > 0) // fix
	{
		RemoveItems(refCharacter, item, iItemsQty);
		AddItems(refToChar, item, iItemsQty);
		//if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("", 0, 0, 0, 0, 1);
		
		AddToTable(refToChar);
		
		// Обновление текущего веса и т.д.
		SetCharWeight();
		SetVariable();
		
		item = Items[iCurGoodsIdx].id;	// fix
		
		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(refToChar, item);	
	}
}

// инфа о предмете
void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = Items[iGoodIndex].name;
	ref    arItm = &Items[iGoodIndex];
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader = LanguageConvertString(lngFileID, GoodName);

	iCurGoodsIdx = iGoodIndex;
	string describeStr = "";

	if(bBettaTestMode)
	{
		describeStr += "id = " + Items[iCurGoodsIdx].id + NewStr();
	}
	describeStr += GetItemDescribe(iCurGoodsIdx);

	fWeight = stf(Items[iCurGoodsIdx].weight);

	BuyOrSell = 0;
	SetFormatedText("QTY_TypeOperation", "");
	SetFormatedText("QTY_Result", "");
	GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[iCurGoodsIdx].picTexture, "itm" + Items[iCurGoodsIdx].picIndex);
	SetFormatedText("QTY_CAPTION", sHeader);
	SetFormatedText("QTY_GOODS_INFO", describeStr);
	LanguageCloseFile(lngFileID);

	iCharQty 	= GetCharacterFreeItem(refCharacter, Items[iCurGoodsIdx].id);
	iStoreQty 	= GetCharacterFreeItem(refToChar, Items[iCurGoodsIdx].id);
		
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;
}

void TransactionOK()
{
	int nTradeQuantity;
	String list;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if(BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}

 	if(BuyOrSell == 1) // Забираем
	{
		RemoveItems(refToChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		AddItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
    	//if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 1);
	}
 	else // Отдаем
	{
		AddItems(refToChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		RemoveItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
		//if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 1);
	}
	
	AddToTable(refToChar);
	EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
	SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	float iWeight;
	float fRefCharWeight, fRefCharMaxWeight;
	string sInterfaceType = sGetInterfaceType();
	SetCharWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if(sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
	    BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{
			if (BuyOrSell != -1)
			{
		    	GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
		    }
			
		    BuyOrSell = -1;
			
		    // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iCharQty)
		    {
		        GameInterface.qty_edit.str = iCharQty;
		    }
		    
		    if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) // Сундуки и трупы бездонны
		    {
				fRefCharWeight = GetItemsWeight(refToChar);
				fRefCharMaxWeight = GetMaxItemsWeight(refToChar);
				iWeight = (fWeight * sti(GameInterface.qty_edit.str));
				if((fRefCharWeight + iWeight) > fRefCharMaxWeight)
				{
					iWeight = fRefCharMaxWeight - fRefCharWeight - 0.01; // чуть меньше
					if(iWeight < 0) // критический фикс в случае перегруза - просто нулим строку ввода
					{
						GameInterface.qty_edit.str = 0;
					}
					else
					{
						GameInterface.qty_edit.str = makeint(iWeight / fWeight );
						iWeight = fWeight * sti(GameInterface.qty_edit.str);
						GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округление
					}		
				}
		    }
		    // проверка на колво доступное <--
		    // квестовые не продать -->
		    if (IsQuestUsedItem(Items[iCurGoodsIdx].id) && Items[iCurGoodsIdx].id != "Gold")
		    {
		        GameInterface.qty_edit.str = 0;
		    }
		    // квестовые не продать <--
		    SetFormatedText("QTY_TypeOperation", XI_ConvertString("Give goods"));
		}
		else
		{
			BuyOrSell = 1;
			
	        // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if((fCharWeight + iWeight) > iCharCapacity)
		    {
		        iWeight = iCharCapacity - fCharWeight - 0.01; // чуть меньше
				
				if(iWeight < 0) iWeight = 0;
				
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округдение
		    }
		    // проверка на колво доступное <--
			
			SetFormatedText("QTY_TypeOperation", XI_ConvertString("Take goods"));
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetCharWeight();
    fCharWeight  = fCharWeight  + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
    SetVariable();
}

void REMOVE_ALL_BUTTON()  // продать все
{
	if(!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iCharQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	if(!bShowChangeWin)
	{
	    ShowItemInfo();
	}
	
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if(!bShowChangeWin) return;
	
	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -1;
	}
	else
	{
		if(BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
		}
		
		BuyOrSell = 0;
	}
	
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	if(!bShowChangeWin) return;
	
	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = 1;
	}
	else
	{
		if(BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - 1);
		}
		
		BuyOrSell = 0;
	}
	
	ChangeQTY_EDIT();
}

// Сколько ещё могет утащить указанного предмета, в штуках
// mitrokosta переписал  без сравнения ссылок
// take == true, значит берём в refCharacter
int GetMaxItemsToTake(bool take, String _item) {
	float curWeight;
	int maxItems, maxWeight;
	
	if (take) {
		curWeight = fCharWeight;
		maxWeight = GetMaxItemsWeight(refCharacter);
	}
	else {
		curWeight = fStoreWeight;
		maxWeight = GetMaxItemsWeight(refToChar);
	}
	
	float itemWeight = stf(Items[GetItemIndex(_item)].weight);
	
	// Это золото и прочая байда - лезла ошибка деления на нуль
	if(itemWeight == 0) {
		return 1000000000;
	}
	
	maxItems = MakeInt((maxWeight - curWeight) / itemWeight);
	if(maxItems < 0) {
		return 0;
	}	
	
	return maxItems;
}

void OfficerReincarnation(ref rPassanger);
{
	ref rOff = GetCharacter(NPC_GenerateCharacter("Clon", "none", rPassanger.sex, rPassanger.model.animation, 1, sti(rPassanger.nation), -1, false, "officer"));
	ChangeAttributesFromCharacter(rOff, rPassanger, true);
	rOff.id = rPassanger.id;
	LAi_SetCurHPMax(rOff);
	RemoveCharacterEquip(rOff, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(rOff, GUN_ITEM_TYPE);
	RemoveCharacterEquip(rOff, MUSKET_ITEM_TYPE);
	RemoveCharacterEquip(rOff, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(rOff, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(rOff, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(rOff, MAPS_ITEM_TYPE);
	DeleteAttribute(rOff, "items");
	rOff.items = "";
	DeleteAttribute(rOff, "isMusketer.weapon");
	DeleteAttribute(pchar, "items.mushket2x2");
	AddPassenger(pchar, rOff, false);
	Log_Info(XI_ConvertString("fighter") + " " + GetFullName(rOff) + " " + XI_ConvertString("Resuscitated") + ".");
}

// проверка на наличие последнего предмета
bool CheckLastItemOnDead()
{
	if(CheckAttribute(&GameInterface, "TABLE_LIST2.tr1.index"))
		iCurGoodsIdx = sti(GameInterface.TABLE_LIST2.tr1.index);
    if(iCurGoodsIdx < 1)
        return false;

    string itemID = Items[iCurGoodsIdx].id;
    if(!CheckAttribute(refToChar, "Items." + itemID) || sti(refToChar.Items.(itemID)) < 1)
        return false;

    return true;
}
