#include <SDL.h>
#include <math.h>
#include <time.h>
#include "action.c"

#define screen_hight 480
#define screen_lenth 640

#define ship_size 32
#define ship_angle 0

/* comande de compilation:
gcc -Wall -g -std=c99 priseenmain.c `sdl-config --cflags --libs` -lm -o priseenmain
*/



int main(int argc, char* argv[]){
	srand(time(NULL));   // should only be called once


//declaration nom
	SDL_Surface *ship, *temp, *background;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Space","Space");

/***********/
	
	
	
	
	int j;

	/*asteroid grosTest;
 	grosTest.taille = 3;
	int testPosition = rand()%4;
	SDL_Rect position;
	switch(testPosition)
	{
		case 0:
			position.x = 0;
			position.y = rand()%480;
			break;
		case 1:
			position.x = rand()%640;
			position.y = 0;
			break;
		case 2:
			position.x = 640;
			position.y = rand()%480;
			break;
		case 3:
			position.x = rand()%640;
			position.y = 480;
			break;
		default:
			position.x = 0;
			position.y = 0;
			break;
	}
	grosTest.position = position;
	grosTest.vitesse = 0.5;
	grosTest.angle = rand()%36;
	grosTest.posr.rx = position.x;
	grosTest.posr.ry = position.y;
	grosTest.id = j;

	*/


//creation de la fenetre
	SDL_Surface* screen = SDL_SetVideoMode(screen_lenth, screen_hight, 0, 0);
//couleur a exclure
	int colorkey;
//angle actuel init a angle de depart
	int curangle = ship_angle;
//vitesse initialle du vessau
	float shipspeed = 0;
//rectangle pour la position du sprite dans l'image
	SDL_Rect shippos;
	SDL_EnableKeyRepeat(10, 10);
//load sprite
	temp = SDL_LoadBMP("greenship-v1.bmp");
	ship = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
//colorkey
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(ship, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	
//init ship position
	shippos.x = (screen_lenth - ship_size) / 2;
	shippos.y = (screen_hight - ship_size) / 2;
	pointreel shipposr;
	shipposr.rx=shippos.x;
	shipposr.ry=shippos.y;

//load background
	temp = SDL_LoadBMP("backgroundlvl1.bmp");
	background = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

/******************************/
	int nombre_asteroid = 0;
	printf("INITIALISATION %d\n",nombre_asteroid);
	asteroid nuageAsteroid[ASTEROID_MAX];
	ajouterAsteroid(nuageAsteroid,&nombre_asteroid);
	ajouterAsteroid(nuageAsteroid,&nombre_asteroid);

	printf("Apres ajout : nb aste = %d\n",nombre_asteroid);

	printf("%d --- %d // %d --- %d\n",nuageAsteroid[0].position.x,nuageAsteroid[0].position.y,nuageAsteroid[1].position.x,nuageAsteroid[1].position.y);


	int gameover = 0;
	while(!gameover){
		SDL_Event event;
//recherche d'evenement

		if (SDL_PollEvent(&event)){
			eventact(event,&gameover,&curangle,&shippos, &shipspeed);
		}
//creation du background
		SDL_BlitSurface(background,NULL,screen,NULL);
//verification des coordoné du ship
		/*if (shippos.x > screen_lenth) {
			shippos.x=0;
			shipposrx=shippos.x;
		}
		if (shippos.x < 0){
			shippos.x=screen_lenth;
			shipposrx=shippos.x;
		}
		if (shippos.y > screen_hight) {
			shippos.y=0;
			shipposry=shippos.y;
		}
		if (shippos.y < 0){
			shippos.y=screen_hight;
			shipposry=shippos.y;
		}*/
		exitscreen(&shippos, &shipposr, screen_lenth, screen_hight);
//dessin du ship
		{
			SDL_Rect shipImage;
			shipImage.y = 0;
			shipImage.w = ship_size;
			shipImage.h = ship_size;
			shipImage.x = ship_size*curangle;
			SDL_BlitSurface(ship, &shipImage, screen, &shippos);
		}
		mouvement(&curangle, &shippos, &shipspeed, &shipposr);

/****** ASTEROIDS ***********/
		/*
		printf("%f ----------------- %d\n",grosTest.vitesse, grosTest.angle);
		exitscreen(&grosTest.position, &grosTest.posr, screen_lenth, screen_hight);
        SDL_BlitSurface(grosTest.surface,NULL,screen,&grosTest.position);

        mouvement(&grosTest.angle,&grosTest.position,&grosTest.vitesse,
			&grosTest.posr);
		*/
		printf("%d --- %d // %d --- %d\n",nuageAsteroid[0].position.x,nuageAsteroid[0].position.y,nuageAsteroid[1].position.x,nuageAsteroid[1].position.y);
		for (j=0;j<nombre_asteroid;j++)
		{
			exitscreen(&nuageAsteroid[j].position, &nuageAsteroid[j].posr, screen_lenth, screen_hight);
        	SDL_BlitSurface(nuageAsteroid[j].surface,NULL,screen,&nuageAsteroid[j].position);

        	mouvement(&nuageAsteroid[j].angle,&nuageAsteroid[j].position,&nuageAsteroid[j].vitesse,
			&nuageAsteroid[j].posr);
		}








	/*	exitscreen(&nuageAsteroid[0].position, &nuageAsteroid[0].posr, screen_lenth, screen_hight);
		{
			SDL_Rect asteroidImage;
			asteroidImage.y = 0;
			asteroidImage.w = 32;
			asteroidImage.h = 32;
			asteroidImage.x = 0;
			SDL_BlitSurface(nuageAsteroid[0].surface, &asteroidImage, screen, &nuageAsteroid[0].position);
		}
		mouvement(&nuageAsteroid[0].angle,&nuageAsteroid[0].position,&nuageAsteroid[0].vitesse,
			&nuageAsteroid[0].posr);

		//printf("%d\n",nuageAsteroid[0].position.x);
	*/
		/*for(j; j < nombre_asteroid; j++)
		{
			SDL_BlitSurface(ship, &shipImage, screen, &shippos);
		}*/		
	

//mise a jour de l'ecran
		
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		//printf("x= %d  y= %d   speed= %f\nrx= %f   ry= %f\n",shippos.x,shippos.y,shipspeed,shipposr.rx,shipposr.ry );
	}
	
//free
	SDL_FreeSurface(background);

//cleanup SDL
	SDL_Quit();
	return 0;
}
