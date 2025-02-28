// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Alle Gerüchte von "+GetCityName(npchar.city)+" zu Ihren Diensten. Was möchten Sie erfahren?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du über irgendeine Frage redest...","Du wiederholst alles wie ein Papagei...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Weißt du, "+NPChar.name+", vielleicht nächstes Mal.","Stimmt, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Jawohl...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "Sag mir, hat ein Galeone namens 'Santa Margarita' in letzter Zeit in deiner Kolonie Halt gemacht? Vielleicht als Preis eines Freibeuters?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Kumpel, es ist ziemlich selten, dass jemand bei unserer Kolonie mit Preisen vorbeikommt und wir haben noch nie eine Galeone mit einem Namen wie diesem gesehen. Hispaniola ist eine wilde Insel und wir sind eine kleine Kolonie. Es ist ruhig hier. Wir handeln mit den Freibeutern in den Highlands für Kuhhäute und getrocknetes Rindfleisch. Kaperschiffe halten sich normalerweise nicht auf, wir haben hier keine Bordelle und wir haben die Spanier in unmittelbarer Nähe. Suchen Sie Ihre Galeone irgendwo anders.";
			link.l1 = "Ich verstehe. Danke für den Rat!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
