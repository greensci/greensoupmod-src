//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef WEAPON_STUNSTICK_H
#define WEAPON_STUNSTICK_H
#ifdef _WIN32
#pragma once
#endif

#include "basebludgeonweapon.h"

#define	STUNSTICK_RANGE		75.0f
#define	STUNSTICK_REFIRE	0.6f

class CWeaponStunStick : public CBaseHLBludgeonWeapon
{
	DECLARE_CLASS(CWeaponStunStick, CBaseHLBludgeonWeapon);
	DECLARE_DATADESC();

public:

	CWeaponStunStick();
	~CWeaponStunStick();

	DECLARE_SERVERCLASS();
	DECLARE_ACTTABLE();

	virtual void Precache();

	void		Spawn();

	float		GetRange(void) { return STUNSTICK_RANGE; }
	float		GetFireRate(void) { return STUNSTICK_REFIRE; }

	int			WeaponMeleeAttack1Condition(float flDot, float flDist);

	bool		Deploy(void);
	bool		Holster(CBaseCombatWeapon* pSwitchingTo = NULL);
	void		ItemPostFrame(void);

	void		Equip(CBaseCombatCharacter* pOwner);
	void		Drop(const Vector& vecVelocity);
	void		PrimaryAttack(void);
	void		SecondaryAttack(void) {}
	void		SetStunState(bool state);
	bool		GetStunState(void);
	void		Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator);

	float		GetDamageForActivity(Activity hitActivity);

	bool		CanBePickedUpByNPCs(void) { return false; }
	void		AddViewKick(void);

private:

	CNetworkVar(bool, m_bActive);
	CNetworkVar(bool, m_bInSwing);
};

#endif // WEAPON_STUNSTICK_H
