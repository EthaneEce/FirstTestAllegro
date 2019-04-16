#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <logg.h>

int coordx(int n,int lng);
int coordy(int o,int lrg);
int coordx1(int n,int lng);
int coordy1(int o,int lrg);

void lancerToutAllegro(int largeur, int hauteur);

int main()
{
    int anim;

    BITMAP*buffer;
    BITMAP*perso;
    BITMAP*perso1;
    BITMAP*perso2;
    BITMAP*fond;
    BITMAP*mechant;
    BITMAP*mechant1;
    BITMAP*mechant2;
    BITMAP*go;
    BITMAP*pause;

    char ke;
    srand(time(NULL));
    int n,o,p,q;
    int lng=1156;
    int lrg=650;
    int test=0;
    int boutton=0;
    int boutton1=0;
    int boutton2=0;

    lancerToutAllegro(lng,lrg);

    buffer=create_bitmap(lng,lrg);
    perso=load_bitmap("persotest.bmp",NULL);
    perso1=load_bitmap("perso1test.bmp",NULL);
    perso2=load_bitmap("perso2test.bmp",NULL);
    fond=load_bitmap("salon.bmp",NULL);
    mechant=load_bitmap("araignee.bmp",NULL);
    mechant1=load_bitmap("araignee1.bmp",NULL);
    mechant2=load_bitmap("araignee2.bmp",NULL);
    go=load_bitmap("gameover.bmp",NULL);
    pause=load_bitmap("pause.bmp",NULL);

    anim=0;

    (n)=(lng/2-(lng/4));
    (o)=(lrg/2);
    (p)=(lng/2+(lng/4));
    (q)=(lrg/2);

    do
    {
        do
        {
            clear_to_color(buffer, makecol(255,255,255));
            draw_sprite(buffer,fond,0,0);
            /*--------------------------------------------------*///Gestion des animations
            if(anim<6)
            {
                draw_sprite(buffer,perso,n,o);
                draw_sprite(buffer,mechant,p,q);
                anim=anim+2;
            }
            if(anim>=6&&anim<12)
            {
                draw_sprite(buffer,perso1,n,o);
                draw_sprite(buffer,mechant1,p,q);
                anim=anim+2;
            }
            if(anim>=12&&anim<=16)
            {
                draw_sprite(buffer,perso2,n,o);
                draw_sprite(buffer,mechant2,p,q);
                anim=anim+2;
            }
            if(anim>16)
            {
                draw_sprite(buffer,perso2,n,o);
                draw_sprite(buffer,mechant2,p,q);
                anim=0;
            }
            /*--------------------------------------------------*/
            draw_sprite(screen,buffer,0,0);
            o=coordy(o,lrg);
            n=coordx(n,lng);
            q=coordy1(q,lrg);
            p=coordx1(p,lng);
            if ((o+36>=q&&o+6<=q+38)&&(n+49>=p+11&&n+18<=p+48))
            {
                rest(500);
                test=1;
            }
            if(key[KEY_ESC]||key[KEY_P])
            {
                do
                {
                    clear_to_color(buffer, makecol(255,255,255));
                    draw_sprite(buffer,pause,lng/4+60,lrg/12);
                    boutton1=draw_bouton(buffer,lng/2-25,lrg/2+100,lng/2-25+60,lrg/2+30+100,makecol(228,22,84),makecol(239,99,141),3,"QUITTER");
                    boutton=draw_bouton(buffer,lng/2-25,lrg/2,lng/2-25+60,lrg/2+30,makecol(36,172,217),makecol(168,222,240),3,"RESUME");
                    boutton2=draw_bouton(buffer,lng/2-25,lrg/2+50,lng/2-25+60,lrg/2+30+50,makecol(36,172,217),makecol(168,222,240),3,"REJOUER");
                    draw_sprite(screen,buffer,0,0);

                    if (boutton2==1)
                    {
                        test=0;
                        anim=0;

                        (n)=(lng/2-(lng/4));
                        (o)=(lrg/2);
                        (p)=(lng/2+(lng/4));
                        (q)=(lrg/2);
                    }

                    if(boutton1==1)
                    {
                        exit(0);
                    }
                }
                while((boutton!=1)&&boutton2!=1);
            }

        }
        while(!key[KEY_SPACE]&&test!=1);

        if (test==1)
        {
            do
            {
                clear_to_color(buffer, makecol(255,255,255));
                draw_sprite(buffer,go,lng/4+60,lrg/12);
                boutton1=draw_bouton(buffer,lng/2-25,lrg/2+50,lng/2-25+60,lrg/2+30+50,makecol(228,22,84),makecol(239,99,141),3,"QUITTER");
                boutton=draw_bouton(buffer,lng/2-25,lrg/2,lng/2-25+60,lrg/2+30,makecol(36,172,217),makecol(168,222,240),3,"REJOUER");
                draw_sprite(screen,buffer,0,0);
                test=0;
                anim=0;

                (n)=(lng/2-(lng/4));
                (o)=(lrg/2);
                (p)=(lng/2+(lng/4));
                (q)=(lrg/2);
                if (key[KEY_ESC])
                    boutton1=1;
            }
            while((boutton!=1&&boutton1!=1));
        }
    }
    while(boutton1!=1);

    readkey();
    return 0;
}
END_OF_MAIN();
