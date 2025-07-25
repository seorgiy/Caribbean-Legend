// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "This is a bug. Let the devs know";
			link.l1 = "Sure!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "What do you need?";
			link.l1 = "Are you "+pchar.questTemp.Shadowtrader.Guardername+"? The local merchant sent me. He is impatiently awaiting your presence at this very moment.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "A-ah, but I've been waiting for him here! I was told that he would come to a tavern! Sorry, I'm on my way at once.";
			link.l1 = "Very well!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "Good evening, captain. Want to get some cheap goods, heh? Follow me!";
			link.l1 = "Lead on.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "Good evening, mister. It is good to meet a new client, ha! Let me introduce myself: I am " + GetFullName(npchar) + ". I've got the cheapest goods in this town, I assure you.";
			link.l1 = "Finally we've met..." + npchar.name + ". I suppose, I will disappoint you: I was looking for you not to trade but to end your filthy racket. You've been a great pain in the arse of an important man. The pain has become so great that he is eager to shut you down... by any means necessary.";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "Stop right there criminal scum! Didn't you know that you have to pay taxes for operating a commercial business? No one breaks the law on my watch! " + GetFullName(npchar) + ", you violated the law and your stolen goods are now forfeit! There are armed soldiers right behind me outside the door, so don't even try to play dumb!";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Really? I didn't expect... Who the devil are you?! This is a setup! I guess I know who is responsible for this! By any means necessary... lads, kill him!";
			link.l1 = "Let's dance, scoundrel!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "Oh God... officer, listen! Let's make a deal. You are a wise and merciful man! I will pay you 5000 pieces of eight and you let us escape through the second floor. You will also take the goods, you need them, right? Why would you need me? I will leave the town right now and no one will ever see us again. And you will get your money. What do you think, officer?";
		link.l1 = "Do you really think, scum, that I will dishonor my duty for such a petty sum?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "Alright, alright, officer, take everything I've got - 10,000 pesos. It's all I have, I swear!";
		link.l1 = "Hm... If I arrest you, all your money will be confiscated... Very well! This smuggling post is closed and all the goods are confiscated... Give me the coin and get lost. Don't show your face here again!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Thank you, thank you, thank you officer! Here is your money, and you won't see me here again. Let's go!";
			link.l1 = "Get out or I will have to arrest you!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ah! Mercy, don't kill me! I will give you all I have!";
			link.l1 = "All your goods will be confiscated by the authorities. Do you really think that I have mercy on you after what just has happened here?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "I... I will give you all my money and belongings! Just let me go! I will leave the island today and you won't see me here again!";
			link.l1 = "Very well. Give me everything you've got on you and get lost. And don't ever try to do business here again - next time I won't spare your pathetic life, you  brigand.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "No way, bastard, you won't buy me off. The only way to deal with your kind is cold steel and hot lead!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received items");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(pchar);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "Shot", "ShadowTrader_killed_end", 1.3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
