// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Ośmielasz się pokazać tutaj swoją twarz?! Nie wiem, czy jesteś odważny, czy głupi...","Jak to się stało, że te leniwe kości pozwoliły wrogowi wtargnąć do mojego mieszkania? To jest poza mną...","Z pewnością, moi strażnicy nie są warci grosza, jeśli takie łajdaki biegają tutaj..."),LinkRandPhrase("Czego potrzebujesz,"+GetSexPhrase("łotr","smrodek")+"?! Moi żołnierze już ruszyli na twój trop, "+GetSexPhrase(", brudny piracie","")+"!","Brudny morderco, natychmiast opuść mój dom! Strażnicy!","Nie boję się ciebie, "+GetSexPhrase("szczur","dziwka")+"! Wkrótce zostaniesz powieszony w naszym forcie, a potem już daleko nie uciekniesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Żołnierze nie są warci ani grosza...","Oni nigdy mnie nie złapią."),RandPhraseSimple("Zamknij swoją paplaninę, "+GetWorkTypeOfMan(npchar,"")+", albo wyrwę ten twoj brudny język!","Radziłbym ci siedzieć cicho, a może, przeżyjesz to..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Wroga w kopalni! Alarm!";
				link.l1 = "Aaah, diabeł!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", panie. Jestem "+GetFullName(npchar)+", inżynier górniczy z kopalni Los-Teques. Czego tu szukasz?","Witaj, señor. Czego chciałeś?","Hmm... czy chciałeś coś ode mnie, senorze? Słucham.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "Jestem tutaj nowy i chciałbym dowiedzieć się więcej o tej kopalni...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "Mam ładunek w moim ładowni, który może cię zainteresować. Dokładnie mówiąc, niewolnicy do twojej kopalni. Chcesz targować się?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "Właśnie przyszedłem, żeby się przywitać, a już wyjeżdżam.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Kopalnia Los-Teques wydobywa złoto dla Hiszpańskiej Korony. Wszystko, co wydobywamy, należy do Hiszpanii. Znajdujemy tu nie tylko złoto, ale także srebrne samorodki i cenne kamienie szlachetne. Nie sprzedajemy tutaj złota, wszystko, co wydobywamy, jest dostarczane do Starego Świata pod eskortą wzmocnionego konwoju\nAle mamy dwa wyjątki dla złotych i srebrnych samorodek. Po pierwsze, możesz kupić pewną ilość z nich w naszym lokalnym sklepie od kwatermistrza. Czasami pensja nie dociera tutaj na czas, więc musimy trzymać tutaj pewne oszczędności monet na takie przypadki, dlatego dozwolony jest lokalny handel\nPo drugie, ciągle doświadczamy potrzeby siły roboczej, więc wymieniamy samorodki na niewolników. Dlatego, jeśli masz coś do zaoferowania, porozmawiaj ze mną, zrobimy interes\nWierzę, że zasady zachowania w kopalni są oczywiste: nie kradnij, nie rozpraszaj skazańców i nie przeszkadzaj żołnierzom, inaczej nie spodobają ci się konsekwencje.";
			link.l1 = "Dobrze, dziękuję!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Oczywiście, senor! Ile ich masz?";
			link.l1 = "Mam "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Senor, niestety, w tej chwili nie potrzebujemy więcej niewolników. Ale sytuacja może się zmienić w każdej chwili, więc sprawdź za kilka tygodni lub w innym czasie.";
				link.l1 = "W porządku, senorze, rozumiem. Nie potrzebujesz ich teraz, ale możesz potrzebować ich za jakiś czas.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oczywiście, senor! Ile ich masz?";
				link.l1 = "Mam "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "Za każdego niewolnika jestem gotów zapłacić ci albo jednym sztabkiem złota, albo dwoma sztabkami srebra. Co wybierasz?";
			link.l1 = "Złote sztabki.";
			link.l1.go = "slaves_g";
			link.l2 = "Srebrne sztabki.";
			link.l2.go = "slaves_s";
			link.l3 = "Przykro mi, senor, ale właśnie zmieniłem zdanie. Kiedy indziej.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Dobrze. Ile niewolników zamierzasz mi sprzedać?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Dobrze. Ile niewolników zamierzasz mi sprzedać?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Senorze, nie mam czasu na głupie żarty. Jeśli masz ochotę na żartowanie, idź do tawerny!";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Senorze, myślę, że potrzebujesz odpocząć. Być może jesteś bardzo zmęczony lub dostałeś udaru ciepła. Idź do tawerny, dobrze odpocznij, a potem możemy kontynuować nasze targowanie.";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "Niestety, panie, teraz nie potrzebujemy tak wielu niewolników. Kopalnia obecnie wymaga "+FindRussianQtyString(sti(location.quest.slaves.qty))+". Czy zamierzasz sprzedać tak wiele?";
				link.l1 = "Tak, oczywiście!";
				link.l1.go = "slaves_max";
				link.l2 = "Hmm... Chyba nie jestem.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Doskonale. Proszę kazać im przynieść je do bram miasta. Wyślę po nich swoich ludzi.";
			link.l1 = "Nie martw się, senorze. Twoi niewolnicy zostaną dostarczeni na czas. Wydam wszystkie odpowiednie rozkazy natychmiast.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "Doskonale. Proszę o przysłanie ich do bram miasta. Wyślę swoich ludzi po nich.";
			link.l1 = "Nie martw się, senorze. Twoi niewolnicy zostaną dostarczeni na czas. Wydam wszystkie odpowiednie rozkazy natychmiast.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
