// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.", "I am listening to you, what's the question?"), "This is the second time you are trying to ask...", "This is the third time you are trying to ask...",
                          "When is this going to end?! I am a busy man, working on colony matters and you are still bothering me!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I changed my mind...", "Not now. Wrong place and time."), "True... But later, not now...",
                      "I'll ask... But a bit later...", "I am sorry, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" Monsieur. I am here as ordered by the Governor-General Chevalier de Poincy. My task is to deliver a baron by the name of Noel Forget to Tortuga, who arrived from the parent state with a task to inspect the colonies, his main purpose is establishing a French West-Indies trading Company. Let me introduce him to you... He will explain all the details himself.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "Your Lordship, you wanted to see me?";
				link.l1.go = "PZ1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("You have taken everything already. What else do you want?", "Is there anything left that you didn't grab?");
            link.l1 = RandPhraseSimple("Just looking around...", "Just checking, I might forget to take something...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "I am very glad to meet you, Captain Charles de Maure, and the Baron. I will do everything so that Monsieur Forget's stay in our colony is as comfortable as possible. And taking advantage of the fact that such a high-ranking Monsieur paid me a visit, I will petition you for one matter.";
			link.l1 = "Most interesting! Tell us about your matter, your Grace.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "In recent months, our colony hasn't been visited by any representative of the Governor-General, as if they completely forgot about us at Saint Kitts! And in the meantime, the Spaniards, craving to make the whole of Hispaniola purely Spanish and to whom the French settlers and buccaneers at the west of the island are a major annoyance, are preparing an attack! My patrol officers, our trading captains and even ordinary fishermen have reported that a powerful Spanish squadron is gathering in Santiago, and that it is preparing to attack Port-au-Prince!";
			link.l1 = "Is the evidence clear enough, your Majesty?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "I don't have accurate intel, but such plenty of information from completely random people can't be mere rumors. Our colony is very important for France, we have the best plantations here, which the Baron can personally see. To lose this colony or even expose it to the risk of being looted is unacceptable!";
			link.l1 = "I will take your evidence into account and inform Chevalier de Poincy. I'm sure that he will take immediate measures.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Thank you, captain...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "No, I did not summon you, monsieur. Did you want something?";
			link.l1 = "How could I? But your messenger met us; he said you had prepared one of the houses in the town for me...";
			link.l1.go = "PZ2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ2":
			dialog.text = "What house, what messenger, what is this insolence?!";
			link.l1 = "What do you mean, what messenger... His name is Henri Thibaut, and...";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "WHAT? Do you even know who he is? Apparently not. But it doesn't matter. What's Levasseur's nephew doing in my town?";
			link.l1 = "Oh, my God...";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "De Maure, can you hear me? Monsieur?";
			link.l1 = "...";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
