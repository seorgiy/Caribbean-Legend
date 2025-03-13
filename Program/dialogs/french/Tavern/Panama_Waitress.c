// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, "+GetAddress_Form(NPChar)+"?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?")," "+GetSexPhrase("Hm, quelle est cette grande idée, "+GetAddress_Form(NPChar)+"? ","Encore avec les questions étranges ? Ma belle, va prendre du rhum ou quelque chose...")+"Bonjour, ami.","Tout au long de cette journée, c'est la troisième fois que tu parles d'une question quelconque..."+GetSexPhrase(" Est-ce là quelques signes d'attention?","")+"Bonjour, mon ami.","Plus de questions, je présume, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis","Je n'ai rien à dire pour le moment."),"Non, non belle...","Pas question, ma chère, la sclérose...","Non, quelles questions ?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
