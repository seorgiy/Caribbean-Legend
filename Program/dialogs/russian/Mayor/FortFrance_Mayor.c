// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать вопрос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня полно работы по управлению делами города, а ты всё вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Месье, я нашёл в джунглях труп бандита, убитого индейцами. На теле кроме прочего, были вот эти серьги - явно привезённые из Европы. Может, они принадлежали кому-то из знатных граждан вашего города?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Ваша Светлость, задание выполнено! Но обеспечить городу зрелище мне не удалось: преступник не пережил своего корабля и на свою казнь не явится.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Ваша Светлость, задание выполнено! Пленник дожидается виселицы у меня в трюме.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Я прибыл по приказу генерал-губернатора Филиппа де Пуанси чтобы принять командование над снаряжённым вами фрегатом.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Я готов принять в эскадру фрегат.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "Я прибыл по вашему приглашению, монсеньор...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "Случилось несчастье, монсеньор!";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Месье, у меня есть достоверная информация о предстоящей контрабандной сделке в пределах этого острова. Я полагаю, вам это будет интересно.";
				link.l1.go = "VPVL_Magor_1";
				break;
				
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Месье, я прибыл, чтобы узнать о судьбе корабля, с контрабандой.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  andre39966
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Дайте поглядеть поближе... Невероятно! Это просто невероятно, Шарль! Это серьги моей жены. Я сам их ей подарил перед отъездом в колонии. Они исчезли несколько месяцев назад при загадочных обстоятельствах. Я так и знал, что они были украдены!\nШарль, я очень рад, что вы пришли прямо ко мне, а не стали сбывать эту дорогую мне вещь лавочникам. Я в долгу не останусь. Как я слышал, вы собираетесь приобрести корабль? Раз вы решили приобщиться к морскому делу, то вам несомненно потребуется карта нашего архипелага. Вот, возьмите её. Уверен, она не раз вам пригодится!";
			link.l1 = "Спасибо, Ваша Светлость!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "Жаль, Шарль, но победителей не судят. Прошу, после вычета всех налогов вам положена награда: пять тысяч песо.";
			link.l1 = "Я рад, что смог оказаться полезным Сен-Пьеру и вам лично. Бой был непростым, но мне даже понравилось.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "Это был нелёгкий бой, Ваша Светлость, мой корабль сильно пострадал. Могу ли я просить вас компенсировать мои потери?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Браво, Шарль! Уверен, вы далеко пойдёте!";
			link.l1 = "До встречи, Ваша Светлость.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "Немного удивлен вашей просьбой, Шарль... Ну, так тому и быть - держите ещё две тысячи от меня лично в качестве жеста доброй воли. До свидания.";
			link.l1 = "Благодарю вас, Ваша Светлость.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Блестяще, Шарль! Вам будет приятно знать, что ваша победа поможет нашим друзьям из Ордена в проведении одной щекотливой операции... Прошу, после вычета всех налогов вам положена награда: восемь тысяч песо.";
			link.l1 = "Я рад, что смог оказаться полезным Сен-Пьеру, Ордену и вам лично. Бой был непростым, но мне даже понравилось.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "Это был нелёгкий бой, Ваша Светлость, мой корабль сильно пострадал. Могу ли я просить вас компенсировать мои потери?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Браво, Шарль! Уверен, вы далеко пойдёте!";
			link.l1 = "До встречи, Ваша Светлость.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "Пожалуй... вы заслужили. Держите ещё две тысячи от меня лично в качестве жеста доброй воли. Спасибо вам, друг мой.";
			link.l1 = "Благодарю вас, Ваша Светлость.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Корабль готов, но у вас нет места для него. Уменьшите вашу эскадру и возвращайтесь, и я сразу передам вам фрегат.";
				link.l1 = "Хорошо.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Да, конечно, корабль готов к выходу в море. Капитан осведомлён и будет выполнять все ваши распоряжения.";
				link.l1 = "Тогда мы отправляемся в путь. До свидания, Ваша Светлость.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Отлично. Принимайте. Капитан осведомлён и будет выполнять все ваши распоряжения.";
			link.l1 = "Тогда мы отправляемся в путь. До свидания, Ваша Светлость.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Капитан де Мор, наконец-то! Давно я не был так рад вашему прибытию! Проходите, устраивайтесь поудобнее.";
			link.l1 = "И вам хорошего дня, Ваша Светлость. Обычно ваша любезность имеет серьёзные причины. Что на этот раз? Пираты, испанцы, индейцы-людоеды?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Не иронизируйте, капитан, я не виноват, что мы с вами вечно попадаем в подобные ситуации. Но, прошу вас, не беспокойтесь, в этот раз стрельбы не будет... не должно быть.";
			link.l1 = "Вы меня интригуете, что ж, давайте по порядку. Чем могу быть полезен?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Вы слышали про заведение мадам Бото, не так ли? После того, как наш портовый, хм... весёлый дом сгорел при бомбардировке города испанцами, одна особа взялась за его восстановление.";
			link.l1 = "Пожар в борделе, и как я это пропустил? Ах да, испанцы... кажется, они в меня тоже тогда стреляли.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Проклятье, Шарль, да что с вами сегодня? Ваши остроты неуместны! Да, это не дело государственной важности, но это важно для меня лично, и мне нужна ваша помощь! Возьмите себя в руки, ради Бога, и выслушайте наконец!";
			link.l1 = "Прошу прощения, Ваша Светлость. Наверное, это от облегчения - я, признаться, подустал в последнее время от всех этих батальных полотен и был уверен, что у вас тут ещё одно на примете. Что ж, давайте про бордель. Мадам Бото, говорите? Не припоминаю.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Да, эта достойная... дама подняла заведение на совершенно новый уровень. Из банального приюта греха сие гостеприимное место превратилось в изысканное гнездо пороков для самого высшего общества. Там льётся рекой дорогое вино, а за карточными столами порой переходят из рук в руки целые состояния. Впрочем, вы сами всё увидите!";
			link.l1 = "Ваша Светлость, я, конечно, не ханжа, и вы так замечательно всё расписали, но с чего бы мне там появляться?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "С того, что вас пригласили, конечно! Я, видите ли, несколько виноват перед маркизой Бото и, чтобы загладить свою вину, обязался привести вас на её приём, при первой же оказии. А назавтра у неё как раз намечается званый вечер. Джулианна не часто даёт свои приёмы для избранной публики, так что окажите мне любезность - составьте компанию. Это будет весьма куртуазно и необременительно, поверьте. Никакой стрельбы и погонь. Вино, красивые женщины, карты и прочие достойные развлечения высшего общества.";
			link.l1 = "Играть в карты у куртизанок... Последний раз я так развлекался, кажется, уже в прошлой жизни. Но я всё ещё не понимаю - зачем вам я?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Вы словно не слушаете! Джулианна Бото, она, скажем так, коллекционирует в своём салоне различных ярких и знаменитых людей. Они придают её приёмам свежесть и интерес. Ну а вы личность весьма и весьма известная, и маркиза долгое время ждала случая заполучить такого гостя. И вот - моя оплошность дала ей эту возможность. Поймите, я не переживу, если она опять откажется меня видеть. А расплатой за провал будет именно это!";
			link.l1 = "Ваша Светлость, вы вдовец, недурны собой и, ко всему прочему, губернатор... Может, я чего-то не понимаю, но, мне кажется, все куртизанки колонии должны искать вашего расположения, а не наоборот?";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "Маркизе Бото покровительствует граф Генрих де Леви-Вантадур, милостью Его Величества, управляющий владениями Новой Франции в Северной Америке. Поверьте, Шарль, здесь, за океаном, нет желающих переходить ему дорогу. Скорее наоборот.";
			link.l1 = "А я уж было решил, что это возраст и вдовство дали гремучую смесь. Значит, дело в политике. Скучно, но ожидаемо. Хорошо, я окажу вам эту маленькую услугу. Будет неплохо вспомнить беззаботную молодость хотя бы на вечер.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Капитан, вы, конечно, многое повидали, но не пытайтесь прикидываться усталым стариком, вам это не идёт. И да, здесь не только политика. Я очень ценю... общество Джулианны и искренне благодарен вам за согласие. Это и правда важно для меня лично. Завтра после заката приходите в дом маркизы Бото. Обещаю, вам никакой политес этот вечер не испортит. И, Шарль, центральный вход в бордель будет закрыт, заходить нужно в боковые двери, в комнату, где обычно принимает Аврора.";
			link.l1 = "Хорошо, я понял. Вино, карты и женщины. Как в старые добрые... До встречи, Ваша Светлость!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Режим исследования: таймер не отключён. Уложитесь в срок!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Шарль, что с вами? На вас лица нет!";
			link.l1 = "Ангерран де Шиво, Ваша Светлость. Он угнал свой фрегат этой ночью. Перебил мою вахту и вышел в море, пока стоял туман.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "Это неприятно, я понимаю, но поверьте - такой исход весьма удовлетворителен. В кораблях и людях у вас нужды нет, а обстоятельства прошедшей дуэли граф де Леви-Вантадур оплатит неплохой суммой. Либо запомнит оказанную ему услугу по замятию дела, что не менее ценно\nДа, де Шиво поступил бесчестно - дважды, если быть точным, но теперь он далеко, а у нас на руках неплохие карты.";
			link.l1 = "Трижды, Ваша Светлость. На дуэли Ангерран признался мне, что жульничал во время игры. Если вы, говоря, что он 'заплатит' за свою подлость, имели в виду именно деньги, то я - нет. Де Шиво перешёл черту! На том корабле был человек... она мне очень дорога, очень! И я не позволю бастарду причинить ей вред! Слышите, Жак, не позволю!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "Кажется, припоминаю, я видел вас в обществе одной... девицы в мужском платье, увешанной оружием, что твой корсар. Шарль, не будьте глупцом! В ваших руках звезда с небес, вы чудом избежали огромных проблем, а теперь пытаетесь влезть в них снова? Оставьте это. Де Шиво убрался - и слава Господу! Что до вашей... боевой подруги - примите дружеский совет - отправляйтесь к Джулианне и забудьте.";
			link.l1 = "Исключено, Ваша Светлость. Некоторые вещи вам просто не понять, сойдёмся на этом, хорошо? А теперь рассказывайте мне всё, что знаете про бастарда. Куда он мог отправиться, сбежав из Сен-Пьера? И оставьте ваши увещевания - я переходил дорогу и Голландской Вест-Индской Компании, и пиратским баронам, и генерал-губернаторам, и даже Святой Инквизиции! Меня так просто не запугать. Я верну её, чего бы мне это ни стоило!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Шарль, а вы не задумывались, чьей милостью назначаются те же генерал-губернаторы? Поймите, это совершенно другой мир! Вы прикоснулись к нему лишь мельком, но он настолько выходит за пределы вашего понимания, что вы словно ребёнок на пороховом складе. И просите меня дать вам горящую лучину\nЧто же до генерал-губернаторов - то сам де Пуанси в прошлом не раз и не два уступал графу дорогу. Как в делах финансовых, так и в политических. Если принять на вооружение определение 'вице-король', столь популярное у простых горожан, то здесь, за океаном, это был бы Генрих де Леви-Вантадур.";
			link.l1 = "А я собираюсь снять шкуру с его единственного потомка мужского пола. Я понимаю, на что иду. А теперь просто скажите - вы знаете хоть что-то, что может мне помочь?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "В другой день я счёл бы этот ваш жест с рукой на пистолете концом нашей дружбы, Шарль. Но я понимаю - вы очень расстроены. И я готов сделать на это скидку и ничего не заметить\nЯ не знаю ничего, что помогло бы вам в ваших поисках. Фрегат вышел в тумане, вроде бы на запад, но потом мог повернуть куда угодно. Вам стоит вернуться к маркизе... Постойте, я не о том! Джулианна много лет знает вашего врага и была лично... знакома с его отцом долгое время. Расспросите её. И она, в отличие от меня, вряд ли будет вас отговаривать.";
			link.l1 = "Так и сделаю. До встречи, Ваша Светлость. Спасибо, что уделили мне время.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова    andre39966
		case "VPVL_Magor_1":
			dialog.text = "Контрабандная сделка, говорите? Хм... весьма любопытно. Расскажите подробнее, что вам известно?";
			link.l1 = "Три дня назад в бухту Ле Марен должен был прибыть корабль с неким грузом контрабанды. Однако он опоздал. У меня есть основания полагать, что он всё же явится со дня на день. Возможно, стоит подготовить встречу, месье губернатор.";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;
		
		case "VPVL_Magor_2":
			dialog.text = "Некий корабль, некий груз... И вы полагаете, что я должен довериться столь туманной информации?";
			link.l1 = "Месье, я понимаю, что информация довольно расплывчата. Но позвольте мне объяснить, при каких обстоятельствах я её получил. (рассказывает) ";
			link.l1.go = "VPVL_Magor_3";
		break;
		
		case "VPVL_Magor_3":
			dialog.text = "Что ж, мы проверим вашу информацию. Если судно с контрабандой действительно бросит якорь у Ле Марен, вас капитан, ждёт достойная награда. Загляните ко мне через три дня. К тому времени всё должно проясниться.";
			link.l1 = "Отлично. Тогда до встречи через три дня.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;
		
		case "VPVL_Magor_4":
			dialog.text = "Хорошо, что вы пришли, капитан. Ваши сведения оказались весьма ценными и заслуживают награды. Вот. Сто пятьдесят дублонов, извольте получить.";
			link.l1 = "Благодарю, месье губернатор. Рад, что информация оказалась полезной. Всегда к вашим услугам.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;
		
		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;
		
		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова     andre39966
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

