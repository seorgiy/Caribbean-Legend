// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Di nuovo domande, "+GetAddress_Form(NPChar)+"...","Domande, domande... Che ne dici di fare affari, "+GetAddress_Form(NPChar)+"eh?","Ascolta, quanto tempo intendi parlare?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Nessuna domanda per ora...","Mi dispiace, non ho nulla da dire ora..."),"Di nuovo, mi dispiace...","Forse è davvero il momento di fare affari...","Mi dispiace, facciamo affari...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
