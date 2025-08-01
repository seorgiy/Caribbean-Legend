#include "items\items.h"

object randItemModels[MAX_LOADED_RANDITEMS];
object itemModels[2];
SetArraySize(&itemModels, ITEMS_QUANTITY);
object buttonModels[MAX_BUTTONS];

aref useLocators[MAX_BUTTONS];
aref useAttrs[MAX_BUTTONS];
int  useLocatorsCount=0;

int iScriptItemStartNum=0;
int iScriptItemEndNum=0;
int iScriptItemCount=0;

float SPAWN_TIME = 168.0; //hours = 168.0

object newItemModels[64];
int newItemModelsCount = 0;

void Items_LoadModel (ref _itemModel, ref _item)
{
	if (!IsEntity(&_itemModel))
	{
		string itemFolder = "items";
		CreateEntity(&_itemModel, "MODELR");
		if (CheckAttribute(_item, "folder"))
			itemFolder = _item.folder;
		SendMessage(&_itemModel, "ls", MSG_MODEL_SET_DIRPATH, itemFolder+"\");
		SendMessage(&_itemModel, "ls", MSG_MODEL_LOAD_GEO, itemFolder + "\" + _item.model);
		SendMessage(&_itemModel, "ls", MSG_MODEL_SET_DIRPATH,"");
		SendMessage(&_itemModel, "ls", MSG_MODEL_SET_TECHNIQUE, "RandItem");
		if(itemFolder == "ammo")
			SendMessage(&_itemModel, "lslff", MSG_MODEL_BLEND, "blenditem", 1000, 0.0, 1.0);
		LayerAddObject(EXECUTE, &_itemModel, ITEMS_LAYER);
		LayerAddObject(REALIZE, &_itemModel, ITEMS_LAYER);

		//Trace("ItemLogic: Loaded model "+itemFolder+"\"+_item.model);
	}
}

void Item_OnLoadLocation(string currentLocation)
{
	//Trace("ItemLogic: On load location "+currentLocation);

	// precache active locators in current location
	aref   activeLocation;
	ref chr = GetMainCharacter();
	int currentLocationIndex = FindLocation(currentlocation);
	chr.itemLocationIndex = currentLocationIndex;
	aref aloc, an, al;
	useLocatorsCount = 0;
	makearef(activeLocation, Locations[currentLocationIndex]);
	makearef (aloc, activeLocation.items);
	for (int i=0; i<GetAttributesNum(aloc); i++)
	{
		an = GetAttributeN(aloc, i);
		if (!CheckAttribute(an,"locator"))
			continue;
		if (!FindLocator(activeLocation.id, an.locator, &al, true))
			continue;

		useLocators[useLocatorsCount] = al;
		useAttrs[useLocatorsCount] = an;
		useLocatorsCount++;
	}
	
	newItemModelsCount = 0;
	
	// Warship 11.05.09 удаление неиспользующихся предметов
	/*
	if(!actLoadFlag) // FIX При лоаде прогружается лока - все че было нагенерено терлось с сундука
	{
		RefreshGeneratedItems();
	}
	*/
	// load buttons & items
	Items_ShowButtons(currentLocation);
	RandItems_OnLoadLocation(activeLocation);
	Box_OnLoadLocation(activeLocation);
	
	// показ предметов в локаторах new
	aref itemShow;
	makearef(itemShow, activeLocation.itemShow);
	int numAttrs = GetAttributesNum(itemShow);
	for (i = 0; i < numAttrs; i++) {
		aloc = GetAttributeN(itemShow, i);
		Items_ShowItemNew(GetAttributeName(aloc), GetItemIndex(GetAttributeValue(aloc)));
	}

	for (int itemN=0; itemN<ITEMS_QUANTITY; itemN++)
	{
		if (!CheckAttribute(&Items[itemN], "startLocator"))
			continue;
		if (!CheckAttribute(&Items[itemN], "startLocation"))
			continue;
		if (!CheckAttribute(&Items[itemN], "shown"))
			continue;
		if (Items[itemN].shown == "1")
		{
			if (Items[itemN].startLocation == currentLocation)
			{
				if (!CheckAttribute(activeLocation, "itemShow." + Items[itemN].startLocator)) {
					Items_ShowItem(itemN);
				}
			}
		}
	}
}

void Item_OnUnLoadLocation()
{
	SetArraySize(&itemModels, ITEMS_QUANTITY);
	//Trace("ItemLogic: On unload location");
	for (int itemN=0; itemN<ITEMS_QUANTITY; itemN++)
	{
		if (IsEntity(&itemModels[itemN]))
			DeleteClass(&itemModels[itemN]);
	}
	
	for (int i = 0; i < 64; i++) {
		if (IsEntity(&newItemModels[i])) {
			DeleteClass(&newItemModels[i]);
		}
	}
	
	for (int buttonN=0; buttonN<MAX_BUTTONS; buttonN++)
	{
		if (IsEntity(&buttonModels[buttonN]))
			DeleteClass(&buttonModels[buttonN]);
	}

	RandItems_OnUnloadLocation();

	ref chr = GetMainCharacter();
	chr.itemLocationIndex = -1;
}

void Item_OnEnterLocator(aref _location, string _locator)
{
	//Trace("ItemLogic: Entered locator "+_locator);
	ref chr = GetMainCharacter();
	int itemN;
	
	if (findsubstr(_locator, "button", 0) != -1)
	{ // use item
		for (itemN=ItemsForLocators_start; itemN<ItemsForLocators_end; itemN++)
		{
			if (!CheckAttribute(&Items[itemN], "useLocator"))
				continue;
			if (!CheckAttribute(&Items[itemN], "useLocation"))
				continue;
			if (!CheckAttribute(&Items[itemN], "shown"))
				continue;
			if (Items[itemN].shown == "0")
			{
				if (Items[itemN].useLocation == _location.id)
				{
					if (Items[itemN].useLocator == _locator)
					{
						Log_SetActiveAction("Action");
						chr.activeItem = itemN;
						chr.activeLocator = _locator;
						chr.activeRandItem = false;
						chr.activeItem.pick = false;
					}
				}
			}
		}
	}
	else
	{
		if (CheckAttribute(_location, "itemShow." + _locator)) {
			Log_SetActiveAction("Pick");
			chr.activeItem = GetItemIndex(_location.itemShow.(_locator));
			chr.activeLocator = _locator;
			chr.activeRandItem = false;
			chr.activeItem.pick = true;
		} else {
			for (itemN=ItemsForLocators_start; itemN<ItemsForLocators_end; itemN++)
			{
				if (!CheckAttribute(&Items[itemN], "startLocator"))
					continue;
				if (!CheckAttribute(&Items[itemN], "startLocation"))
					continue;
				if (!CheckAttribute(&Items[itemN], "shown"))
					continue;
				if (Items[itemN].startLocator == _locator)
				{
					if (Items[itemN].shown == "1")
					{
						if (Items[itemN].startLocation == _location.id)
						{
							Log_SetActiveAction("Pick");
							chr.activeItem = itemN;
							chr.activeLocator = _locator;
							chr.activeRandItem = false;
							chr.activeItem.pick = true;
						}
					}
				}
			}
		}
	}
    // ===> eddy. проверка вхождения ГГ в локаторы группы Item.
    QuestCheckEnterLocItem(_location, _locator);
    // <===
	BLI_RefreshCommandMenu();
}

void Item_OnExitLocator(aref _location, string _locator)
{
	Log_SetActiveAction("Nothing");
	Characters[GetMainCharacterIndex()].activeItem = "";
	BLI_RefreshCommandMenu();
    // ===> eddy. проверка выхождения ГГ из локаторов группы Item.
    QuestCheckExitLocItem(_location, _locator);
    // <===
}

void Item_OnPickItem()
{
	Log_SetActiveAction("Nothing");
	aref activeLocation;
	ref chr = GetMainCharacter();
	makearef(activeLocation, Locations[sti(chr.itemLocationIndex)]);

	int langFile = LanguageOpenFile("ItemsDescribe.txt");
	string displayItemName, youvegotString;
	youvegotString = LanguageConvertString(langFile, "youve_gotNotif");
	PlayStereoSound("interface\important_item.wav");

	if (chr.activeRandItem == true)
	{
		string activeRandItemAttribute = "RandItemType"+sti(chr.activeItem);
		if (CheckAttribute(activeLocation, activeRandItemAttribute))
		{
			SendMessage(&randItemModels[sti(chr.activeItem)], "lslff", MSG_MODEL_BLEND, "blenditemlit", 1000, 1.0, 0.0);
			GenerateAndAddItems(GetMainCharacter(), Items[sti(activeLocation.(activeRandItemAttribute))].id, 1);
			displayItemName = LanguageConvertString(langFile, Items[sti(activeLocation.(activeRandItemAttribute))].name);
			//Log_SetStringToLog(youvegotString+" "+displayItemName+"!");
			//notification(youvegotString+" "+displayItemName+"", "BoxPlus");

			activeLocation.(activeRandItemAttribute) = -1;
		}
	}
	else
	{
		int activeItem = sti(chr.activeItem);
		string locator = chr.activeLocator;
		//Trace("ItemLogic: picking item "+Items[activeItem].id);
		QuestPointerDelLoc(activeLocation.id, "item", locator);
		
		if(HasSubStr(Items[activeItem].id, "cannabis"))
		{
			notification(LanguageConvertString(langFile, "flower_find"), "Alchemy");
			if(Items[activeItem].id == "cannabis7")
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 10.0);
			else
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 2.0);
		}
		
		ref itemModel;
		if (CheckAttribute(activeLocation, "itemShow." + locator + ".modelIndex")) {
			itemModel = &newItemModels[sti(activeLocation.itemShow.(locator).modelIndex)];
			DeleteAttribute(activeLocation, "itemShow." + locator);
		} else {
			itemModel = &itemModels[activeItem];
			Items[activeItem].shown = false;
		}
		SendMessage(itemModel, "lslff", MSG_MODEL_BLEND, "blenditemlit", 1000, 1.0, 0.0);
		GenerateAndAddItems(GetMainCharacter(), Items[activeItem].id, 1);

		displayItemName = LanguageConvertString(langFile, Items[activeItem].name);
		//Log_SetStringToLog(youvegotString+" "+displayItemName+"!");
		// ===> перехват взятия предметов из локатора item на метод обрабоки для квестовых нужд 
		QuestCheckTakeItem(activeLocation, Items[activeItem].id);
		// <===
	}
	DeleteAttribute(chr,"activeItem");
	LanguageCloseFile(langFile);
	QuestsCheck(); // legendary edition
}

void Item_OnUseItem()
{
	aref aloc, an, al;
	aref activeLocation;
	ref chr = GetMainCharacter();
	int activeItem = sti(chr.activeItem);
	makearef(activeLocation, Locations[sti(chr.itemLocationIndex)]);

	makearef (aloc, activeLocation.items);
	// boal баг! нет предмета, а он работает!!!
    if (!CheckCharacterItem(chr, Items[activeItem].id))
    {
		Log_SetStringToLog(XI_ConvertString("You have not need item"));
        PlaySound("interface\knock.wav");
        return;
    }
    Log_SetActiveAction("Nothing");
	//Log_SetStringToLog("Using "+Items[activeItem].id);
	//Trace("ItemLogic: using item "+Items[activeItem].id);
	Items[activeItem].shown = true;
	Items[activeItem].shown.used = true; //использован
	Items_LoadModel(&itemModels[activeItem], &Items[activeItem]);

	FindLocator(activeLocation.id, chr.activeLocator, &al, true);
	SendMessage(&itemModels[activeItem], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
	SendMessage(&itemModels[activeItem], "lslff", MSG_MODEL_BLEND, "blenditem", 1000, 0.0, 1.0);

	SetEventHandler("frame", "Item_OnUseFrame", 0);
	TakeItemFromCharacter(GetMainCharacter(), Items[activeItem].id);
	Items[activeItem].startLocator = "";
	al.active = true;
	al.timePassed = 0;

	int langFile = LanguageOpenFile("ItemsDescribe.txt");
	string displayItemName, youvegotString;
	youvegotString = LanguageConvertString(langFile, "used_itemNotif");
	displayItemName = LanguageConvertString(langFile, Items[activeItem].name);
	//Log_SetStringToLog(youvegotString+" "+displayItemName+"!");
	notification(youvegotString+" "+displayItemName+"!", "BoxMinus");
    PlaySound("interface\sobitie_na_karte_001.wav");

    // ===> перехват на метод обрабоки для квестовых нужд при опускании предмета в локаторы button. Эдди.
    QuestCheckUseButton(activeLocation, chr.activeLocator, Items[activeItem].id);
    // <===
	DeleteAttribute(chr,"activeItem");
	
	CompleteQuestName("OnUse_"+Items[activeItem].id, "");
}

void Item_OnUseFrame()
{
	aref aloc, an, al;
	aref activeLocation;
	ref chr = GetMainCharacter();

    if (CheckAttribute(chr, "itemLocationIndex") && sti(chr.itemLocationIndex) > 0) // boal fix 230804
    {
    	makearef(activeLocation, Locations[sti(chr.itemLocationIndex)]);

    	makearef (aloc, activeLocation.items);
    	bool usedOnFrame=false;
    	for (int i=0; i<useLocatorsCount; i++)
    	{
    		an = useAttrs[i];
    		al = useLocators[i];
    		if (!CheckAttribute(al, "active"))
    			continue;
    		if (al.active != "1")
    			continue;
    		int timePassed = sti(al.timePassed) + GetDeltaTime();
    		al.timePassed = timePassed;
    		if (timePassed > BUTTON_ACTIVATION_TIME)
    		{
    			al.active = false;
    			continue;
    		}

    		usedOnFrame = true;
    		float timeK = makefloat(timePassed) / makefloat(BUTTON_ACTIVATION_TIME);
    		float deltaY = makefloat(an.deltaY) * timeK;

    		SendMessage(&buttonModels[i], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y)+deltaY, makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));

    		for (int j=0; j<ITEMS_QUANTITY; j++) // TO_DO: ДИЧЬ
    		{
    			if (Items[j].useLocator == an.locator)
    			{
    				SendMessage(&itemModels[j], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y)+makeFloat(an.itemDeltaY)+deltaY, makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
    				break;
    			}
    		}
    	}
    }
    else
    {
        if (MOD_BETTATESTMODE == "On") Log_Info("Error: Item_OnUseFrame нет mch.itemLocationIndex ");
    }
	if (!usedOnFrame)
		DelEventHandler("frame", "Item_OnUseFrame");
}

void Items_ShowButtons(string _locationName)
{
	aref al;
	//Trace("ItemLogic: found "+useLocatorsCount+" buttons");
	for (int i=0; i<useLocatorsCount; i++)
	{
		Items_LoadModel(&buttonModels[i], &useAttrs[i]);
		al = useLocators[i];
		if (useAttrs[i].trigged != "1")
			SendMessage(&buttonModels[i], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
		else
			SendMessage(&buttonModels[i], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y)+makefloat(useAttrs[i].deltaY), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
	}
}

void Items_ShowItem(int _itemN)
{
	aref al;
	aref activeLocation;
	ref chr = GetMainCharacter();
	makearef(activeLocation, Locations[sti(chr.itemLocationIndex)]);

	if (Items[_itemN].model == "")
	{
		Trace("ItemLogic: no model for item "+activeLocation.id+"."+Items[_itemN].id);
		return;
	}

	if (Items[_itemN].startLocator != "")
	{ //unused
		Items_LoadModel(&itemModels[_itemN], &Items[_itemN]);

		if (!FindLocator(Items[_itemN].startLocation, Items[_itemN].startLocator, &al, true))
		{
			Trace("ItemLogic: locator for item "+_itemN+" not found! ["+Items[_itemN].startLocation+">>"+Items[_itemN].startLocator);
		}
		else
		{	
			Trace ("ItemLogic: showing item at "+al.x+", "+al.y+", "+al.z);
			SendMessage(&itemModels[_itemN], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
		}	
	}
	else
	{ //used
		if (Items[_itemN].useLocation != activeLocation.id)
			return;

		Items_LoadModel(&itemModels[_itemN], &Items[_itemN]);

		for (int i=0; i<useLocatorsCount; i++)
		{
			al = useLocators[i];
			if (useAttrs[i].locator == Items[_itemN].useLocator)
			{
				SendMessage(&itemModels[i], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y)+makeFloat(useAttrs[i].itemDeltaY)+makeFloat(useAttrs[i].deltaY), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
				return;
			}
		}
	}
}

void Items_ShowItemNew(string locator, int _itemN) {
	aref al;
	aref activeLocation;
	ref chr = GetMainCharacter();
	makearef(activeLocation, Locations[sti(chr.itemLocationIndex)]);
	
	int modelIndex = newItemModelsCount;
	if (modelIndex >= 64) {
		trace("Items_ShowItemNew: >= 64 items!");
		return;
	}
	newItemModelsCount++;

	if (_itemN < 0) {
		trace("Items_ShowItemNew: item not found!!!");
	}

	if (Items[_itemN].model == "")
	{
		Trace("ItemLogic: no model for item "+activeLocation.id+"."+Items[_itemN].id);
		return;
	}

	activeLocation.itemShow.(locator).modelIndex = modelIndex;

	Items_LoadModel(&newItemModels[modelIndex], &Items[_itemN]);
	if (!FindLocator(activeLocation.id, locator, &al, true)) {
		trace("ItemLogic: locator for item "+_itemN+" not found! ["+activeLocation.id+">>"+locator);
	} else {
		Trace ("ItemLogic: showing item at "+al.x+", "+al.y+", "+al.z);
		SendMessage(&newItemModels[modelIndex], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
	}
}

void Items_HideItem(int itemN)
{
}

int Items_FindItem(string itemID, ref itemARef)
{
	int idx = FindItem(itemID);
    if (idx >= 0) makearef(itemARef,Items[idx]);
	return idx;
}

int Items_FindItemIdx(string itemID) // нужно для поиска только номера
{
	return GetItemIndex(itemID);
}

// ************** RANDOM ITEMS *****************
void RandItems_OnLoadLocation(ref _location)
{
	string locatorName;
	aref randItemLocator;
	for (int i=1; i<MAX_LOADED_RANDITEMS; i++)
	{
		string lastSpawnTimeString = "LastSpawnTime"+i;
		string randItemTypeString = "RandItemType"+i;
		locatorName = "randitem"+i;
		if (!FindLocator(_location.id, locatorName, &randItemlocator, true))
			break;

        // boal -->
        if (!SetLocationQuestRandItem(i, _location, locatorName, randItemLocator))
        {
        // boal <--
            // randitem locator found
    		if (CheckAttribute(_location, lastSpawnTimeString))
    		{ // already spawned?
    			if (CheckAttribute(_location, randItemTypeString))
    			{
    				if (sti(_location.(randItemTypeString)) != -1)
    				{
    					RandItems_DrawRandItem(i, _location, randItemLocator);
    				}
    				else
    				{ //already picked up, try to respawn
    					if ((stf(_location.(lastSpawnTimeString))+SPAWN_TIME) < Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()))
    					{
    						RandItems_SpawnRandItem(i, _location, randItemLocator);
    					}
    				}
    			}
    			else
    			{ // nothing here
    				if ((stf(_location.(lastSpawnTimeString))+SPAWN_TIME) < Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()))
    				{
    					RandItems_SpawnRandItem(i, _location, randItemLocator);
    				}
    			}
    		}
    		else
    		{
    			RandItems_SpawnRandItem(i, _location, randItemLocator);
    		}
		}
	}
}

void RandItems_OnUnloadLocation()
{
	for (int itemN=0; itemN<MAX_LOADED_RANDITEMS; itemN++)
	{
		if (IsEntity(&randItemModels[itemN]))
			DeleteClass(&randItemModels[itemN]);
	}
}

float Items_MakeTime (float _h, float _d, float _m, float _y)
{
	return (_h+24.0*(_d + 30.0*(_m + 12.0*_y)));
}

void RandItems_SpawnRandItem(int _index, aref _location, aref al)
{
	aref randItem;
	string lastSpawnTimeString;
	int n;

	string alName = GetAttributeName(al);
	string alNameAttribute = "items."+alName;
	if (CheckAttribute(_location, alNameAttribute))
	{
		n = Items_FindItem(_location.items.(alName), &randItem);
		if (n == -1)
			return;

		lastSpawnTimeString = "LastSpawnTime"+_index;
		_location.(lastSpawnTimeString) = Items_MakeTime(0, 15, 1, 2003);
	}
	else
	{
		n = Items_FindItem(RandItems[rand(RANDITEMS_QUANTITY-1)].id, &randItem);
		if (n == -1)
			return;

		lastSpawnTimeString = "LastSpawnTime"+_index;
		_location.(lastSpawnTimeString) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	}
	
    if (GetCharacterSkillToOld(GetMainCharacter(), SKILL_FORTUNE) < rand(15)) return; // boal fix
    
	if (!CheckAttribute(randItem, "model") || randItem.model == "")
	{
		Trace("ItemLogic: no model for item "+_location.id+"."+randItem.id);
		return;
	}

	Items_LoadModel(&randItemModels[_index],  randItem);
	SendMessage(&randItemModels[_index], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));

	lastSpawnTimeString = "RandItemType"+_index;
	_location.(lastSpawnTimeString) = n;
}

void RandItems_DrawRandItem(int _index, aref _location, aref al)
{
	string randItemTypeString = "RandItemType"+_index;
	int n = sti(_location.(randItemTypeString));
	
    if (GetCharacterSkillToOld(GetMainCharacter(), SKILL_FORTUNE) < rand(15)) return; // boal fix
    
	if (Items[n].model == "")
	{
		Trace("ItemLogic: no model for item "+_location.id+"."+Items[n].id);
		return;
	}
	
	Items_LoadModel(&randItemModels[_index],  &Items[n]);
	SendMessage(&randItemModels[_index], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
}

void RandItem_OnEnterLocator(aref _location, string _locator)
{

    int randIndex = sti(strcut(_locator, 8, strlen(_locator)-1));
	string randItemAttribute = "RandItemType"+randIndex;
	ref chr = GetMainCharacter();
	if (CheckAttribute(_location, randItemAttribute))
	{
		int currentType = sti(_location.(RandItemAttribute));
		if (currentType != -1)
		{
			Log_SetActiveAction("Pick");
			chr.activeItem = randIndex;
			chr.activeLocator = _locator;
			chr.activeRandItem = true;
			chr.activeItem.pick = true;
			BLI_RefreshCommandMenu();
		}
	}
}

// ****************** BOXES ********************
void Box_EnterToLocator(aref loc, string locName)
{
	if(!CheckAttribute(loc,locName)) return;
	
	if(HasSubStr(locName, "private"))
	{
		// check if private box opened
		if(!CheckAttribute(loc, locName+".opened"))
			{
			if(CheckAttribute(loc, locName+".key")) 
			{
				bool bOk = (CheckAttribute(loc, locName+".skel")) && (CheckCharacterItem(pchar, "keys_skel"))
				if(CheckCharacterItem(pchar, loc.(locName).key) || bOk) //проверяем ключ и отмычки
				{
					loc.(locName).opened = true;
					PlaySound("interface\key.wav");
					if(!bOk) notification(XI_ConvertString("BoxKeyOpened"), "Key");
					if(!CheckCharacterItem(pchar, loc.(locName).key)) notification(XI_ConvertString("BoxOpened"), "Key");
					
					if(CheckAttribute(loc, locName+".key.delItem"))
					{
						TakeItemFromCharacter(pchar, loc.(locName).key); //забрать ключ
					}
					//--> квестовые ситуации
					if (pchar.location == "Tartarusprison" && CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "LSC" && loc.(locName).key == "crowbar")
					{
							DoQuestFunctionDelay("LSC_ChadGuardAttack", 7.0);
						}
						if (pchar.location == "CarolineBank" && loc.(locName).key == "key_facioQ")
						{
							DoQuestCheckDelay("LSC_DrinkInCarolina", 1.0);
						}
						if (pchar.location == "Tortuga_townhallRoom" && loc.(locName).key == "kaleuche_key" && CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "chest")
						{ // Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
							chrDisableReloadToLocation = true;
							DoQuestFunctionDelay("FMQT_MercenEnter", 7.0);
							pchar.questTemp.FMQT.Open = "true";
						}
						//<-- квестовые ситуации
					}
					else 
					{
						if (CheckCharacterItem(pchar, "keys_skel")) notification(XI_ConvertString("BoxClosed"), "none");
						notification(XI_ConvertString("You have not need key"), "Key");
						PlaySound("interface\box_locked.wav");
						return;
				}
			}
			else
			{	
				if(CheckAttribute(loc, locName+".closed")) //проверяем, не закрыт ли сундук
				{
					notification(XI_ConvertString("Box is closed"), "none");
					PlaySound("interface\door_locked.wav");
					return;
			}
		}
	}
	}
	
	// Warship 15.08.09 Проверка на квестовую закрытость сундуков (не только приватов, вообще всех)
	if(CheckAttribute(loc, locName + ".QuestClosed"))
	{
		notification(XI_ConvertString("Box is closed"), "none");
		PlaySound("interface\door_locked.wav");
		return;
	}
	if(CheckAttribute(loc, locName + ".NotChest")) // Jason: для выброшенных на берег сундуков
	{
		Log_Testinfo("Нет доступа");
		return;
	}
	
		pchar.boxname = locName;
		Log_SetActiveAction("OpenBox");
		BLI_RefreshCommandMenu();
	}

void Box_ExitFromLocator(aref loc, string locName)
{
	DeleteAttribute(GetMainCharacter(),"boxname");
	Log_SetActiveAction("Nothing");
	BLI_RefreshCommandMenu();
}

void OpenBoxProcedure()
{
	ref chr = GetMainCharacter();
	if( !CheckAttribute(chr,"boxname") ) return;
	int locidx = FindLoadedLocation();
	if(locidx<0) return;
	string atrName = chr.boxname;
	aref ar;
	makearef(ar,Locations[locidx].(atrName));
	if(GetAttributesNum(ar)==0)
	{
		Locations[locidx].(atrName).Money = 0;
		makearef(ar,Locations[locidx].(atrName));
	}
	// God_hit_us  это такой прикол - задействовать в ловушки для сундуков(boal)
	// токо сундуки и дома
	if (sti(chr.GenQuest.God_hit_us) == 1 && rand(100) >= (85 + GetCharacterSkillToOld(chr, SKILL_FORTUNE)) && chr.location != "SentJons_HouseF3_Room2" && chr.location != "IslaMona_TwoFloorHouse" && chr.location != "IslaMona_TwoFloorRoom" && chr.location != "SantaCatalina_houseSp3_bedroom") // 280313 лесник сняты ловушки с исла моны.
	{
		Log_Info(XI_ConvertString("Trap"));
		PlaySound("people\clothes1.wav");
		DoQuestCheckDelay("God_hit_us", 0.2);
	}
	else
	{
		if (CheckAttribute(chr, "questTemp.Guardoftruth.ArchyBoom") && chr.location == "IslaDeVieques_House" && atrName == "box1") GuardOT_ArchyChestBoom(); // Jason 070712
		else
		{
			if (CheckAttribute(chr, "questTemp.Ksochitam.ShoreShip") && chr.location == "Shore_ship4") Ksochitam_ShoreshipOpenBox(); // Jason 220712
			else 
			{
				// сюда можно ставить квестовые реакции при открытии сундука с выводом интерфейса содержимого
				if (CheckAttribute(chr, "questTemp.Mtraxx.Grotbox") && chr.location == "PortoBello_Cave" && atrName == "box1") Mtraxx_WolfreekGrotOpenBox(); // Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(chr, "questTemp.Mtraxx.Cavebox") && chr.location == "Panama_Cave" && atrName == "box1") Mtraxx_WolfreekCaveOpenBox();
				if (CheckAttribute(chr, "questTemp.Mtraxx.WolfreekBox") && chr.location == "IslaMona_WaterCave" && atrName == "private1") Mtraxx_WolfreekFindTreasure();
				if (CheckAttribute(chr, "questTemp.Mtraxx.Pasquale.Grabbing") && chr.location == "LaVega_TwoFloorHouse" && atrName == "private1") Mtraxx_PasqualeCheckChest();
				if (CheckAttribute(chr, "questTemp.HelenDrinking.Loot.Box") && chr.location == "SantaCatalina_PearlCave" && atrName == pchar.questTemp.HelenDrinking.Loot.Box.Id) {
					if (CheckAttribute(chr, "questTemp.HelenDrinking.GoForLoot")) {
						HelenDrinking_GotLoot();
					}
					HelenDrinking_ClearLootChest();
				}
				LaunchItemsBox(&ar);
			}
		}
	}
}

void Box_OnLoadLocation(ref _location)
{
	string locatorName;
	aref boxLocator;
	int i;
	bool isAbordageBox = false;
	if (CheckAttribute(_location, "boarding"))
	{
		if (_location.boarding == "true")
		{
            if (isShipInside(_location.id) || _location.id == "Deck_Near_Ship")// boal fix 08.01.04
            {
                isAbordageBox = false;
            }
            else
            {
	            isAbordageBox = true;
            }
		}
	}

       
	// private box
	for (i=1; i < MAX_HANDLED_BOXES; i++)
	{
		locatorName = "private"+i;
		if (!FindLocator(_location.id, locatorName, &boxlocator, true))
		{
			break;
		}

		if (!CheckAttribute(_location, locatorName))
		{
			_location.(locatorName) = "";
			_location.(locatorName).open = true;
		}
/*		
		// Warship генерим предметы в сундуке
		if(!CheckAttribute(_location, locatorName + ".opened")) 
		{
			makearef(boxLocator, _location.(locatorName));
			FillGenerableItemsForChest(boxLocator);
		}	
*/		
	}

	// simple box
	for (i=1; i < MAX_HANDLED_BOXES; i++)
	{
		locatorName = "box"+i;
		if (!FindLocator(_location.id, locatorName, &boxlocator, true))
		{
			break;
		}

		// found box
		bool needRespawn;
		// boal -->
		//needRespawn = true;
	    needRespawn = SetLocationQuestBox(_location, locatorName);
				
		if (!needRespawn)
		{
		// boal <--
    		if (!CheckAttribute(_location, (locatorName)))
    		{
    			needRespawn = true;
    			_location.(locatorName) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
    		}
    		else
    		{
    			if ((sti(_location.(locatorName)) + SPAWN_TIME) < Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()))
    			{
    				needRespawn = true;
    				_location.(locatorName) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
    			}
    			else
    			{
    				needRespawn = false;
    			}
    		}
            if (isShipInside(_location.id) || _location.id == "Deck_Near_Ship")// boal fix 08.01.04
            {
                needRespawn = false;
            }
            //aref boxItems;
            //aref boxRef;
            //string boxItemName;
            //int k;
            // перетираем общие сундуки boal 11/03/06 -->
            if (!needRespawn && CheckAttribute(_location, "MustSetReloadBack"))
            {
                //clear items in box
    			if (CheckAttribute(_location, locatorName))
    			{
                    DeleteAttribute(_location, locatorName + ".items");
				    _location.(locatorName).items = "";
				    _location.(locatorName).money = 0;
    			}
            }
			// <--
            
    		//respawn items in box
    		if (needRespawn || isAbordageBox)
    		{
    			//clear items in box
    			if (CheckAttribute(_location, locatorName))
    			{
    				/*makearef(boxRef, _location.(locatorName));
    				_location.(locatorName).money = 0; //fix
    				if (CheckAttribute(boxRef, "items"))
    				{
    					makearef(boxItems, boxRef.items);
    					DeleteAttribute(boxItems,  "");
    					for (k=0; k<GetAttributesNum(boxItems);k++)
    					{
    						boxItemName = GetAttributeName(boxItems, k);
    						DeleteAttribute(boxItems, boxItemName);
    					}
    				} */
    				DeleteAttribute(_location, locatorName + ".items");
    				DeleteAttribute(_location, locatorName + ".Treasure"); // признак сокровища в сундуке boal
				    _location.(locatorName).items = "";
				    _location.(locatorName).money = 0;
    			}

    			//fill box with new items
    			string goodItemName;
    			int spawnItemsCount = OBJECTS_IN_BOX;
    			ref chr = GetMainCharacter();
    			spawnItemsCount = spawnItemsCount + spawnItemsCount * GetCharacterSkillToOld(chr, "Fortune") / 10.0;
				// belamour legendary edition крафтовый инструментарий в сундук верфи -->
				if(hrand(99, _location.id) <= makeint(1 + GetCharacterSPECIALSimple(chr, SPECIAL_L) - 4))
				{
					if(CheckAttribute(_location,"id.label") && _location.id.label == "Shipyard" && CheckAttribute(_location,"box1"))
					{
						log_testinfo("Сгенерировался крафтовый инструментарий");
						if(GetDataDay() <  16) _location.box1.items.mechanic_tool = 1;
						else _location.box1.items.Tailor_Tool = 1;
					}
				}
				// <-- портняжный и слесарный инструмент
    			for (int j=0; j<spawnItemsCount; j++)
    			{
    				if (needRespawn || isAbordageBox)
    				{
    					string itemID;
    					if (SpawnItem(chr, &itemID,isAbordageBox, GetCharacterSkillToOld(chr, "Fortune")))
    					{
    						if (CheckAttribute(_location, locatorName+".items."+itemID))
    						{
    							_location.(locatorName).items.(itemID) = sti(_location.(locatorName).items.(itemID)) + 1;
    						}
    						else
    						{
    							_location.(locatorName).items.(itemID) = 1;
    						}
    					}
    				}

    			}
				if (needRespawn || isAbordageBox) // это должно быть здесь когда уже известно значение переменной needRespawn
				{
					// Warship генерим предметы в сундуке
					makearef(boxLocator, _location.(locatorName));
					FillGenerableItemsForChest(boxLocator);
				}
    		}//respawn
		}

	} //for(i)
}

// Warship Для новой системы - перебор итемов для генерации, т.к. везде ложится по-старинке - items.(itemID) = n, а генерить нужно
void FillGenerableItemsForChest(aref _chest)
{
	int i, count;
	String itemID;
	
	aref chestItems;
	aref item;
	
	makearef(chestItems, _chest.items);
	
	for(i = 0; i < GetAttributesNum(chestItems); i++)
	{
		item = GetAttributeN(chestItems, i);
		itemID = GetAttributeName(item);
		
		if(IsGenerableItem(itemID))
		{
			count = sti(chestItems.(itemID));
			DeleteAttribute(chestItems, itemID);
			
			itemID = GetGeneratedItem(itemID);
			chestItems.(itemID) = count;
		}
	}
}

bool SpawnItem(ref _chr, ref _id, bool isAbordageBox, float luck)
{
	int i = rand(RANDITEMS_QUANTITY-1);
	int chrRank = sti(_chr.rank);
	int itemRank = 0;
	aref randItem;
	if (Items_FindItem(RandItems[i].id, &randItem) == -1)
	{
		return false;
	}
	if (CheckAttribute(randItem, "minLevel"))
	{
		itemRank = sti(randItem.minLevel);
	}
	if (itemRank > chrRank)
	{
		return false;
	}

	float itemProb = 0.05;
	if (CheckAttribute(randItem, "rare"))
	{
		itemProb = stf(randItem.rare);
	}
	if (isAbordageBox)
	{
		itemProb = itemProb * (1.5 + luck/20.0);
	}
	if (itemProb > 1.0)
	{
		itemProb = 1.0;
	}
	int rndNumber = rand(1000);
	if (rndNumber > (itemProb*1000))
	{
		return false;
	}
	// отличные клинки в сундуках больше не генерятся <-- ugeen
	if(CheckAttribute(randItem,"quality") && sti(randItem.quality) >= B_EXCELLENT)
	{
		return false;
	}
	
	_id = GetGeneratedItem(randItem.id);
	return true;
}

// mitrokosta установить предмет в локации
void SetItemInLocation(string itemID, string location, string locator) {
	int index = FindLocation(location);
	if (index < 0) {
		return;
	}
	
	locations[index].itemShow.(locator) = itemID;
}

// mitrokosta убрать предмет из локации
void RemoveItemFromLocation(string location, string locator) {
	int index = FindLocation(location);
	if (index < 0) {
		return;
	}
	
	DeleteAttribute(&locations[index], "itemShow." + locator);
}

object g_TmpModelVariable; // TO_DO: код от к3, в скриптах нет вообще, есть проверка в ядре
