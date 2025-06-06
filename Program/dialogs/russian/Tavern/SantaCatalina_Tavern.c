// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
		    if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Конечно, Элен. Что такое?", "А, наконец-то вспомнила, что хотела?", "Никогда не видел тебя такой забывчивой, ты меня пугаешь. Может, сходишь к врачу?",
							  "Так, Элен. Выспись, проветрись - в общем, отдохни. Потом и вернёшься. Хорошо?", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Да нет, ничего.", "Нет-нет, извини, что побеспокоила.",
						  "И правда, что-то до сих пор не могу вспомнить...", "Да, пожалуй, лучше всего будет сделать именно так.", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
							  "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
						  "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Послушай, "+npchar.name+", кто такой Ян Свенсон и как мне его найти?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Послушай, не появлялся ли у вас в городе ученый-алхимик, лекарь? Он итальянец, лет тридцати, зовут Джино Гвинейли. Не слыхал о таком?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "Первый раз вижу человека, который ничего не слышал о Лесном Дьяволе. Так прозвали его испанцы, а за голову этого капера с Провиденсии ещё лет пятнадцать тому назад давали целый мешок золота! Да, летят годы... Вот уже и про нашего Яна стали забывать. Может, и вправду пора ему на покой.";
			link.l1 = "Я здесь недавно и многого не знаю...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "Если вас интересует прошлое, могу продать вам одну рукопись. Многие отдали бы за неё целое состояние, но я...";
			link.l2 = "Ты мне зубы не заговаривай! Я, кажется, задал тебе вопрос и могу повторить. Где живёт Ян Свенсон? У меня к нему есть серьёзный разговор.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "Он живёт в особняке напротив резиденции нашего мэра, рядом с фонтаном. Вот только сейчас он пребывает в расстроенных чувствах и без особой нужды к нему лучше не соваться.";
			link.l1 = "Что так?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "Пропала его любимица Элен, по прозвищу Румба, дочь старого приятеля по лихим годам Шона МакАртура, упокой Господь его душу. Своих детей у него нет, так он привязался к этой чертовке, как к собственной дочери. И вот неделю назад наша Румба пропала вместе со своей шхуной 'Радугой' и командой\nЖаль девчонку. Редкая красавица и умница, каких мало. Не даром её прозвали Румбой, огонь, а не девка! Отец успел многому её научить, 'Радуга' досталась ей в наследство, так из команды никто не списался на берег, и даже старые морские волки признали её своим капитаном...";
			link.l1 = "Что могло с ними случиться?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Кто же знает... Неделя - срок небольшой, но вдова МакАртура Глэдис уверена, что с её дочерью случилось что-то скверное и смогла убедить в этом Свенсона. Тот поднял на ноги своих людей, но пока безрезультатно. 'Радуга' и все, кто были на ней, как в воду канули\nЗа тысячу песо скажу, где найти тетушку Глэдис.";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "Твоя осведомленность весьма разорительна, но ты меня заинтересовал. Вот твои деньги. Где её искать?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Не стоит. Сам разберусь, если потребуется. Бывай, спасибо за рассказ!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Её дом рядом с пристанью, налево от причала. Но там её скорее всего нет. Она целыми днями торчит на стенах форта, всё высматривает свою ненаглядную дочку. Небось уже все глаза выплакала.";
			link.l1 = "Спасибо за рассказ! Бывай, дружище!";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Нет, не слыхал. Есть у нас травники и лекари, но ни одного с таким именем.","Впервые такое чудное имя слышу. Нет, таких у нас отродясь не водилось.","Да у нас и вовсе никаких алхимиков нет. Лекари есть, но ни одного с таким чудным именем.");
			link.l1 = "Ясно. Жаль. Буду искать дальше!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}