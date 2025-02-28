// Глэдис МакАртур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ах, капитан! Вы знаете, я всё рассказала Элен. Вы не представляете, какой камень упал с моей души!";
				link.l1 = "Вы всё правильно сделали, миссис МакАртур. Девушка должна знать правду, какой бы она ни была. А я прибыл к вам по делу касательно Элен.";
				link.l1.go = "Helena_hire";
			}
			else
			{
			dialog.text = "Здравствуйте, "+pchar.name+"! Очень рада вас видеть! Не желаете ли немного рому?";
			link.l1 = "Спасибо, миссис МакАртур, но меня ждут дела.";
			link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "Что вам угодно, сэр?";
			link.l1 = "Вы - Глэдис МакАртур?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "Именно так. А вот вас я что-то не припомню, молодой человек. Так что объясните, что вы от меня хотели?";
			link.l1 = "Меня заинтересовала история пропажи вашей дочери, миссис МакАртур. Почему вы решили, что она пропала? Я слышал, у Элен была опытная команда...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ах, я абсолютно уверена в этом! Вот послушайте: пять дней назад была годовщина смерти мужа. Элен очень любила отца и обязательно вернулась бы к этой дате домой. Она и отлучилась буквально на пару дней забрать груз красного дерева в бухте Четумаль у дружественных нам индейцев мискито\nИндейцы уважают и побаиваются нашего покровителя Яна Свенсона, и никогда не сделали бы ей дурного. Господин Свенсон уже навёл справки. Дерево загрузили в тот же день. С тех пор Элен и её людей никто не видел.";
			link.l1 = "Быть может, на неё напали пираты?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Что за вздорное предположение! Вы, наверное, знаете, что господин Свенсон - один из пяти пиратских баронов, и входит в Совет Берегового братства. Без его ведома ни один пират не посмеет тут озоровать. Разве что кто-то из новичков...";
			link.l1 = "А испанцы? Могла же она натолкнуться на испанский патруль?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "Я плохо разбираюсь в политике, но говорят, что местные золотые и серебряные рудники полностью выработаны, а других богатств, ради которых стоило бы в дикой сельве рисковать жизнями благородных идальго тут нет. Поэтому они тут редкие гости. К тому же индейцы настроены против них весьма враждебно\nСлучайная же встреча с испанским патрулём не могла закончиться трагически для Элен, так как ничем предосудительным с их точки зрения она не занималась. 'Радуга' наверняка шла под голландским флагом, и все бумаги у Элен были справлены заранее, включая торговую лицензию.";
			link.l1 = "Возможно, незадолго до её отплытия произошли какие-нибудь события, или случилось что-то странное, чему вы тогда не придали значения?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ах, ну что вы! Мы, слава Господу нашему, живём здесь размеренной жизнью. Разве что... пару недель назад Элен получила записку от очередного ухажёра с просьбой о свидании. Она у меня девушка видная, хотя и небогатая\nТак что женихов у неё хоть отбавляй. Вот только не люб ей никто и под венец она не торопится. Скольким парням голову успела заморочить. Вся в свою мать, такая же ветреница!";
			link.l1 = "Глядя на вас, миссис МакАртур, сложно вообразить, что вы когда-то были сердцеедкой...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "Что? А, не обращайте внимания, я сама не своя от горя. О чём это я? Ах, да, записка. Так вот записку эту написал Джимми Хиггинс. Он из людей Джекмана, живёт в Марун-Тауне неподалёку отсюда, но появляется здесь частенько. Джекман тоже пиратский барон, но господин Свенсон отчего-то его недолюбливает.";
			link.l1 = "И что же Элен?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Ох и смеялась же она. Ей за день до этого сделал предложение капитан английского корвета, так она даже ему отказала. А тут простой боцман с пиратского корыта... Нет уж, у дочки Шона МакАртура будет жених посолидней!";
			link.l1 = "А как звали того английского капитана?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Ох, да откуда ж мне знать! Настоящие джентльмены у нас редкие гости. Простите, к вам это не относится. Вы спросите у этого Хиггинса. Он должен помнить. Джимми тогда всё порывался устроить потасовку с тем капитаном из-за Элен. Его дружки еле оттащили. Но они оба покинули Блювельд за несколько дней до отплытия Элен.";
			link.l1 = "Что ж, спасибо за рассказ. Попробую поискать вашу пропажу. Если что-нибудь узнаю, обязательно сообщу вам или мистеру Свенсону. Надеюсь отыскать вашу дочь живой и здоровой.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Вы собираетесь отправиться на поиски? Да благословит вас Господь на правое дело, да направит Он вас по верному пути, да укрепит Он вашу руку! Я буду молиться за вас! Скажите ваше имя, благородный человек?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". Надеюсь вернуться вскоре с добрыми вестями, миссис МакАртур. До встречи!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Режим исследования: срок квеста увеличен в два раза");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Вы что-нибудь узнали о моей бедной дочке, "+pchar.name+"?";
			link.l1 = "Сожалею, миссис МакАртур, пока ничего нового, но отчаиваться рано. Я продолжаю поиски. Отсутствие плохих новостей  само по себе является хорошей новостью.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "Вы опоздали, капитан. Труп моей бедной девочки нашли на одном из пляжей Антигуа. Боже, как над ней издевались перед смертью! Не уберегла я свою красавицу...";
			link.l1 = "Примите мои соболезнования. Что теперь поделаешь...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ах, молодой человек, оставьте меня наедине с моим горем...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "Не знаю, чем отблагодарить вас, капитан, за спасение моей дочери. Она всё рассказала мне, и я восхищаюсь вашим мужеством и благородством. Вот, возьмите золотых дублонов. Это немного, но я предлагаю их от всего сердца. И не смейте отказываться!";
			link.l1 = "Хорошо, Глэдис, не буду. Но я спасал вашу дочь вовсе не из-за денег, и вы это знаете.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Оставьте эти деньги себе, Глэдис. Вам они нужнее.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Я очень рада, что смогла хоть как-то отплатить за ваш благородный поступок. Двери моего дома всегда открыты для вас, и мы с Элен будем рады видеть вас здесь в любое время дня и ночи.";
			link.l1 = "Спасибо, миссис МакАртур. Я буду навещать вас и Элен по возможности.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ах, ну что вы... Я просто хотела, чтобы ваш благородный поступок был хоть капельку вознаграждён. Знайте, что двери моего дома всегда открыты для вас, и мы с Элен будем рады видеть вас здесь в любое время дня и ночи.";
			link.l1 = "Спасибо, миссис МакАртур. Я буду навещать вас и Элен по возможности.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Капитан, вам всегда будут рады в нашем доме! Вы, наверное, к Элен? Боюсь, она слишком утомилась за последние дни и закрылась у себя в комнате. Не пугайтесь, иногда такое с ней бывает.";
				link.l1 = "Точно? С ней всё хорошо?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ах, месье де Мор! Всегда рада видеть у себя в доме спасителя моей дочери. Вы хотели видеть Элен? Она у себя в комнате, капитан. После гибели 'Радуги' и своего чудесного спасения, она почти не выходит на улицу. Я впервые вижу её в таком смятении...";
			link.l1 = "Благодарю вас, миссис МакАртур.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ах, месье де Мор! Всегда рада видеть у себя в доме спасителя моей дочери. Вы хотели видеть Элен?";
			link.l1 = "Нет. Я хочу задать вам несколько вопросов и очень рассчитываю на вашу откровенность. От неё в первую очередь зависит безопасность Элен. Вам знаком этот перстень?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Боже милостивый! Это перстень...  её отца!";
			link.l1 = "Мистера МакАртура?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "Нет. Элен наша приёмная дочь, хотя и ничего не знает об этом. Её родители погибли, и я решила выдать её за своего ребенка. Шон удочерил Элен, но про то, что она не моя дочь, не знал даже он.";
			link.l1 = "Так кто же настоящие родители девушки?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "Её отец известен мне как пират Бучер, капитан фрегата 'Нептун'. Я видела его всего раза два. А мать - красивая молодая женщина с рыжими волосами в мужской одежде. Больше ничего не могу сказать про неё, кроме того, что она была плохой матерью\nЯ бы ни за что не оставила такую малютку в чужих руках. Оба они трагически погибли. А обещанный гонец в вашем лице появился спустя целых двадцать лет. Вас прислал Бучер? Он жив?";
			link.l1 = "Успокойтесь, миссис Глэдис! Нет никаких оснований полагать, что Бучер воскрес из мёртвых, хотя вы - уже второй человек, кому это пришло в голову. Недавно я встретился с тем, кто должен был показать вам этот перстень...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "";
			link.l1 = "Чистая случайность помешала ему сделать это вовремя и всю жизнь он мучился из-за того, что не смог выполнить последний приказ своего капитана. Он умер на днях, и... впрочем, довольно о грустном. Скажите,  Глэдис, неужели мать Элен ничего не оставила ребенку на память о себе? Может быть, какую-то безделушку?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "Она оставила странный клочок старой карты. Пошутила, что это её наследство. Какая может быть польза от обрывка пергамента? Я полагаю, что это была неудачная шутка. Она была очень возбуждена и немного не в себе. Но я на всякий случай сохранила этот, с позволения сказать, 'подарок'\nМало ли что... Если хотите, я отдам его вам, если вы пообещаете мне когда-нибудь объяснить, что всё это значит.";
			link.l1 = "Непременно, миссис МакАртур. Я возьму этот обрывок карты на время. Мне нужно будет посоветоваться с мистером Свенсоном.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "Вы снова помогаете нам, месье де Мор! И я уже просто не знаю, как вас благодарить. Возьмите хотя бы этот пистолет мужа. Он очень гордился им и говорил, что это редкая вещь. Он всё равно пылится без дела - так пусть хоть найдёт достойное применение в ваших руках! Берите, берите!";
			link.l1 = "Спасибо, Глэдис. Пистолет действительно великолепный. Благодарю и разрешите откланяться.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Пусть этот пистоль ещё послужит Элен. У меня достаточно оружия.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "Ну почему же вы не хотите принять от меня ни одного подарка? Вы меня огорчаете...";
			link.l1 = "Думаю, что сейчас я вас обрадую: я хочу вернуть золото, которое вам должен был передать гонец на достойное содержание дочери капитана Бучера. Конечно, эти дублоны ни в коей мере не являются компенсацией за вашу любовь и преданность, но они ваши по праву. Распорядитесь ими по своему усмотрению.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ах, капитан! У меня нет слов... Я даже и представить себе не могу, что на свете ещё остались такие... благородные люди, как вы! Идите же скорее к моей девочке, она ждёт вас!";
			link.l1 = "Уже бегу, миссис МакАртур.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Вы серьёзно? О чём пойдёт речь?";
			link.l1 = "По просьбе мистера Свенсона я беру Элен к себе офицером на корабль. Девушке угрожает серьёзная опасность. Пока мы с Яном не решим эту проблему, Элен нужна надёжная защита. Надеюсь, я смогу её обеспечить.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ах, как славно! Я и не осмеливалась просить вас об этом. Лучшей защиты, чем ваша, моей девочке и не отыскать. А как Элен-то будет рада снова выйти в море!";
			link.l1 = "Спасибо за лестный отзыв, миссис МакАртур! А теперь мне пора к вашей... приёмной дочери.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "О, Боже! Моя доченька!";
			link.l1 = "Глэдис, стучаться надо!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "Ох, простите, молодые люди! Ухожу! Элен, помни, о чём я тебе говорила!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "Думаю, что в этот раз она просто слишком заработалась. Она мне всё рассказала, капитан! Спасибо вам, что вчера помогали доченьке корабль новый выбрать!";
			link.l1 = "А? Кхм, всегда пожалуйста. До свидания, миссис МакАртур.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}