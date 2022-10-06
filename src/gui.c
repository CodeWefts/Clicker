
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <playground.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gui.h"

int im_print_text(int x, int y, const char* text)
{
    int i;
    int sx,sy;
    pg_get_mouse_coords(&sx,&sy);

    for (i=0 ; text[i] != '\0' ; i++ )
        pg_put_char(x+i,y,text[i], 0xFFFFFFFF);
    if ((sx <= x+i && sx >= x) && sy == y && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
    {
        for (i=0 ; text[i] != '\0' ; i++ )
            pg_put_char_ex(x+i,y,text[i], 0xFFFFFFFF,0xFF949292,PG_COL_REPLACE);
    }
    

    return i;
}

int im_print(int x, int y, const char* format, ...)
{
    va_list list;
    va_start(list,format);
    char buffer[1024];
    vsprintf(buffer, format, list);
    va_end(list);

    im_print_text(x,y,buffer);
    return 0;
}

bool im_button(int x, int y,const char* text)
{
    int i = im_print_text(x,y,text); //longueur du text
    //coordonnees souris
    int sx,sy;
    pg_get_mouse_coords(&sx,&sy);

    if ((sx <= x+i && sx >= x) && sy == y && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        return true;
    }
    
    
    return false;
}