// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, "+GetSexPhrase("joven caballero","jovencita")+"¿?","¿Qué necesitas, "+GetSexPhrase("guapo","bonita")+"¿Pregunta lo que quieras?"),"¿Preguntas otra vez?","Tee-hee, si te parece bien - preguntas...",""+GetSexPhrase("Mm, ¿por qué no eliges una belleza para ti? Estoy empezando a sospechar de ti...","Mm, ¿por qué no eliges una belleza para ti? No tenemos chicos aquí, me temo, je-je...")+"Entendido. Por favor, предоставьте текст для перевода.","bloque",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión, discúlpame.","De hecho, olvídalo..."),"Yo... disculpas, no tengo preguntas, por ahora.","Tienes razón, es la tercera vez ya. Perdóname.","Tal vez la próxima vez, señora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
