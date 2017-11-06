//
//  autoshoot.cpp
//  pwned
//
#include "autoshoot.h"

void AutoShoot(C_BaseEntity* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
    if (!vars.aimbot.autoshoot)
        return;
    
    if (!player || !activeWeapon || activeWeapon->GetAmmo() == 0)
        return;
    
    CSWeaponType weaponType = (CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType;
    
    if (weaponType == CSWeaponType::WEAPONTYPE_KNIFE || weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE)
        return;
    
    
    if (cmd->buttons & IN_USE)
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    
    float nextPrimaryAttack = activeWeapon->GetNextPrimaryAttack();
    
    if (nextPrimaryAttack > pGlobals->curtime)
    {
        if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
            cmd->buttons &= ~IN_ATTACK2;
        else
            cmd->buttons &= ~IN_ATTACK;
    }
    else
    {
        if (vars.aimbot.autoscope && activeWeapon->GetCSWpnData()->m_iZoomLevels > 0 && !localplayer->IsScoped())
            cmd->buttons |= IN_ATTACK2;
        else if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
            cmd->buttons |= IN_ATTACK2;
        else
            cmd->buttons |= IN_ATTACK;
    }
    
}

void ContinuousPistols(CUserCmd* cmd, C_BaseCombatWeapon* weapon)
{
    if(!vars.aimbot.autopistol)
        return;
    
    if(!weapon->IsPistol())
        return;
    
    if (cmd->buttons & IN_ATTACK)
    {
        static bool bAttack = false;
        
        if (bAttack)
            cmd->buttons |= IN_ATTACK;
        else
            cmd->buttons &= ~IN_ATTACK;
        
        bAttack = !bAttack;
    }
    
}


// Todo
void AutoKnife(C_BaseEntity* local)
{
//    if(!vars.misc.knifebot)
        return;
    
    if(!local)
        return;
    
    C_BaseCombatWeapon* weapon = GetActiveWeapon(local);
    
    if(!weapon)
        return;
    
    if(!weapon->IsKnife())
        return;
    
    
    
    
}




















