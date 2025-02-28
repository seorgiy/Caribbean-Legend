// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was denken Sie über unsere Festung? Sieht gut aus, ja? Und die Garnison ist noch nicht schlechter, ha...","Das Leben eines Fortsoldaten ist ziemlich langweilig... Wachen und patrouillieren, schlafen und ausruhen und dann immer wieder das Gleiche. Aber in der Stadt ist es anders... Was willst du, "+GetAddress_Form(NPChar)+"?"),"Einen Soldaten mit dummen Fragen zu belästigen, ist nicht willkommen, "+GetAddress_Form(NPChar)+"...","Es ist das dritte Mal, dass du heute versuchst, mich zu fragen...","Es ist nicht einfach, ein Soldat zu sein und dennoch bist du wieder hier"+GetSexPhrase(", Schurke,  "," ")+" versucht mich zu verärgern. Sei vorsichtig, sonst landest du im Keller des Forts...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Es tut mir leid, Sie gestört zu haben, ich habe meine Meinung geändert.","Ich habe nichts zu sagen, Entschuldigung."),"Du hast recht, ich entschuldige mich.","Du hast recht, es ist schon das dritte Mal. Entschuldige mich.","Entschuldigung, es ist nichts.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
