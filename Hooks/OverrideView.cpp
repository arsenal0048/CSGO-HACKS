#include "main.h"

void hkOverrideView(void* thisptr, CViewSetup& setup)
{
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(vars.misc.enabled && vars.misc.fov > 0)
    {
        if(!local)
            return;
        
        if(local->IsScoped())
            return;
        
        setup.fov += vars.misc.fov;
    }
    
    createmoveVMT->GetOriginalMethod<tOverrideView>(19)(thisptr, setup);
}
