// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous pour un soldat ?","Soldat a toute sa vie planifiée - garde, bousculade... Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Tu ne devrais pas importuner un soldat avec des questions stupides, "+GetAddress_Form(NPChar)+"...","C'est la troisième fois aujourd'hui que tu essaies de me poser une question...","Le destin d'un soldat n'est point aisé, et maintenant toi, canaille, tu me rends fou...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Compris...","Oui, tu as raison, déjà la troisième fois...","Désolé...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
