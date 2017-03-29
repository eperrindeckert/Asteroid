#include <SDL.h>
#include "mouvement.c"
void exitscreen(SDL_Rect *pos,pointreel* posr , int dimx, int dimy){
	if ((*pos).x > dimx){
		(*pos).x=0;
		(*posr).rx=(*pos).x;
		//(*pos).y=dimy-(*pos).y;
	}
	if ((*pos).x < 0){
		(*pos).x=dimx;
		(*posr).rx=(*pos).x;
		//(*pos).y=dimy-(*pos).y;
	}
	if ((*pos).y > dimy){
		//(*pos).x=dimx-(*pos).x;
		(*pos).y=0;
		(*posr).ry=(*pos).y;
	}
	if ((*pos).y < 0){
		//(*pos).x=dimx-(*pos).x;
		(*pos).y=dimy;
		(*posr).ry=(*pos).y;
	}

}

void eventact(SDL_Event event, int* exit, int* angle, SDL_Rect *pos, float* speed ){
	switch (event.type){
//evenement croix en haut a gauche
		case SDL_QUIT:
			*exit=1;
			break;
			
		case SDL_KEYDOWN:
                	switch (event.key.keysym.sym) {
//event escape
				case SDLK_ESCAPE:
					*exit=1;
					break;
// event spour ralentire et z pour accelerer
				case SDLK_z:
					*speed=*speed+0.01;
					if ((*speed)>1){
						*speed=1;
					}
					break;
				case SDLK_s:
					*speed=*speed-0.01;
					if ((*speed)<0){
						*speed=0;
					}
					break;
//event q et d pour tourner
				case SDLK_q:
					if (*angle<35){
						*angle = *angle + 1;
					}
					else {
						*angle = 0;
					}
					break;
				case SDLK_d:
					if (*angle>0){
						*angle = *angle - 1;
					}
					else {
						*angle = 35;
					}
					break;

				// SPAWN ASTEROID//
				case SDLK_o:
					ajouterAsteroid(nuageAsteroid,&nombre_asteroid);
					break;


				default:
					break;
			}
			break;
	}
}
