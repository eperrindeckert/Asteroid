#include <SDL.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define pi 3.1416
#define ASTEROID_MAX 10



//srand(time(NULL));   // should only be called once

struct pointreel
{
	float rx;
	float ry;
};
typedef struct pointreel pointreel;

struct asteroid
{
	int taille;
	SDL_Rect position;
	float vitesse;
	int angle;
	pointreel posr;
	SDL_Surface* surface;
	int id;
};
typedef struct asteroid asteroid;

void mouvement(int* angle, SDL_Rect *pos, float* speed, pointreel* posr){
	float temp;
	temp = ((*angle)*10) * (pi/180.0);
	(*posr).rx=(*posr).rx + *speed * cos(temp);
	(*pos).x=(int)(*posr).rx;
	(*posr).ry=(*posr).ry - *speed * sin(temp);
	(*pos).y=(int)(*posr).ry;
}

asteroid nouveauAsteroid(int* nb)
{
	asteroid objet;
	objet.taille = 3;
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
	objet.position = position;
	objet.vitesse = 0.3;//rand()%6;
	objet.angle = rand()%36;
	objet.posr.rx = position.x;
	objet.posr.ry = position.y;
	objet.id = *nb;
	*nb = *nb+1;
	SDL_Surface* temp = SDL_LoadBMP("asteroid.bmp");
	objet.surface = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	return objet;
}

void ajouterAsteroid(asteroid* tab, int* nb)
{
	if(*nb == ASTEROID_MAX)
	{
		printf("Nombre d'asteroids dépassé...\n");
		return;
	}
	tab[*nb] = nouveauAsteroid(nb);
	nb++;
}

void supprimerAsteroid(asteroid* tab, int* nb, int id_cible)
{
	if(id_cible==(*nb-1))
	{
		*nb = *nb - 1;
	}
	else
	{
		tab[id_cible] = tab[id_cible+1];
	}
}







