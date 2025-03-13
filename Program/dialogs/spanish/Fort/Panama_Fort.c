// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué piensas de nuestro fuerte? Se ve bien, ¿verdad? Y la guarnición no está peor todavía, ja...","La vida de un soldado de fortaleza es bastante aburrida... Vigilar y patrullar, dormir y descansar y luego lo mismo una y otra vez. Pero es diferente en la ciudad... ¿Qué quieres, "+GetAddress_Form(NPChar)+"¿?"),"Molestar a un soldado con preguntas estúpidas no es bienvenido, "+GetAddress_Form(NPChar)+"...","Es la tercera vez que intentas preguntarme hoy...","No es fácil ser un soldado y, sin embargo, aquí estás de nuevo"+GetSexPhrase(", imbécil,  "," ")+" intentando cabrearme. Ten cuidado o acabarás en el sótano del fuerte...","bloqueo",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión, perdón por molestarte.","No tengo nada que decir, disculpas."),"Tienes razón, me disculpo.","Tienes razón, ya es la tercera vez. Perdóname.","Lo siento, no es nada.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
