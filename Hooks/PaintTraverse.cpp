#include "main.h"

#include "../Drawings/menu.h"

#include "../Hacks/crosshair.h"
#include "../Hacks/dlights.h"
#include "../Hacks/esp.h"
#include "../Hacks/spectators.h"

void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce)
{
    if (vars.misc.noscope && !strcmp("HudZoom", pPanel->GetName(panel)))
        return;
    
    paintVMT->GetOriginalMethod<tPaintTraverse>(42)(thisptr, panel, forceRepaint, allowForce);
    
    C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    static VPANEL last = 0;
    
    if(!last)
    {
        if(strstr(pPanel->GetName(panel), "FocusOverlayPanel"))
        {
            specfont    = draw->createfont(specfont, "Tahoma", 12, FONTFLAG_OUTLINE);   // Used for spectatorwindow
            mFont       = draw->createfont(mFont, "Tahoma", 14, FONTFLAG_NONE);         // Menu font
            eFont       = draw->createfont(eFont, "Verdana", 12, FONTFLAG_DROPSHADOW);  // ESP font
            sFont       = draw->createfont(sFont, "Verdana", 11, FONTFLAG_OUTLINE);     // Used for sliders
            
            last = panel;
        }
        
        {   // Initialisation
            vars.colors.ctchams     = Color(40, 204, 67, 255);
            vars.colors.ctchams_ign = Color(0, 124, 255, 255);
            
            vars.colors.tchams      = Color(204, 173, 40, 255);
            vars.colors.tchams_ign  = Color(255, 69, 0, 255);
            
            vars.colors.tbox        = Color(204, 173, 40, 255);
            vars.colors.tbox_ign    = Color(255, 69, 0, 255);
            
            vars.colors.ctbox       = Color(40, 204, 67, 255);
            vars.colors.ctbox_ign   = Color(0, 124, 255, 255);
            
            vars.colors.hands       = Color::Black();
            vars.colors.weapon      = Color::White();
            
            vars.colors.scope       = Color::Red();
            vars.colors.world       = Color::Red();
            vars.colors.sky         = Color::Red();
        }
        
    }
    
    
    if(panel == last)
    {
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
            return;
        
        pwnmymenu();
        
        {   // Drawing features / own scope just for readablity
            
            DrawPlayerESP();    // Player esp
                        
            DrawScope(local);   // Draws the crosshar for noscope
            
            rCrosshair(local);  // Draws recoil crosshair
            
            DLights();          // Renders in dlights
            
            Spectatorlist();    // Draws speclist
            
        }
        
        if(vars.menu)
        {   // Draw menu items
            menu->renderMenu();
            draw->drawmouse();
        }
        
    }
    
}
