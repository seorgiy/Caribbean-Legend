//#include "DIALOGS\convoy_traider.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("Ahhh, verdammt! Ich weiß, wer du bist! Nur ein völliger Idiot würde dich anheuern, um sein Schiff zu eskortieren. Lebewohl!","Oh, ich weiß, wer du bist! Du sagst, du möchtest mich als Eskorte anheuern? Ich bin doch kein Narr...");
				link.l1 = RandPhraseSimple("Heh, was für ein Jammer!","Die Leute sind heutzutage sicherlich zu leicht zu erschrecken!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ich bin "+GetFullName(NPChar)+", ein Händler. Ich hörte, Sie suchen eine Arbeit?";
				link.l1 = "So etwas. Und Sie, wie ich gehört habe, suchen nach dem Kapitän, der Sie und Ihr Schiff zu Ihrem Zielort eskortieren wird?";
				link.l1.go = "prepare_convoy_quest_2";
			}
		break;
		
		case "prepare_convoy_quest_2":
			dialog.text = "Genau. Darüber hinaus glaube ich, dass du genau die richtige Person für meine Eskorte bist. Was würdest du sagen?";
			link.l1 = "Nun, mach mir ein Angebot, und vielleicht schließt du einen Handel ab.";
			link.l1.go = "prepare_convoy_quest_3";
		break;
		
		case "prepare_convoy_quest_3":
			LookShipConvoy();
			GenerateConvoyQuest(npchar);
			dialog.text = "Ich muss eskortiert werden zu "+XI_ConvertString("Colony"+pchar.quest.destination+"Gen")+", das sich auf "+XI_ConvertString(GetIslandByCityName(pchar.quest.destination)+"Dat")+", in "+FindRussianDaysString(sti(pchar.ConvoyQuest.iDay))+", und dafür werde ich dich bezahlen "+FindRussianMoneyString(sti(pchar.ConvoyQuest.convoymoney))+". Also, deine Entscheidung?";
			link.l1 = "Ich bin drin.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "Ich denke nicht, dass es ein interessanter Vorschlag ist.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_refused");
		break;
		
		case "convoy_agreeded":
			chrDisableReloadToLocation = false;
		    pchar.convoy_quest = pchar.quest.destination;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_agreeded");
		break;
		
		case "complete_convoy_quest":
			dialog.text = "Oh! Danke dir. Unter deinem Schutz fühlte ich mich sicher wie nie zuvor. Hier ist deine wohlverdiente Belohnung.";
			Link.l1 = "Du bist willkommen.";
			link.l1.go = "exit";
			//слухи
			AddSimpleRumour(LinkRandPhrase("A merchant captain by the name of " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted when one needs an escort.", 
				"Negociant named " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("He","She") +" protected his ship in the best way possible while escorting him to " + XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + ".", 
				"I heard that you keep the word given to trader captains that ask you for an escort. A trader named " + GetFullName(npchar) + " speaks well about you."), sti(npchar.nation), 40, 1);
			pchar.quest.generate_convoy_quest_progress = "completed";
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			AddDialogExitQuest("convoy_refused");
		break;
	}
} 

// boal 03.05.04 квест сопроводить торговца -->
void GenerateConvoyQuest(ref npchar)
{
	int iTradeMoney, iNation;

	DeleteAttribute(NPChar, "Ship");
    SetShipToFantom(NPChar, "trade", true);

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.ConvoyQuest.City), GetArealByCityName(pchar.quest.destination));
	if (sti(daysQty) > 14) daysQty = 14;
	pchar.ConvoyQuest.iDay = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*600*sti(pchar.GenQuest.Convoy.Shipmod)+rand(100))*sti(daysQty)/sti(pchar.ConvoyQuest.iDay);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.4); //то размер награды увеличивается
	pchar.ConvoyQuest.convoymoney = iTradeMoney;			


	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(pchar.quest.destination);
	//Log_Info(pchar.ConvoyQuest.City);

	SetTimerCondition("generate_convoy_quest_timer", 0, 0, sti(pchar.ConvoyQuest.iDay), false);

	pchar.quest.generate_convoy_quest_progress = "begin";

	pchar.quest.generate_convoy_quest_failed.win_condition.l1 = "NPC_Death";
	pchar.quest.generate_convoy_quest_failed.win_condition.l1.character = "QuestTrader";
	pchar.quest.generate_convoy_quest_failed.win_condition = "generate_convoy_quest_failed";
}

void LookShipConvoy()
{
	switch(makeint(6-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.Convoy.Shipmod = 0.7;
		break;
		case 1:
			pchar.GenQuest.Convoy.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.Convoy.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.Convoy.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.Convoy.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.Convoy.Shipmod = 3;
		break;
	}
}
