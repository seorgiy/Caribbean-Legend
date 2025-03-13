// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jak mogę ci pomóc?","Co mogę dla ciebie zrobić?"),"Powiedz mi, co cię trapi, "+GetAddress_Form(NPChar)+"?","Po raz trzeci, "+GetAddress_Form(NPChar)+", czego potrzebujesz?","Dość mam ciebie. Wynocha!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam.","To nic, przepraszam."),"Wybacz mi, to nic.","Masz rację, to już trzeci raz. Przepraszam...","Przepraszam.",npchar,Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Słuchaj, czy widziałeś lub spotkałeś człowieka o imieniu Joachim Merriman, tutaj w Hawanie lub w jej okolicach? To jest senior w średnim wieku, Portugalczyk z wąsem, cesarską brodą i przenikliwymi oczami. Może w zatoczce lub w dżungli? Szukam go.";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "N-nie, żeglarzu, z-zupełnie nie. Rzadko mam tu gości, widzisz, uh... i ja... n-nie widziałem nikogo podobnego do człowieka, którego opisałeś, więc...";
			link.l1 = "Naprawdę? Więc dlaczego się jąkasz i unikasz wzroku? Nie kłam mi teraz, znasz prawdę. Lepiej powiedz mi jeszcze raz - widziałeś tego człowieka?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "J-Ja mówię ci, Senorze, n-nikogo nie widziałem! J-Jąkałem się o-od dziecka...";
			link.l1 = "Kłamstwa, same kłamstwa. Widzę to w twoich oczach. Gdzie on jest, gdzie jest Merriman?! Powiedz mi, TERAZ!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Nie znam żadnego Merrimana! Nigdy wcześniej nie słyszałem tego nazwiska! I nie próbuj mnie skrzywdzić, bo Komendant powiesi cię w fortecy! Więc stąpaj ostrożnie, chłopcze!";
			link.l1 = "Ach, tak myślisz? Dobrze. Teraz słuchaj mnie bardzo uważnie: Joachim Merriman jest czarownikiem. Święta Inkwizycja go poszukuje. Wiele lat temu w Europie został skazany na spalenie na stosie za kopanie grobów, bezczeszczenie umarłych i czary. I wiem na pewno, że teraz ukrywa się gdzieś tutaj, na obrzeżach Hawany...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "...niedawno oczyściłem pobliską jaskinię z zombie i wiem, kto za tym stoi! Gdzieżby indziej Merriman miałby się udać, jeśli nie na cmentarz! Wiesz, gdzie on jest. Ale rób, jak chcesz, nie tknę cię nawet palcem, ale odwiedzę Inkwizytorów w Santiago. Ojciec Vincento uzna za bardzo interesujące, że Joachim Merriman ukrywa się na cmentarzu w Hawanie ze swoim wspólnikiem, miejscowym stróżem...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "...Czy już zeszły kolory z twojej twarzy? Daję ci słowo szlachcica: Jeden dzień po tym, jak zgłoszę swoje odkrycia, cała wyspa będzie pełna hiszpańskich żołnierzy. A ty będziesz rozciągany na torturach, błagając i płacząc, aż zdradzisz, gdzie ukrywa się ten Czarnoksiężnik. Najpóźniej wtedy zostaniesz spalony na stosie jako jego wspólnik, a ja będę oglądał auto-da-fe. Jak ci się to podoba?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "P-p-proszę, señor! Nie biorę w tym żadnego udziału, przysięgam! Ja... ja po prostu nic nie mogłem zrobić... Jak mogłem się mu przeciwstawić?! To straszny człowiek, on potrafi... nie masz pojęcia, co on może zrobić! Litości, błagam cię!";
			link.l1 = "Zaufaj mi, wiem, co on potrafi. Widziałem to na własne oczy. Więc? Gdzie on jest? Powiedz mi, a obiecuję, że nie wciągnę cię w tę sprawę.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "On... On ukrywa się w jaskini poniżej cmentarza. Można się tam dostać tylko przez drzwi kaplicy. Kiedy wychodzi, ukrywam się w swoim domu i siedzę tam. Nie masz pojęcia, jak bardzo chciałbym pozbyć się tego koszmaru!\nAle nie odważyłbym się nawet zbliżyć. Ja... Widziałem go, jak kopał świeży grób, a potem... potem zmarły wstał i chodził po cmentarzu w blasku księżyca! Prawie wtedy straciłem rozum! Ale Merriman zabronił mi odejść. Zagroził mi, że jeśli opuszczę mój dom bez jego pozwolenia choćby na pół dnia, znajdzie mnie i zamieni w to plugastwo... chodzący szkielet!";
			link.l1 = "Jak często opuszcza swą jaskinię?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Cóż, przynoszę mu jedzenie i mikstury lecznicze z miasta i... cokolwiek innego, czego żąda. Wyjeżdża raz lub dwa razy w miesiącu... kiedy księżyc jest w pełni. Zostawia notatkę przy drzwiach, pisze, czego potrzebuje... D-dostarczam to i kładę przy drzwiach, a on to zabiera, gdy wraca.";
			link.l1 = "Widzę. Te drzwi do jego legowiska - czy są jakoś zamknięte?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "Tak jest. Zawsze jest zamknięta. Jest bardzo solidna, a zamek jest masywny i skomplikowany.";
			link.l1 = "Hm... Merriman nie jest głupcem, z pewnością musi mieć inne wyjście ze swojej kryjówki, jak jego dom w Europie. Gdybyśmy wyważyli drzwi, wymknąłby się, nigdy więcej go nie znajdziemy. Hmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Panie, czy przysięgniesz, że nie wydasz mnie Inkwizycji?";
			link.l1 = "Dałem ci moje słowo, a słowo szlachcica jest święte. Przysięgam, że cię nie wydam.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Och, niech Cię Bóg błogosławi, Senor! Wiem, jak dostać się do jaskini. Jest klucz, drugi klucz... Ja go mam. Merriman nie wie, że do tego zamka są dwa klucze. Nigdy bym nie odważył się wejść, ale ty...";
			link.l1 = "Daj mi klucz, a uwolnię cię od tego koszmaru.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Proszę bardzo, Senor. Naprawdę zamierzasz wejść do jego legowiska?";
			link.l1 = "Jestem. Zamknij się w domu i czekaj tam, gdy wejdę do środka. Jeśli nie wrócę, zostaw wszystko i uciekaj, ile sił w nogach.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Ale bądź ostrożny, Senor. Z jego jaskini dochodzą przerażające dźwięki i boję się nawet pomyśleć, kto mógłby tam zamieszkiwać. Ale Merriman nie jest sam - to pewne.";
			link.l1 = "Wezmę wszystkie możliwe środki. Żegnaj.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
