#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("First Tavern Visit " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("The alarm is raised in the town, and everyone is looking for you. If I were you, I wouldn't stay here.", "All the city guards are scouring the town looking for you. I am not a fool and I will not talk to you!", "Run, "+ GetSexPhrase("mate","lass") +", before the soldiers turn you into mincemeat..."),
					LinkRandPhrase("What do you need, "+ GetSexPhrase("scoundrel","stinker") +"?! The city guards have your scent, you won't get far"+ GetSexPhrase(", filthy pirate!","") +"", "Murderer, leave my place at once! Guards!", "I am not afraid of you, "+ GetSexPhrase("scoundrel","rat") +"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, an alarm is never a problem for me...", "They will never get me."),
					RandPhraseSimple("Shut your mouth, " + GetWorkTypeOfMan(npchar, "") + ", or I'll rip your tongue!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", and all there - to catch pirates! That's what I tell you, mate: sit quietly and you will not die..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("And it's you, bastard! You think we're pouring you rum here? Certainly not! Boys! To arms! Kill this scoundrel!", "Want a drink, pirate? Ha! No! Now we'll show you what's what! Lads, draw your blades!");
				link.l1 = RandPhraseSimple("Huh? What?", "Stop!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Monsieur, I'm looking for work. Do you have any jobs?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "I've fulfilled your assignment. The longboat with the rum has been delivered to Le Francois Bay and handed over to your people.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				FreeSitLocator("FortFrance_tavern", "sit7");
				dialog.text = "Did you want anything, monsieur?";
				Link.l1 = "Hello barkeep, I need to hire a crew for my ship. Can you help me with that?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Hello again. What is it this time, monsieur?";
				Link.l1 = ""+npchar.name+", I realize that I am bothering you, but just one more question. I need a navigator - any idea where I can find one?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "What is it that you want, monsieur?";
				Link.l1 = "I hoped you could answer a couple of questions.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "I would like to rent a room.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "I am delighted to see you sir! How may I be of service? Rum, brandy, Scotch whiskey?";
				Link.l1 = "I'd like a bottle of your best French wine and a room key.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "You have already paid monsieur, your room is upstairs.";
				Link.l1 = "Merci.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "How can I serve you, Captain? You probably want a drink after what happened.";
				Link.l1 = "That can wait. I actually want to discuss what happened.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "I beg your pardon, "+GetAddress_Form(NPChar)+", but today I cannot offer you a single drop of spirits.";
				Link.l1 = "What? What sort of tavern cannot spare even a drop of rum? Did I miss some grand celebration that drained your stores?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Welcome to my humble tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "', sir. I'm glad to see you.","At your service, sir! In our tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' we are always glad to welcome new visitors.","First time here, sir? Do not hesitate, here at '" + XI_ConvertString(NPChar.City + "TavernName") + "' you always feel at home!"), LinkRandPhrase("Come in, monsieur captain. I don't recognize you so this must be your first time at '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","Never met you before, monsieur. Let's get acquainted: I'm "+GetFullName(npchar)+", the innkeeper of '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","I'm glad to welcome our new guest, Monsieur Captain! In my tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' first drink is always on the house! I am the owner of this place, "+GetFullName(npchar)+", welcomes you."), LinkRandPhrase("Senor Captain! Welcome to the tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "'!","Oh, what a shining hidalgo has visited our taverna '" + XI_ConvertString(NPChar.City + "TavernName") + "'! Is it your first time here, sir?","Buenas dias, senor! I'm "+GetFullName(npchar)+", humble owner of '" + XI_ConvertString(NPChar.City + "TavernName") + "', we are glad to welcome you here!"),LinkRandPhrase("Hello, mynheer kapitein. I am the owner of tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "'. First time staying with us?","Good afternoon, mynheer. Welcome to the tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","Very good to see you mynheer kapitein! Our very own tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' greets you! Rum, wine, or if I could tempt you, we have a naughty new little Dutch spirit called gin?"));
				Link.l1 = LinkRandPhrase("A cozy place you've got here... Allow me to introduce myself - "+GetFullName(pchar)+", it's a pleasure to meet you.",""+GetFullName(pchar)+", it's a pleasure to meet you. So, what can you offer me?","My name is "+GetFullName(pchar)+" and I am new to this port. Tell me, what is this tavern best known for?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "Ahoy, Rumba! Back from a journey, or setting out on a new one?";
					link.l1 = "Hello, "+npchar.name+". Just decided to stop by.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "So, cap'n, have you brought me " + FindRussianMoneyString(iTemp) + ".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Yes, I have. Here they are...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "No, I haven't yet...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "What would you like, my good "+ GetSexPhrase("sir","lady") +"?";
						link.l1 = "A bottle of rum for my mate at that table over there.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, honorable guests! Hey, you - move over and make room for a gallant captain! And be quick about it, before I throw you out, haha!","Merciful God above! If it isn't "+GetFullName(pchar)+"! I just got a new shipment of choicest wines, please come in!","Oh, "+GetAddress_Form(NPChar)+", are you having troubles? Allow me to treat you? This bottle is on the house. Trust me, it's the best wine around..."),LinkRandPhrase("Oh, it's Captain "+GetFullName(pchar)+"! Hey, you! Show some respect to the good captain! This isn't a barn! Please excuse me, cap'n, their mothers clearly never taught them manners.","Well well, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! We're in for a long night, haha! Girls you'd best have on your best dresses!","Good afternoon, "+GetFullName(pchar)+", I am glad to see you! Please sir, I have a request. I just bought new tables, so please no fighting tonight."),LinkRandPhrase("Hello, captain. Make yourself at home, but keep in mind that even Captain Sharp himself minds his manners in my establishment.","O-ho-ho! Look who's here? It's "+GetFullName(pchar)+" himself! And we were just starting to get bored in your absence! How about you regale the fellows with an adventure while I open a new barrel of rum, cap'n?","O-ho-ho! It's "+GetFullName(pchar)+" himself! I hope you're not going to steal away my customers to the high seas again with the stories of your grand adventures?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! This old salt is always happy to see you in his establishment! Please sir, have a seat and the girls will take care of you!","Please captain, make yourself comfortable! Always happy to greet me favourite guest. What's yer poison?","Glad to see you again, "+GetFullName(pchar)+"! Would you like a table to yourself? Or would you like to sit at the bar?"),LinkRandPhrase("Good afternoon, captain. There's a chill in the air, allow me to offer you some excellent mulled wine I've just made, on the house!","Hello, captain "+GetFullName(pchar)+"! I am glad that you have come to visit again. What would you like?","I am glad to have you, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! I'm glad you patronize my poor establishment! We do everything we can to please."),LinkRandPhrase("Captain! Welcome, welcome! I have got some magnificent d'Anjou fit for King Louis himself and saved it especially for you!",""+GetFullName(pchar)+"! I am so glad that you've come. Shall I drive away all these sea rats or would you prefer them to stay? Trust me, I would gladly clear the entire tavern for you!","My God, here's Captain "+GetFullName(pchar)+"! Hey, flirts - get the very best tablecloth to the captain's table!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Oh, I see I am remembered here... Avast, fill my glass mate, while I take a look around...","Calm down, mate, today I am in a good mood. Let's start with rum, shall we?..."),RandPhraseSimple("Oh... you are not too happy to have me here? I hope I misheard you, ha!","Ahoy. I hope your wine is better than your greeting? Otherwise I can get angry, you know...")),RandPhraseSimple(RandPhraseSimple("Always glad to visit you, mate. What do you have to warm up a salty dog?","Ahoy mate, your establishment gets better with each coming day! Coming to visit here is always a pleasure..."),RandPhraseSimple("You haven't forgotten an old wanderer? I am flattered, mate.","Good to see an old friend again... You still have some rum left?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("I am listening, captain.","My tavern '" + XI_ConvertString(NPChar.City + "TavernName") + "' at your service, Captain!","All ear, Cap'n! What would you like today?");
				Link.l1 = "Are there boys on the island ready to try their luck on the seas?";
				Link.l1.go = "crew hire";
				Link.l2 = "I hoped you could answer a couple of questions.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "I would like to talk about financial affairs.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery in the church?", "What do you know about the recent robbery in the church?", "Have you heard anything about the recent robbery in the church?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "People say that you know just about everything in this colony. I want to buy "+pchar.GenQuest.Device.Shipyarder.Type+", and I was told that it had being sold in your town. Well, someone was selling it on the street market. Can you tell me anything about it?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Looking for a racketeer by the name of "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Where can I find him?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hello, " + npchar.name + ". I need to find Jacob van Berg - where is he? I don't see him in your tavern...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hello, " + npchar.name + ". I am looking for a caballero by the name of Fernando Rodriguez. Did he show up in your town?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "I came to collect my winnings, which were kept safe with you. " + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "I was wondering where can a find a man by the name of "+pchar.GenQuest.Marginpassenger.q2Name+"? He lives in your town.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("You got a free room, mate?", "Have you got a free room, I would stay here for a while.");
					link.l3.go = "room";
				}
				Link.l4 = "Alas, I am already leaving, " + NPChar.name + ". See you.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ah, well, come on in, come on in. You're always welcome here.";
			link.l1 = "Yes, thank you. It was good to see you. Farewell.";
			link.l1.go = "exit";
			Link.l2 = "I could use some new hands. Just make sure they're capable, alright?";
			Link.l2.go = "crew hire";
			link.l3 = "I'd like to rest on solid ground and gather my thoughts, not when my mother's bustling about the house.";
			link.l3.go = "Helen_room";
			Link.l4 = "Could I ask you something? ";
			Link.l4.go = "quests";
			link.l5 = " I've got a matter to discuss with you, "+ NPChar.name + ".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "What would you like, gracious "+ GetSexPhrase("sir","lady") +"?";
				link.l1 = "A bottle of rum for my messmate at that table over there.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("I am listening, captain.","What can I offer you, captain?","So cap'n, what'll it be?");
			Link.l1 = "I need a crew, " + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + ", let's have a talk...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "I would like to talk about financial affairs.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Can you tell me anything about the recent robbery in the church?", "What do you know about the recent robbery in the church?", "Have you heard anything about the recent robbery in the church?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "People say that you know just about everything in this colony. I want to buy "+pchar.GenQuest.Device.Shipyarder.Type+", and I was told that it had being sold in your town. Well, someone was selling it on the streets. Can you tell me anything about it?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Tell me about a racketeer by the name of "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Where can I find him?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hello, " + npchar.name + ". I need to find Jacob van Berg - where is he? I don't see him in your tavern...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hello, " + npchar.name + ". I am looking for a caballero by the name of Fernando Rodriguez. Did he show up in your town?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "I came to collect my winnings, which are kept safe with you. " + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "I was wondering where can a find a man by the name of "+pchar.GenQuest.Marginpassenger.q2Name+"? He lives in your town.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("You got a free room, mate?", "Have you got a free room, I would stay here for a while.");
				link.l3.go = "room";
			}
			Link.l4 = "I guess I'll come back later.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "And what would you need sailors for, captain? I don't see your ship in the port.";
				link.l1 = RandPhraseSimple("Exactly... I had moored in the wrong place.", "I forgot to enter the port...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Usually there are many men looking to become sailors, but it's too late right now - they will start to show up in the morning. Perhaps you'd like to rent a room and wait for them?";
				link.l1 = "Alright. Do you have vacant rooms?";
				link.l1.go = "room";
				link.l2 = "I am not interested in a room at the moment. See you.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "You think that we serve wanted criminals here? Be thankful that I am not calling the guards.";
					link.l1 = "Thanks.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Captain, there's not a soul in the tavern today. Everyone willing has gone with Captain Blackwood.";
						link.l1 = "That's a pity!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ah, sorry captain you're just a bit too late. All the lads looking to say just shipped with gallant captain " + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = "That's a pity!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Captain, people say that you're quite stingy. We have no one here who'd like to join your crew.";
									link.l1 = "I see...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "I am all ears.";
			//link.l1 = "I am looking for a job. Can you help me?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Can you tell me the latest news?","What's going on in these lands?",
                                    "What's new on land?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "I came on a different business.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Do you know where can I find " + pchar.GenQuest.EncGirl.name +"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Can you tell me where I could look for " + pchar.GenQuest.EncGirl.sLoverId + "?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Ahoy, I came at your son's invitation."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "So, have you seen  " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Can you tell me where should I look for  " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Do you know where can I find the captain of a patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "So, have you seen " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Do you know anything about the captain of a patrol " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Could you tell me where can I find a man called " + pchar.GenQuest.Hold_GenQuest.Name + "?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "I have found by chance not far from here some ship documents....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Listen, I am looking for an old friend of mine, "+pchar.GenQuest.FindFugitive.Name+" is his name. A fellow captain told me that he was heading to your settlement. Have you met him by chance?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Nothing, thank you, .";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("What did you say? " + pchar.GenQuest.Hold_GenQuest.Name + "? Hmm... Never heard of him.",
						"Are you certain that he hails from our town? I've never heard of such a person.",
						"There wasn't anyone like that in our little colony. Never heard of him in all my time here.");
					link.l1 = "Are you certain?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Check out " + pchar.GenQuest.Hold_GenQuest.foundStr + ", he can be found there quite often.";
					link.l1 = "Thank you, I'll do just that.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple("What did you say? " + pchar.GenQuest.Hold_GenQuest.Name + "? Hmm... Never heard of him. Are you certain that he hails from our village? I've never heard of such a person.",
						"He-he... Well, now only the Lord Himself knows where to look for him - in hell or in heaven. He died over a year ago, but people are still asking about him... No rest for the poor bastard..."),
						RandPhraseSimple("You will not find him there - in the land of the living at least. He died not so long ago - yellow fever... God rest his soul... What a stout man he used to be! When he was young, he was a great adventurer! But when death comes after you, there is not much you can do...",
						"Oh, have you missed him? He left these places long ago. No one knows where he went to - maybe to the North American colonies, maybe home to Europe. He just gathered his belongings and made off."),
						"Oh, are you looking for that " + pchar.GenQuest.Hold_GenQuest.Name + " who got rich and bought himself a house in New England? You know, there were times when I sold him rum on credit - he still owes me. People are so ungrateful, you know.");
					link.l1 = "I see. Well, thanks anyway.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "Well, where else to look for him, if not the tavern? He's a frequent visitor there - drowns his sins in wine, he-he. Come back a bit later - if he shows up, I'll tell him to wait for you.";	
					link.l1 = "Thank you, I'll do that.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "How can't I be sure if I know everyone here personally. It's not the first year I am running the tavern here. "+
				"I have seen them all in all possible conditions. Sometimes a wife would come to pick her husband up, at times they would leave by themselves, and on some occasions I had to toss them out. 'Am I sure?!' Of course, I am!";
			link.l1 = "Well, thanks anyway...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("He is a frequent visitor here, but right now he's not there. Come back from time to time - I will tell him to wait here for you if he shows up.","He is a frequent visitor here. If you come back later, you're certain to find him there.","Come back from time to time - he is a frequent visitor here. I will let him know that you were looking for him.");
			link.l1 = "Thank you, I'll come back later...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "He's already come here, so should be somewhere around...";
			link.l1 = "Thanks.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Is there a man who doesn't know him? The entire settlement is talking about him for several days already.";
			link.l1 = "Could you tell me more?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "A bit, the captain was executed, the same can be said about some of his crewm. The rest were scattered across the Caribbean stripped of rank and position... For what? According to a judge, he had sunk a pirate during a patrol and hid the loot for himself\n"+
				"Here's the thing, neither the owner of this vessel or goods have been found ... they've been combing the local bays and inlets looking for them but to no avail.";
			link.l1 = "What, none of the crew revealed the location of the cache?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Not a single one! Even under torture! I still can't understand, why would the governor believe in that slander so eagerly. Captain " + pchar.GenQuest.CaptainComission.Name + " had a good reputation, and his crew was well-trained and disciplined, that any admiral would envy him.";
			link.l1 = "And where should I look for the surviving crew members?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "That I don't know - they have scattered to the four winds... Although... there's still one of them remaining, but I doubt you would learn much from him. He was badly concussed. You know, he served as a gunner under " + pchar.GenQuest.CaptainComission.Name + ". He was found unconscious in a cove two days after that accident. First he was sent to the hospital and treated like a hero, but as the plot thickened, they threw him into the dungeon and tried to interrogate him, but then decided that first he should be medically treated, anyway.";
			link.l1 = "He still here now?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Yes, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + " is his name. He drops in from time to time, spends the pennies he earns begging on rum. Poor soul. If I see him, I'll tell him to wait here for you.";
			link.l1 = "Thank you, I'll come back later.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Do I know him? Of course, I do. And what do you need him for?";
			link.l1 = "I have business with him...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = "" + GetAddress_Form(pchar) + ", you should be cautious with that 'business'. " + pchar.GenQuest.CaptainComission.Name + " is detained on suspicion of piracy, and the governor's men are now scouring the island searching for his accomplices.";
			link.l1 = "You don't say! And what did he do?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "I don't know whether it's true or not, but they say that he had stashed away the cargo confiscated from a passing pirate ship and didn't turn it in. And still no one found neither that pirate, nor the cargo. I still can't understand, why would the governor believe in that slander so eagerly. Captain " + pchar.GenQuest.CaptainComission.CapName + "  had a decent reputation, and he was a great soldier, you can trust my word, " + GetAddress_Form(pchar) + ".";
			link.l1 = "Well, thanks for the warning. See you.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "And what do you need her for?";
			link.l1 = "I have business with her...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Half the men in our settlement seem to have business with her. If our women had caught her, they would toss her outside the town gates, naked.";
			link.l1 = "Oh well... "+ GetSexPhrase("It seems that I got into a long line, then. Well, if anyone else comes around asking for her, tell them to stand in line behind me.","I see") +"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "He is a frequent visitor here - he usually comes over in search for a job, but right now he's not there. Come back from time to time - I will tell him to wait here for you if he shows up.";
			link.l1 = "Thank you, I'll come back later...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, so you are "+ GetSexPhrase("that captain, who brought","that lass, who brought") +" my prodigal son with a young bride?";
				link.l1 = "Yes, it was me who had helped.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, there "+ GetSexPhrase("he is, our benefactor","she is, our benefactress") +". Expecting a reward, I take it?";
				link.l1 = "Well, I'm fine without a reward, but just your thanks would do well.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "I am very grateful to you that you haven't abandoned my son in dire straits and helped him to find a way out of a delicate situation. Allow me to thank you and please accept this modest sum and a gift from me personally.";
			link.l1 = "Thank you. Helping out this young couple was my pleasure.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Thanks? What thanks?! It's been a half a year since that blockhead was hanging around without a job - and look at him, he's got enough time for an affair! When I was his age, I was already running my own business! Pfft! A governor has a marriageable daughter - and that dunce has brought a slut without kith or kin to my house and dared to ask for my blessing!";
			link.l1 = "I guess you don't believe in love at first sight?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Love? Love!? Are you mocking me or are you stupid? Shame on you to indulge the young in their caprices and act like a procurer! Not only have you taken a girl from her home, but you also ruined my boy's life. There will be no thanks to you. Farewell.";
			link.l1 = "Same to you then.";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Let me take a look! Hmm... But you're a captain yourself. I think you should see the harbormaster about this.";
				link.l1 = "Thank you for your advice.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Let me take a look! Oh! Judging by the name, this belongs to one of my patrons, quite a respected gentleman. I myself can hand these documents over to the owner. Will you give them to me?";
				link.l1	= "On second thought...";
				link.l1.go = "exit";
				link.l2 = "Take them. I'm happy I could be of service.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("I don't care whom to serve since money has no nationality. But I will not be helping you since you came under the flag of " + NationNameGenitive(sti(pchar.nation)) + ".", "I am just a simple tavern owner, but collaboration with " + NationNameAblative(sti(pchar.nation)) + " doesn't seem appealing to me.");
				link.l1 = RandPhraseSimple("Well, as you wish...", "Well, as you like...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("We usually have a lot of passengers here. Still, I don't think that there would be even one duffy among them, who might agree to travel on your ship. Your ill repute precedes you, only a fool would take ship with such a scoundrel.", "I am quite frequently approached by merchants who need escorting. But your ill repute precedes you, and I will not recommend you to anyone. I care for my own reputation, you know. No one want hires a wolf to guard their sheep.");
				link.l1 = RandPhraseSimple("Oh, really, you shouldn't believe all that gossip...", "I see. It's difficult to make everyone shut up.", "People are just too soft these days...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "And where is your ship? Or are you going to carry the passengers on your back and swim?";
				link.l1 = "Hey, you'v got a point...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "I might have a job if you're not afraid to come to pirate settlements or to the ports of enemy nations. Are you looking for something in particular?";
			link.l1 = "That shouldn't be a problem. I guess I could provide escort.";
			link.l1.go = "work_1";
			link.l2 = "Do you have any passengers? I can take them wherever they want, if they pay for it.";
			link.l2.go = "work_2";
			link.l3 = "No, such work is not for me. Thanks.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "They usually do not ask me about escort duty. Ask the merchants in the tavern - perhaps they would need your services.";
				link.l1 = "Fine, as you say.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "I am sorry, but I don't have anyone willing to travel with you.";
					link.l1 = "I see.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "There's one man, who just came in - he was recently asking about a passing vessel. You can talk to him, if you like.";
					link.l1 = RandPhraseSimple("Who is he? Maybe he is a scoundrel? Or, even worse, a wanted pirate?", "And who is he? Will there be any trouble with him?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "No, today no one ha asked about it. Perhaps, another day.";
					link.l1 = RandPhraseSimple("Well, if it's not there, it's not...", "Just my luck... Oh, well, see you, then.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "There's no one for today. Come back in a couple of days.";
				link.l1 = "Fine, as you say.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Who could know? You asked - I answered.", "Well, this is for you to solve. I would not vouch for anyone there.", "All sorts come here. This is a tavern cap'n, not the governor's manor.");
			Link.l1 = "Thanks, we'll bargain, then.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Who could know? You asked - I answered.", "Well, this is for you to solve. I would not vouch for anyone there.", "All sorts come here. This is a tavern cap'n, not the governor's manor.");
			Link.l1 = "I see. Let's figure out who this man is...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Of course, Helen. How long are you staying? And what, have you had a spat with old Gladys?";
			if(!isDay())
			{
				link.l1 = "Just to sleep until morning. If I go home now, I'll surely wake her.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "No, no, I just need to set sail at night, and I don't want to wake her.";
				link.l1.go = "Helen_room_night";
				link.l2 = "I want a good, long sleep and to take my time getting up. I'll take a room for a day.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "The room is occupied, " + GetAddress_Form(NPChar) + ", there's nothing I can do for you.";
				link.l1 = "Well, that's a pity...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Monsieur Henri Thibaut is renting the room at the moment, and he paid for a month in advance, so there's nothing I can do for you, captain.";
				link.l1 = "Well, that's a pity...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "The room is occupied, " + GetAddress_Form(NPChar) + ", there's nothing I can do for you.";
				link.l1 = "Well, that's a pity...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "The room is occupied, " + GetAddress_Form(NPChar) + ", there's nothing I can do for you.";
				link.l1 = "Well, that's a pity...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Alas, no, Captain. All rooms are taken by Blackwood and his men.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Ah, what a pity!";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "All rooms? Are there more than one room here?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "You want to rent a room? No problem. 100 pieces of eight and it's yours.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Here's your money.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm... I guess I'll come back later...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "The room is all yours. Come in and relax.";
				link.l1 = "Thanks, mate.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "You want to rent a room? No problem. 100 pieces of eight and it's yours.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Here's your money.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm... I guess I'll come back later...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "The room is all yours. Come in and relax.";
					link.l1 = "Thanks, mate.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Excuse me, captain, unfortunately there is no room available. The guest won't leave. And still hasn't paid me...";
				link.l1 = "Looks like we'll have to spend the night in the common room...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "Sorry. Let's talk about something else.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "So call the guards. What kind of guest is this: he doesn't pay money, he doesn't want to move out...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "How long are you planning to stay here?";
			if(!isDay())
			{
				link.l1 = "Until morning.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Until night.";
				link.l1.go = "room_night";
				link.l2 = "Until next morning.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "The room is at your disposal, captain. Absolutely free.";
				link.l1 = "Thanks, buddy.";
				link.l1.go = "room_day_wait";
				link.l3 = "Not now. Let's talk about something else.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "That will cost you 5 pieces of eight.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Deal. Here you go.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("At that price? Are you renting royal chambers? I'd rather stay in the common room for free.",
            "Alas, the luxury of sleeping on a bed is beyond my current means, as it seems. Guess I'll have to sleep in the common room on a bench.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Not right now. Let's change the subject.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "The room is at your disposal, captain. Absolutely free.";
				link.l1 = "Thanks, buddy.";
				link.l1.go = "room_day_wait_next";
				link.l3 = "Not now. Let's talk about something else.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "That will cost you 10 pieces of eight.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Deal. Here you go.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("At that price? Are you renting royal chambers? I'd rather stay in the common room for free.",
            "Alas, the luxury of sleeping on a bed is beyond my current means, as it seems. Guess I'll have to sleep in the common room on a bench.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Not right now. Let's change the subject.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "The room is at your disposal, captain. Absolutely free.";
				link.l1 = "Thanks, buddy.";
				link.l1.go = "room_night_wait";
				link.l3 = "Not now. Let's talk about something else.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "That will cost you 5 pieces of eight.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Deal. Here you go.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("At that price? Are you renting royal chambers? I'd rather stay in the common room for free.",
            "Alas, the luxury of sleeping on a bed is beyond my current means, as it seems. Guess I'll have to sleep in the common room on a bench.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Not right now. Let's change the subject.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "Get the hell out of here, you scoundrel! The common room may be free but we have expectations of decent behavior!";
				link.l1 = "Alright, alright, I'm leaving.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Get the hell out of here, you scoundrel! The common room may be free but we have expectations of decent behavior!";
				link.l1 = "Alright, alright, I'm leaving.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Stop this outrageous behavior in my tavern this instant or I am calling the guards!";
			link.l1 = "Alright, alright, I'm leaving.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "I don't know much about it... You'd better ask the patrons.";
			link.l1 = "I see, thanks.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "We don't provide services on credit, "+ GetSexPhrase("mister","miss") +".";
			link.l1 = "I pay in good coin. Do you no longer accept gold or silver?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "I am sorry, "+ GetSexPhrase("mister","miss") +" captain, but your friend had a debt, and I thought...";
			link.l1 = "Think less and work faster, matey. Now, how much does my valiant friend owe you?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", mis"+ GetSexPhrase("ter","s") +" captain, and he also pawned some church books - that's all he had on him, which had some value.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Here are your coins. Hand over the manuscripts. And careful with them - this isn't a book of bawdy woodcuts, but Holy Scripture!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Wait a bit... I'll be back with the money";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", mis"+ GetSexPhrase("ter","s") +" captain.";
				link.l1 = "I will pay off his debt and take whatever he left to secure it.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "No, mis"+ GetSexPhrase("ter","s") +", that won't work like that.";
			link.l1 = "What do you mean - 'that won't work like that'? A captain's debt is paid - he's good. You have your money back - you're good. I take his pledge - I am good. Everyone's good - so why 'that won't work like that'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Because, mis"+ GetSexPhrase("ter","s") +" captain, I don't need the money. Because I know that captain all too well, so I never actually expected him to pay back and take these manuscripts from me.";
			link.l1 = "What do you mean - you don't need money? So you planned to keep these books right from the start? But why, in God's name?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "In God's name - exactly, that's why, mis"+ GetSexPhrase("ter","s") +". My little boy was very sick, and me and my wife gave a vow to make a donation to the Church if our Blessed Lord cured the child of fever. Our Lord's mercy is without end, my boy is alive and well, and now we must keep our vow. And just about time captain " + PChar.GenQuest.ChurchQuest_1.CapFullName + " shows up and pawns these church books. I could not allow such obscenity - paying for drinks with the Word - and therefore I decided to hand over this books to the pastor of our parish.";
			link.l1 = "Well, certainly this is a good deed, but you should also know that these books actually belong to another priest - actually, not just a priest, but a bishop and my spiritual shepherd. And he might get angry and even accurse those who would dare donate stolen Church property. I would like to buy them from you and bring them safely home. You can donate the money to your parish, I'm sure God will appreciate it all the same.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+ GetSexPhrase("ter","s") +"... Mis"+ GetSexPhrase("ter","s") +" captain... Of course, I had no idea! I will give them back, and I will require no money in return. You just put in a word for us to the bishop - perhaps, he could bless us and relieve us of our vow...";
			link.l1 = "Of course your vow will be considered kept! After all, you've given up your profit to return the books to their rightful owner. The particular church doesn't matter, for there is only one God and one Holy Catholic Apostolic Church, right? Alright, give them to me, and good luck to you...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Never heard of it before... Just what is it, actually? I've never heard about such a thing in all my time.";
			link.l1 = "Well, it's a shipwright's tool, "+pchar.GenQuest.Device.Shipyarder.Describe+". Was anyone offering to you anything like that?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hmm... Yes, one strange type had indeed brought that thing to me. He didn't tell me what it was, though - just tired to exchange it for booze. Of course, I refused - I had no need in that trinket.";
				link.l1 = "And what did he look like and where did he go? I need that instrument badly.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, nothing like that. Sorry, I can't help you. Ask around.";
				link.l1 = "I see. Well - time to ask around!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? He was recently there, and by now he should have come to his companion - the shopkeeper. Try to look for him at the shop - surely he must be there.";
				link.l1 = "Thanks! You've helped me out a lot!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Today, early in the morning, he's sailed out on his lugger for a marine. I bet that he is standing now at the bulwark, admiring the view. If you need him, you can try to find him at sea or wait until he comes back in a couple of days...";
				link.l1 = "Thanks! I guess I will not be waiting - it's gonna be easier to find him at see. Good luck!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Why are you shouting? He's been waiting for you for quite some time. He already drank off a full quart of rum. Go upstairs to the room, you will find him there.";
			link.l1 = "Oh, I see. Hopefully he's still awake.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Yes, I know that gentleman. He should be somewhere in the town - I just recently saw him walking past my window.";
				link.l1 = "Thank you! I will go looking for him!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Yes, I know that gentleman. He should be somewhere in the town - I just recently saw him walking past my window.";
					link.l1 = "Thank you! I will go looking for him!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Yes, he is now visiting our town. Right now he is not here - he sailed out on his brigantine. He's likely not far from here, within the waters of our island.";
					link.l1 = "Thanks mate! You've helped me out a lot!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? Never heard of him. No, I don't know anything about this man.";
				link.l1 = "I see... Well, the search continues....";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Yes, of course. Congratulations captain. I am already aware of your victory. Here is your money.";
			link.l1 = "Thank you, " + npchar.name + ".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Errr, mister, "+pchar.GenQuest.Marginpassenger.q2Name+" died about "+LinkRandPhrase("a month","three weeks","two months")+" ago. "+LinkRandPhrase("Suddenly succumbed to fever","He was stabbed at the town gates - bandits or those red-skinned savages","He was shot in a duel")+". May God rest his soul...";
				link.l1 = "Damn it!.. And what am I supposed do with his... Well, whatever. Thanks for the information. See you, " + npchar.name + ".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Yeah, he should be somewhere in the town. Look for him on the streets. But keep in mind that every day till noon he is at the governor's office, and after nine in the evening he locks himself up in his house.";
				link.l1 = "Thanks! I'll go looking for him...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("It seems that your skipper was telling the truth. "+pchar.GenQuest.FindFugitive.Name+" has indeed recently arrived at our settlement. Look for him on the streets during the day time - he is usually loitering his time away.", "You have already asked me about that man, and I told you everything I knew!", "Are you kidding me or you're an idiot indeed?! You're asking all the same for a third time already!", "Just to think, how such an idiot could become captain...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Thank you, friend, you've helped me out a lot!", "Yeah, yeah, fine.", "Wow, Wow, don't get so excited. I just forgot.", "Well, he did, as you can see...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("No, mate, I've never heard that name before. Ask around - maybe someone knows him...", "You have already asked me about that man, and I told you: I don't know!", "Are you kidding me or you're an idiot indeed?! You're asking all the same for a third time already!", "Just to think, how such an idiot could become captain...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("I see. Well, thanks anyway.", "Yeah, yeah, fine.", "Wow, Wow, don't get so excited. I just forgot.", "Well, he did, as you can see...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Unfortunately, I can't help you right now - nobody of the people I know would serve under you. But I can give you an advice - talk to that sailor who just took the table right behind you. He and his buddies have just left one merchant ship. Perhaps, they will agree to come with you.";
			link.l1 = "Alright, I'll do just that! Thank you very much!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name 	= StringFromKey("HollandGambit_23");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "I cannot tell you anything specific, friend. At this moment no navigators are frequenting my place. Try to ask around in the port - perhaps, people would know more.";
			link.l1 = "I see. Alright, I'll go talk to the people.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "At once, monsieur!.. The very best French wine! "+sld.name+"! Go get the best guest room ready! That`ll be 1000 pesos, monsieur.";
			link.l1 = "Here.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Get out, scoundrel! You're taking up valuable space for paying customers!";
				link.l1 = "Fine, alright... I'm leaving.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "Yeah - and scare all my customers with the fact that my guards drag people out of the tavern? And some of my customers don't being around soldiers. Makes them nervous, see? I don't want to ruin my reputation...";
				link.l1 = "Hmm, what if I solve your problem?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "Make up your mind? He's armed, he's some kind of professional mercenary...";
				link.l1 = "Hmm, you're right, I don't feel like arguing with an armed mercenary...";
				link.l1.go = "Exit";
				link.l2 = "Well I'm not a cloistered nun either... And I still want to rent a room.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "Well, if you can, ahem... convince him to move out, then the room is yours until morning. Free of charge, of course.";
				link.l1 = "You know, I changed my mind. I don't feel like convincing anyone.";
				link.l1.go = "Exit";
				link.l2 = "You'll want to watch this. Your unwanted guest is about to go flying out of your tavern like a giant seagull.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "I see. That'll be five silver.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Of course, here you go.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "Actually, you know what... Maybe another time. I'll spend the rest of the day on my feet.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Wise decision. That'll be five silver, and good night to you.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Here you go, and thank you - good night.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "On second thought, I don't feel like sleeping. I'll wander the town, take in some night air.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Of course, Helen. That'll be ten pesos.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Of course, here you go.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "Actually... I could do something useful with a whole day. Maybe another time.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "As you wish, Helen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "You might even find yourself sleepy after a good walk.";
			link.l1 = "Ha-ha, maybe.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "As you see fit.";
			link.l1 = "Well, until next time.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Of course, Helen, I'm all ears.";
			link.l1 = "What's the latest news or interesting rumors in town?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "He pays triple the usual price, so... you understand. And I wouldn't recommend refusing him - he has a difficult temperament. Especially lately.";
			link.l1 = "What's wrong with him?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "Obsession, that's what. At first, he was a generous, kind fellow. His sailors would throw money around in taverns, buy gifts for girls. A real celebration would begin when the 'Lady Beth' came into port. And now? Now they only buy provisions and recruit people indiscriminately. As if they need not sailors, but just working hands. Well, you can talk to him yourself.";
			link.l1 = "Maybe I will. Thanks.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
