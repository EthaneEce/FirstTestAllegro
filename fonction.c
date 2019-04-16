#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <logg.h>

void lancerToutAllegro(int largeur, int hauteur)
{
    /// initialisation générale
    allegro_init();
    /// pour utiliser le clavier
    install_keyboard();
    /// pour utiliser la souris
    install_mouse();
    /// initialisation du MODE GRAPHIQUE
    //on fixe le mode couleur (8, 16, 24 ou 32 bits)
    set_color_depth(desktop_color_depth());
    // on essaie d’ouvrir une fenêtre de largeur*hauteur pixels
    // si l’ouverture échoue on quitte
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,largeur,hauteur,0,0)!=0)
    {
        allegro_message("probleme mode graphique : %s", allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    /// si on veut afficher le pointeur de souris
    show_mouse(screen);
}

int coordy(int o,int lrg)
{
    if(key[KEY_UP])
    {
        if(o==0)
        {
            return o;
        }
        else
        {
            o--;
            return o;
        }
    }

    if(key[KEY_DOWN])
    {
        if(o==lrg-40)
        {
            return lrg-40;
        }
        else
        {
            o++;
            return o;
        }
    }
    else
    {
        return o;
    }

}

int coordx(int n,int lng)
{
    if(key[KEY_LEFT])
    {
        if(n==0)
        {
            return n;
        }
        else
        {
            n--;
            return n;
        }
    }
    if(key[KEY_RIGHT])
    {
        if(n==lng-75)
        {
            return lng-75;
        }
        else
        {
            n++;
            return n;
        }
    }
    else
    {
        return n;
    }
}

int coordy1(int o,int lrg)
{
    if(key[KEY_W])
    {
        if(o==0)
        {
            return o;
        }
        else
        {
            o--;
            return o;
        }
    }

    if(key[KEY_S])
    {
        if(o==lrg-40)
        {
            return lrg-40;
        }
        else
        {
            o++;
            return o;
        }
    }
    else
    {
        return o;
    }
}

int coordx1(int n,int lng)
{
    if(key[KEY_A])
    {
        if(n==0)
        {
            return n;
        }
        else
        {
            n--;
            return n;
        }
    }
    if(key[KEY_D])
    {
        if(n==lng-75)
        {
            return lng-75;
        }
        else
        {
            n++;
            return n;
        }
    }
    else
    {
        return n;
    }
}

int draw_bouton(BITMAP *buffer, int posx, int posy, int pos2x, int pos2y, int color1, int color2, int profondeur, char* texte)
{
    int pos_mouse=1; // Pour savoir si la souris est sur le bouton
    int color; // Pour definir la couleur du bouton
    int c_hg; // Couleur du coin haut gauche
    int c_bd; // Couleur du coin bas droite
    int texte_x; // Position du texte en x
    int texte_y; // Position du texte en y
    int retour=0; // Renvoi
    int i;

    if(profondeur >5)
        profondeur=5;
    if(profondeur <=0)
        profondeur=1;

    // Si la souris est sur le bouton on modifie la valeur de pos_mouse
    if(mouse_x>=posx && mouse_x<=pos2x && mouse_y>=posy && mouse_y<=pos2y)
    {
        pos_mouse=2;
        // Si l'utilisateur clique sur le bouton
        if(mouse_b & 1)
        {
            pos_mouse=3;
            // On renvoie un 1 si le bouton est enfoncé
            retour=1;
        }
    }
    else
        pos_mouse=1;

    // Changement des couleurs pour les effets de perspective et pour savoir si la souris est sur le bouton
    switch(pos_mouse)
    {
    case 1:
        c_hg=255;
        c_bd=0;
        color=color1;
        texte_x=(posx+pos2x)/2;
        texte_y=(posy+pos2y)/2;
        break;
    case 2:
        c_hg=255;
        c_bd=0;
        color=color2;
        texte_x=(posx+pos2x)/2;
        texte_y=(posy+pos2y)/2;
        break;
    case 3:
        c_hg=0;
        c_bd=255;
        color=color2;
        texte_x=((posx+pos2x)/2)+profondeur;
        texte_y=((posy+pos2y)/2)+profondeur;
        break;
    }

    // Dessin de lignes blanches et noires pour la perspective
    for(i=0; i!=profondeur; i++)
    {
        hline(buffer,posx,posy+i,pos2x-i,makecol(c_hg,c_hg,c_hg));
        vline(buffer,posx+i,posy,pos2y-i,makecol(c_hg,c_hg,c_hg));
        hline(buffer,posx+i,pos2y-i,pos2x,makecol(c_bd,c_bd,c_bd));
        vline(buffer,pos2x-i,posy+i,pos2y,makecol(c_bd,c_bd,c_bd));
    }

    // Remplissage du bouton
    rectfill(buffer,posx+profondeur,posy+profondeur,pos2x-profondeur,pos2y-profondeur,color);
    // Ecriture du texte
    textprintf_centre(buffer,font,texte_x,texte_y,makecol(255,255,255),"%s",texte);

    // Renvoi : 1 si le bouton a été cliqué, 0 sinon
    return retour;
}
