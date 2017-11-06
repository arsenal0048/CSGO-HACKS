#pragma once

extern HFONT espfont, specfont, mFont, osFont, sFont, tFont, cFont, heading;

typedef int ViVec_t;

class ViVecMouse
{
public:
    
    ViVec_t x, y;
    ViVecMouse(void);
    ViVecMouse(ViVec_t X, ViVec_t Y);
    
};

class cdrawings
{
public:
    
    wstring wstringtostring(string str);
    wstring StringToWstring(string str);
    HFONT createfont(HFONT font, const char* szFont, int tall, int flags);
    Vector2D GetTextSize(const char* text, HFONT font);
    
    void drawbox(int x, int y, int w, int h, Color color);
    void drawboxoutline(int x, int y, int w, int h, Color color);
    void fillrgba(int x, int y, int w, int h, Color color);
    void drawline(int x, int y, int xx, int yy, Color color);
    void drawstring(int x, int y, Color color, HFONT font, const char* szString, bool bCenter = false);
    void drawgradient(int x, int y, int w, int h, Color col1, Color col2);
    void GradientH(int x, int y, int width, int height, Color color1, Color color2);
    void Line(Vector2D start_pos, Vector2D end_pos, Color col);
    void RectOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined);
    void BorderBox(int x, int y, int w, int h, int thickness, Color color);
    void drawcolorpicker(int x, int y, const char *szString, Color &col);
    
    bool inArea(int x, int y, int w, int h);
    
    void handleinput(int eventcode, string arr[100]);
    void textbox(int x, int y, int w, const char* szString, string szValue[100], int inputIndex, int index, bool* var);
    
    ViVecMouse GetMouse();
    int CalcPos(int x);
    
    void drawmouse();
    void drawCrosshair(int x, int y, Color col);
    
    bool MoveMenu(int & x, int & y, int w, int h, int index);
    
    
    
    size_t m_nCurrentPos[100];      // Credit's to reactiioN @ uc
    string m_szCurrentString[100];
    
    string m_szChangedValue[100];
    
    bool IsKeyPressed(int eventCode, ButtonCode_t keyCode)
    {
        return (eventCode == keyCode) ? true : false;
    }
    
};

extern vector<string> keynames;

extern cdrawings* draw;



