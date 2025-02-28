// Таннеке Эверс - просто девушка
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Здравствуйте! Кажется, мы с вами незнакомы? Я вас раньше не видела, это точно...";
				link.l1 = TimeGreeting()+". Всё верно - я недавно у вас тут... в гостях. Меня зовут "+GetFullName(pchar)+" и я капитан корабля.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Вы что-то хотели?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать тебе пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у вас дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Вы были капитаном?";
			link.l1 = "Почему - был? Я и сейчас капитан... а-а, я всё понял! Вы считаете, что мой корабль утонул или разбился у рифов. Нет. Он сейчас стоит у берегов Западного Мэйна. А сюда я добрался на баркасе, правда, закончилось всё неудачно - баркас получил пробоину и затонул.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Вы приплыли сюда на баркасе? И как же вам удалось пройти через шторм?";
			link.l1 = "Какой шторм? Не было никакого шторма...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Но как же? Ведь за пределами Острова постоянно бушует шторм. Все так говорят.";
			link.l1 = "Ну, значит, это не так, или мне повезло. Море было абсолютно спокойным... простите, а могу я узнать имя своей прекрасной собеседницы?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ой! Извините, я не представилась... Таннеке меня зовут.";
			link.l1 = "Очень приятно, Таннеке. Будем знакомы.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "А с какой же целью вы решили отправиться на наш Остров на баркасе? А-а, я понимаю - вас подхватило течением и принесло прямиком сюда. Ведь об Острове толком никто ничего не знает, и попадают сюда случайно...";
			link.l1 = "Не совсем так. Об Острове ходят достаточно точные слухи, включая и о его местоположении. Вот я и решил увидеть собственными глазами то, о чём другие только судачат...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Теперь понятно. Вы, как и Адольф Барбье, начитались записей капитана Альворадо и решили поискать золото адмирала де Бетанкура. Увы, я огорчу вас, капитан: даже такой ушлый пройдоха, как Барбье, не смог отыскать казну адмирала, так что навряд ли и вы отыщете\nДа и сдаётся мне, что всё это выдумки и никакого золота де Бетанкура не существует, а Антонио просто врёт об этом, чтобы показать, какой важной персоной был его дед... Ну, а теперь будете жить с нами. Попасть сюда легко, а вот выбраться - наверное, невозможно. Живым, я имею в виду.";
			link.l1 = "Ничего. Думаю, я сумею решить эту проблему. Не с золотом пресловутого Бетанкура - я о нём впервые слышу - а с тем, как покинуть Остров. Живым. Рад был поболтать, Таннеке. Ещё увидимся!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Задавайте, капитан...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "А как вы попали сюда?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Вы не пытались выбраться с Острова?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Как вам живётся тут, на Острове?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "А девушкам тоже приходится покупать еду у адмирала, или им выдают бесплатно?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Я голландка, но жили мы в Сантьяго. Мои родители устроили меня работать прислугой в семью банкира, Джеральди, слышали про таких? Три года назад один из членов этой семейки отправился на курьерском люггере по делам в Новую Испанию. Мне было сказано ехать с ним. На второй день пути нас догнала бригантина под испанским флагом\nОфицер с бригантины прибыл на наше судно и о чём-то беседовал с капитаном, в результате чего тот пришёл в ярость и выставил офицера прочь. Едва гость поднялся на свой корабль, как нас тут же атаковали. Наш капитан попытался скрыться, но это ему не удалось: бригантина взяла нас на абордаж. Как я поняла, им был нужен Джеральди, мой хозяин, потому что они ворвались в каюту, схватили его и увели, а меня вместе с матросами загнали в трюм\nЯ думала, что нападавшие затопят судно и нам придёт конец, но они просто развернулись и ушли. Матросы сумели выбраться из трюма, но капитан погиб в бою, а никто из матросов не умел вычислять курс. Мы просто поплыли наугад, потом нас подхватил внезапно налетевший шторм и понёс неведомо куда\nЧерез несколько часов наш люггер буквально врезался во внешнее кольцо. Где-то там он и стоит по сей день. Мне повезло выжить в этой кутерьме, а когда рассвело, я и несколько 'счастливчиков' добрались до Острова.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Нет. А как вы себе это представляете? Кораблей, годных для выхода в море, тут нет, а отправиться в путь на лодке - значит, подписать себе смертный приговор. Как я уже говорила - там часто бушуют шторма. На моей памяти была одна попытка - пятеро жителей построили приличную лодку, с парусом и вёслами\nОни несколько часов боролись с течением, затем всё-таки вышли в море и скрылись за горизонтом. А через пару дней один из этой пятерки вернулся на внешнее кольцо... Привязанный к отломанной мачте, мёртвый. Это надолго отбило у всех желание повторять подобные геройства.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "А нормально. Уж точно не хуже, чем в качестве прислуги у этой заносчивой семейки ростовщиков. Просто надо привыкнуть, а потом даже начинаешь любить это место. И, кстати, я не одна такая. А кланы... мне они не мешают.";
			link.l1 = "Интересно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Конечно, покупаем. Ой, капитан, работы тут для девушки достаточно: прибрать, приготовить, помочь другим... в общем, без дела не сидим, но никто не перерабатывается, а пираты обычным жителям провиант продают дёшево, в отличие от кланов. Так что проблем с пропитанием у нас нет\nЯ помогаю Джиллиан и Натали, они, если надо - мне. Дружим. Есть на острове ещё одна девушка, испанка, Рамона её зовут - но она особняком держится, да и мы не горим желанием с ней близко общаться.";
			link.l1 = "А чего так?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Ну, скажем... у нас разные взгляды на жизнь. Пообщаетесь с ней - поймёте.";
			link.l1 = "Занятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдёт!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдёт!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьёзному мужчине...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Осторожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял.", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}