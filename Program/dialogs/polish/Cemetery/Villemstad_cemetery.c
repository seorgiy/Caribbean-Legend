// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jak mogę ci pomóc?","Co mogę dla ciebie zrobić?"),"Powiedz mi, co cię trapi, "+GetAddress_Form(NPChar)+"?","Po raz trzeci, "+GetAddress_Form(NPChar)+"Czego potrzebujesz?","Dość mam ciebie. Wynoś się!","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie, przepraszam.","To nic, przepraszam."),"Przebacz mi, to nic.","Masz rację, to już trzeci raz. Wybacz mi...","Przepraszam.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
