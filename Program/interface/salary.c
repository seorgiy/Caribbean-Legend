int nPaymentQ;
int nMoraleDecreaseQ;

void InitInterface(string iniName)
{
    // лочим квест и карту
    bQuestCheckProcessFreeze = true;
    if(IsEntity(&worldMap))
    {
    	wdmLockReload            = true;
    }
    
 	StartAboveForm(true);

	GameInterface.title = "titleSalary";

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);


	int tmpLangFileID = LanguageOpenFile("interface_strings.txt");
	SetFormatedText("INFO_TEXT1",LanguageConvertString(tmpLangFileID,"Salary info"));
	//SetFormatedText("INFO_TEXT2",LanguageConvertString(tmpLangFileID,"Officer info"));
	SetFormatedText("INFO_TEXT3",LanguageConvertString(tmpLangFileID,"All info"));
	LanguageCloseFile(tmpLangFileID);

    CalculateInfoData();
    
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0)
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	
	EI_CreateFrame("INFO_BORDERS", 250,152,550,342);
}

void ProcessBreakExit()
{
	SkipSailorPayment();
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	SkipSailorPayment();
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
 	EndAboveForm(true);
 	
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	PostEvent("StopQuestCheckProcessFreeze", 1000);//boal 230804 заморозка проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
	case "B_OK":
		if(comName=="activate" || comName=="click")
		{
			ExecuteSailorPayment();
   			IDoExit(RC_INTERFACE_SALARY_EXIT);
		}
	break;

	case "B_CANCEL":
		if(comName=="activate" || comName=="click")
		{
			SkipSailorPayment();
			IDoExit(RC_INTERFACE_SALARY_EXIT);
		}
		if(comName=="upstep")
		{
			if(GetSelectable("B_OK"))	{SetCurrentNode("B_OK");}
		}
	break;
	}
}

void ExecuteSailorPayment()
{
	AddMoneyToCharacter(GetMainCharacter(),-nPaymentQ);
	Statistic_AddValue(GetMainCharacter(), "PartitionPay", nPaymentQ);
	ChangeCharacterComplexReputation(pchar,"authority", 1);
	DeleteAttribute(GetMainCharacter(),"CrewPayment");
	if(nPaymentQ >= 3000) AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, makefloat(nPaymentQ) / 3000.0);
}

void SkipSailorPayment()
{
	ref mchref = GetMainCharacter();

	mchref.CrewPayment = nPaymentQ;

	int cn;
	ref chref;
	
	ChangeCharacterComplexReputation(mchref,"authority", -5);
	
	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mchref,i);
		if(cn >= 0)
		{
            chref = &Characters[cn];
			AddCrewMorale(chref, -nMoraleDecreaseQ);
			if (i > 0 && CheckAttribute(chref, "loyality") && !CheckAttribute(chref, "OfficerWantToGo.DontGo") && !IsEquipCharacterByArtefact(chref, "totem_04"))
			{
			    chref.loyality = makeint(chref.loyality) - 1;
			}
		}
	}
	int iPassenger;
    for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
            chref = &Characters[iPassenger];
			if (CheckAttribute(chref, "loyality") && !CheckAttribute(chref, "OfficerWantToGo.DontGo") && !IsEquipCharacterByArtefact(chref, "totem_04"))
			{
    			chref.loyality = makeint(chref.loyality) - 1;
			}
		}
	}

	if(AddCrewMorale(mchref, 0) <= I_MIN_MORALE)
    {
		if (IsEntity(&worldMap) && GetCrewQuantity(mchref) > 0 && !IsCharacterEquippedArtefact(mchref, "totem_02"))
    	{
            MunityOnShip("ShipMunity");
        }
		else
        {
            mchref.quest.Munity_on_Ship_Map.win_condition.l1 = "MapEnter";
            mchref.quest.Munity_on_Ship_Map.win_condition    = "Munity_on_Ship_Map";
        }
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	int i,cn;
	ref mchref,chref;

	mchref = GetMainCharacter();
	float nLeaderShip = GetSummonSkillFromNameToOld(mchref,SKILL_LEADERSHIP);
	nPaymentQ = 0;
	if( CheckAttribute(mchref,"CrewPayment") )
    {
		nPaymentQ += makeint(mchref.CrewPayment); // а тут помним все до копейки!
	}
	
	nMoraleDecreaseQ = 40-nLeaderShip;
	// belamour legendary edition перк получил время работы старый метод не подходит
	if(GetOfficersPerkUsing(mchref,"IronWill") )	nMoraleDecreaseQ /= 2; // у офицеров тоже нужно смотреть!!!

	//CreateString(true,"payment",""+nPaymentQ,FONT_NORMAL,COLOR_NORMAL,320,390,SCRIPT_ALIGN_CENTER,1.0);
    SetFormatedText("INFO_TEXT3",MakeMoneyShow(nPaymentQ, MONEY_SIGN,MONEY_DELIVER));
	if( sti(mchref.Money) < nPaymentQ )
	{
		SetSelectable("B_OK",false);
		SetCurrentNode("B_CANCEL");
	}
}