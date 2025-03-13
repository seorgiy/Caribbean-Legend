// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Quel genre de questions ?","Que veux-tu ?");
			link.l1 = RandPhraseSimple("J'ai changé d'avis.'","Je n'ai rien à dire maintenant.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "Je cherche Monsieur Jones. Le connaissez-vous?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "Il y a beaucoup de Jones ici. Le plus renommé que je connaisse est un aide de camp sous le colonel Fox, Benjamin Jones. Il accueille généralement les visiteurs au quartier général du régiment.";
				link.l1 = "A-t-il une soeur du nom de Molly?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Quel Jones cherchez-vous ? Je connais au moins deux douzaines d'entre eux...","Nous avons trop de Jones ici. Vous devez être plus précis.","Il y a beaucoup de Jones ici, ainsi que des Johnson ou des Jackson. Vous devez être plus précis, hein ?");
				link.l1 = "Il a une soeur adulte nommée Molly. On m’a dit qu’elle est d’une rare beauté ?";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Hm, j'ai bien peur de ne pas pouvoir vous aider avec ça.","Non, je ne le connais pas.","Phah ! Si la Molly Jones que je connais est une rare beauté, alors le Colonel Fox est un curé de paroisse."),LinkRandPhrase("Je connais quelques Molly Jones. L'une d'elles a un frère mais... ce n'est pas celle que vous cherchez. Seul un homme ayant vécu avec des singes la qualifierait de 'belle rare'.","Je suis désolé, mais tous les Jones que je connais n'ont pas de soeurs.","Je suis désolé, je ne peux pas vous aider. Demandez à quelqu'un d'autre."));
			link.l1 = "Je vois. Désolé pour le dérangement.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Oui, mais elle serait mieux en tant que son frère. Cette mastodonte ne se trouvera probablement pas de mari à cause de sa vilaine trogne.";
			link.l1 = "Merci bien.";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensez-vous que je travaille pour le service secret de "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Eh bien... non. Adieu alors.";
			link.l1.go = "exit";
			link.l2 = "Une autre question, alors ?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Est-ce que j'ai l'air d'un bureau d'enquete? Je ne sais pas, je ne sais rien.";

            link.l1 = "Tu es vraiment une tête de linotte ! Va-t'en.";
			link.l1.go = "exit";
			link.l2 = "Une autre question, alors ?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
