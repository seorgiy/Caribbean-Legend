// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie jakiś czas temu...","Nie spotkałem nigdy takich ciekawskich ludzi ani w mojej stoczni, ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moim zadaniem jest budowa statków. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz nic do omówienia."),"Umph, gdzież mi pamięć uciekła...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
