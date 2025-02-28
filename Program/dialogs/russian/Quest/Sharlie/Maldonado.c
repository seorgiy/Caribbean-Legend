// Алонсо де Мальдонадо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ты что-то хотел?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "Стой, капитан "+GetFullName(pchar)+"...";
			link.l1 = "Почему-то я даже не удивлён присутствию здесь испанцев... наверное, уже привык к тому, что за мной постоянно кто-то охотится. Чего тебе надо на этом проклятом острове, кастилец? Смерти ищешь?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Моё имя - Алонсо де Мальдонадо. Тебе оно ничего не говорит, но зато имя Диего де Монтойя ты должен знать хорошо. Он был моим лучшим другом. Он спас мне жизнь. И он пал от твоей руки.";
			link.l1 = "Как я понимаю, ты меня преследовал, чтобы отомстить?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "И не только. Маска Кукулькана у тебя, как я понимаю?";
			link.l1 = "О! Ещё один охотник за сокровищами! Решил довершить дело, начатое доном Диего?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "Меня не интересуют сокровища. Я видел их в Тайясале столько... Мигель Дичозо смог вывезти лишь ничтожную их часть. Мне нужна маска.";
			link.l1 = "Ты был в Тайясале? Слабо верится. Дичозо вернулся из похода на Тайясаль один, как я помню. ";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "Я был в Тайсале за двадцать лет до того, как туда пришёл Дичозо. Тогда же, когда этот сумасшедший колдун Канек при помощи ужасного ритуала с человеческим жертвоприношением спрятал маску на этом острове.";
			link.l1 = "Ушам не верю! Ты что, из того самого отряда конкистадоров, который был принесён в жертву при создании Стража Истины? Вы же все погибли!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "Не все. Я остался жив.";
			link.l1 = "И почему ица пощадили тебя? Чем же ты так отличился?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Тебе этого не понять. Как, впрочем, и мне. Меня никто на щадил. Я помню, словно это случилось вчера... После того, как дикарь вырезал дагой из спины Каскоса кусок кожи, затем умертвил его, а потом начал свои жуткие завывания, меня словно втянуло внутрь истукана. Я очнулся далеко за пределами Тайясаля, а ещё оказалось, что за одно мгновение прошло двадцать лет!";
			link.l1 = "Пространственно-временная воронка... Чёрт возьми, Ксатл Ча не солгал ни на йоту! Откуда ты узнал про маску? Для чего она тебе?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "Я должен остановить исчадие ада, вызванное сумасшедшим индейским колдуном. Это порождение зла, стремящееся уничтожить наш мир!";
			link.l1 = "Ясно... Ты разговаривал с отцом Винсенто, так? Инквизитор ведёт двойную игру, кто бы сомневался... Он послал тебя следить за мной и выйти на Ксочитэм? Браво! Ты отлично справился с заданием, дон Алонсо!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "Господь укрепит мою руку в борьбе против зла. Я вернусь в Тайясаль и при помощи маски навечно запечатаю врата, через которые демон в обличии человека намеревается пройти в наш мир.";
			link.l1 = "А вот тут у тебя ошибочка вышла, дон Алонсо. Демон УЖЕ среди нас. И нельзя позволить ему УЙТИ через эти врата. А для этого достаточно не дать ему завладеть маской.";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Этого недостаточно. Кто бы из нас ни был прав - верно одно: врата должны быть закрыты навечно, и сделать это можно одним лишь путём: уничтожить маску на алтаре в Тайясале. Тогда демон будет бессилен что-либо сделать.";
			link.l1 = "Хм. Я согласен, что это самый надёжный вариант... и как же ты намерен попасть в Тайясаль? Ты знаешь туда дорогу?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Лёгкого пути в Тайясаль, по которому мы проникли туда, уже двадцать лет как не существует - тропы завалены камнями и заросли джунглями. Но есть ещё один проход, долгий и опасный. Это тропа начинает свой бег из бухты на севере Юкатана\nПри помощи отца Винсенто и дона Рамона де Мендосы я соберу отряд отборных солдат, и мы пробьёмся сквозь сельву, охраняемую дикарями ица. Путь будет тяжёл, но Господь дарует нам силы и мужество, ибо мы пойдём на битву во имя нашей веры.";
			link.l1 = "Дон Алонсо, мои стремления вообще-то схожи с твоими. Не пора ли забыть вражду хотя бы на время и объединить наши силы? Вдвоём нам будет проще осуществить это предприятие.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Я испанский солдат, я не вступаю в союзы с еретиками и не заключаю сделок с французами. Кроме того, я объявил тебе вендетту за дона Диего. Жизнь за жизнь!";
			link.l1 = "По-моему, ты просто упрямый баран, дон Алонсо! Сам утверждаешь, что нашему миру угрожает вселенское зло, и сам же отказываешься от моей помощи в столь важном деле! Отец Винсенто не одобрил бы твоего решения!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "Сейчас решения принимаю я, а не отец Винсенто! Помолись напоследок и приготовься умереть, французский капитан!..";
			link.l1 = "Ох, сколько раз за последние месяцы я слышал эту фразу! К бою, тупоголовый кабальеро!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}