// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Preguntas, "+GetAddress_Form(NPChar)+"¿?","¿Cómo puedo ayudarle, "+GetAddress_Form(NPChar)+"¿?"),"Entendido. Proporciona текст для перевода."+GetSexPhrase("Hum, ¿cuál es la gran idea, "+GetAddress_Form(NPChar)+"¿ ","¿Otra vez con las preguntas extrañas? Chiquillo, ve a tomar algo de ron o algo así...")+"Hola, amigo.","Durante todo este día, esta es la tercera vez que hablas de alguna pregunta..."+GetSexPhrase(" ¿Son estos algunos signos de atención?","Entendido. Начнем с первого перевода.")+"Entendido. Пожалуйста, предоставьте текст для перевода.","Más preguntas, supongo, "+GetAddress_Form(NPChar)+"¿?","bloqueo",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión","No tengo nada de qué hablar en este momento."),"No, no hermosa...","No querido...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
