// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Pytania, "+GetAddress_Form(NPChar)+"?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?")," "+GetSexPhrase("Hm, co to za pomysł, "+GetAddress_Form(NPChar)+"? ","Znowu te dziwne pytania? Kociaku, idź się napić rumu czy coś...")+" ","Przez cały ten dzień, to już trzeci raz, kiedy mówisz o jakimś pytaniu..."+GetSexPhrase("  Czy to jakieś oznaki uwagi?"," ")+" ","Więcej pytań, jak mniemam, "+GetAddress_Form(NPChar)+"?"," blok ",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie","Nie mam teraz nic do powiedzenia."),"Nie, nie piękna...","Nie ma mowy, kochanie, skleroza...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
