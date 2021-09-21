/*
//  main.c
//  SDL images: Display multiples images on a window and modify them
//
//  Created by Sebastian Morera on 2021-08-21.
 
Concepts important du SDL:
1) Gestion de fênetre
2) Gestion de rendu (permettre de dessiner dans notre fênetre
3) Créer/Charger des textures (Texture (SDL2) est l'équivalent de surface (SDL1.2)
*/

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)

void SDL_ExitWithDestruction(SDL_Renderer *renderer, SDL_Window *window, const char *message);
void SDL_ExitWithError(const char *message);
void PAUSE(void);


int main()
{
    char *title = "Tutorial";
    SDL_Window *window = NULL; //, *lignes[256] = {NULL};;
    SDL_Renderer *renderer = NULL;
    
    SDL_Surface *imageDeFond = NULL, *zozor = NULL, *sapin = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect positionFond, positionZozor, positionSapin;
    
    positionFond.x = 0; //(WINDOW_WIDTH - positionFond.w) / 2;
    positionFond.y = 0; //(WINDOW_HEIGHT - positionFond.h) / 2;
    positionZozor.x = 500;
    positionZozor.y = 260;
    positionSapin.x = 600;
    positionSapin.y = 100;

    // Initialisation SDL + affichage fênetre avec une image + une icone de fênetre
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Lancement SDL, chargement de tous les systemes
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        SDL_ExitWithError("Initialisation de la SDL");
    
    // Création fenêtre + rendu
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Impossible de creer la fenetre et le rendu");

    SDL_SetWindowTitle(window, title);  // Titre de la fênetre
    
    // Création de l'icone pour la fênetre
    SDL_Surface *icone = IMG_Load("sdl_icone.bmp");
    SDL_SetWindowIcon(window, icone);
    SDL_FreeSurface(icone);
    
    imageDeFond = IMG_Load("lac_en_montagne.bmp");
    //imageDeFond = SDL_LoadBMP("kunfuPanda.bmp");
    
    if (imageDeFond == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger image");
    
    texture = SDL_CreateTextureFromSurface(renderer, imageDeFond);
    SDL_FreeSurface(imageDeFond);
    
    if (texture == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de creer la texture");
    
    if(SDL_QueryTexture(texture, NULL, NULL, &positionFond.w, &positionFond.h) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger la texture");
    
    if(SDL_RenderCopy(renderer, texture, NULL, &positionFond) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible d afficher la texture");
   
    /* Chargement et blittage de Zozor sur la scène */
    zozor = IMG_Load("zozor.bmp");
    if (zozor == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger image");
    
    SDL_SetColorKey(zozor, SDL_TRUE, SDL_MapRGB(zozor->format, 0, 0, 255));
    SDL_SetSurfaceAlphaMod(zozor, 128);
    texture = SDL_CreateTextureFromSurface(renderer, zozor);
    SDL_FreeSurface(zozor);
    
    if (texture == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de creer la texture");

    if(SDL_QueryTexture(texture, NULL, NULL, &positionZozor.w, &positionZozor.h) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger la texture");
    
    if(SDL_RenderCopy(renderer, texture, NULL, &positionZozor) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible d afficher la texture");
    
    /* Chargement et blittage du sapin sur la scène */
    sapin = IMG_Load("sapin.png");
    if (sapin == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger image");
    
    texture = SDL_CreateTextureFromSurface(renderer, sapin);
    SDL_FreeSurface(sapin);

    if (texture == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de creer la texture");

    if(SDL_QueryTexture(texture, NULL, NULL, &positionSapin.w, &positionSapin.h) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger la texture");
    
    if(SDL_RenderCopy(renderer, texture, NULL, &positionSapin) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible d afficher la texture");
    
    SDL_RenderPresent(renderer); // Afficher l'image de fond
    
    
    // Events (ce que le programme doit faire)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    PAUSE(); // Mise en pause du programme
    

    // Destruction de tous les élements crées
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void SDL_ExitWithDestruction(SDL_Renderer *renderer, SDL_Window *window, const char *message)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_ExitWithError(message);
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("Erreur: %s > %s \n", message ,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void PAUSE()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


/*
 SDL_Window *window = NULL; //, *lignes[256] = {NULL};;
 SDL_Renderer *renderer = NULL;
 
 // Création fenêtre
 window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
 if (!window)
     SDL_ExitWithError("Creation fenetre echouee");
 
 // Création renderer (triggers the program that control your graphics hardware and sets flags)
 renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);     // creates a renderer to render our images
 if (!renderer)
     SDL_ExitWithError("Initialisation du renderer");
 
 
 if (SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE) != 0)
     SDL_ExitWithError("Impossible de changer la couleur du rendu");
 
 if (SDL_RenderDrawPoint(renderer, 100, 450) != 0)
     SDL_ExitWithError("Impossible de dessiner un point");
 
 if (SDL_RenderDrawLine(renderer, 50, 50, 500, 500) != 0)
     SDL_ExitWithError("Impossible de dessiner une ligne");
 
 SDL_Rect rectangle;
 rectangle.x = 300;
 rectangle.y = 300;
 rectangle.w = 200;
 rectangle.h = 120;
 
 if (SDL_RenderFillRect(renderer, &rectangle) != 0)
     SDL_ExitWithError("Impossible de dessiner un rectangle");
 

 SDL_RenderPresent(renderer);    // Raffraichir le rendu
 
 if (SDL_RenderClear(renderer) != 0)     // Nettoyer l'écran, effacer le rendu
     SDL_ExitWithError("Effacement rendu echouee");
 
 PAUSE(); // Mise en pause du programme
 
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 
 */

