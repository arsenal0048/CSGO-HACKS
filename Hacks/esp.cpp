#include "esp.h"
#include "../Hacks/autowall.h"

void DrawSkeleton(C_BaseEntity* pEntity, Color color)
{
    studiohdr_t* pStudioModel = pModelInfo->GetStudioModel( pEntity->GetModel() );
    
    if ( !pStudioModel )
        return;
    
    static matrix3x4_t pBoneToWorldOut[128];
    
    if ( !pEntity->SetupBones( pBoneToWorldOut, 128, 256, 0) )
        return;
    
    for ( int i = 0; i < pStudioModel->numbones; i++ )
    {
        mstudiobone_t* pBone = pStudioModel->pBone( i );
        
        if ( !pBone || !( pBone->flags & 256 ) || pBone->parent == -1 )
            continue;
        
        Vector vBone1 = pEntity->GetBonePosition(i);
        Vector vBoneOut1;
        
        Vector vBone2 = pEntity->GetBonePosition(pBone->parent);
        Vector vBoneOut2;
        
        if(WorldToScreen(vBone1, vBoneOut1) && WorldToScreen(vBone2, vBoneOut2))
        {
            draw->drawline(vBoneOut1.x, vBoneOut1.y, vBoneOut2.x, vBoneOut2.y, color);
        }
        
    }
    
}

Color GetColorBase(Color& col)
{
    return Color(col.r(), col.g(), col.b(), 255);
}

void DrawHealthbar(int x, int y, int w, int h, int health, Color color)
{
    if(health > 100)
    {
        health = 100;
    }
    int hw = h - ((h) * health) / 100;
    draw->fillrgba(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
    draw->fillrgba(x, y + hw - 1, w, h - hw + 2, color);
    draw->drawbox(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
    
}

void DrawPlayerESP()
{
    if(!vars.visuals.enabled)
        return;
    
    if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        return;
    
    int getscreenw, getscreenh;
    pEngine->GetScreenSize(getscreenw, getscreenh);
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetTeam() != 2 && entity->GetTeam() != 3)
            continue;
        
        if(vars.visuals.enemyonly && entity->GetTeam() == local->GetTeam())
            continue;
        
        player_info_t info;
        
        pEngine->GetPlayerInfo(i, &info);
        
        auto vis = IsVisible(local, entity);
        
        Color playercolor = [&]() -> Color
        {
            if(entity->GetTeam() == 3)
                return vis ? GetColorBase(vars.colors.ctbox) : GetColorBase(vars.colors.ctbox_ign);
            else if(entity->GetTeam() == 2)
                return vis ? GetColorBase(vars.colors.tbox) : GetColorBase(vars.colors.tbox_ign);
        }();
        
        boxstruct players;
        
        if(DrawPlayerBox(entity, players))
        {
            
            
            if(vars.visuals.box)
                draw->drawboxoutline(players.x, players.y, players.w, players.h, playercolor);
                    
            if(vars.visuals.name)
                draw->drawstring(players.x + players.w / 2, players.y - 12, Color::White(), espfont, info.name, true);
                            
            if(vars.visuals.healthtext)
                draw->drawstring(players.x + players.w / 2, players.y + players.h + 8, Color::White(), espfont, std::to_string(entity->GetHealth()).c_str(), true);
            
            if(vars.visuals.health)
                DrawHealthbar(players.x - 5, players.y, 3, players.h, entity->GetHealth(), Color(43, 206, 91, 255));
            
            if(vars.visuals.armour)
                DrawHealthbar(players.x, players.y + players.h + 3, players.w, 2, entity->GetArmor(), Color(72, 136, 189, 255));
            
            if(vars.visuals.snapline)
                draw->drawline(getscreenw / 2, getscreenh, players.x + players.w / 2, players.y + players.h, playercolor);
            
            if(vars.visuals.skeleton)
                DrawSkeleton(entity, Color::White());
            
            if(entity->IsDefusing())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "DEFUSING", true);
            
            if(entity->IsGrabbingHostage())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "RESCUING", true);
            
            if(entity->IsRescuing())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "CARRYING", true);
            
            if((entity->IsScoped()))
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "SCOPED", true);

        }
    
    }
    
}


/* Display menu */
void pwnmymenu()
{
    
    if(pInputSystem->IsButtonDown(KEY_INSERT))
    {
        vars.menu = !vars.menu;
        }
    
    }
