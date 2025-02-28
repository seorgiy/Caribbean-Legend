// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Wie finden Sie unsere Festung? Sieht gut aus, ja? Und die Garnison ist noch nicht schlimmer, ha...","Das Leben eines Fortsoldaten ist ziemlich öde... Bewachen und patrouillieren, schlafen und ruhen und dann das Ganze von vorne. Aber in der Stadt ist es anders... Was willst du, "+GetAddress_Form(NPChar)+"?"),"Einen Soldaten mit dummen Fragen zu belästigen, ist nicht willkommen, "+GetAddress_Form(NPChar)+"...","Das ist das dritte Mal, dass du versuchst, mich heute zu fragen...","Es ist nicht einfach, ein Soldat zu sein, und doch bist du schon wieder hier"+GetSexPhrase(", Tölpel,  "," ")+" versuchst mich zu ärgern. Sei vorsichtig, sonst landest du im Keller des Forts...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Es tut mir leid, ich habe es mir anders überlegt und Sie belästigt.","Ich habe nichts zu sagen, Entschuldigung."),"Du hast recht, ich entschuldige mich.","Du hast recht, es ist bereits das dritte Mal. Entschuldige mich.","Entschuldigung, es ist nichts.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
