#include <stdio.h>
#include <stdarg.h>
#include <playground.h>
#include <string.h>

#include "../src/gui.h"
#include "../src/utils.h"

void t_ascii_draw(int x, int y, const char* filepath)
{
    FILE* file= fopen(filepath,"r");
    if (file == NULL)
    {
        printf("Sale merde\n");
        return;
    }

    int penX = x;
    int penY = y;
    char line[1024];
    while(fgets(line,sizeof(line),file) != NULL)
    {
        int len = strlen(line);
        for(int i=0; i < len ;i++)
        {
            if (line[i]==10)
            {
                penX = x;
                penY++;
            }
            else if(line[i] != 10)
            {
                pg_put_char(penX,penY,line[i],PG_COL_REPLACE);
                penX++;
            }
        }

    }
    fclose(file);

}

void test(void)
{
    t_ascii_draw(10,10,"assets/triforce.txt");
}