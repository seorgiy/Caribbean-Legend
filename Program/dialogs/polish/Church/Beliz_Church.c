// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania, "+GetSexPhrase("mój synu","moja córka")+"?","Pytaj, słucham..."),"Słucham, mów teraz, "+GetSexPhrase("mój synu","moja córka")+"... ","Po raz trzeci, "+GetSexPhrase("mój synu","moja córka")+", proś o co potrzebujesz.","Duchowny ma wiele pracy, a ty mnie rozpraszasz, "+GetSexPhrase("mój synu","moja córka")+"...","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie teraz, ojcze..."),"Nie mam nic do powiedzenia, przepraszam.","Zapytam, ale później. Wybacz mi, ojcze.","Przepraszam, święty ojcze...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
