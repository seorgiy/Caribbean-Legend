// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, да и вообще в Тортуге, я таких однообразно любознательных не видал.",
                          "Моё дело - корабли строить, давайте этим и займёмся.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "Я ищу Гая Марше. Последнее, что я слышал -  он поставил свой галеон 'Санта-Маргарита' к тебе в доки на ремонт...";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Свой галеон? Хо-хо, ну вы и сказали, право, капитан... Да у Гая Марше лишь только один шлюп был, да и тот, видавший виды... галеон этот он захватил в качестве приза, когда решил в каперы податься. И вот ведь везучий, зараза, взял такой корабль в первый же свой рейд\nЯ предложил ему за этот галеон неплохую цену, но он, представляете, отказался! Вместо этого он продал за полцены свой дырявый шлюп, а на полученные деньги починил и оснастил на свой вкус трофейный галеон!\nПоставил новые паруса, перекрасил корпус кое-где, название сменил... плохая это примета. Конечно, прежнее имя уж больно папистским было, но как по мне, нормальное. У меня дочку вот Маргаритой зовут... На мои вопросы, зачем всё это, ответил, что хватит с него каперства, будет заниматься торговлей. Только поймал удачу за хвост - и всё...";
			link.l1 = "Торговля, чай, поспокойнее будет, а папистские галеоны не каждый день на шлюпе захватывать удастся. И как теперь называется его новое судно?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "'Восхитительный'... Кстати, неудивительно, он вокруг своего галеона бегал как за невестой и всё им восхищался.";
			link.l1 = "Ясно. Гай сейчас на Тортуге?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Нет. Он ушёл в плавание на своём новом корабле и на Тортугу пока не возвращался. А вот куда он отправился, не ведаю. Он мне в этом вопросе не отчитался.";
			link.l1 = "Вот ведь незадача... а он мне так нужен. Да и выпили бы по кружечке за его 'восхитительный' корабль. Ладно, спасибо за информацию.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Да без проблем. Обращайтесь ещё, капитан. И не забывайте, что в моих доках всегда найдётся место для ремонта вашего корабля!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

