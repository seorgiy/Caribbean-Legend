// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "¿Qué deseas, señor? Lo siento, solo estoy...'llora'... oh... Lo siento.";
					link.l1 = "¿Por qué estás tan molesta, mi señora? ¿Lágrimas en una cara tan hermosa? ¿Qué ha sucedido?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = "¡Señor! ¡Señor, ayuda! ¡Asesinato!";
				link.l1 = "¿Eh? ¿Asesinando a quién? ¿Dónde? ¿Es esto una broma, mi querido?";
				link.l1.go = "FMQP";
				break;
			}
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Te he pedido que subas. No te quedes aquí y atraigas atención.";
					link.l1 = "Bien, me voy, no quiero comprometerte...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Soy nuevo aquí, así que por favor, no me distraigas de mi trabajo. Todavía no me acostumbro...";
					link.l1 = "¿Y dónde está la camarera que trabajaba aquí antes que tú? "+pchar.questTemp.different.FackWaitress.Name+", como recuerdo...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Vuelve otra vez, cariño. Podríamos divertirnos de nuevo. Si tuviera más tiempo libre...";
					link.l1 = "¡Claro que lo haré, estuviste genial!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "No te conozco, así que no me molestes...";
					link.l1 = "¿Dónde está mi dinero?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Lo siento, "+GetSexPhrase("guapo","belleza")+", Estoy demasiado ocupado ahora. Es un buen momento para la taberna pero no para las charlas!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Por favor, capitán, ¡no pelee aquí! Es un trabajo duro limpiar este lugar.";
					link.l1 = ""+GetSexPhrase("Hm... Ni siquiera iba a hacerlo.","¿Parezco un borracho buscando pelea? Solo soy una chica, igual que tú, no te preocupes.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (drand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("¡Oh, capitán! ¿Te gustaría compartir una cama conmigo hoy? No me gusta jactarme pero...","Toma asiento, capitán. Siempre es un placer conocer a un verdadero lobo de mar como tú.")+"";
						link.l1 = "Qué lástima que tenga prisa ahora. ¡La próxima vez!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "¡Con mucho gusto, cariño!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Toma asiento, capitán. Prueba nuestro ron, juega una partida de cartas o dados. ¡Siéntete como en casa! Siempre es un placer conocer a un verdadero lobo de mar como tú.";
						link.l1 = "Gracias, bonita.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Habla con el maestro si quieres pedir algo. Está detrás del mostrador del bar.";
					link.l1 = "Gracias por el consejo.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Si quieres descansar y recuperar tu salud, alquila una habitación entonces. Pasar toda la noche en el salón no te ayudará mucho.";
					link.l1 = "Mi agradecimiento.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Quiero hacerte unas preguntas.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "Escucha entonces. Alquila una habitación aquí en la taberna. Ve allí y espérame. Me escabulliré allí un poco más tarde...";
			link.l1 = "¡Ja! ¡Lo haré, cariño! ¡Te estaré esperando!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = dRand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Ella ya no trabaja aquí, se ha retirado... Lo siento, tengo un trabajo que hacer.";
			link.l1 = "Bien...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Escucha bien, idiota lujurioso. ¡No sé dónde está tu dinero! Y si sigues presionándome, llamaré a los guardias y te encontrarás en prisión!";
			link.l1 = "Bien, no se necesitan guardias... Que tonto...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Exactamente, tal tonto. La próxima vez serás más inteligente y decente.";
			link.l1 = "Lo intentaré... (susurrando) Puta de mierda...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "¿Puedes oírme?";
			link.l1 = "Ughh...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "¿Te sientes mal? ¿Tienes dolor de cabeza?";
			link.l1 = "Maldición... ¿dónde estoy?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "¿No te acuerdas? Te han robado.";
			link.l1 = "¿Qué? Oh... Mi cabeza... ¿Quién se atrevería?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "¿Cómo debería saberlo? Entraron a la fuerza, amenazaron con matar, revisaron tus bolsillos y se fueron.";
			link.l2 = "Ya veo... Mierda... Me gustaría un poco de agua... Gracias.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "No, no es nada, señor... gracias por su amabilidad pero yo ... (llorando)";
			link.l1 = "¿Alguien te ha ofendido? Calma, bonita, cuéntame todo.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "No, no, señor, no es nada. Perdóname por mi falta de contención, es solo que... Es mi hermano, dicen que está muerto pero no lo creo. No sé qué creer pero siento con mi propio corazón que está en grandes apuros. Y no tengo a nadie más que a Angelo después de que nuestros padres pas... (llorando)";
			link.l1 = "Entiendo, pero te pido que te calmes, por favor. ¿Qué le pasó a tu hermano?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Señor... por favor no me malinterprete, pero ¿por qué debería importarle a un capitán tal una chica ordinaria y modesta de la taberna? Ni siquiera tengo nada que prometerle por su ayuda...";
			link.l1 = "De hecho, tienes razón. La abnegación no es para mí, así que sé fuerte, todos perdemos a nuestros parientes. C'est la vie como decimos en Francia...";
			link.l1.go = "exit";
			link.l2 = "Una mujer siempre puede encontrar una forma de agradecer a un hombre.... Ja-ja. Ahora, solo deja de llorar y cuéntame sobre tu problema.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Joven señorita, ¿no le han informado que nuestra Iglesia nos enseña a ayudarnos mutuamente? Intentaré ayudarte si puedo hacerlo, por supuesto.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = "¿Fue una 'pista'? ¡Disculpa, fue mi error hablar contigo! Adiós 'caballero'...";
				link.l1 = "Como desees, cariño.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Bueno entonces... Al menos eres honesto en tus deseos. Te prometo que si encuentras a Angelo o me dices lo que realmente le sucedió, obtendrás lo que pediste...";
				link.l1 = "Querida señorita, es un placer hacer negocios contigo... Ahora vayamos directo a la historia de tu hermano.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "¿Estás bromeando? ¿Realmente quieres ayudarme gratis?";
			link.l1 = "Solo un mal hombre no ayudaría a una niña llorando. No te preocupes, realmente quiero ayudarte. ¿Qué le pasó exactamente a Angelo?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Muy bien, señor. Mi hermano, él... oh, no es fácil contener las lágrimas para mí, lo siento mucho... Estábamos realmente pobres debido a mi... modestia en el trabajo quizás... Y Angelo comenzó a trabajar con los contrabandistas locales. Pensó que su pequeño bote de pesca ganaría más dinero transportando algo para evitar las aduanas.";
			link.l1 = "Para decirlo en palabras más simples, ¿tu hermano se convirtió en un criminal, verdad?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "No, señor, no entiendes ... ¡él no es así! ¡Lo hizo por mí! Para salvarme de ganar dinero extra aquí ... ya sabes a lo que me refiero. Estábamos endeudados y lo hizo por mi honor y mi alma. Y luego ... fue atrapado. No fue un gran problema, incluso pedí más dinero prestado para pagar su liberación ... Pero dijeron que murió.";
			link.l1 = "¿Ellos dijeron? ¿Quién dijo? ¿Y por qué no les crees? ¿Murió en una prisión?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Sí. Cuando llevé dinero para pagar su liberación, el comandante me dijo que Angelo murió de tuberculosis. ¡Imagínate! Llegó allí en buen estado de salud y murió dos semanas después justo en esas celdas. Ellos... ni siquiera me permitieron ver el cuerpo. Dijeron que enterraron a los prisioneros justo en la bahía cerca del fuerte para evitar una epidemia.";
			link.l1 = "¿Una epidemia? Suena muy cierto. Entonces, ¿simplemente no quieres creer en ello o tienes razones más serias?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "¡No... No! (llorando) Sé que suena estúpido, pero estoy seguro de que lo sabría si él muriera. Verás, Angelo siempre fue fuerte, un verdadero marinero. Pero hay una cosa más\nMi abuelo murió de consunción cuando era niño y él, un viejo, había estado luchándola durante años. Sé cómo funciona, la consunción no mata a la gente en días, ¡créeme!";
			link.l1 = "Hm... Tú también me has hecho dudar, algo está muy mal aquí. No puedo prometerte nada pero intentaré averiguar más.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "¡Incluso una promesa simple es mucho más de lo que esperaba! ¡Eres tan amable, señor! ¡Estaré esperando aquí!";
			link.l1 = "¡Oh, juventud! Tan inconstante en sentimientos... ¿Serías tan amable de devolverme mi mano, belleza, aún la necesito ja-ja... Muy bien entonces, iré a buscar por ahí.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "¡No, no bromas! ¡Arriba! ¡Dos matones están asesinando a un noble caballero! ¡Ayúdale, capitán, eres el único hombre armado aquí!";
			link.l1 = "¡Corre afuera, llama a los guardias! ¡Voy a subir!";
			link.l1.go = "FMQP_1";
			link.l2 = "Querido, debes haberme confundido con un guardia. Llama a una patrulla en caso de asesinato.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "¡A-ah, guardias! ¡Ayúdenme!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
