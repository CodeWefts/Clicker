//Morgane

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <playground.h>

#include "game.h"
#include "gui.h"
#include "utils.h"


void game_init(Game* game, int width, int height)
{
    game->candyCounter.freq = 4.f; // candies per seconds
    game->candyCounter.value = 0;
    game->candyCounter.timer = 1.f / game->candyCounter.freq;
 
    game->lollipopCounter.freq = 0.5f;
    game->candyCounter.value = 0;
    game->candyCounter.timer = 1.f / game->candyCounter.freq;

    game->screenSize.width = width;
    game->screenSize.height = height;
}
void counter_update(Count* candy, float frameTime)
{
    candy->timer -= frameTime;
    if(candy->timer <= 0)
    {
        candy->value++;
        candy->timer = 1.f / candy->freq;
    }
}
void counters_update(Game* game)
{
    float frameTime = pg_io_get_frame_time();
    counter_update(&game->candyCounter, frameTime);

    counter_update(&game->lollipopCounter, frameTime);
    
    im_print(1, 1 , "You have %d cand%s", game->candyCounter.value, (game->candyCounter.value <= 1) ? "y" : "ies");
    im_print(1, 2, "You have %d lollipop%s", game->lollipopCounter.value,(game->lollipopCounter.value <= 1) ? "s" : "");
}


void game_state_save_text(Game *self, const char* filename)
{
    FILE* file = fopen(filename,"w");
    
    fprintf(file,"%s: %d\n","Candies", self->candyCounter.value);
    fprintf(file,"%s: %d\n","Lollipops", self->lollipopCounter.value);
    fprintf(file,"%s: %d\n","CandiesEaten", self->candiesEaten);
    fprintf(file,"%s: %d\n","CandiesThrown", self->candiesThrown);
    fprintf(file,"%s: %d\n","LollipopHidden", self->research.lollipopvalue);

    fprintf(file,"%s: %d\n","eatAllUnlocked", (self->eatAllUnlocked)? 0 : 1 );
    fprintf(file,"%s: %d\n","throwUnlocked", (self->throwUnlocked)? 0 : 1 );
    fprintf(file,"%s: %d\n","village", (self->village)? 0 : 1 );
    
    fclose(file);

}
void game_state_load_text(Game* self, const char* filename)
{
    signed char texte[1024];
    signed char texte1[1024];
    signed char texte2[1024];
    signed char texte3[1024];
    signed char texte4[1024];
    signed char texte5[1024];
    signed char texte6[1024];
    signed char texte7[1024];

    int candy,lollipop,eat,throw,research, eatunlock, throwunlock,village;

    FILE* file = fopen(filename,"r");

    fscanf(file,"%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n%s %d\n",texte,&candy,texte1,&lollipop,texte2,&eat,texte3,&throw,texte4,&research,texte5,&eatunlock,texte6,&throwunlock,texte7,&village);

    self->candyCounter.value = candy;
    self->lollipopCounter.value = lollipop;
    self->candiesEaten = eat;
    self->candiesThrown = throw;
    self->research.lollipopvalue = research;


    self->eatAllUnlocked = (eatunlock==0) ? true : false ;
    self->throwUnlocked =  (eatunlock==0) ? true : false ;
    self->village =  (eatunlock==0) ? true : false ;
    
    
    fclose(file);
}


void main_update(Game* game)
{
    
    im_print(1, 9 , "You have eat %d secret lollipop%s", game->research.lollipopvalue, (game->candiesEaten <= 1) ? "" : "s");

    if ((game->candyCounter.value > 100) || (game->eatAllUnlocked == true))
    {
        int eat;
        game->eatAllUnlocked = true;
        if (im_button(1,4,"EAT ALL CANDIES"))
        {
            eat = game->candyCounter.value;
            game->candiesEaten += eat;
            game->candyCounter.value = 0;
        }
        im_print(1, 6 , "You have eat %d cand%s", game->candiesEaten, (game->candiesEaten <= 1) ? "y" : "ies");
        
        
    }

    if ((game->candyCounter.value > 1000)|| (game->throwUnlocked == true))
    {
        int throw;
        game->throwUnlocked = true;
        if (im_button(1,5,"THROW ALL CANDIES"))
        {
            throw = game->candyCounter.value;
            game->candiesThrown += throw;
            game->candyCounter.value = 0;

        }
        im_print(1, 7 , "You have eat %d cand%s", game->candiesThrown, (game->candiesThrown <= 1) ? "y" : "ies");
    }

    if (game->candyCounter.value > 20)
    {
        game->village = true;
        im_button(50,25,"VILLAGE");
    }

    
    // Save    
    if (im_button(61, 1, "SAVE"))
    {
        game_state_save_text(game, "save.txt");
    }
    // Load
    if (im_button(81, 1, "LOAD"))
    {
        game_state_load_text(game, "save.txt");
    }

    // Draw GUI
    draw_box(0,0,game->screenSize.width-1,8);
    draw_line_vertical(0,0,game->screenSize.width-40,8);
    draw_line_vertical(0,0,game->screenSize.width-20,8);
    


}
void debug_update(Game* game)
{
    im_button(50-3,1,"BEBUG");
    draw_line_horizontal(0,8,game->screenSize.width,8);
    draw_box(50-4,0,(game->screenSize.width/2)+2,2);

    //changer la valeur de candy
    im_print_text(1,10,"CHANGE CANDIES'S VALUE");
    {
    if(im_button(30,10,"+1"))
    {
        game->candyCounter.value += 1;
    }
    if(im_button(30,11,"+5"))
    {
        game->candyCounter.value += 5;
    }
    if(im_button(30,12,"+10"))
    {
        game->candyCounter.value += 10;
    }
    if(im_button(30,13,"+100"))
    {
        game->candyCounter.value += 100;
    }
    }
    {
    if(im_button(60,10,"-1"))
    {
        game->candyCounter.value -= 1;
    }
    if(im_button(60,11,"-5"))
    {
        game->candyCounter.value -= 5;
    }
    if(im_button(60,12,"-10"))
    {
        game->candyCounter.value -= 10;
    }
    if(im_button(60,13,"-100"))
    {
        game->candyCounter.value -= 100;
    }
    }
    //changer la valuer de lollipop
    im_print_text(1,15,"CHANGE LOLLIPOP'S VALUE");
    {
        if(im_button(30,15,"+1"))
    {
        game->lollipopCounter.value += 1;
    }
    if(im_button(30,16,"+5"))
    {
        game->lollipopCounter.value += 5;
    }
    if(im_button(30,17,"+10"))
    {
        game->lollipopCounter.value += 10;
    }
    if(im_button(30,18,"+100"))
    {
        game->lollipopCounter.value += 100;
    }
    }
    {
        if(im_button(60,15,"-1"))
    {
        game->lollipopCounter.value -= 1;
    }
    if(im_button(60,16,"-5"))
    {
        game->lollipopCounter.value -= 5;
    }
    if(im_button(60,17,"-10"))
    {
        game->lollipopCounter.value -= 10;
    }
    if(im_button(60,18,"-100"))
    {
        game->lollipopCounter.value -= 100;
    }
    }
    // changer la vitesse d'apparition des candies
    im_print_text(1,20,"CHANGE CANDIES'S SPEED");
    {
        if(im_button(30,20,"+0.1"))
        {
         game->candyCounter.freq += 0.1;
        }
        if(im_button(30,21,"+0.5"))
        {
            game->candyCounter.freq += 0.5;
        }
        if(im_button(30,22,"+1"))
        {
            game->candyCounter.freq += 1;
        }
        if(im_button(30,23,"+10"))
        {
            game->candyCounter.freq += 10;
        }
    }
    {
        if(im_button(60,20,"-0.1"))
        {
         game->candyCounter.freq -= 0.1;
        }
        if(im_button(60,21,"-0.5"))
        {
            game->candyCounter.freq -= 0.5;
        }
        if(im_button(60,22,"-1"))
        {
            game->candyCounter.freq -= 1;
        }
        if(im_button(60,23,"-10"))
        {
            game->candyCounter.freq -= 10;
        }
    }
    // changer la vitesse d'apparition des lollipop
    im_print_text(1,25,"CHANGE LOLLIPOP'S SPEED");
    {
        if(im_button(30,25,"+0.1"))
        {
         game->lollipopCounter.freq += 0.1;
        }
        if(im_button(30,26,"+0.5"))
        {
            game->lollipopCounter.freq += 0.5;
        }
        if(im_button(30,27,"+1"))
        {
            game->lollipopCounter.freq += 1;
        }
        if(im_button(30,28,"+10"))
        {
            game->lollipopCounter.freq += 10;
        }
    }
    {
        if(im_button(60,25,"-0.1"))
        {
         game->lollipopCounter.freq -= 0.1;
        }
        if(im_button(60,26,"-0.5"))
        {
            game->lollipopCounter.freq -= 0.5;
        }
        if(im_button(60,27,"-1"))
        {
            game->lollipopCounter.freq -= 1;
        }
        if(im_button(60,28,"-10"))
        {
            game->lollipopCounter.freq -= 10;
        }
    }
    //changer candieseaten
    im_print_text(1,30,"CHANGE CANDIESEATEN'S VALUE");
    {
        if(im_button(30,30,"+1"))
        {
         game->candiesEaten += 1;
        }
        if(im_button(30,31,"+5"))
        {
            game->candiesEaten += 5;
        }
        if(im_button(30,32,"+10"))
        {
            game->candiesEaten += 10;
        }
        if(im_button(30,33,"+100"))
        {
            game->candiesEaten += 100;
        }
    }
    {
        if(im_button(60,30,"-1"))
        {
         game->candiesEaten -= 1;
        }
        if(im_button(60,31,"-5"))
        {
            game->candiesEaten -= 5;
        }
        if(im_button(60,32,"-10"))
        {
            game->candiesEaten -= 10;
        }
        if(im_button(60,33,"-100"))
        {
            game->candiesEaten -= 100;
        }
    }
    //changer goldenLollipop
    im_print_text(1,35,"CHANGE GOLDENLOLLIPOP'S VALUE");
    {
        if(im_button(30,35,"+1"))
        {
         game->candiesEaten += 1;
        }
        if(im_button(30,36,"+5"))
        {
            game->candiesEaten += 5;
        }
        if(im_button(30,37,"+10"))
        {
            game->candiesEaten += 10;
        }
        if(im_button(30,38,"+100"))
        {
            game->candiesEaten += 100;
        }
    }
    {
        if(im_button(60,35,"-1"))
        {
         game->candiesEaten -= 1;
        }
        if(im_button(60,36,"-5"))
        {
            game->candiesEaten -= 5;
        }
        if(im_button(60,37,"-10"))
        {
            game->candiesEaten -= 10;
        }
        if(im_button(60,38,"-100"))
        {
            game->candiesEaten -= 100;
        }
    }
}
void village_update(Game* game)
{
    ascii_draw(20,10,"assets/HDV.txt");
    draw_box(44,18,50,20);
    im_button(45,19,"Hotel");

    ascii_draw(0,35,"assets/maison.txt");
    draw_box(10,40,21,42);
    im_button(11,41," MARCHAND ");
}
void chatmain_update(Game* game)
{
    int sx,sy;
    char texte[]= "Salut \n";
    pg_get_mouse_coords(&sx,&sy);

    ascii_draw(0,39,"assets/homme_main.txt");
    
    switch(game->dialogue)
    {
        case DIA1:
        {
            if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
            {
                draw_box(sx,sy-5,sx+40,sy);
                im_print_text(sx+1,sy-4,"SALUT !");
                im_print_text(sx+1,sy-3,"Je ne sais pas ce que tu fais ici");
                im_print_text(sx+1,sy-2,"mais il n'y a rien d'interessant (*_*)");
                im_print_text(sx+1,sy-1,"(Clique sur moi pour me parler)");

            }
            if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                game->dialogue = DIA2;
            }
            break;
        }
        case DIA2:
        {
            if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
            {
                draw_box(sx,sy-2,sx+40,sy);
                im_print_text(sx+1,sy-1,"Non vraiment...");
            }
            if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                game->dialogue = DIA3;
            }
            break;
        }
        case DIA3:
        {
           if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
            {
                draw_box(sx,sy-2,sx+40,sy);
                im_print_text(sx+1,sy-1,"Bon...");
            } 
            if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                game->dialogue = DIA4;
            }
            break;
        }
        case DIA4:
        {
           if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
            {
                draw_box(sx,sy-2,sx+40,sy);
                im_print_text(sx+1,sy-1,"Tu comptes rester la longtemps ?");
            } 
            if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                game->dialogue = DIA5;
            }

            break;
        }
        case DIA5:
        {
           if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
            {
                draw_box(sx,sy-2,sx+40,sy);
                im_print_text(sx+1,sy-1,"Tu as des choses a faire...");
            } 

            break;
        }

        

        default: break;
    }


}
void hotel_update(Game* game)
{
    ascii_draw(0,0,"assets/in_hotel.txt");
/*
    if ((sx <= 15 && sx >= 0) && (sy <= 50 && sy >= 39) && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
            {
                draw_box(sx,sy-10,sx+15,sy);
                im_print_text(sx+1,sy-9,"SALUT");
            }*/
}
void merchant_update(Game* game)
{
    int sx,sy;
    pg_get_mouse_coords(&sx,&sy);
    ascii_draw(0,0,"assets/merchant.txt");


    im_print_text(13,27,"O--");
    if(sx <= 16 && sx >= 13 && sy == 27 && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
    {
        draw_box(30,9,70,11);

        switch(game->dialogue_merchant)
        {
            case DIAA1:
            {
                if ((sx <= 16 && sx >= 13) && sy == 27 && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT))
                {
                    im_print_text(31,10,"CECI VAUT 120 BONBONS                  ");
                }
                if ((sx <= 16 && sx >= 13) && sy == 27 && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
                {
                    game->dialogue_merchant = DIAA2;
                }
                break;
            }
            case DIAA2:
            {
                if ((sx <= 16 && sx >= 13) && sy == 27 && pg_io_mouse_button_up(GLFW_MOUSE_BUTTON_LEFT) && game->candyCounter.value >= 120)
                {
                    im_print_text(31,10,"MERCI, J'EN AI ENCORE EN STOCK         ");
                }
                if ((sx <= 16 && sx >= 13) && sy == 27 && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
                {

                    game->dialogue_merchant = DIAA1;
                }
                break;
            }


            default : break;
        }
    }
        

}

bool research(Game* game,bool research ,int x, int y)
{

    if (research == false)
    {
        int sx,sy;
        pg_get_mouse_coords(&sx,&sy);

        im_print_text(x,y,"O--");
        if (sx <= x+3 && sx >= x && sy == y && pg_io_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            game->research.lollipopvalue += 1;
            im_print_text(x,y,"OOO");
            research = true;
            return true;
        }
    }

}



void game_update(Game* game)
{
    counters_update(game);
    
    switch(game->display)
    {
        case INTRO:
        {
            im_print_text((game->screenSize.width/2)-20,(game->screenSize.height/2)-10,"BIENVENUE DANS LE CLICKER DE MORGANE");
            if(im_button((game->screenSize.width/2)-10,(game->screenSize.height/2)-8,"COMMENCER"))
            {
                game->display = MAIN;
            }
            break;
        }
        case MAIN :
        {
            main_update(game);
            chatmain_update(game);
            if (game->candyCounter.value > 20 || game->village == true)
            {
                game->village = true;
                if (im_button(50,25,"VILLAGE"))
                {
                    game->display = VILLAGE;
                }
            }
            
            if (im_button(40,25,"DEBUG"))
                game->display = DEBUG;
            break;
        }
        case DEBUG:
        {
            debug_update(game);

            if (im_button(game->screenSize.width-7,1,"RETOUR"))
                game->display = MAIN;
            break;
        }
        case VILLAGE:
        {
            village_update(game);


            research(game,game->research.lollipop1,0,10);


            if (im_button(game->screenSize.width-7,1,"RETOUR"))
                game->display = MAIN;
            if (im_button(45,19,"Hotel"))
                game->display = HOTEL;
            if (im_button(11,41," MARCHAND "))
                game->display = MERCHANT;

            break;
        }

        case HOTEL:
        {
            research(game,game->research.lollipop2,0,10);
            hotel_update(game);
            if (im_button(game->screenSize.width-7,1,"RETOUR"))
                game->display = VILLAGE;

            break;
        }
        case MERCHANT:
        {
            merchant_update(game);
            
            if (im_button(game->screenSize.width-7,1,"RETOUR"))
                game->display = VILLAGE;

            break;
        }

        default: break;
    }

    


}
