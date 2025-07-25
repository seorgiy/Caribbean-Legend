//Jason общий диалог мещан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity, sTitle;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Ходит слух, что вы и есть владел"+ GetSexPhrase("ец","ица") +" этого города, "+ GetSexPhrase("сэр","мисс") +".", "Какая приятная встреча, сам"+ GetSexPhrase("","а") +" глава города обратил"+ GetSexPhrase("ся","ась") +" ко мне с вопросом.");
					link.l1 = RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +". Удачи!", "Просто осматриваю город. До свидания.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Хочу обсудить финансовые дела.", "Касательно финансов...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("Тревога! Здесь больной псих с оружием!", "К оружию, к оружию! Здесь больной псих!");
						link.l1 = RandPhraseSimple("А? Что?", "Э, ты чего это?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("Чего тебе? Проходи мимо.", "Хватит загораживать дорогу, отвали.");
						link.l1 = RandPhraseSimple("Знаешь, что? Не гавкай!", "Поумерь свой пыл. Не то быстро охлажу его!");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("Хочу спросить тебя.", "Минутку внимания, всего один вопрос.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("Хочу обсудить финансовые дела.", "Касательно финансов...");
								link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "Приветствую, "+GetAddress_Form(NPChar)+". Вижу, вы капитан собственного корабля. Я хотел бы попросить вас об одной услуге...";
					link.l1 = "Слушаю вас, "+GetAddress_FormToNPC(NPChar)+". О чём пойдёт речь?";
					link.l1.go = "passenger";
					link.l2 = "Простите, "+GetAddress_FormToNPC(NPChar)+", но я очень спешу.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
				LinkRandPhrase("Меня зовут ", "Моё имя ", "Можешь называть меня ")
				+GetFullName(npchar)
				+LinkRandPhrase(". Чего тебе нужно?", ". Я тебя раньше здесь не "
				+NPCharSexPhrase(NPChar, "видел", "видела")
				+", кто ты так"+ GetSexPhrase("ой","ая") +"?", ". Кто ты и что тебе от меня надо?"),

				LinkRandPhrase("Приветствую вас, " + GetAddress_Form(NPChar) + ". Моё имя " + GetFullName(npchar) + ". А как зовут вас?",
				 "Здравствуйте, " + GetAddress_Form(NPChar) + "! Я " + GetFullName(npchar) + ". Могу я узнать ваше имя?",
				 "Да, " + GetAddress_Form(NPChar) + ". Что вы хотели? Кстати, меня зовут " + GetFullName(npchar) + ". А вас?"));

				Link.l1 = pcharrepphrase(
				LinkRandPhrase("Разрази меня гром! ", "Тысяча чертей! ", "Чтоб тебе пусто было! ") + "Да я капитан "+ GetFullName(Pchar)+ LinkRandPhrase(", ты разве не слыхал"+NPCharSexPhrase(NPChar,"","а")+" обо мне"+NPCharSexPhrase(NPChar,", каналья?","?"), " и "+ GetSexPhrase("самый известный пират","самая известная женщина-пират") +" в этих водах! ", " и провалиться мне на этом месте, если это не так!"),
				LinkRandPhrase("Я " + GetFullName(Pchar) + ", капитан.", "Меня зовут " + GetFullName(Pchar) + ".", "Можешь называть меня капитан "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Весь город на ушах - прибыл дон Фернандо де Аламида, королевский ревизор. Знаете, я тут многое повидал, но такого... Людей меняет не горе, а то, как они с ним справляются. Говорят, после гибели отца он стал другим человеком. Теперь во всём Архипелаге не сыскать более неподкупного и... безжалостного служаки.", "Вы только гляньте на 'Святое Милосердие'! Говорят, сам король приказал построить его по особым чертежам. И заметьте - ни единой царапины. Словно сама Дева Мария хранит его. Хотя слухи слышал такие... может, и не Дева вовсе.", "Знаете, сколько раз пытались убить дона Фернандо? Двенадцать атак в открытом море - и это только за последний год! Ну, с таким верным и обученным экипажем, да ещё и под защитой Господа - переживёт и тринадцатую!"), LinkRandPhrase("Слышали? Дон Фернандо де Аламида прибыл в наш город, и, говорят, сейчас где-то на улицах. Увидеть бы его своими глазами...", "Сложный человек этот дон Фернандо. Одни говорят - спаситель, чистит Отечество от скверны. Другие шепчутся - мол, после смерти отца что-то надломилось в нём и скоро наплачемся. А я скажу так: бойтесь не его. Бойтесь тех, кто его таким сделал.", "Такой видный мужчина, этот дон Фернандо! Но знаете что странно? Он словно и не замечает никого. Всё служба да служба. Я слышал, была одна девушка... но после встречи с каким-то священником он полностью отверг мирские радости. Словно дал обет."), RandPhraseSimple(RandPhraseSimple("Чёртов ревизор! Пока он здесь - город словно мёртвый. Ни торговли, ни веселья. Даже дышать, кажется, нужно тише. А знаете, что самое жуткое? В каждом порту одно и то же. Как по писаному. Ну не мог Его Королевское Величество специально придумать эту пытку для всех нас!", "Дон Фернандо опять посетил приют. Щедро жертвует, молится часами. Такого достойного человека нужно ставить в пример этим проклятым казнокрадам!"), RandPhraseSimple("Ха! 'Святой' Фернандо опять закрыл все бордели. Ну, ничего, скоро он отчалит и сразу откроют обратно.", "Рези... ревизор приплыл, вот что! Дон Фернандо де Альмейда, или, как его, Аламида! Такой важный, что сам губернатор перед ним на цыпочках ходит. Говорят, он в глаза смотрит и сразу видит все грехи. Жуть!")));
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== Леди Бет в порту города
			}
			else
			{
				link.l1 = PCharRepPhrase("Хотел"+ GetSexPhrase("","а") +" кое-что узнать об этом городишке!", "Хотел"+ GetSexPhrase("","а") +" узнать кое-что о городе.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("Хочу обсудить финансовые дела.", "Касательно финансов...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Послушайте, может вы мне подскажете. Я хочу купить "+pchar.GenQuest.Device.Shipyarder.Type+", и мне сказали, что эта вещь у вас в городе продавалась. Ну, кто-то продавал на улицах. Ничего об этом сказать не можете?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Ты в курсе", "Ты знаешь", "Ты знаешь что-нибудь о том") + ", что недавно была ограблена местная церковь?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("А, это ты "+GetFullName(Pchar)
                        +" "+ GetSexPhrase("- старый пройдоха","- отчаянная деваха") +"", "Рад тебя видеть, "+ GetSexPhrase("старина","красавица") +" "
                        + Pchar.name, "О, да это же "+ GetSexPhrase("сам капитан","сама") +" "
                         +GetFullName(Pchar))
						+LinkRandPhrase(". Думал, тебя уже нет на этом свете!", ". И, наверное, "+ GetSexPhrase("как всегда пьян.","уже слегка навеселе.") +"", ". И, как вижу, ещё на свободе!")
						+LinkRandPhrase(" Ну, говори, чего тебе нужно?", " Чего тебе на этот раз?", " Опять тревожишь меня по пустякам?"),
						LinkRandPhrase(TimeGreeting() + ", капитан ", "Здравствуйте, "+GetAddress_Form(NPChar)+" ", "Приветствую вас, капитан ")+GetFullName(Pchar)
						+LinkRandPhrase(". Что может быть нужно "+ GetSexPhrase("такому почтенному человеку","такой бравой девушке") +", как вы, от меня?", ". Зачем вы пришли?", ". Что на этот раз вы хотите узнать?")),
                                        
                        PCharRepPhrase(LinkRandPhrase("Здравствуйте, капитан ", "Приветствую, ах это вы "+GetAddress_Form(NPChar)+" ", "А, капитан ")
						+GetFullName(Pchar)
						+LinkRandPhrase(", я думал"+NPCharSexPhrase(NPChar, " ", "а ")+"мы больше с вами не встретимся,",
										 ", не скажу, что рад"+NPCharSexPhrase(NPChar, " ", "а ")+"вас видеть, но", ", вижу, вы ещё живы, прискорбно, а")
						+LinkRandPhrase(" что вам нужно?", " зачем вы пришли?", " чем могу быть "+NPCharSexPhrase(NPChar, "полезен?", "полезна?")),
						LinkRandPhrase(TimeGreeting() + ", капитан " + GetFullName(Pchar) + ". Чем могу помочь?",
						"О, да это же сам"+ GetSexPhrase("","а") +" капитан " + GetFullName(Pchar) + "! Что вы хотите узнать на этот раз?",
						"Здравствуйте, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + ". Вы что-то хотели?"))
						);                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто ш"+ GetSexPhrase("ёл","ла") +" в таверну."),
						RandPhraseSimple("Ладно, ничего. Удачи!", "Просто осматриваю город. До свидания."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Какие вопросы?";
			link.l1 = "Вам ничего не говорит имя в этих бумагах?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Мне нет дела до незнакомых бумаг, да и читать я не умею. Ступайте к ростовщику, он, говорят, и дьявольской грамоте обучен.",
			"Понятия не имею о чём вы говорите, поспрашивайте ещё жителей этого города, капитан " + GetFullName(Pchar) + ".", 
			"Даже не знаю как вам помочь, капитан " + GetFullName(Pchar) + ". Попробуйте обратиться к ростовщику, может он знает?");
			link.l1 = "С удовольствием воспользуюсь Вашим советом!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("А ты не врёшь, капитан " + GetFullName(Pchar)+"?",
				"И что с того " + PChar.name+"?",
				"Я запомню тебя, " + GetFullName(Pchar)+".")
				 + " А теперь говори, чего тебе надо?",
				LinkRandPhrase("Приятно познакомиться, капитан " + PChar.name,
				"Рад"+NPCharSexPhrase(NPChar, " ", "а ")+" нашему знакомству, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
				 "Очень приятно, капитан " + PChar.name) + ". Но вряд ли вы просто хотели узнать моё имя, не так ли?");
            link.l1 = PCharRepPhrase("Хотел"+ GetSexPhrase("","а") +" кое-что узнать об этом городишке!", "Хотел"+ GetSexPhrase("","а") +" узнать кое-что о городе.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("Хочу обсудить финансовые дела.", "Касательно финансов...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Послушайте, может вы мне подскажете. Я хочу купить "+pchar.GenQuest.Device.Shipyarder.Type+", и мне сказали, что у вас в городе она продавалась. Ну, кто-то продавал на улицах. Ничего об этом сказать не можете?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Ты в курсе", "Тебе что-нибудь известно о том", "Ты знаешь что-нибудь о том") + ", что недавно была ограблена местная церковь?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто ш"+ GetSexPhrase("ёл","ла") +" в таверну."),
                                        RandPhraseSimple("Ладно, ничего. Удачи!", "Просто осматриваю город. До свидания."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
				PCharRepPhrase(LinkRandPhrase("О, да я рад"+NPCharSexPhrase(NPChar, " ", "а ")+" тебе, как выпивке, спрашивай, чего хочешь.", "Любишь поболтать, капитан? Что ж, я тоже... Особенно за кружечкой рома.", "Да, " + PChar.name + "?"),
				LinkRandPhrase("Ну, чего тебе ещё?", "Вижу, капитан "+PChar.name+", ты охотни"+ GetSexPhrase("к","ца") +" поболтать? ", "Замучил"+ GetSexPhrase("","а") +" вопросами, капитан, лучше бы угостил"+ GetSexPhrase("","а") +" ромом.")),
		        PCharRepPhrase(LinkRandPhrase("Что вы хотели узнать "+ GetAddress_Form(NPChar) + "?", "Я вас слушаю капитан.", "Мне нужно идти, поэтому спрашивайте скорее, капитан."),
                LinkRandPhrase("Всегда рад"+NPCharSexPhrase(NPChar, " ", "а ")+" приятному собеседнику, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Говорите.",
                "Да, " + GetAddress_Form(NPChar) + "?",
                "Любите поболтать, капитан? Что ж, я тоже...")));
			link.l1 = LinkRandPhrase ("Какие байки в ходу в здешней таверне?","Что новенького в этих краях?","Как течёт жизнь на суше?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("Не объясните мне дорогу?", "Что-то я никак не найду дороги кое-куда...", "Подскажите дорогу...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Хочу узнать, что тут говорят об одном человеке.", "Не знаете, что говорят тут об одной персоне?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Хотелось бы узнать кое-что о местных жителях.", "Не расскажете немного о местных жителях?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто ш"+ GetSexPhrase("ёл","ла") +" в таверну."),
            RandPhraseSimple("Ладно, ничего. Удачи!", "Просто осматриваю город. До свидания."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "О ком из жителей вы хотите узнать?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "О губернаторе.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "О местном хозяине таверны.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "О хозяине верфи.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "О местном хозяине магазина.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Ни о ком. Забудь.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Гм, "+pchar.GenQuest.Device.Shipyarder.Type+"? Впервые слышу... Хоть что это за вещь такая - сколько живу на свете, ничего подобного в глаза не видел"+ NPCharSexPhrase(npchar, "","а") +".";
			link.l1 = "Ну, это судостроительный инструмент, "+pchar.GenQuest.Device.Shipyarder.Describe+". Кто-нибудь такое продавал в городе, или, может, носил с собой и вы заметили?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Хм... Да, видел я человека с похожей вещью, ходил он по улицам несколько часов назад. Интересная штуковина.";
				link.l1 = "А как выглядел этот человек и куда пошёл? Мне очень нужен этот инструмент.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Нет, ничего такого не видел"+ NPCharSexPhrase(npchar, "","а") +". Поспрашивайте ещё у кого.";
				link.l1 = "Ясно. Пойду спрашивать!";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Нет, я ничего об этом не знаю.", "Мне ничего не известно по этому вопросу.", "Я ничего не знаю.");
					link.l1 = LinkRandPhrase("Ладно, хорошо.", "Ясно, спасибо.", "Хорошо, извини.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Я ничего об этом не знаю, но вы можете расспросить завсегдатаев в таверне - они уж точно что-нибудь вам расскажут.", "Я вам ничего сказать не могу, спросите лучше кого-нибудь в таверне.", "Мне ничего конкретного не известно, но я слышал, что об этом трепались в таверне.");
				link.l1 = "Спасибо и на том.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "Капитан, мне нужно добраться до колонии " + XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", это на "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", за "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Ваше судно выглядит быстрым и надёжным. Я готов заплатить за это путешествие "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+". Что скажете?"; // belamour gen
			}
			else
			{
				dialog.text = "Капитан, мне нужно добраться до колонии " + XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", это на "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", за "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Я понимаю, что это звучит крайне рискованно, но, быть может, " + FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)) + " станут для вас хорошим подспорьем?";
			}
			link.l1 = "Пожалуй, я соглас"+GetSexPhrase("ен","на")+". Лишние деньги не помешают.";
			link.l1.go = "passenger_1";
			link.l2 = "Сожалею, "+GetAddress_FormToNPC(NPChar)+", но мне совсем в другую сторону. Ничем не могу помочь.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Жаль. Ну что же, подожду другого корабля. Прощайте!";
			link.l1 = "Всего доброго.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Я очень рад, что вы согласились. Расчёт произведём по прибытии на место, вы не против?";
			link.l1 = "Нет, не против. Отправляйтесь на моё судно, "+GetAddress_FormToNPC(NPChar)+". Мы скоро отчаливаем.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "горожанина");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", что на " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Вы выполнили свою часть сделки, теперь я выполню свою. Вот ваши деньги, капитан, и спасибо за приятное путешествие!";
			link.l1 = "Да не за что, "+GetAddress_FormToNPC(NPChar)+"! Всего доброго.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Осторожней на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;

	}
}