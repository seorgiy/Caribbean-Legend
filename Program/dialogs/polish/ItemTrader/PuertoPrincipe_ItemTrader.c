// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Pytania znowu, "+GetAddress_Form(NPChar)+"...","Pytania, pytania... A może handlujemy, "+GetAddress_Form(NPChar)+"co?","Słuchaj, jak długo zamierzasz rozmawiać?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Nie mam teraz pytań...","Przykro mi, nie mam teraz nic do powiedzenia..."),"Jeszcze raz przepraszam...","Może rzeczywiście nadszedł czas na handel...","Przepraszam, przejdźmy do handlu...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
