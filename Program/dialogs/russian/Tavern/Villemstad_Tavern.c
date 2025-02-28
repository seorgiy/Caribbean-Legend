// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали эту тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "Слышал"+ GetSexPhrase("","а") +", у вас на острове заваруха была серьёзная... Рабы, вроде, восстали.";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "Слышал, что гнусный негодяй Барт Португалец наконец-таки попался в руки правосудия! Он у вас в тюрьме? А когда состоится его казнь, не в курсе? Я бы пришёл посмотреть, у меня с этим мерзавцем свои счёты...";
                link.l1.go = "Portugal";
            }
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Да уж, такого никогда не бывало... Больше тысячи рабов участвовали в бунте. Две плантации сожгли дотла, а хозяев убили почти всех поголовно. Комендант опасался, что они на город пойдут - ввёл военное положение. А все началось с истории любви двух невольников - Таманго и Изауры...";
			link.l1 = "Интересно! Расскажи подробнее, кто это?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Таманго и Изаура - это рабы с плантации Бленхейм, ну, с той, которую сожгли первой. Любовь у них была. А потом приехал из Европы сын хозяина плантации, Леонсио, и положил глаз на Изауру. В общем, решил наложницей своей сделать. Это очень не понравилось Таманго, да и Изаура была не в восторге - любила она этого черномазого\nА надо сказать, что Таманго у себя в Африке был каким-то не то вождем, не то царьком... Здоров он, как бык, топором махать мастер, да и среди рабов авторитет. Вот и подбил их на восстание\nНочью напали на охрану и вырезали всех голландцев в Бленхейме. Изаура открыла им ворота усадьбы - они и там всех перебили. Потом пошли всей толпой на соседнюю плантацию, Бленбург, и устроили там такую же резню. Затем ушли в джунгли и исчезли без следа...";
			link.l1 = "Вот так история! Прямо сюжет для романа! И откуда ты всё это знаешь?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Слухи, "+ GetSexPhrase("минхер","госпожа") +", слухами земля полнится. Ром развязывает языки, достаточно просто слушать...";
			link.l1 = "И чем всё закончилось? Нашли этих черномазых?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "Какое там! Пока не подоспело подкрепление, никто и шагу в джунгли не делал. Потом прибыл военный корабль с отрядом солдат, обыскали они остров - никого нет.";
			link.l1 = "Ну ты подумай! Тысяча человек - и все как в воду канули!";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Именно, "+ GetSexPhrase("минхер","госпожа") +"! В воду они и канули!";
			link.l1 = "Ты это о чём сейчас, " + npchar.name + "? Не понимаю что-то...";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "Хе-хе... Бьюсь об заклад - уплыли они с острова. Дело в том, что на следующую ночь после восстания со стоянки кораблей пропал барк. Не пить мне рому до конца дней моих, если это не дело рук Таманго и его братии! Поэтому и нет их на острове.";
			link.l1 = "Ладно, спасибо за интересный рассказ, " + npchar.name + ". Хотя не представляю, как негры могут управляться с парусами.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Ну, видать могут... Может, кто из них раньше матросом ходил. Заглядывайте ко мне ещё, " + pchar.name + ", не забывайте, а я вам ещё историй приготовлю.";
			link.l1 = "Спасибо! Ну, мне пора.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Да, отловили этого пирата, всё верно. И вы можете себе представить как? Его подобрали на шлюпке, одного, посреди моря. Он даже пикнуть не успел, как отправился в трюм к крысам. Забавно, правда - такой опасный пират и так глупо попасться!";
			link.l1 = "И чего его в одиночку в море понесло?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Наверно, решил слинять от своих подельничков, не иначе... не поделили чего-то. А теперь им занялась сама Компания - а с этими ребятами шутки плохи. Говорят, он не так давно захватил судно Компании с чем-то ценным. Видимо, только потому, что из него хотят выудить некие сведения, он до сих пор не болтается на виселице.";
			link.l1 = "Так когда состоится его казнь, ты не знаешь?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Этого никто не знает. Думаю, как узнает Компания, что хочет, так и повяжут ему пеньковый галстук. Португалец сейчас в тюрьме под надёжной охраной. Недавно к нам привезли ещё и его боцмана - с тем так ещё удивительнее - он сам сдался голландцам в Филипсбурге. Ну, они его и пристроили по соседству с бывшим капитаном, хе-хе...";
			link.l1 = "Чудеса да и только! Ладно, буду следить за новостями. Не хочу пропустить это представление. Бывай, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

