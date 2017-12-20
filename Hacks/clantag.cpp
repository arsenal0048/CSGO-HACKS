#include "clantag.h"

// Thanks @pwned

void clantag()
{
    if(!vars.misc.clantag)
        return;

    static int Tick;
    Tick++;
    
    if (Tick > 0 && Tick < 15)
    {
        SetClanTag("x            ", "Xanax");
    }
    else if (Tick > 30 && Tick < 45)
    {
        SetClanTag("xa           ", "Xanax");
    }
    else if (Tick > 60 && Tick < 75)
    {
        SetClanTag("xan          ", "Xanax");
    }
    else if (Tick > 90 && Tick < 105)
    {
        SetClanTag("xana         ", "Xanax");
    }
    else if (Tick > 120 && Tick < 135)
    {
        SetClanTag("xanax         ", "Xanax");
    }
    else if (Tick > 150 && Tick < 165)
    {
        SetClanTag(" xanax        ", "Xanax");
    }
    else if (Tick > 180 && Tick < 195)
    {
        SetClanTag("  xanax       ", "Xanax");
    }
    else if  (Tick > 210 && Tick < 225)
    {
        SetClanTag("   xanax      ", "Xanax");
    }
    else if (Tick > 240 && Tick < 255)
    {
        SetClanTag("    xanax     ", "Xanax");
    }
    else if (Tick > 270 && Tick < 285)
    {
        SetClanTag("     xanax    ", "Xanax");
    }
    else if (Tick > 300 && Tick < 315)
    {
        SetClanTag("      xanax   ", "Xanax");
    }
    else if (Tick > 330 && Tick < 345)
    {
    
        SetClanTag("       xanax  ", "Xanax");
    }
    else if (Tick > 360 && Tick < 375)
    {
        SetClanTag("        xanax  ", "Xanax");
    }
    else if (Tick > 390 && Tick < 405)
    {
        SetClanTag("         xanax ", "Xanax");
    }
    else if (Tick > 420 && Tick < 435)
    {
        SetClanTag("          xanax", "Xanax");
    }
    else if (Tick > 450 && Tick < 465)
    {
        SetClanTag("           xana", "Xanax");
    }
    else if (Tick > 480 && Tick < 495)
    {
        SetClanTag("            xan", "Xanax");
    }
    else if (Tick > 510 && Tick < 525)
    {
        SetClanTag("             xa", "Xanax");
    }
    else if (Tick > 540 && Tick < 555)
    {
        SetClanTag("              x", "Xanax");
    }
    else if (Tick > 570 && Tick < 585)
    {
        SetClanTag("               ", "Xanax");
    }


    // Reset 
    if(Tick > 585)
    {
        Tick = 0;
    }    
}
