#include "encounters\encounters.h"
#include "encounters\encounters_map.c"
#include "encounters\encounters_quest.c"

//#include "scripts\utils.c"

#define MAX_MAP_ENCOUNTERS		128
object MapEncounters[MAX_MAP_ENCOUNTERS];

extern void InitEncounters();

void Enc_ExcludeNation(ref rEnc, int iNation)
{
	string sNation = Nations[iNation].Name;
	rEnc.Nation.Exclude.(sNation) = true;
}

void Enc_AddShips(ref rEnc, string sEType, int iShipsMin, int iShipsMax)
{
	rEnc.(sEType).ShipsMin = iShipsMin;		
	rEnc.(sEType).ShipsMax = iShipsMax;
}

void Enc_AddClasses(ref rEnc, int iRank, int iMClassMin, int iMClassMax, int iWClassMin, int iWClassMax)
{
	string sRank = "Rank." + iRank;
	rEnc.(sRank).0 = iMClassMin; rEnc.(sRank).1 = iMClassMax;
	rEnc.(sRank).2 = iWClassMin; rEnc.(sRank).3 = iWClassMax;
}
void EncountersInit()
{
	if(LoadSegment("Encounters\Encounters_init.c"))
	{
		InitEncounters();
		UnloadSegment("Encounters\Encounters_init.c");
	}

	ReleaseMapEncounters();
}

int FindEncounter(int type, int nat)
{
	int iTypes[2]; 
	int i;
	SetArraySize(&iTypes, MAX_ENCOUNTER_TYPES * 10);
	for(i = 0; i < MAX_ENCOUNTER_TYPES*10; i++) iTypes[i] = -1;
	int iNumTypes = 0;

	ref rCharacter = GetMainCharacter();
	int iCharacterRank = sti(rCharacter.rank);
	
	int iChance = rand(250);
	
	for (i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		if(sti(EncountersTypes[i].Type) == type)
		{
			if(sti(EncountersTypes[i].Skip) || !Encounter_CanNation(i, nat)) { continue; }
			// check chance
			if (iChance > sti(EncountersTypes[i].Chance)) { continue; }
			// check MinRank / MaxRank
			if(sti(EncountersTypes[i].MinRank) > iCharacterRank || sti(EncountersTypes[i].MaxRank) < iCharacterRank) { continue; }
			
			iTypes[iNumTypes] = i;
			iNumTypes++;
		}
	}
	if(iNumTypes == 0) 
	{
		return -1;
	}
	int findnum = rand(iNumTypes-1);
	while(findnum >=0 && iTypes[findnum] == -1) findnum--;
	return iTypes[findnum];
}

int FindWarEncounter()
{
	int iTypes[100];
	int iNumTypes = 0;

	ref rCharacter = GetMainCharacter();
	int iCharacterRank = sti(rCharacter.rank);

	int iChance = rand(250);// boal 13.03.2004

	for (int i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		if (sti(EncountersTypes[i].Type) == ENCOUNTER_WAR)
		{
			if (sti(EncountersTypes[i].Skip)) { continue; }
			// check chance
			if (iChance > sti(EncountersTypes[i].Chance)) { continue; }
			// check MinRank / MaxRank
			if (sti(EncountersTypes[i].MinRank) <= iCharacterRank && sti(EncountersTypes[i].MaxRank) >= iCharacterRank)
			{
				iTypes[iNumTypes] = i;
				iNumTypes++;
			}
		}
	}
	if (iNumTypes == 0) 
	{
		//Trace("FindWarEncounter: not find any war encounters!");
		return -1;
	}
	return iTypes[rand(iNumTypes-1)];
}

int FindMerchantEncounter()
{
	int iTypes[100];
	int iNumTypes = 0;

	ref rCharacter = GetMainCharacter();
	int iCharacterRank = sti(rCharacter.rank);

	int iChance = rand(250);// boal 13.03.2004

	for (int i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		if (sti(EncountersTypes[i].Type) == ENCOUNTER_TRADE)
		{
            if (sti(EncountersTypes[i].Skip)) { continue; } // fix
			// check chance
			if (iChance > sti(EncountersTypes[i].Chance)) continue;
			// check MinRank / MaxRank
			if (sti(EncountersTypes[i].MinRank) <= iCharacterRank && sti(EncountersTypes[i].MaxRank) >= iCharacterRank)
			{
				iTypes[iNumTypes] = i;
				iNumTypes++;
			}
		}
	}
	if (iNumTypes == 0) 
	{
		//Trace("FindMerchantEncounter: not find any merchant!");
		return -1;
	}
	return iTypes[rand(iNumTypes - 1)];
}

int FindSpecialEncounter()
{
	int iTypes[100];
	int iNumTypes = 0;
	
	ref rCharacter = GetMainCharacter();
	int iCharacterRank = sti(rCharacter.rank);
	
	int iChance = rand(200);// boal 13.03.2004
	
	for (int i=0; i<MAX_ENCOUNTER_TYPES; i++)
	{
		if (sti(EncountersTypes[i].Type) == ENCOUNTER_SPECIAL)	
		{
            if (sti(EncountersTypes[i].Skip)) { continue; } // fix
			// check chance
			if (iChance > sti(EncountersTypes[i].Chance)) continue;
			// check MinRank / MaxRank
			if (sti(EncountersTypes[i].MinRank) <= iCharacterRank && sti(EncountersTypes[i].MaxRank) >= iCharacterRank)
			{
				iTypes[iNumTypes] = i;
				iNumTypes++;
			}		
		}
	}
	if (iNumTypes == 0) 
	{
		return -1;
	}
	return iTypes[rand(iNumTypes-1)];
}

bool Encounter_CanNation(int iEncounter, int iNation)
{
	string sNation = "Nation.Exclude." + Nations[iNation].Name;
	if (!CheckAttribute(&EncountersTypes[iEncounter], sNation)) return true;
	return !sti(EncountersTypes[iEncounter].(sNation));
}

bool Encounter_GetClassesFromRank(int iEncounter, int iRank, ref rMClassMin, ref rMClassMax, ref rWClassMin, ref rWClassMax)
{
	ref rEnc = &EncountersTypes[iEncounter];

	rMClassMin = 0; rMClassMax = 0; 
	rWClassMin = 0; rWClassMax = 0;

	string sRank = "Rank." + iRank;
	
	trace("sRank : " + sRank + " iEncounter : " + iEncounter);
	
	if (!CheckAttribute(rEnc, sRank))
	{
		// find nearest rank 
		if (CheckAttribute(rEnc, "Rank"))
		{
			int iLastRank = -1;
			int iBestRank = 1000;

			aref aRanks; makearef(aRanks, rEnc.Rank);
			int iNumRanks = GetAttributesNum(aRanks);
			for (int i=0; i<iNumRanks; i++)
			{
				aref aRank = GetAttributeN(aRanks, i);
				string sName = GetAttributeName(aRank);
				int iCurRank = sti(sName);
				if (abs(iRank - iCurRank) < iBestRank)
				{
					iBestRank = abs(iRank - iCurRank);
					iLastRank = iCurRank;
				}
			}
			if (iLastRank == -1) { return false; }
			sRank = "Rank." + iLastRank;
		}
		else
		{
			return false;
		}
	}

	rMClassMin = rEnc.(sRank).1;
	rMClassMax = rEnc.(sRank).0;

	rWClassMin = rEnc.(sRank).3;
	rWClassMax = rEnc.(sRank).2;
	
	trace("rMClassMin " + rMClassMin + " rMClassMax " + rMClassMax + " rWClassMin " + rWClassMin + " rWClassMax " + rWClassMax);
	
	return true;
}

//belamour найти подтип энкаунтера от айди
int FindRealEncounterTypeFromId(string _id)
{
    if(_id == "") return -1;
    aref rEnc;
    makearef(rEnc, worldMap.encounters.(_id).encdata);
    return sti(rEnc.RealEncounterType);
}