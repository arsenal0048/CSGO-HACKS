//
//  aimbot.cpp
//  vHook
// thanks pwned even though its from aimtux lol
//

#include "aimbot.h"
#include "antiaim.h"
#include "autoshoot.h"
#include "autowall.h"

C_BaseEntity* Aimbot::curTarget = nullptr;

int Hitscan(C_BaseEntity* entity)
{
    vector<int> hitboxes;

    hitboxes.push_back(HITBOX_HEAD);
    hitboxes.push_back(HITBOX_NECK);
    hitboxes.push_back(HITBOX_LOWER_NECK);
    hitboxes.push_back(HITBOX_PELVIS);
    hitboxes.push_back(HITBOX_BODY);
    hitboxes.push_back(HITBOX_THORAX);
    hitboxes.push_back(HITBOX_CHEST);
    hitboxes.push_back(HITBOX_UPPER_CHEST);
    hitboxes.push_back(HITBOX_RIGHT_THIGH);
    hitboxes.push_back(HITBOX_LEFT_THIGH);
    hitboxes.push_back(HITBOX_RIGHT_CALF);
    hitboxes.push_back(HITBOX_LEFT_CALF);
    hitboxes.push_back(HITBOX_RIGHT_FOOT);
    hitboxes.push_back(HITBOX_LEFT_FOOT);
    hitboxes.push_back(HITBOX_RIGHT_HAND);
    hitboxes.push_back(HITBOX_LEFT_HAND);
    hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
    hitboxes.push_back(HITBOX_RIGHT_FOREARM);
    hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
    hitboxes.push_back(HITBOX_LEFT_FOREARM);

    if(vars.aimbot.hitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}

/* Just paste from aimtux and itll work
 void Smooth(Vector& angle)
 {
 if(!vars.aimbot.enabled)
 return;
 
 if(!vars.aimbot.smooth)
 return;
 
 Vector viewAngles = Vector(0.f, 0.f, 0.f);
 pEngine->GetViewAngles(viewAngles);
 
 Vector delta = angle - viewAngles;
 NormalizeAngles(delta);
 
 float smooth = powf(vars.aimbot.smoothf, 0.4);
 smooth = std::min(0.99f, smooth);
 
 Vector toChange = delta - delta * smooth;
 
 return angle = viewAngles + toChange;
 }
 */

void DoAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bSendPacket)
{
    if(!vars.aimbot.enabled)
        return;
    
    Vector eyepos = local->GetEyePosition();
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(weapon->GetAmmo() < 1)
            continue;
        
        if(weapon->IsKnife() || weapon->IsBomb())
            continue;
        
        if(gCorrections[entity->GetIndex()].whitelist)
            continue;
        
        Vector vFrom, vTo;
        
        Aimbot::curTarget = entity;
        
        vFrom = GetHitboxPosition(entity, Hitscan(entity));
        
        if(vars.aimbot.prediction)
            eyepos += entity->GetVelocity() * pGlobals->interval_per_tick;
        
        vTo = CalcAngle(eyepos, vFrom);
        
        auto isVISIBLE = IsVisible(local, entity);
        float getdmg = 0.f;
        Autowall::FireBulletData data;
        bool canHit = false;
        
        if(vars.aimbot.autowall)
        {
            getdmg = Autowall::GetDamage(vFrom, true, data);
            canHit = getdmg >= vars.aimbot.mindmg;
        }
        
        atTargets = vTo;
        
        if(canHit || isVISIBLE)
        {
            if(GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.fov)
            {
                if(vars.aimbot.autoshoot)
                {
                    AutoShoot(local, weapon, pCmd);
                }
                
                if(vars.aimbot.autocrouch)
                {
                    pCmd->buttons |= IN_DUCK;
                }
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            
        }
        
    }
    
}
