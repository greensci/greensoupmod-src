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

	void	Fire(void);
	void    firesecond(void);


	void    toolplus(void);

	void    toolminus(void);
};

IMPLEMENT_SERVERCLASS_ST(CToolCamera, DT_ToolCamera)

END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_ToolCamera, CToolCamera);
PRECACHE_WEAPON_REGISTER(weapon_ToolCamera);

BEGIN_DATADESC(CToolCamera)



END_DATADESC()



CToolCamera::CToolCamera(void)
{

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
// what are you reading this ?
//-----------------------------------------------------

void CToolCamera::Fire(void)
{

	engine->ServerCommand("cl_drawhud 0\n");

}
void CToolCamera::firesecond(void) {

	engine->ServerCommand("cl_drawhud 1\n");
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
		Fire();
	}
	if ((pOwner->m_afButtonPressed & IN_ATTACK2))
	{
		firesecond();
	}

	

	BaseClass::ItemPostFrame();
}
