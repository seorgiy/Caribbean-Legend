// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Pytania, "+GetAddress_Form(NPChar)+"?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?")," "+GetSexPhrase("Hm, co to za wielki pomysł, "+GetAddress_Form(NPChar)+"? ","Znowu te dziwne pytania? Dziewczyno, idź napij się rumu czy coś...")+" ","Przez cały ten dzień, to już trzeci raz, gdy mówisz o jakimś pytaniu..."+GetSexPhrase(" Czy to jakieś oznaki uwagi?","")+" ","Więcej pytań, przypuszczam, "+GetAddress_Form(NPChar)+"?","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie","Nie mam w tej chwili nic do powiedzenia."),"Nie, nie piękna...","Nie ma mowy, kochanieńka...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
