// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Preguntas, "+GetAddress_Form(NPChar)+"¿?","¿Cómo puedo ayudarte, "+GetAddress_Form(NPChar)+"?"),"Hola, Amigo."+GetSexPhrase("Eh, ¿cuál es la gran idea, "+GetAddress_Form(NPChar)+"¿? ","¿Otra vez con las preguntas extrañas? Cariño, ve a tomar un poco de ron o algo así...")+"Entendido, предоставьте текст для перевода.","Durante todo este día, es la tercera vez que hablas de alguna pregunta..."+GetSexPhrase(" ¿Son estos algunos signos de atención?","Entendido. Proporcionьте текст, который нужно перевести, и я переведу его для вас.")+"Hola, amigo.","Más preguntas, supongo, "+GetAddress_Form(NPChar)+"¿?","bloqueo",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión","No tengo nada de qué hablar en este momento."),"No, no hermosa...","No, querida...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
