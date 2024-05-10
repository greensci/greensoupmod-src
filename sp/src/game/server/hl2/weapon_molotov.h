//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:		Molotov weapon
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//

#include "basehlcombatweapon.h"

#ifndef	WEAPON_MOLOTOV_H
#define	WEAPON_MOLOTOV_H

class CGrenade_Molotov;

class CWeaponMolotov : public CBaseHLCombatWeapon
{
public:
	DECLARE_CLASS( CWeaponMolotov, CBaseHLCombatWeapon );

	DECLARE_SERVERCLASS();

private:
	bool  m_bRedraw;
	Vector				m_vecTossVelocity;

public:

	void				Precache( void );
	void				Spawn( void );

	void CheckThrowPosition(CBasePlayer* pPlayer, const Vector& vecEye, Vector& vecSrc);

	
	int					CapabilitiesGet( void ) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	
	void				ThrowMolotov(CBasePlayer* pPlayer);
	void				ItemPostFrame( void );
	void				PrimaryAttack( void );
	

	void				Operator_HandleAnimEvent( animevent_t *pEvent, CBaseCombatCharacter *pOperator );

	bool                Reload(void);
	bool Holster(CBaseCombatWeapon* pSwitchingTo = NULL);
	bool Deploy(void);


	DECLARE_ACTTABLE();
	DECLARE_DATADESC();

	CWeaponMolotov(void);
};

#endif	//WEAPON_MOLOTOV_H
