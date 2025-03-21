// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                          "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "Я - капитан "+GetFullName(pchar)+". Ваш человек встретил меня в порту и сообщил, что вы желаете меня видеть. Слушаю вас внимательно.";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "Это снова я, месье "+GetFullName(npchar)+". Я привёз Бертрана Пинетта. Он у меня в трюме.";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "Это снова я, месье "+GetFullName(npchar)+". Давайте поговорим.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "Это снова я, месье "+GetFullName(npchar)+". Давайте поговорим.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "Это снова я, месье "+GetFullName(npchar)+". Вы, видимо, уже и не ждали меня увидеть.";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			dialog.text = "А-а, капитан "+GetFullName(pchar)+"! Очень рад вас видеть. Совсем заждался, уже и отчаиваться начал... Хорошо. У меня к вам такое дело: некоторое время назад к вам в порту подходил человек по имени Бертран Пинетт с целью подняться на борт вашего судна. Такой состоятельный на вид господин, в роскошном парике. Ведь я прав?";
			link.l1 = "Да, припоминаю такого господина. Он действительно обращался ко мне с целью нанять моё судно.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			//Log_Info("Вы получили тяжёлый кошель");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "Нанять ваше судно? Капитан, вы меня очень обяжете, если сообщите мне подробности этого дела. В долгу я не останусь. Вот этот туго набитый золотом кошель теперь ваш. Держите и поведайте мне всё, что касается Бертрана Пинетта.";
			link.l1 = "Хорошо. Месье Пинетт зафрахтовал моё судно для того, чтобы я доставил его и двух его друзей с Гваделупы на испанский Мэйн, а именно - в залив Москитос, что у Порто-Белло. Я выполнил его заказ и перевёз Бертрана и его товарищей в указанное место, где они покинули мой корабль и ушли в джунгли.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Ясно. А месье Пинетт не говорил, куда он дальше намерен отправиться? И что за спутники были у него?";
			link.l1 = "По словам месье Пинетта, они собирались в Панаму. А друзья у него были достаточно интересные: два офицера - один испанец, второй - француз. Уж не знаю, что их связывало, но мне платили не за то, чтобы я задавал им вопросы.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Испанский офицер? И французский? О! Вот это да! Ай да месье Пинетт! Такого прохиндея ещё поискать надо! И тут денежек ухватил, и наверняка немало! В Панаму, говорите...";
			link.l1 = "Да. Это всё, что я знаю о Бертране Пинетте. Что-нибудь ещё, месье, или я могу откланяться?";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "Постойте, капитан. У меня к вам будет деловое предложение. Вы же не против заработать немного денег? Но сначала позвольте мне вкратце объяснить вам ситуацию относительно месье Пинетта. Это касается дела, которое я хочу вам поручить.";
			link.l1 = "Ну, давайте послушаем.";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "Месье Бертран Пинетт появился в нашей колонии года два назад, и весьма успешно занялся бизнесом с капитанами кораблей. Проще говоря, он обтяпывал самые разные дела и... делишки. Ему привозили товар, который был в дефиците в нашей колонии для продажи, он договаривался о перевозках и доставках ценных вещей, не гнушался и работорговлей, как я слышал. Он систематически брал у меня в банке кредиты для своих махинаций, но всегда расплачивался точно, в срок и с процентами\nИ вот, незадолго до своего исчезновения с вашей помощью, он взял у меня очередной кредит для... одной операции. Причём этот кредит превышал любой из тех, что я выдавал ему ранее. Но поскольку клиент старый, с безупречной кредитной историей, то я и поверил ему. Как оказалось - зря. Месье Пинетт сбежал, и возвращать займ, очевидно, не собирается.";
			link.l1 = "И как велика сумма, которую он вам должен, позвольте поинтересоваться?";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "Велика. Примерно сто пятьдесят тысяч песо, не считая процентов. Кредит был выдан в золотых дублонах, десять сундуков по сто пятьдесят штук.";
			link.l1 = "Кхм... Два года примерно расплачивался по счетам, приучил вас, а потом взял огромную сумму и скрылся.";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "Именно так, капитан. Поэтому я бы хотел поручить вам работу: отыскать этого негодяя и привезти ко мне в Бас-Тер. А тут уж мы с губернатором и комендантом подумаем, как заставить его раскошелиться. Вы видели его в лицо, вы его отвозили - у вас больше шансов найти месье Пинетта, чем у кого-либо ещё. Я, конечно, направлю по его следу профессионального охотника за головами, но мне кажется, что ваша помощь может оказаться эффективнее.";
			link.l1 = "И что насчёт награды?";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "Я дам вам за успешную работу сундучок с дублонами, сто пятьдесят штук.";
			link.l1 = "Мне кажется, что за поиски и, по сути, похищение человека, да ещё в испанском городе, награда как-то невелика.";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "Капитан, я полагаю, что месье Пинетт не скупился с оплатой... моими деньгами, раз вы так низко цените предложенную награду. Я смею вас уверить, что это вознаграждение достойное. Вы, безусловно, вправе отказаться, но... я хочу сообщить вам ещё кое-что, и вы наверняка измените своё мнение.";
			link.l1 = "И что же это может быть?";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "За пару дней до того, как Пинетт сбежал с Гваделупы, из казематов форта Бас-Тер сбежал военнопленный, испанский гранд, офицер, дон Карлос де Мильяр. Этот побег стал возможен благодаря предательству французского офицера, лейтенанта морской пехоты... Капитан, а теперь сопоставьте события и пораскиньте мозгами: кто уплыл на вашем корабле из Гваделупы вместе с месье Бертраном Пинеттом?";
			link.l1 = "Гм... А какое я имею к этому делу отношение? Я просто отвёз пассажиров по найму...";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "Да, конечно! Лично у меня нет сомнений в том, что вы не принимали участие в организации побега дона де Мильяра. Но ведь наш губернатор, и комендант, и командующий гарнизоном вполне могут рассудить иначе. Тут как минимум - соучастие, а как максимум... боюсь подумать. Сами посудите - вы взяли на борт испанца, наверняка в какой-то потайной бухте, вывезли его с острова... я прав, капитан?";
			link.l1 = "Мне всё понятно. Вы меня шантажируете. Зря я к вам зашёл...";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "Что вы, капитан! Какой шантаж! Я всего лишь прошу вас помочь мне и предлагаю хорошую оплату за эту помощь. Будьте так любезны - отыщите месье Пинетта и привезите в Бас-Тер. Я буду ждать. Думаю, двух месяцев вам вполне будет достаточно для путешествия к Панаме и назад.";
			link.l1 = "Вы не оставили мне выбора. Однако я не думаю, что такой способ ведения дел послужит установлению между нами дружеских отношений. До свидания, месье.";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("Режим исследования: срок квеста увеличен в два раза");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - Старт квеста "Мерзкий Божок"
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Прекрасные новости, капитан "+GetFullName(pchar)+"! Я сейчас же отправлю своих подручных на ваш корабль. Теперь эта птичка от меня никуда не улетит... Ну, а вы заслужили свое вознаграждение - получите. Вот ваш сундук. И ещё, чтобы вы поменьше на меня обижались, небольшой подарок - амулет.";
			link.l1 = "Благодарю. Полагаю, ваше молчание об этой истории также входит в вознаграждение?";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			//Log_Info("Вы получили сундучок с дублонами");
			//Log_Info("Вы получили амулет 'Рыбак'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "О какой истории, капитан? Я что-то не припоминаю никакой истории, связанной с вами. Буду рад видеть вас среди моих клиентов. Ну а молчание... вы же знаете - оно как золото.";
			link.l1 = "Иногда даже дороже золота, месье. Я ваш урок усвоил прочно. Всего доброго!";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "Давайте. Бертран Пинетт, полагаю, у вас на корабле?";
			link.l1 = "Нет. Зато у меня есть кое-что другое для вас. Возьмите и прочтите это.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Что это?";
			link.l1 = "Читайте, читайте, месье. Потом продолжим.";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(читает) Кхм... Что это за бред лихорадочного больного?";
			link.l1 = "Вы серьёзно? Ну ладно, я отнесу этот 'бред' месье Клоду Франсуа де Лиону. Думаю, ему будет крайне интересно узнать, кто есть истинный организатор исчезновения судна 'Куражю' и партии алмазов. Что вы так побледнели?";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "Значит, вы всё-таки нашли Пинетта...";
			link.l1 = "Да. Так что я предлагаю вам сделку: вы забываете про Карлоса де Мильяра, Жана Дено и прочих лиц, а я забываю про содержимое этого письма.";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "Хорошо, капитан... я согласен.";
			link.l1 = "Вот и славно. Надеюсь, вы не держите на меня зла - мне кажется, что мы в расчёте. Всего доброго.";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "Кхе-кхе... Вы правы, капитан...";
			link.l1 = "У меня для вас кое-что припасено. Возьмите и прочтите это.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "Значит, вы всё-таки нашли Пинетта...";
			link.l1 = "Да. Так что я предлагаю вам сделку: вы восстанавливаете моё доброе имя перед французскими властями, и немедленно, а я забываю про содержимое этого письма.";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "Но...";
			link.l1 = "Меня не волнует, как вы это сделате. Если завтра же преследования не прекратятся, я изыщу способ уведомить месье Клода Франсуа де Лиона о том, о чём вы сейчас только что прочли.";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



