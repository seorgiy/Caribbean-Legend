// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que voulez-vous ? Demandez.","Je vous écoute, quelle est la question ?"),"C'est la deuxième fois que vous essayez de demander...","C'est la troisième fois que vous essayez de demander...","Quand cela va-t-il se terminer ?! Je suis un homme occupé, travaillant sur les affaires de la colonie et vous continuez de m'importuner !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis, désolé.","Pas maintenant. Mauvais endroit et mauvais moment."),"Vrai, je n'ai rien à dire pour le moment, désolé.","Je demanderai, plus tard.","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"... ",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Tu as déjà tout pris. Que veux-tu de plus ?","Y a-t-il quelque chose que tu n'as pas encore pris ?");
            link.l1 = RandPhraseSimple("Je jette juste un coup d'œil...","Je vérifie juste, j'ai peut-être oublié de prendre quelque chose...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
