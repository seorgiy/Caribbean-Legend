// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Thank you, Captain! I can't even imagine what I would have done without you...";
			link.l1 = "I can imagine. You would have died of starvation or ended up in the stomach of a savage from Dominica. But you've got a chance to repay me.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "How can I help you, Captain?";
			link.l1 = "I want to know more about one man. He is our common friend, so to speak. A very close friend of yours actually. I mean captain Butcher. Yes, the one you hanged twenty years ago. Lord, why are you so pale? Do you want a sip of rum?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Have... have you been sent by him?";
			link.l1 = "Nonsense! How can I be 'sent by him' if he is dead! I am more interested in the things he has left rather than Butcher himself. Letters, documents, things like that. Perhaps you have found something in his pockets... Wait! I don't get it. Do you really think that Butcher is alive? You have executed him yourself!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Fuck! You haven't got a clue. That means you have not been sent by Butcher like I thought...";
			link.l1 = "Well, well. This is just getting more interesting. It seems that Henry had all the right reasons to be scared of Butcher and that's why he died from the heart attack... Is Butcher alive?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "He is, Captain... And they are looking for me.";
			link.l1 = "Raymond, they told me that you aren't a stupid man. Don't try to play games with me. You are safe of any threat here. Tell me everything you know and I will come up with something to help you. Perhaps we share common enemies. Let's start with Butcher.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "He is alive, but his name is different now! His men paid me a visit the night of the execution. Jackman and another man with some odd nickname. As far as I remember it was the 'Drowned man'.";
			link.l1 = "Hangman. Henry the Hangman.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Right! They offered me a simple deal - to die in the most painful way or save their captain. So I had to fake the execution with special equipment I had created in my free time. You see, such a construction of belts and clamps can allocate the body's weight.\nAll I had to do was to link it with a secret hook in the loop. The 'corpse' had to play its role well though. I have to say that Lawrence's acting was most believable, he did everything right, except he refused to piss himself, because of...";
			link.l1 = "Have you just called Butcher 'Lawrence'?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "That is his true name. I told you that he is called Lawrence Beltrope. I have been restless since he returned to the Caribbean a year ago. And when I found out that some bad people are looking for me...\nI have even written a confession for the authorities just in case. I am keeping it with me at all times as I am too afraid to give it away. They might think that I was a willing abettor. Please, let me stay with your crew. I swear, I am an excellent physician and can help you a lot.";
			link.l1 = "Fine. And what about Butcher's... eh, Beltrope's personal items? Is he related to Thomas Beltrope?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "No clue. Don't have anything special left from Beltrope himself. But I will give you everything I have, you are free to do whatever you want with it. All papers related to the subject are in my bag. I saved everything just in case and keep it close to myself.\nHere, take a look... this is the legend of captain Butcher, this is my confession... These are things that belonged to Joshua Leadbeater...";
			link.l1 = "Stop! Leadbeater? Who is that?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Oh! He was a very special man. He was the one who chased down Butcher himself. People remembered him as the 'masked man'. He was murdered shortly after Butcher's execution. Someone slit his throat with a shark's tooth! One cut and he was done. When he was still alive, he must have suffered a lot.\nIf you would've seen his face under the mask, it was nothing but meat! He had this journal page in his pocket when he died. It must have been from the writings of Jessica Rose. Creepy story! Read it, it will make things much more understandable.\nAnd this is the tooth itself. Can you see the letters? S.D.... Whatever that means. There are also some bloodstains left.";
			link.l1 = "Enough! I need to read everything carefully and think about it. And you will be my passenger or ship doctor until I deal with all of this. You can breathe freely, Raymond, you are safe on my ship.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Yes, captain?";
			Link.l1 = "Listen to my order!";
            Link.l1.go = "stay_follow";
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, give me a full ship report.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "I want you to purchase certain goods every time we are docked.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "It's nothing. Dismissed!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Come on, Captain, I am a physician, not a purser. Although, in the past, I used to work in a different capacity... nevermind. I really don't do accounting, sorry.";
			Link.l1 = "Fine, so be it. You are my physician - as we agreed upon after you joined my crew.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Captain, to be completely honest, I never gathered much experience with trade. Never bargained, never tracked price tags. Also... I'd rather keep staying on the ship if you don't mind. Some of those merchants might recognize me and before you know it - masked men come shortly.";
			link.l1 = "So, you will go on living in fear of your past... Right, breathe out, I will do it myself.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Orders?";
            Link.l1 = "Stand here!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Follow me and keep up!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Change the type of ammo for your firearm.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choosing the type of ammo:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "There is change of disposition!";
            Link.l1 = "Dismissed.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
