

object wdmLoginToSea;
object wdm_fader;
bool wdmLockReload = false;
bool questwdmLockReload = false;

void wdmReloadToSea()
{
	//Если запрещена перегрузка, ничего не делаем
	if(wdmLockReload)
	{
		return;
	}
	if(questwdmLockReload)
	{
		Log_Info(XI_ConvertString("questwdmLock"));
		return;
	}
	// расчеты ВМЛ -->
	EmptyAllFantomCharacter();
	PGG_DailyUpdate();
	Siege_DailyUpdate();//homo осады 05/11/06
	SaveCurrentQuestDateParam("WordMapEncounters_DailyUpdate"); //homo карта 25/03/07
	// расчеты <--
	
	wdmLockReload = true;
	//Обновим текст перегрузки
	SetReloadNextTipsImage();
	//Очищаем объект логина
	DeleteAttribute(&wdmLoginToSea, "");
	//Обновляем параметры
	worldMap.encounter.type = "";
	worldMap.playerShipUpdate = "";
	worldMap.info.updateinfo = "";
	//Добавляем группу игрока
	WdmAddPlayerGroup();
	//Добавляем энкаунтеры
	bool isShipEncounterType;
	isShipEncounterType = WdmAddEncountersData();
	//Отконектим все энкаунтеры от атрибутов и поставим в очередь удаления
	SendMessage(&worldMap, "l", MSG_WORLDMAP_CREATEENC_RELEASE);
	//Погодные эффекты
	WdmStormEncounter();
	//Удаляем атрибуты выделенных энкаунтеров
	worldMap.deleteUpdate = "";
	
	//  AutoSave boal 17.04.24 -->
	if (sti(wdmLoginToSea.storm) == 0 && !isShipEncounterType && MakeAutoSave2()) // не в шторме, не в бою
	{
		SetEventHandler("evntSaveGameAfter","WdmReloadAferSave", 0);
	}
	else
	{
		WdmReloadStart(isShipEncounterType);
	}
	//  AutoSave boal 17.04.24 <--
	
	
}
//  AutoSave boal 17.04.24 -->
void WdmReloadAferSave()
{
	DelEventHandler("evntSaveGameAfter","WdmReloadAferSave"); // убрать прерывание
	WdmReloadStart(false); // то, что было бы сразу
}
void WdmReloadStart(bool isShipEncounterType)
{
	//Фейдер
	SetEventHandler("FaderEvent_StartFade", "WdmStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "WdmEndFade", 0);
	wdm_fader.thisWorldMapFader = "";
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeOutTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
	//Установим картинку для фейдера
	string imageName = "loading\sea_0" + rand(2) + ".tga";
	if(isShipEncounterType)
	{
		imageName = RandPhraseSimple("loading\battle.tga", "loading\shipcannon.tga"));
	}
	if(MakeInt(wdmLoginToSea.storm) != 0)
	{
		imageName = "loading\Storm.tga";
		/*if(MakeInt(wdmLoginToSea.tornado) != 0)
		{
			imageName = "loading\Twister.tga";
		}*/ // boal пусть будет одна
	}
	wdmLoginToSea.imageName = imageName;
	SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "loading\ImgBack.tga");
	SendMessage(&wdm_fader, "ls",FADER_PICTURE, imageName);
}
//  AutoSave boal 17.04.24 <--
void WdmStartFade()
{
	PauseAllSounds();
	//Delete EventHandler
	DelEventHandler("FaderEvent_StartFade", "WdmStartFade");
	//Delete entity
	worldMap.playerShipUpdate = "";
	DeleteClass(&worldMap);
	worldMap.isLoaded = "false";
	DeleteWmInterface();
}

void WdmEndFade()
{
	int a = GetEventData();
	aref reload_fader = GetEventData();
	//Delete EventHandler
	DelEventHandler("FaderEvent_EndFade", "WdmEndFade");
	//Switch to sea
	ReloadProgressStart();	
	sIslandID = worldMap.island;
	SeaLogin(&wdmLoginToSea);
	LayerAddObject(SEA_REALIZE, &reload_fader, -1);
	ReloadProgressEnd();
}

void QuitFromWorldMap()
{
	//Fade out
	SetEventHandler("FaderEvent_StartFade", "WdmStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "WdmEndFadeA", 0);
	wdm_fader.thisWorldMapFader = "";
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeOutTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
}

void WdmEndFadeA()
{
	//Delete EventHandler
	DelEventHandler("FaderEvent_EndFade", "WdmEndFadeA");
	//Switch to sea
	Event("QuitFromWorldMap");

}

// VANO function: return sea coordinates
void WdmPrepareMapForAbordage(aref arPos)
{
	//Координаты игрока на карте
	float psX = MakeFloat(worldMap.playerShipX);
	float psZ = MakeFloat(worldMap.playerShipZ);
	//Учитываем остров
	if(worldMap.island != WDM_NONE_ISLAND)
	{
		//Island
		wdmLoginToSea.island = worldMap.island;
		float ix = MakeFloat(worldMap.island.x);
		float iz = MakeFloat(worldMap.island.z);
		int scale = WDM_MAP_TO_SEA_SCALE;
		if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina"
			|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo"
			|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
		{
			scale = 25;
		}
		arPos.x = (psX - ix)*scale;
		arPos.z = (psZ - iz)*scale;
		arPos.y = worldMap.playerShipAY;
		worldMap.zeroX = ix;
		worldMap.zeroZ = iz;
	}else{
		//no Island
		wdmLoginToSea.island = "";
		//Player ship
		arPos.x = 0;
		arPos.z = 0;
		arPos.y = worldMap.playerShipAY;
		worldMap.zeroX = worldMap.playerShipX;
		worldMap.zeroZ = worldMap.playerShipZ;
	}
}

void WdmAddPlayerGroup()
{
	//Координаты игрока на карте
	float psX = MakeFloat(worldMap.playerShipX);
	float psZ = MakeFloat(worldMap.playerShipZ);
	//if (CheckAttribute(pchar, "questTemp.Sharlie.Sea"))//Jason
	//{
	//	psX = 600.524;
	//	psZ = -500.507;
	//}
	//Учитываем остров
	if(worldMap.island != WDM_NONE_ISLAND)
	{
		//Island
		wdmLoginToSea.island = worldMap.island;
		float ix = MakeFloat(worldMap.island.x);
		float iz = MakeFloat(worldMap.island.z);
		int scale = WDM_MAP_TO_SEA_SCALE;
		if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina"
			|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo" 
			|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
		{
			scale = 25;
		}
		wdmLoginToSea.playerGroup.x = (psX - ix)*scale;
		wdmLoginToSea.playerGroup.z = (psZ - iz)*scale;
		wdmLoginToSea.playerGroup.ay = worldMap.playerShipAY;
		worldMap.zeroX = ix;
		worldMap.zeroZ = iz;
	}else{
		//no Island
		wdmLoginToSea.island = "";
		//Player ship
		wdmLoginToSea.playerGroup.x = 0;
		wdmLoginToSea.playerGroup.z = 0;
		wdmLoginToSea.playerGroup.ay = worldMap.playerShipAY;
		worldMap.zeroX = worldMap.playerShipX;
		worldMap.zeroZ = worldMap.playerShipZ;
	}
}

bool WdmAddEncountersData()
{
	bool isShipEncounter = false;
	//Удалим все существующие записи об морских энкоунтерах
	ReleaseMapEncounters();
	//Количество корабельных энкоунтеров в карте
	int numEncounters = wdmGetNumberShipEncounters();
	//Позиция игрока на карте
	float mpsX = MakeFloat(worldMap.playerShipX);
	float mpsZ = MakeFloat(worldMap.playerShipZ);
	//Позиция игрока в мире
	float wpsX = MakeFloat(wdmLoginToSea.playerGroup.x);
	float wpsZ = MakeFloat(wdmLoginToSea.playerGroup.z);
	//Перебираем все энкоунтеры карты
	for(int i = 0; i < numEncounters; i++)
	{
		//Получим информацию о данном энкоунтере
		if(wdmSetCurrentShipData(i))
		{
			//Если не активен, то пропустим его
			if(MakeInt(worldMap.encounter.select) == 0) continue;
			//Добавляем информацию об морских энкоунтере
			string encStringID = worldMap.encounter.id;
			if(encStringID == "") continue;
			encStringID = "encounters." + encStringID + ".encdata";
			if(CheckAttribute(&worldMap, encStringID) == 0) continue;
			int mapEncSlot = FindFreeMapEncounterSlot();
			if(mapEncSlot < 0) continue;
			ref mapEncSlotRef = GetMapEncounterRef(mapEncSlot);
			aref encDataForSlot;
			makearef(encDataForSlot, worldMap.(encStringID));
			CopyAttributes(mapEncSlotRef, encDataForSlot);
			//Отмечаем свершение корабельного энкоунтера
			isShipEncounter = true;
			//Описываем его параметры
			string grp; grp = "group" + i;
			float encX = MakeFloat(worldMap.encounter.x);
			float encZ = MakeFloat(worldMap.encounter.z);
			wdmLoginToSea.encounters.(grp).x = wpsX + (encX - mpsX)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).z = wpsZ + (encZ - mpsZ)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).deltax = (encX - mpsX)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).deltaz = (encZ - mpsZ)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).ay = worldMap.encounter.ay;
			wdmLoginToSea.encounters.(grp).type = mapEncSlot;
			wdmLoginToSea.encounters.(grp).id = worldMap.encounter.id;
			//Помечаем энкоунтера на удаление
			encStringID = worldMap.encounter.id;
			encStringID = "encounters." + encStringID;
			if(CheckAttribute(&worldMap, encStringID + ".quest") == 0)
			{			
				worldMap.(encStringID).needDelete = "Reload delete non quest encounter";
			}
			if(CheckAttribute(encDataForSlot,"Task.Target") && encDataForSlot.Task.Target == PLAYER_GROUP)
			{
				DeleteAttribute(pchar, "worldmap.FollowCounter");
				log_testinfo("worldmap преследователь Task Target "+encDataForSlot.Task.Target+" удалён");
			}
		}
	}
	return isShipEncounter;
}

void WdmStormEncounter()
{
	wdmLoginToSea.storm = worldMap.playerInStorm;
	if(MakeInt(wdmLoginToSea.storm) != 0)
	{
		wdmLoginToSea.tornado = worldMap.stormWhithTornado;
	}else{
		wdmLoginToSea.tornado = "0";
	}

	//wdmLoginToSea.tornado = "1";

	if(CheckAttribute(&worldMap, "stormId") != 0)
	{
		if(worldMap.stormId != "")
		{
			string encStringID = worldMap.stormId;
			encStringID = "encounters." + encStringID;
			worldMap.(encStringID).needDelete = "Reload delete storm";
		}
	}	
}