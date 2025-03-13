// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions ?","Que désirez-vous, "+GetAddress_Form(NPChar)+"?"),"Des questions encore, "+GetAddress_Form(NPChar)+"...","Des questions, des questions... Que diriez-vous de faire du commerce, "+GetAddress_Form(NPChar)+"hein ?","Ecoutez, combien de temps comptez-vous parler ?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Pas de questions pour le moment...","Désolé, je n'ai rien à dire pour l'instant..."),"Désolé encore une fois...","Peut-être qu'il est vraiment temps de commercer...","Je suis désolé, commerçons...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
