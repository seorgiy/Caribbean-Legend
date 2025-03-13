// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas?","¿Qué deseas, "+GetAddress_Form(NPChar)+"¿?"),"¿Preguntas de nuevo, "+GetAddress_Form(NPChar)+"...","Preguntas, preguntas... ¿Qué tal si comerciamos, "+GetAddress_Form(NPChar)+"¿Eh?","Escucha, ¿cuánto tiempo piensas hablar?","bloque",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sin preguntas por ahora...","Lo siento, no tengo nada que decir ahora..."),"Una vez más, lo siento...","Quizás realmente sea hora de comerciar...","Lo siento, vamos a comerciar...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
