//================= Copyright Builders league united corporation ===============//
//
// Purpose:	 base weapon
// note: THIS IS A TEST NOT A REAL GUN !!!!!!!!!!!!!!!!!!
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "npcevent.h"
#include "basehlcombatweapon.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "gamerules.h"
#include "in_buttons.h"
#include "props.h"
#include "soundent.h"
#include "game.h"
#include "vstdlib/random.h"
#include "gamestats.h"
#include "beam_shared.h"
#include "IEffects.h" 

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


class CKauTooler : public CBaseHLCombatWeapon
{
	int tool = 0;
	DECLARE_DATADESC();
public:
	DECLARE_CLASS(CKauTooler, CBaseHLCombatWeapon);

	CKauTooler(void);

	DECLARE_SERVERCLASS();

	void	ItemPostFrame(void);

	//void	ChangeEntity(void); 
	void	Precache(void);

	void	Fire(void);
	void    firesecond(void);


	void    toolplus(void);

	void    toolminus(void);
};

IMPLEMENT_SERVERCLASS_ST(CKauTooler, DT_KauTooler)

END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_KauTooler, CKauTooler);
PRECACHE_WEAPON_REGISTER(weapon_KauTooler);

BEGIN_DATADESC(CKauTooler)



END_DATADESC()



CKauTooler::CKauTooler(void)
{

}

//-----------------------------------------------------
// Precache
//-----------------------------------------------------

void CKauTooler::Precache(void)
{
	BaseClass::Precache();
	//p recache models , sound , and other things
}

//-----------------------------------------------------
// Fire
// what are you reading this ?
//-----------------------------------------------------

void CKauTooler::Fire(void)
{


	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	Vector vecSrc;
	Vector vecMaster;
	Vector vecAiming;
	QAngle Angle;
	if (pOwner)
	{
		CBaseViewModel* pViewModel = pOwner->GetViewModel();
		pViewModel->GetAttachment(pViewModel->LookupAttachment("muzzle"), vecMaster, Angle);

		vecSrc = pOwner->Weapon_ShootPosition();
		vecAiming = pOwner->GetAutoaimVector(AUTOAIM_2DEGREES);
	}
	else
	{
		CBaseCombatCharacter* pOwner = GetOwner();

		vecSrc = pOwner->Weapon_ShootPosition();
		Vector vecReplacethis;
		vecAiming = vecReplacethis - vecSrc;
		VectorNormalize(vecAiming);

		vecMaster = vecSrc;
	}

	trace_t	tr;
	UTIL_TraceLine(vecSrc, vecSrc + vecAiming * MAX_TRACE_LENGTH, MASK_SHOT, pOwner, COLLISION_GROUP_NONE, &tr);

	CBeam* pBeam = CBeam::BeamCreate("sprites/lgtning.vmt", 2.0);
	pBeam->PointEntInit(vecMaster, this);
	pBeam->SetAbsStartPos(tr.endpos);
	pBeam->SetEndAttachment(1);
	pBeam->SetBrightness(255);
	pBeam->SetColor(0, 255, 0);
	pBeam->RelinkBeam();
	pBeam->LiveForTime(0.3);
	g_pEffects->Sparks(tr.endpos);
	WeaponSound(SPECIAL1);

}
void CKauTooler::firesecond(void) {

	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	Vector vecSrc;
	Vector vecMaster;
	Vector vecAiming;
	QAngle Angle;


	if (pOwner)
	{
		CBaseViewModel* pViewModel = pOwner->GetViewModel();
		pViewModel->GetAttachment(pViewModel->LookupAttachment("muzzle"), vecMaster, Angle);

		vecSrc = pOwner->Weapon_ShootPosition();
		vecAiming = pOwner->GetAutoaimVector(AUTOAIM_2DEGREES);
	}
	else
	{
		CBaseCombatCharacter* pOwner = GetOwner();

		vecSrc = pOwner->Weapon_ShootPosition();
		Vector vecReplacethis;
		vecAiming = vecReplacethis - vecSrc;
		VectorNormalize(vecAiming);

		vecMaster = vecSrc;
	}
	CPASAttenuationFilter filter(GetOwner());
	filter.MakeReliable();

	
	
	trace_t    tr;
	UTIL_TraceLine(vecSrc, vecSrc + vecAiming * MAX_TRACE_LENGTH, MASK_SHOT, pOwner, COLLISION_GROUP_NONE, &tr);

	if (tr.m_pEnt)
	{

		if (tr.DidHitWorld()) // if the end result is world
		{
			CBeam* pBeam = CBeam::BeamCreate("sprites/lgtning.vmt", 2.0);
			pBeam->PointEntInit(vecMaster, this);
			pBeam->SetAbsStartPos(tr.endpos);
			pBeam->SetEndAttachment(1);
			pBeam->SetBrightness(255);
			pBeam->SetColor(255, 0, 0);
			pBeam->RelinkBeam();
			pBeam->LiveForTime(0.3);

			g_pEffects->Sparks(tr.endpos);
			WeaponSound(SPECIAL1);
			//EmitSound(filter, GetOwner()->entindex(), "Weapon_AR1.NPC_Double");
		}

		else // if the end result is not the world  
		{
			CBeam* pBeam = CBeam::BeamCreate("sprites/lgtning.vmt", 2.0);
			pBeam->PointEntInit(vecMaster, this);
			pBeam->SetAbsStartPos(tr.endpos);
			pBeam->SetEndAttachment(1);
			pBeam->SetBrightness(255);
			pBeam->SetColor(255, 0, 0);
			pBeam->RelinkBeam();
			pBeam->LiveForTime(0.3);

			UTIL_RemoveImmediate(tr.m_pEnt);
			g_pEffects->Sparks(tr.endpos);
			Vector forward;
			AngleVectors(tr.m_pEnt->GetAbsAngles(), &forward);
			g_pEffects->MetalSparks(tr.endpos, forward);
			g_pEffects->Dust(tr.endpos, forward, 4, 10);
			g_pEffects->Ricochet(tr.endpos, forward);
			
			EmitSound(filter, GetOwner()->entindex(), "Weapon_AR1.NPC_Reload");
			UTIL_ScreenShake(GetAbsOrigin(), 3.0f, 100.0f, 1.0f, 128, SHAKE_START, false);
		}
		
	}
	// with this you can fire beam 
	
}



void CKauTooler::toolplus(void)
{
	UTIL_CenterPrintAll("delete\n");

	UTIL_ClientPrintAll(HUD_PRINTTALK, "Message text");
	UTIL_ClientPrintAll(HUD_PRINTCONSOLE, "Message text");


}
void CKauTooler::toolminus(void)
{
	UTIL_CenterPrintAll("Delete Mode\n");
	UTIL_ClientPrintAll(HUD_PRINTTALK, "delete");


}


//-----------------------------------------------------
// ADD NAME HERE
// remove a prop and draw a beam
//-----------------------------------------------------


//-----------------------------------------------------
// ItemPostFrame
//-----------------------------------------------------

void CKauTooler::ItemPostFrame(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());



	if ((pOwner->m_afButtonPressed & IN_ATTACK))
	{
		Fire();
	}
	if ((pOwner->m_afButtonPressed & IN_ATTACK2))
	{
		firesecond();
	}

	if ((pOwner->m_afButtonPressed & IN_RELOAD))
	{
		toolminus();
	}
	if ((pOwner->m_afButtonPressed & IN_USE))
	{
		toolplus();
	}

	BaseClass::ItemPostFrame();
}
