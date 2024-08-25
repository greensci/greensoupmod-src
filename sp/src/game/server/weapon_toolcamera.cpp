//================= Copyright Builders league united corporation ===============//
//
// Purpose:	 camera gun
// note: THIS IS A CAMERA NOT A REAL GUN !!!!!!!!!!!!!!!!!!
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


class CToolCamera : public CBaseHLCombatWeapon
{
	int tool = 0;
	DECLARE_DATADESC();
public:
	DECLARE_CLASS(CToolCamera, CBaseHLCombatWeapon);

	CToolCamera(void);

	DECLARE_SERVERCLASS();

	void	ItemPostFrame(void);

	//void	ChangeEntity(void); 
	void	Precache(void);

	void	ShowHUD(void);
	void    HideHUD(void);


	void    ZoomPlus(void);

	void    ZoomMinus(void);
	void	ActZoom(void);
	void    ItemHolsterFrame(void);
	virtual void Equip(CBaseCombatCharacter* pOwner);
	bool    m_bVisibility;
	int     m_iZoomScale;
	int     m_iDefaultFOV;

};

IMPLEMENT_SERVERCLASS_ST(CToolCamera, DT_ToolCamera)

END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_ToolCamera, CToolCamera);
PRECACHE_WEAPON_REGISTER(weapon_ToolCamera);

BEGIN_DATADESC(CToolCamera)
DEFINE_FIELD(m_bVisibility, FIELD_BOOLEAN),
DEFINE_FIELD(m_iZoomScale, FIELD_INTEGER),
DEFINE_FIELD(m_iDefaultFOV, FIELD_INTEGER),
END_DATADESC()



CToolCamera::CToolCamera(void)
{
	
	m_bVisibility = true;
	m_iZoomScale = 75;
}

//-----------------------------------------------------
// Precache
//-----------------------------------------------------

void CToolCamera::Precache(void)
{
	BaseClass::Precache();
	//p recache models , sound , and other things
	
}

//-----------------------------------------------------
// Fire
// why are you reading this ?
//-----------------------------------------------------

void CToolCamera::ShowHUD(void)
{
	
	if (m_bVisibility) {
		UTIL_CenterPrintAll("Press Right Click to Hide HUD, E to Zoom in and R to Zoom out\n");
	}
	else {
		engine->ServerCommand("cl_drawhud 1\n");
		WeaponSound(WPN_DOUBLE);
		m_bVisibility = true;
	}

}
void CToolCamera::HideHUD(void) {

	if (m_bVisibility) {
		engine->ServerCommand("cl_drawhud 0\n");
		WeaponSound(WPN_DOUBLE);
		m_bVisibility = false;
	}
	else {
		UTIL_CenterPrintAll("Press Left Click to Show HUD, E to Zoom in and R to Zoom out\n");
	}
}
void CToolCamera::ZoomPlus(void)
{
	
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());

	if (pPlayer == NULL)
		return;
	if (m_iZoomScale > 10)
	m_iZoomScale -= 5;
	if (pPlayer->SetFOV(this, m_iZoomScale, 0.1f))
	{
		ActZoom();
	}
	


}
void CToolCamera::ActZoom(void)
{
	if (m_iZoomScale == 175) {
		UTIL_CenterPrintAll("4x");
	}
	if (m_iZoomScale == 130) {
		UTIL_CenterPrintAll("3x");
	}
	if (m_iZoomScale == 100) {
		UTIL_CenterPrintAll("2x");
	}
	if (m_iZoomScale == 75) {
		UTIL_CenterPrintAll("1x");
	}
	if (m_iZoomScale == 45) {
		UTIL_CenterPrintAll("0.5x");
	}
	if (m_iZoomScale == 10) {
		UTIL_CenterPrintAll("0.1x");
	}
	if (m_iZoomScale <= 5) {
		UTIL_CenterPrintAll("0.01x");
	}
}
void CToolCamera::ZoomMinus(void)
{
	
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());

	if (pPlayer == NULL)
		return;

	if(m_iZoomScale < 175)
	m_iZoomScale += 5;
	if (pPlayer->SetFOV(this, m_iZoomScale, 0.1f))
	{
		ActZoom();
	}
	

}
//change to another weapon thingy
void CToolCamera::ItemHolsterFrame(void)
{
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());
	if (pPlayer->SetFOV(this, 0, 0.0f))
	{
		engine->ServerCommand("cl_drawhud 1\n");
		m_bVisibility = true;
		m_iDefaultFOV = pPlayer->GetFOV();
		m_iZoomScale = pPlayer->GetFOV();
	}
	

}


//-----------------------------------------------------
// ADD NAME HERE
// remove a prop and draw a beam
//-----------------------------------------------------


//-----------------------------------------------------
// ItemPostFrame
//-----------------------------------------------------

void CToolCamera::ItemPostFrame(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());



	if ((pOwner->m_afButtonPressed & IN_ATTACK))
	{
		ShowHUD();
	}
	if ((pOwner->m_afButtonPressed & IN_ATTACK2))
	{
		HideHUD();
	}
	if ((pOwner->m_afButtonPressed & IN_USE))
	{
		ZoomPlus();
	}
	if ((pOwner->m_afButtonPressed & IN_RELOAD))
	{
		ZoomMinus();
	}




	BaseClass::ItemPostFrame();
}

// ---------------------------------------------------------------------------- -
// Purpose: Give this weapon longer range when wielded by an ally NPC.
//-----------------------------------------------------------------------------
void CToolCamera::Equip(CBaseCombatCharacter * pOwner)
{
	/*m_iZoomScale = ToBasePlayer(GetOwner())->GetFOV();
	m_iDefaultFOV = ToBasePlayer(GetOwner())->GetFOV();*/

	BaseClass::Equip(pOwner);
}