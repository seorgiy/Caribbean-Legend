// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Allez-y, que voulez-vous ?","Nous en parlions justement. Vous devez avoir oublié...","C'est la troisième fois aujourd'hui que tu parles d'une question...","Ecoute, c'est une boutique. Les gens achètent des choses ici. Ne me dérange pas !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tu sais, "+NPChar.name+"Peut-être la prochaine fois.","Ah, j'ai oublié pour une raison quelconque...","Oui, c'est vraiment la troisième fois...","Hum, je ne vais pas...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
