void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "quest_fight":
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "DeliverToBander_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
			dialog.text = "¿Quién diablos eres tú?";
			link.l1 = "Silencio, cálmate. Tu compañero encarcelado llamado "+pchar.questTemp.jailCanMove.Deliver.name+" me ha enviado aquí, ¿lo conoces?";
			link.l1.go = "Step_1";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Step_1":
			dialog.text = "¿Tienes alguna prueba de que no eres uno de los perros del gobernador?";
			link.l1 = "Me ha pedido que entregue una nota. Aquí está.";
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;
		
		case "Step_2":
			dialog.text = "Veamos...(leyendo). ¡Maldita sea! Un mal momento para ser atrapado... Carajo, tal trato... Escucha, marinero, supongo que eres "+GetSexPhrase("fuerte camarada","chica hábil")+"¿Quieres ganar unas monedas? Todos nos beneficiaremos del trato.";
			link.l1 = "Siempre quiero. ¿Cuál es el trato?";
			link.l1.go = "Step_3";
		break;
			
		case "Step_3":
			dialog.text = "Puedo compartir información interesante contigo. No la necesito, no llegaré a tiempo, gracias a nuestro amigo en común, pero podría serte útil. No gratis.";
			link.l1 = "¿Cuánto?";
			if (drand(2) == 0) link.l1.go = "Step_4";
			else link.l1.go = "Step_4d";
		break;
		
		case "Step_4":
			iTotalTemp = 0;
			dialog.text = "Cincuenta mil pesos.";
			if(makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Mm, bastante caro. Pero digo que sí, si el negocio lo vale. ¡Estoy dentro! Dame los detalles.";
				link.l1.go = "Step_5";
			}
			link.l2 = "No interesado.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_4d":
			iTotalTemp = 250+drand(25)*10;
			dialog.text = ""+FindRussianDublonString(iTotalTemp)+"¡Ni una sola moneda menos!";
			if (GetCharacterItem(pchar, "gold_dublon") >= iTotalTemp)
			{
				link.l1 = "Hm, bastante caro. Pero estoy de acuerdo si el negocio lo vale. ¡Estoy dentro! Dame los detalles.";
				link.l1.go = "Step_5";
			}
			link.l2 = "No interesado.";
			link.l2.go = "Step_no";
		break;
		
		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = "Bueno-bueno, lo que sea, "+GetSexPhrase("te engañaron, idiota","te han engañado, estúpida chica")+". Ahora paga, ¡en efectivo!";
					link.l1 = "Vete a la mierda con un ancla... ¡Tu amigo me ha dicho que sus colegas son generosos!";
					link.l1.go = "Step_fight";
				break;
				
				case 1://кидалово
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					dialog.text = "Está bien, escucha. Me informaron que en "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" no lejos de "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+"  habrá dos "+pchar.questTemp.jailCanMove.Deliver.add1+" barcos mercantes - los "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" y el "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" con sus bodegas llenas de "+pchar.questTemp.jailCanMove.Deliver.add+". Puedes intentar atraparlos.";
					link.l1 = "¡Espléndido! Parece que hice bien al compartir monedas contigo.";
					link.l1.go = "Step_lay";
				break;
				
				case 2://наведем на торговый корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10+rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					
					dialog.text = "Bueno, escucha. Me informaron que en "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" no lejos de "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" habrá dos "+pchar.questTemp.jailCanMove.Deliver.add1+" barcos mercantes - los "+pchar.questTemp.jailCanMove.Deliver.ShipName1+" y el "+pchar.questTemp.jailCanMove.Deliver.ShipName2+" con sus bodegas llenas de "+pchar.questTemp.jailCanMove.Deliver.add+". Puedes intentar atraparlos.";
					link.l1 = "¡Espléndido! Parece que hice bien en compartir monedas contigo.";
					link.l1.go = "Step_trader";
				break;
				
				case 3://наведем на курьерский корабль
					if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
					else RemoveItems(pchar, "gold_dublon", iTotalTemp);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5+rand(5);
					dialog.text = "Bien, escucha. Me informaron que en "+FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms))+" no lejos de "+pchar.questTemp.jailCanMove.Deliver.Island.Areal+" navegará en un cúter de mensajería "+pchar.questTemp.jailCanMove.Deliver.add2+" llamado "+pchar.questTemp.jailCanMove.Deliver.ShipName+". Hay muchas joyas en ella. Puedes intentar atraparla.";
					link.l1 = "¡Espléndido! Parece que hice bien en compartir monedas contigo.";
					link.l1.go = "Step_cureer";
				break;
			}
		break;
			
		case "Step_fight":
			dialog.text = "Si no fuera tan tonto, estaría bebiendo su ron en una taberna ahora y no sentado en las casamatas. Así que todas las quejas van para él, ¡ja-ja! Ahora dame tu dinero o no saldrás de aquí con vida.";
			link.l1 = "¿Estás tan seguro de eso, payaso?";
			link.l1.go = "quest_fight";
			link.l2 = "Está bien, toma tus monedas... Estoy superado en número...";
			link.l2.go = "Step_takemoney";
		break;
		
		case "Step_takemoney":
			dialog.text = "Bien hecho, "+GetSexPhrase("compañero","chica")+"Nuestro amigo común te los devolverá, ja-ja... una vez que esté muerto. Piérdete. Silenciosamente.";
			link.l1 = "¡Maldito seas!";
			link.l1.go = "exit";
			if (iTotalTemp == 0) AddMoneyToCharacter(pchar, -50000);
			else RemoveItems(pchar, "gold_dublon", 300);
			AddQuestRecord("GivePrisonFree", "17");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;
		
		case "Step_lay":
			dialog.text = "Claro... Lo que sea, ahora vete, silenciosamente.";
			link.l1 = "Adiós.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_lay";//придем - а там пусто
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_trader":
			dialog.text = "Claro... Como sea, ahora vete, en silencio.";
			link.l1 = "Adiós.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "13");
			AddQuestUserData("GivePrisonFree", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("GivePrisonFree", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_CreateTraderShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_cureer":
			dialog.text = "Seguro... Lo que sea, ahora vete, silenciosamente.";
			link.l1 = "Adiós.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "14");
			AddQuestUserData("GivePrisonFree", "sDay", FindRussianDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("GivePrisonFree", "sText", pchar.questTemp.jailCanMove.Deliver.add2);
			AddQuestUserData("GivePrisonFree", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
			AddQuestUserData("GivePrisonFree", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1 = "location";
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
            pchar.quest.jailCanMoveDeliver_ShipsCAttack.function = "Deliver_CreateCureerShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_CureerShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Step_no":
			dialog.text = "Lo que sea entonces. Ahora vete, no tenemos nada de qué hablar contigo.";
			link.l1 = "Bien, adiós.";
			link.l1.go = "exit";
			AddQuestRecord("GivePrisonFree", "16");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			AddQuestUserData("GivePrisonFree", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;

		case "Second time":
			dialog.text = "¿Qué más quieres? Ya te he dicho que te largues.";
			link.l1 = "Está bien, voy en camino...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "Second time";
		break;
		
		case "Man_FackYou":
			dialog.text = "¿Quieres que te apuñalen, "+GetSexPhrase("petimetre","chica estúpida")+"¿¡!?";
			link.l1 = LinkRandPhrase("¡Diablo!","¡Caramba!","¡Maldita sea!");
			link.l1.go = "fight";
		break;
	}
}

void GetBandersTradeShore()//выберем остров для торгашей и курьера
{
	pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandId();
	pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
	while (pchar.questTemp.jailCanMove.Deliver.Island.Shore == "")
	{
		pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandId();
		pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.jailCanMove.Deliver.Island)) pchar.questTemp.jailCanMove.Deliver.Island.Shore = "";
	} 
	pchar.questTemp.jailCanMove.Deliver.Island.Town = FindTownOnIsland(pchar.questTemp.jailCanMove.Deliver.Island);
	if (pchar.questTemp.jailCanMove.Deliver.Island.Town == "" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Caiman" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Terks" || pchar.questTemp.jailCanMove.Deliver.Island.Town == "Dominica")
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = GetConvertStr(pchar.questTemp.jailCanMove.Deliver.Island, "LocLables.txt") + "");
	}
	else
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = XI_ConvertString("Colony" + pchar.questTemp.jailCanMove.Deliver.Island.Town + "Gen");
	}
}

void GetBandersTradeGoods()//выберем товар для торгашей
{
	switch (rand(6))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_EBONY;
			pchar.questTemp.jailCanMove.Deliver.add = "ebony";
		break;
		
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_MAHOGANY;
			pchar.questTemp.jailCanMove.Deliver.add = "redwood";
		break;
		
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_CHOCOLATE;
			pchar.questTemp.jailCanMove.Deliver.add = "cacao";
		break;
		
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_COFFEE;
			pchar.questTemp.jailCanMove.Deliver.add = "coffee";
		break;
		
		case 4:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_CINNAMON;
			pchar.questTemp.jailCanMove.Deliver.add = "cinnamon";
		break;
		
		case 5:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_FOOD;
			pchar.questTemp.jailCanMove.Deliver.add = "provisions";
		break;
		
		case 6:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_WEAPON;
			pchar.questTemp.jailCanMove.Deliver.add = "weapons";
		break;
	}
}

void GetBandersTradeNation()//выберем нацию торгаша и курьера
{
	switch (rand(3))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Nation = SPAIN;
			pchar.questTemp.jailCanMove.Deliver.add1 = "Spanish";
			pchar.questTemp.jailCanMove.Deliver.add2 = "Spanish Treasury";
		break;
		
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Nation = FRANCE;
			pchar.questTemp.jailCanMove.Deliver.add1 = "French";
			pchar.questTemp.jailCanMove.Deliver.add2 = "French Treasury";
		break;
		
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Nation = HOLLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "Holland";
			pchar.questTemp.jailCanMove.Deliver.add2 = "Dutch West India Company";
		break;
		
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Nation = ENGLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = "English";
			pchar.questTemp.jailCanMove.Deliver.add2 = "English Treasury";
			break;
	}
}
