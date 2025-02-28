// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "Pax vobiscum! Итак, я наконец узрел в своей обители французского капитана, храброго солдата и, надеюсь, верного и преданного слугу Священной Римской Католической церкви. Проходи, "+GetSexPhrase("сын мой","дочь моя")+", располагайся.";
				link.l1 = "Здравствуйте, Ваше Преосвященство. Долог и тернист был мой путь сюда. Per aspera ad astra...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Итак, "+GetSexPhrase("сын мой","дочь моя")+", я вижу по твоим глазам, что ты несёшь мне новости. Рассказывай, я весь внимание.";
				link.l1 = "Я нашёл вашего бывшего секретаря, Ваше Преосвященство...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Ты несёшь какие-нибудь новости из Сан-Хосе, "+GetSexPhrase("сын мой","дочь моя")+"?";
				link.l1 = "Да, Ваше Преосвященство. Я раскопал кое-что касательно судьбы фрегата Мигеля Дичозо. Как только корабль приблизился к выходу в океан, он немедленно был захвачен внезапно налетевшим штормом и унесён назад в Карибское море...";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Да благословит Господь дела твои, "+GetSexPhrase("сын мой","дочь моя")+"... Что тебе угодно?";
				link.l1 = TimeGreeting()+", Ваше Преосвященство. Есть какие-нибудь новости по нашему делу?"
				link.l1.go = "guardoftruth_17";
				break;
			}
			dialog.text = "Ты что-то хотел"+GetSexPhrase("","а")+", "+GetSexPhrase("сын мой","дочь моя")+"?";
			link.l1 = "Да нет, ничего, отче.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "Путь добродетели всегда труден и тернист, "+GetSexPhrase("сын мой","дочь моя")+". Но достигнутая цель сполна вознаграждает праведника за труды его...";
			link.l1 = "Согласен, святой отец. Я выполнил ваше поручение полностью: капер, похитивший драгоценную утварь уже у вас, а теперь я возвращаю приходу Сантьяго и украденное: остензорий, крест и кадило. Вот, возьмите их.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Благодарю тебя за верную службу церкви и успешную помощь приходу Сантьяго, "+GetSexPhrase("сын мой","дочь моя")+". Твои труды не должны остаться без награды. Прихожане собрали пожертвования отважному воину добра, и я с радостью передаю их тебе. Держи.";
			link.l1 = "Спасибо, ваше преподобие... Не ожидал.";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			//Log_Info("Вы получили сундучок с дублонами");
			PlaySound("interface\important_item.wav");
			dialog.text = "Верная служба церкви всегда поощряется с моей стороны, "+pchar.name+". Надеюсь, что я получил в твоём лице преданного воина во благо и защиту веры во Христа, ибо серьёзная угроза нависла над нами...";
			link.l1 = "О чём вы сейчас, святой отец?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Сын мой, возможно, именно ты выступишь орудием в борьбе против зла, ибо многие знамения указывают на это.";
			link.l1 = "Какие знамения?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Многие, "+GetSexPhrase("сын мой","дочь моя")+"... И одно из них - твоё желание помочь в розысках золота индейских язычников из Тайясаля, ибо то, что содержится в этих сокровищах, и несёт в себе опасность для всего христианского мира.";
			link.l1 = "Не могли бы вы немного просветить меня насчёт этого золота, святой отец? Историю его исчезновения я уже знаю, а вот подробности... и что за угроза?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Слушай и внимай, "+GetSexPhrase("сын мой","дочь моя")+", однако помни, что всё услышанное тобой не предназначается ни для чьих ушей, кроме твоих... Ещё задолго до того, как небезызвестный тебе Мигель Дичозо вывез сокровища язычников из старого индейского города, мною в рамках моей миссии на архипелаге был схвачен и допрошен индеец племени ица, потомок языческой цивилизации майя\nОт него-то мы узнали и о Тайясале, и о том, что силы зла уже готовятся нанести страшный удар по всему христианскому миру. Последствия будут ужасны. Я приложил все усилия, дабы предотвратить катастрофу, сообщил в Эскориал и в Ватикан\nК моему гласу прислушались, и на Карибы был командирован дон Рамон де Мендоса-и-Риба, который основал свою ставку на острове Провиденсия и приступил к поискам Тайясаля. Однако сей кабальеро был движим отнюдь не стремлением предотвратить катастрофу, а жаждой личного обогащения\nПоэтому Господь отвернулся от него - все его усилия были тщетны и привели лишь к бессмысленной гибели испанских солдат. Я написал прошение в Эскориал об отстранении де Мендосы от этого дела ввиду некомпетентности, и оно было удовлетворено, но тут...";
			link.l1 = "Появился Мигель Дичозо.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Кукулькана?! О, Пресвятая Дева! Опять Кукулькан... ";
			else sTemp = "Хм... ";
			dialog.text = "Именно, "+GetSexPhrase("сын мой","дочь моя")+"! При помощи этого авантюриста, в прошлом - наёмника, был найден Тайясаль и сокровищница древних майя. Однако недолгой была радость барона - сокровища сгинули вместе с Дичозо. Вероятно, вместе с золотыми слитками и украшениями, Мигель прихватил с собой древний источник зла в нашем мире, артефакт почитаемого майя языческого божества, называемый Маской Кукулькана...";
			link.l1 = sTemp+" Но о каком зле вы говорите, ваше преосвященство? Откуда вы про него знаете?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "Зло, несущее погибель всем христианам на Карибах, Новом Свете и, возможно, даже в Старом. Конец может быть скорым и внезапным, и никто даже не осознает того, что произошло. И предвестники этого конца уже повсюду!";
			link.l1 = "Какие предвестники? Я не понимаю...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "Сын мой, неужели ты настолько слеп, что не замечаешь их? Они появились уже как четверть века назад...";
			link.l1 = "Хочу смиренно заметить, ваше преосвященство, что продолжительность моей жизни исчисляется ровно этим сроком, так что моё неведение вполне оправдано...";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "Я понял тебя, "+pchar.name+". Но разве не обратил ты внимание на странные вещи, творящиеся на архипелаге, когда прибыл сюда из Европы? Разве не кажется тебе странным, что колдовство, чёрная магия и прочие нечистые обряды здесь имеют куда большую силу, нежели в других краях? Языческие амулеты, заговорённые индейскими шаманами, приобрели реальную мощь, ощутить которую на себе может каждый\nХристиане-алхимики овладели искусством создания заговорённых предметов, не понимая того, что тем самым они служат злу. Разве ты не чувствуешь это неестественное, богомерзкое присутствие чего-то... непознанного?";
			link.l1 = "Вы правы, отче. Меня это удивило сначала, но теперь я, пожалуй, к этому даже как-то привык... Новый Свет же!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "Так было не всегда и в Новом Свете. То, о чём я тебе рассказываю, появилось тут всего двадцать пять лет назад, и оно с каждым днём всё более и более набирает силу. Это означает лишь одно: он уже пришёл сюда, он среди нас, и он действует...";
			link.l1 = "О ком вы говорите? Кто этот таинственный 'Он'?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "Заклятый враг всех христиан. Можно сказать - демон, желающий разрушить все устои существующего мира...";
			link.l1 = "Вы говорите об Антихристе?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Возможно. Но неважно, какое имя он носит. Важно, что он собирается сделать. Для того, чтобы этого не произошло, я и нахожусь здесь. Но мы увлеклись, "+GetSexPhrase("сын мой","дочь моя")+", а ты, как человек дела, вероятно, хочешь конкретики, а не пространных рассуждений?";
			link.l1 = "Я узнал от вас сейчас много нового и важного, ваше преосвященство. И готов слушать дальше.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "Ты воспитан и учтив, "+GetSexPhrase("сын мой","дочь моя")+". Это хорошо. Теперь ближе к вопросу, по которому ты пожаловал ко мне. Найти вывезенные Дичозо из Тайясаля сокровища - вот наша с тобой совместная цель, ибо именно среди них мы сможем, вероятно, найти то, что позволит нам противостоять в борьбе против зла.";
			link.l1 = "Но быть может Дичозо уже покинул Архипелаг и находится сейчас вместе с этим золотом в Старом Свете?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "Нет, это не так. У меня есть косвенные доказательства того, что эти сокровища остались на Карибах. Какие - это пока тебе знать не нужно, ты должен просто доверять мне. Кроме того, я полагаю, что Дичозо лгал барону\nЕго рассказ о том, что Тайясаль - это руины среди джунглей, не соответствуют показаниям допрошенного индейца ица. Также очень настораживает тот факт, что из всей экспедиции выжил один Дичозо.";
			link.l1 = "Я так понимаю, дон Мендоса тоже так считает, раз организовал нападение на Сен-Пьер с целью отыскать Дичозо?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "Действия барона не должны тебя беспокоить, "+GetSexPhrase("сын мой","дочь моя")+". Им движет жажда золота и наживы, а она - плохой попутчик, когда дело касается борьбы со злом и спасения мира...";
			link.l1 = "У вас есть какие-то подозрения, где нам искать сокровища и самого Дичозо?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "Я думаю об этом ежеминутно, "+GetSexPhrase("сын мой","дочь моя")+", но пока ничего точного сообщить тебе не могу. Но есть человек, который поможет нам приблизиться к нашей общей цели. Это мой бывший секретарь, учёный, которого я привёз с собой из Генуи. Он присутствовал при допросе индейца ица, и, вероятно, слишком сильно проникся услышанным\nЗло овладело им. Он употребил данный ему Создателем талант лекаря в тёмных целях - стал заниматься чернокнижием. Он самовольно провёл несколько бесед с индейцем, без моего ведома, после чего исчез. Мы должны спасти эту заблудшую душу...";
			link.l1 = "Я должен найти этого человека?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Да, "+GetSexPhrase("сын мой","дочь моя")+". Это первый шаг к тому, чтобы отыскать сокровища и оружие против зла. Он может многое сообщить нам.";
			link.l1 = "Кто этот человек?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "Его зовут Джино Гвинейли. Молодой человек тридцати лет. Способный лекарь и алхимик. Как я уже говорил, занялся чернокнижием и исследованием магичеких сил. По моим последним сведениям, он скрывается где-то у англичан\nВооружись полученным знанием, "+GetSexPhrase("сын мой","дочь моя")+", и найди алхимика и лекаря Джино. Если ты смог найти морского разбойника, похитившего драгоценную утварь, то сможешь отыскать и моего беглого секретаря и доставить его сюда. Действуй же, "+GetSexPhrase("сын мой","дочь моя")+"! Благословляю тебя.";
			link.l1 = "Я понял, ваше преосвященство. Не буду терять ни минуты. До встречи!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "Я едва не выдал себя возгласом удивления. Отец Винсенто поручил мне найти и доставить к нему лекаря и алхимика Джино Гвинейли. Того самого Джино, который живёт в комнате на втором этаже моего дома в Сент-Джонсе!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "Мне нужно найти некоего Джино Гвинейли, который скрывается где-то в английских поселениях. Будем искать, учитывая то, что Джино - алхимик и лекарь. Где же такой человек может прятаться?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Я не сомневался в том, что услышу от тебя именно эти слова, "+pchar.name+". Я всё более укрепляюсь в том, что тебя прислало мне само Провидение. Где этот несчастный блудный сын?";
			link.l1 = "Я боюсь, что вам не понравится то, что вы услышите, но выбора у меня нет. Ваш секретарь мёртв.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Да спасёт Господь его душу и да простит грехи его тяжкие... Как это случилось, "+GetSexPhrase("сын мой","дочь моя")+"?";
			link.l1 = "Я нашёл Джино на Антигуа. Он там скрывался в одном из старых домов, который обустроил под лабораторию. На мои уговоры отправиться в путь по доброй воле он не поддался. Услышав же ваше имя и увидев, что я готов применить силу, он вытащил из складок своего длинного балахона какой-то пузырёк с прозрачной жидкостью и мигом осушил его...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "Дальше творилось что-то страшное: он покраснел, затем посинел, упал на пол, начал корчиться в судорогах и через минуту испустил дух, а по комнате расплылся сильный запах миндаля. Ваш секретарь выпил какой-то яд - настолько он не желал встречи с вами.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Бедный раб Божий Джино... даже свою последнюю минуту жизни он провёл во грехе - совершил самоубийство. Я буду молиться за его душу...";
			link.l1 = "После того, как ваш секретарь перестал шевелиться, я обыскал его обиталище и нашёл вот этот фолиант. Быть может, он вас заинтересует, или поможет в наших розысках? Здесь какие-то учёные записи...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("Вы отдали альманах");
			PlaySound("interface\important_item.wav");
			dialog.text = "Это альманах несчастного Джино. В нём он вёл записи всех своих изысканий. Дай мне его, "+GetSexPhrase("сын мой","дочь моя")+", я изучу то, что там написано. Возможно, что-то натолкнёт нас на правильный путь\nХоть ты и не доставил в мою обитель Джино Гвинейли живым, я всё равно доволен твоей работой и проявленным усердием, "+GetSexPhrase("сын мой","дочь моя")+". А сейчас у меня есть для тебя некоторые новости.";
			link.l1 = "Слушаю вас, отец Винсенто.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Я добыл сведения о том, что последнее место, где видели фрегат Дичозо с сокровищами на борту - остров Тринидад. Известно мне и приблизительное время - первая половина апреля месяца 1654 года от рождества Христова\nОтправляйся на Тринидад и попытайся узнать хоть что-нибудь о дальнейшей судьбе фрегата: куда он направлялся, какие были планы у капитана, любую мелочь. Я понимаю, прошло уже много дней с того момента, а память людская коротка, но... утопающий цепляется за соломинку.";
			link.l1 = "Я сделаю всё для того, чтобы эта соломинка стала не меньше бревна.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Дай мне свою верительную грамоту, я впишу туда разрешение на посещение колонии Сан-Хосе.";
			link.l1 = "Возьмите.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "Вот... теперь всё. Не забывай поднимать флаг Испании на своём корабле. Ступай же с моим благословением, "+GetSexPhrase("сын мой","дочь моя")+"!";
			link.l1 = "Погодите, Ваше Преосвященство. Вы позволите вопрос?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Да, конечно. Что ты хотел узнать?";
			link.l1 = "В нашу прошлую встречу вы рассказывали об индейце, который поведал вам о Тайясале. Я долго думал об этом... Скажите, у этого язычника было что-нибудь при себе? Какие-то предметы, записи, что-то иное? Это могло бы оказаться полезным.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "При том индейце не было никаких значимых вещей, "+GetSexPhrase("сын мой","дочь моя")+". Набедренная повязка, примитивные украшения, бамбуковая трубка с травами да кусок грубой кожи, который был использован в качестве кляпа\nВсе вещи индейца были переданы прибывшему по распоряжению Эскориала уже известному вам барону Рамону де-Мендосе-и-Риба. Но уверяю, ничего интересного там не было.";
			link.l1 = "Всё ясно, отец Винсенто. Спасибо за ответ. До встречи!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Да смилуется над нами Всевышний... Что стало дальше с Мигелем Дичозо? Ты узнал?";
			link.l1 = "Увы, нет. Последнее, что сообщил очевидец - 'Санта-Квитерию' понесло штормом в сторону Мартиники. Погиб корабль, или спасся - доподлинно неизвестно. Но у меня есть подозрения, что Мигель Дичозо всё-таки остался жив.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Почему ты так решил, "+GetSexPhrase("сын мой","дочь моя")+"?";
			link.l1 = "Ключ именно в том, что фрегат скрылся в направлении Мартиники. А совсем недавно славный кабальеро по имени Диего де Монтойя, человек самого дона Рамона де Мендосы, атаковал Сен-Пьер, и целью его было найти Мигеля Дичозо, якобы скрывающегося там.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Значит, барон считает, что Дичозо укрылся у французов...";
			link.l1 = "Я неплохо знаю Сен-Пьер и губернатора Жак Дьель дю Парке, Ваше Преосвященство. И ни про какого испанца по имени Мигель Дичозо в Сен-Пьере не слышали. Скажите, как мне найти Диего де Монтойю? Я бы хотел побеседовать с ним по поводу Дичозо.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Ты уверен, что он станет разговаривать с тобой, "+GetSexPhrase("сын мой","дочь моя")+"? Не думаю. Разве что на языке шпаг и пистолетов.";
			link.l1 = "Может, ваше имя смогло бы развязать ему уста?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Ох,  "+pchar.name+". Навряд ли подручный барона пойдёт тебе навстречу. Отдать ему приказ прибыть в Сантьяго на аудиенцию ко мне - это возможно, но я не уверен, что Диего будет со мной искренним.";
			link.l1 = "Какие же будут наши дальнейшие действия, отче?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Оставь меня на какое-то время, "+GetSexPhrase("сын мой","дочь моя")+". Я должен проанализировать сказанное тобой, а также сопоставить все факты, которые мне известны, в единое целое. И тогда я скажу, что мы предпримем дальше. Зайди ко мне позже.";
			link.l1 = "Хорошо, Ваше Преосвященство. Так и поступим. Буду заглядывать периодически...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "Да благословит Господь дела твои... Что ты хотел"+GetSexPhrase("","а")+", "+GetSexPhrase("сын мой","дочь моя")+"?";
			link.l1 = "Есть какие-нибудь новости, Ваше Преосвященство?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Пока нет, "+GetSexPhrase("сын мой","дочь моя")+". Но не отчаивайся, я и мои люди работаем над этим. Заходи позже.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Да, "+GetSexPhrase("сын мой","дочь моя")+", есть некоторая информация о Мигеле Дичозо. Я недаром считал, что Дичозо всё ещё на архипелаге и жив. И дон Диего де Монтойя был прав. Получено свидетельство от человека, знавшего Мигеля Дичозо в лицо, в том, что этого кабальеро видели в пиратском посёлке Ле Франсуа на Мартинике, как раз в апреле 1654 года, после исчезновения 'Санта-Квитерии'...";
			link.l1 = "Значит, фрегат всё же разбился у берегов этого острова?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Не торопись, "+GetSexPhrase("сын мой","дочь моя")+". Вот как раз о крушении какого бы то ни было корабля в то время у Мартиники сведений нет. А фрегат - не люггер, и его гибель наверняка привлекла бы внимание.";
			link.l1 = "Может, имеет смысл обыскать прибрежные воды и пляжи на предмет останков корабля?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Сын мой, это всё уже давно проделал небезызвестный тебе дон Диего де Монтойя, и - безрезультатно. Но ты слушай дальше... Мои источники на Провиденсии сообщают, что барон Рамон де Мендоса уверен, что 'Санта-Квитерия' до сих пор бороздит Карибское море, но под другим названием\nИменно поэтому он устроил на Мигеля Дичозо охоту. По словам барона, 'Санта-Квитерию' часто видели у берегов острова Исла-Тесоро, а в последнее время её неоднократно замечали в составе военной эскадры под английским флагом.";
			link.l1 = "Странно всё это. Смотритель маяка Тринидада утверждал, что выстоять в такой шторм кораблю было невозможно... А теперь её видят под английским флагом. Не вяжется одно с другим никак. Почему барон решил, что это именно 'Санта-Квитерия'? Она что, настолько уникальна?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Именно так. Этот фрегат строился по усовершенствованной технологии в Европе, имеет неординарный внешний вид и выдающиеся ходовые характеристики. Так сообщил мой источник.";
			link.l1 = "И как теперь назвается 'Санта-Квитерия'?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "А вот это мне к сожалению не известно... Отправляйся на Исла Тесоро, "+pchar.name+", и попробуй узнать что-нибудь про фрегат Дичозо. Быть может, так мы сумеем найти и его бывшего капитана.";
			link.l1 = "Будет сделано, Ваше Преосвященство!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "Рад, что ты всё же решился прийти на встречу, "+GetSexPhrase("сын мой","дочь моя")+"...";
			link.l1 = "Здравствуйте, Ваше Преосвященство. После встречи с доном Алонсо де Мальдонадо, я уже и не думал, что когда-либо встречусь с вами.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Дон Алонсо де Мальдонадо нарушил приказ. Я строжайше запретил ему вступать в конфликт с тобой, "+GetSexPhrase("сын мой","дочь моя")+", ибо прекрасно знал, чем это для него закончится. В задачу де Мальдонадо входило сопровождение тебя в Тайясаль - Алонсо уже бывал там\nКроме того, приданный ему отряд испанских солдат и эскадра должны были выступить ударной групировкой в боях против краснокожих безбожников ица. Движимый своенравием и необузданной жаждой мести, Алонсо повёл себя недостойно\nОн не только сорвал поход в индейский город и погубил вверенные ему войсковые части и эскадру, но также посеял вражду и недоверие в твоём сердце в отношении меня. Смею тебя заверить, "+GetSexPhrase("сын мой","дочь моя")+" - я полностью и всецело на твоей стороне.";
			link.l1 = "Хотелось бы в это верить.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Не сомневайся, "+pchar.name+". Мною, как верным и преданным слугой Христа и представителем его церкви, движет лишь одно: остановить конец света, который несёт воплощение индейского демона. Я сразу подозревал, а теперь уверен окончательно: именно тебя Господь избрал Своим орудием в борьбе против зла!";
			link.l1 = "Но почему вы так решили, отец Винсенто? Я просто военный капитан...";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Ты сумел сделать то, что не смогли ни я со своими помощниками, ни барон Мендоса с доном Диего, ни кто-либо другой. Ты сумел найти проклятый остров и найти на нём артефакт Кукулькана. Разве нет?";
			link.l1 = "Да, я действительно завладел маской Кукулькана.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "И разве сможешь ты утверждать, что это произошло случайно? Сын мой, сам Всевышний вёл тебя по этому пути! Он укрепил твою руку в сражениях, направил твои ноги по верной дороге и оберегал в час опасности! Ты - его разящий меч, который спасёт христианский мир!";
			link.l1 = "Кхм... Отец Винсенто, но ведь миссия по сути уже выполнена. Маска у меня, а, значит, воплощение Кукулькана не сможет пройти в прошлое...";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "Ты заблуждаешься, "+GetSexPhrase("сын мой","дочь моя")+". Демон сможет пройти через врата независимо от того, есть у него эта маска, или нет. С этим артефактом ему будет проще осуществить свои чёрные дела в нашем минувшем времени. Единственное, что сможет его остановить - это уничтожение врат.";
			link.l1 = "Дон Алонсо сказал мне то же самое...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "И он был прав! Именем Господа нашего, Иисуса Христа, я призываю тебя на битву против зла, "+GetSexPhrase("сын мой","дочь моя")+"! Ты не можешь отказаться от возложенной на тебя великой задачи. Мы все теперь зависим от тебя, "+GetSexPhrase("сын мой","дочь моя")+".";
			link.l1 = "Ваше Преосвященство, мне, право, даже неловко...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Скромность всегда была твоим украшением, "+GetSexPhrase("сын мой","дочь моя")+". Выступи на эту битву ради своих близких, ради всех христиан... и ради самого себя, ибо если демон победит, ты погибнешь вместе со всеми.";
			link.l1 = "Пожалуй, вы меня убедили, отец Винсенто. Я колебался с принятием решения о походе в Тайясаль, но теперь у меня не осталось сомнений. Чем вы можете помочь мне?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Дорогу в Тайясаль знали два человека: Алонсо де Мальдонадо и Мигель Дичозо. Дон Алонсо мёртв. А вот Дичозо... Мне доложили, что его совсем недавно видели в поселении Шарптаун, что на Исла Тесоро. Возможно, он и сейчас там. Ты должен найти Дичозо и убедить выступить твоим проводником в Тайясаль\nЗолотом или силой, но ты должен заставить этого человека провести тебя в индейский город. Там ты найдёшь врата, через которые зло проникло в наш мир, и запечатаешь их при помощи маски навеки.";
			link.l1 = "А что насчёт боевой ударной группировки?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Эта группировка была под командованием Алонсо де Мальдонадо. Увы! У меня нет возможности собрать ещё один отряд испанских солдат. Тебе придётся сделать это при помощи своих людей, "+GetSexPhrase("сын мой","дочь моя")+". Но я всё же окажу тебе возможную помощь.";
			link.l1 = "Какую?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Через пять дней сюда, в эту часовню, прибудет отец Адриан. Он привезёт с собой освящённые обереги, которые помогают воинам Христа в бою. Кроме того, он обеспечит тебя в достаточном количестве лечебными и прочими эликсирами. А сейчас я преподношу тебе, "+GetSexPhrase("сын мой","дочь моя")+", вот этот клинок\nЭто меч рыцарей Храма, грозное оружие наших предков, овеянное славой. Чести носить его удостаивались только лучшие воины. Возьми, владей им с гордостью, и сокруши врагов нашей веры с именем Господа на устах!";
			link.l1 = "Спасибо! Меч просто изумителен, нет слов...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			//Log_Info("Вы получили рыцарский меч 'Танат'");
			PlaySound("interface\important_item.wav");
			dialog.text = "Благословляю тебя, "+GetFullName(pchar)+", на священный бой. Осеняю тебя святым крестом. И да хранит тебя Бог, и да не оставит он тебя ни в поисках, ни в пути, ни в бою. Аминь.";
			link.l1 = "Аминь!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "А теперь ступай, "+GetSexPhrase("сын мой","дочь моя")+". Отыщи Мигеля Дичозо, и с его помощью пробейся в город язычников. Не забудь про отца Адриана - он снабдит тебя оберегами и лекарствами. А мне пора в обратный путь, в Сантьяго. До свидания, "+GetSexPhrase("сын мой","дочь моя")+".";
			link.l1 = "До свидания, отец Винсенто...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}