#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
//temps du jeu 


void sauvegarder (savestate s, char * nomfichier) 
{

FILE* saVe = NULL;
    saVe = fopen(nomfichier,"wb");
 
 if(saVe != NULL) {
 
 fwrite( &s, sizeof(savestate), 1, saVe);
 
                  
                  }
                 
  fclose(saVe);
 
}
int charger (savestate *s, char * nomfichier)
{

FILE* saVe = NULL; 
saVe = fopen(nomfichier,"rb");
if(saVe != NULL) {

fread(&(*s), sizeof(savestate), 1, saVe);


            printf("test ahawa %d  %d  %d",s->level,s->time,s->perso);      
                 }
fclose(saVe);
return 0; 
                 
}



void initenemy2(es *e)
{
	e->imgEnemy = IMG_Load ("drone.png");
	e->posEN.x = 1450;
	e->posEN.y = 350;
	e->posEN.w = 156;
	e->posEN.h = 156;
	e->posSprit.x = 0;
	e->posSprit.y = 785;
	e->posSprit.w = 156;
	e->posSprit.h = 156;
	e->direct = 0;
}

void initenemy3(es *e)
{
	e->imgEnemy = IMG_Load ("drone.png");
	e->posEN.x = 2000;
	e->posEN.y = 520;
	e->posEN.w = 156;
	e->posEN.h = 156;
	e->posSprit.x = 0;
	e->posSprit.y = 785;
	e->posSprit.w = 156;
	e->posSprit.h = 156;
	e->direct = 0;
}





void moveIA(SDL_Rect a, es *e)
{
	/*if(e->posEN.x > a.x)
	{
		e->direct = 1;
		e->posSprit.y = 630;
	}
	else
	{
		if (e->posEN.x < a.x) 
		{
			e->direct = 0;
			e->posSprit.y = 785;
		}
	}*/

	if(e->posEN.y > a.x)
	{
		e->direct = 1;
		e->posSprit.y = 630;
	}
	else
	{
		if (e->posEN.y < a.x) 
		{
			e->direct = 0;
			e->posSprit.y = 785;
		}
	}
	if (e->direct == 0)
		e->posEN.x+=10;
	else
		e->posEN.x-=10;

}





void deplacerdrone(es *e)
{
	if(e->posEN.y > 600)
	{
		e->direct = 1;
		e->posSprit.y = 785;
	}
	else
	{
		if (e->posEN.y < 100) 
		{
			e->direct = 0;
			e->posSprit.y = 785;
		}
	}
	if (e->direct == 0)
		e->posEN.y+=10;
	else
		e->posEN.y-=10;	
}




void afficherTemps (int temps, SDL_Surface *screen)
{
        if (temps>=1000)
	temps=temps/1000;
	TTF_Font *fontTest=TTF_OpenFont("college.ttf",50);
	SDL_Color colortime={255,255,255};
	char timeText[20];
	sprintf(timeText,"time: %d",temps);
	SDL_Surface *time;
	time=TTF_RenderText_Blended(fontTest,timeText,colortime);
	
	
	SDL_Rect timepose;
	timepose.x=50;
	timepose.y=-10;
	SDL_BlitSurface(time,NULL,screen,&timepose);
	SDL_FreeSurface(time);
        TTF_CloseFont(fontTest);
	
}
void initTemps(Temps * temps, SDL_Surface *screen ){


temps->font0=TTF_OpenFont("college.ttf",30);
temps->font1=TTF_OpenFont("college.ttf",20);

//color chrono
temps->colorChrono.r=255;
temps->colorChrono.g=255;
temps->colorChrono.b=255;

//color msg
temps->colorMsg.r=255;
temps->colorMsg.g=255;
temps->colorMsg.b=255;


temps->msg=NULL;
temps->PositionMsg.x=screen->w-(screen->w/3)-50;
temps->PositionMsg.y=0;

temps->chrono=NULL;
temps->PositionChrono.x=screen->w-(screen->w/3)-50;
temps->PositionChrono.y=30;

}

//AFFICHERTEMPS


int afficher_temps(Temps *temps, int duree_en_seconde, SDL_Surface *screen){

int duree=0;

char timeText[20];
sprintf(timeText,"%d%c%d",(duree_en_seconde-1-(SDL_GetTicks()/1000))/60,':',(duree_en_seconde-1-(SDL_GetTicks()/1000))%60);
temps->chrono=TTF_RenderText_Blended(temps->font0,timeText,temps->colorChrono);
temps->msg=TTF_RenderText_Blended(temps->font1,"time left:",temps->colorMsg);

duree=SDL_GetTicks()/1000;

if(duree<duree_en_seconde){

 SDL_BlitSurface(temps->chrono, NULL, screen, &temps->PositionChrono);
 SDL_BlitSurface(temps->msg, NULL, screen, &temps->PositionMsg);

return 0;
}

return 1; 

}
void afficherscore (float score, SDL_Surface *screen)
{
        
	TTF_Font *fontTest=TTF_OpenFont("college.ttf",50);
	SDL_Color colortime={255,255,255};
	char timeText[20];
	sprintf(timeText,"score: %f",score);
	SDL_Surface *time;
	time=TTF_RenderText_Blended(fontTest,timeText,colortime);
	
	
	SDL_Rect timepose;
	timepose.x=300;
	timepose.y=-10;
	SDL_BlitSurface(time,NULL,screen,&timepose);
	SDL_FreeSurface(time);
        TTF_CloseFont(fontTest);
	
}
//collision perfect pixel 

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y)
{
    	SDL_Color color;
    	Uint32 col = 0;
    	

        	char *pPosition = (char *)pSurface->pixels;
	
       		pPosition += (pSurface->pitch * y);

        	pPosition += (pSurface->format->BytesPerPixel * x);

        	memcpy(&col, pPosition, pSurface->format->BytesPerPixel);

   
   	 SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
   	 return (color);
}
//rima +
int collisionmap(SDL_Surface *masque, SDL_Rect posPerso, int det)
{
    SDL_Color col, col2, col3;

    if (det == 1) // droit
    {
        col = GetPixel(masque, posPerso.x + 150, posPerso.y);
        col2 = GetPixel(masque, posPerso.x + 150, posPerso.y+75);
        col3 = GetPixel(masque, posPerso.x +150, posPerso.y+150);
    }
    else if (det == 0) // gauche
    {
        col = GetPixel(masque, posPerso.x , posPerso.y );
        col2 = GetPixel(masque, posPerso.x , posPerso.y + 75);
        col3 = GetPixel(masque, posPerso.x , posPerso.y + 150);
    }
    else if (det == 2) // haut
    {
        col = GetPixel(masque, posPerso.x, posPerso.y );
        col2 = GetPixel(masque, posPerso.x+75, posPerso.y );
        col3 = GetPixel(masque, posPerso.x+150, posPerso.y );
    }
    else if (det == 3) // down
    {
        col = GetPixel(masque, posPerso.x , posPerso.y+150);
        col2 = GetPixel(masque, posPerso.x + 75, posPerso.y+150 );
        col3 = GetPixel(masque, posPerso.x + 150, posPerso.y + 150);
    }

    if (col.r ==0 && col.g ==0&& col.b == 0)
        return 1;
    else if (col2.r ==0 && col2.g ==0 && col2.b ==0)
        return 1;
    else if (col3.r ==0 && col3.g == 0 && col3.b ==0)
        return 1;
    else
        return 0;
}

void initialiser_mini_map(minimap*m)
{	
	m->map=IMG_Load("map1.png");
	m->gps=IMG_Load("gps.png");

	m->pos_map.x=300; 
	m->pos_map.y=90;
	
	
}
//rima +
void initialiser_mini_map3(minimap*m3)
{	
	m3->map=IMG_Load("map3.png");
	m3->gps=IMG_Load("gps.png");

	m3->pos_map.x=300; 
	m3->pos_map.y=90;
	
} 

void initialiser_mini_map2(minimap*m2)
{	
	m2->map=IMG_Load("map2.png");
	m2->gps=IMG_Load("gps.png");

	m2->pos_map.x=300; 
	m2->pos_map.y=90;
	
} 


//rima modification 
void MAJMinimap(SDL_Rect pos_perso, minimap *m, SDL_Rect camera, int redimensionnement,Objet *backg) {
   
    SDL_Rect posJoueurABS = {pos_perso.x + camera.x, pos_perso.y + camera.y, pos_perso.w, pos_perso.h};
   
    SDL_Rect pos_gps = {(posJoueurABS.x - camera.x) * redimensionnement / 100, (posJoueurABS.y - camera.y) * redimensionnement / 100, pos_perso.w, pos_perso.h};
    
    m->pos_gps = pos_gps;
    
    m->pos_gps.x += m->pos_map.x;
    m->pos_gps.y += m->pos_map.y;
}


void afficher_minimap(minimap m ,SDL_Surface * screen )
{
    SDL_BlitSurface(m.map, NULL, screen, &m.pos_map);
    SDL_BlitSurface(m.gps, NULL, screen ,&m.pos_gps);
} 

void liberer( minimap m)
{
	SDL_FreeSurface(m.map);
	SDL_FreeSurface(m.gps);
}


void initPerso(personnage *p){

p->sens=1;
p->imgperso = IMG_Load("rect2.png");
p->position_personnage.x=0;
p->position_personnage.y=520;

p->crouch=0;

p->vie=3; 	
p->posSprit.x=0;
p->posSprit.y=320;	
p->posSprit.w=150;
p->posSprit.h=150;	

p->up=0;


p->pos_score.x=600;
p->pos_score.y=30;

p->posrel.x = -50;  
p->posrel.y = 0;


p->vitesse=0; 
p->acceleration=0;

}

void afficher_personnage(personnage p,SDL_Surface *ecran)
{
  SDL_BlitSurface(p.imgperso,&p.posSprit,ecran,&p.position_personnage);
}


void animerPerso (int action,personnage* p){

switch(action){

case 1:

p->posSprit.y =1260;
if(p->crouch==0){
p->posSprit.x = p->posSprit.x+156; 
if(p->posSprit.x>=450)
p->posSprit.x=450;
}else
{p->crouch=1;
p->posSprit.x=0;
}
break;
case 2:
p->crouch=0;
 if(p->sens==1){
p->posSprit.y=150;

if(p->posSprit.x>900) 
{
p->posSprit.x=0;  
}
else 
p->posSprit.x = p->posSprit.x+156; 
}
else if(p->sens==0){

p->posSprit.y =0;

if(p->posSprit.x>900) 
{
p->posSprit.x=0;  
}
else 
p->posSprit.x = p->posSprit.x+156; 
}
break;




case 4:
p->crouch=0;
p->posSprit.y =779;

if(p->posSprit.x>=1200) 
{
p->posSprit.x=0;  
}
else 
p->posSprit.x = p->posSprit.x+156; 
break;

case 5:
p->crouch=0;
p->posSprit.y =630;

if(p->posSprit.x>=1200) 
{
p->posSprit.x=0;  
}
else 
p->posSprit.x = p->posSprit.x+156; 
break;




case 6:
p->posSprit.y =779;
p->posSprit.x=0;  
break;

case 8:
p->posSprit.y =630;
p->posSprit.x=0;  
break;



}
}
void deplacerPerso (personnage *p,int action,Uint32 dt){



if((action==4) &&(p->position_personnage.x<500)&&(p->vitesse>=0))
p->position_personnage.x +=(p->vitesse) *dt;

if((action==5) &&(p->position_personnage.x>30)&&(p->vitesse>=0))
p->position_personnage.x -=(p->vitesse) *dt;




}
void deplacerPerso1 (personnage *p,int action,Uint32 dt){



if((action==4) &&(p->position_personnage.y<550)&&(p->vitesse>=0))
p->position_personnage.y +=(p->vitesse) *dt;

if((action==5) &&(p->position_personnage.y>30)&&(p->vitesse>=0))
p->position_personnage.y -=(p->vitesse) *dt;
if((action==2) &&(p->position_personnage.x<850)&&(p->vitesse>=0))
p->position_personnage.x +=(p->vitesse) *dt;





}




void vitesse_perso(personnage *p,int action,Uint32 dt){

(p->vitesse)+=(p->acceleration)*dt;

switch (action){ 
case 4:
if((p->vitesse)<1)
 p->acceleration+=0.001;
break;

case 5:
if((p->vitesse)<1)
 p->acceleration+=0.001;
break;


case 6: 
if((p->vitesse)>0.1)
(p->acceleration)-=0.005;
break;

case 8: 
if((p->vitesse)>0.1)
(p->acceleration)-=0.005;
break;
}

if((p->vitesse)>0.5)
p->vitesse=0.5;
if((p->vitesse)<0.1)
p->vitesse=0.1;

}
void Saute(personnage *p,int action){

if((p->up==0)&&(p->position_personnage.y>380))
		p->position_personnage.y-=70;
else if ((p->up==0)&&(p->position_personnage.y==380))
p->up=1;



if((p->up==1)&&(p->position_personnage.y<520))
p->position_personnage.y+=70;
else if ((p->up==1)&&(p->position_personnage.y==520))
p->up=0;



if(p->sens==1)
p->position_personnage.x +=50;

if(p->sens==0)
p->position_personnage.x -=50;
}

void mis_a_jour(personnage *p,int *action,int *att,int *jum,int *retl,int *retr) {

switch(*action){
case 1:
	(*jum)=0;
	(*att)=0;
	(*retr)=0;
	(*retl)=0;
break;

case 2:
	(*att)=0;
	(*retr)=0;
	(*retl)=0;
	(*jum)++;

break;



case 4:
	(*jum)=0;
	(*att)=0;
	(*retr)=0;
	(*retl)=0;
	p->sens=1;

break;

case 5:
	(*jum)=0;
	(*att)=0;
	(*retr)=0;
	(*retl)=0;
	p->sens=0;

break;



case 6:
retr++;
break;


case 8:
retr--;
break;

}


}
void liberer_perso(personnage *p){
SDL_FreeSurface(p->imgperso);
}




////////////////////////////////////////////////////////////
void initenemy(es *e)
{
	e->imgEnemy = IMG_Load ("drone.png");
	e->posEN.x = 1000;
	e->posEN.y = 520;
	e->posEN.w = 156;
	e->posEN.h = 156;
	e->posSprit.x = 0;
	e->posSprit.y = 785;
	e->posSprit.w = 156;
	e->posSprit.h = 156;
	e->direct = 0;
}
void initenemy1(es *e)
{
	e->imgEnemy = IMG_Load ("drone.png");
	e->posEN.x = 500;
	e->posEN.y = 320;
	e->posEN.w = 156;
	e->posEN.h = 156;
	e->posSprit.x = 0;
	e->posSprit.y = 785;
	e->posSprit.w = 156;
	e->posSprit.h = 156;
	e->direct = 0;
}

void afficherenemy(es e,SDL_Surface *screen)
{
	SDL_BlitSurface(e.imgEnemy,&e.posSprit,screen,&e.posEN);
}

void animerenemy(es *e)
{
	switch(e->direct)
	{
		case 0 : 
			if(e->posSprit.x >= 1200)
				e->posSprit.x = 0;
			else
				e->posSprit.x = e->posSprit.x + e->posSprit.w;
			break;
		case 1 : 
			if(e->posSprit.x >= 1200)
				e->posSprit.x = 0;
			else
				e->posSprit.x = e->posSprit.x + e->posSprit.w;
			break;
	}
}

void deplacer(es *e)
{
	if(e->posEN.x > 500)
	{
		e->direct = 1;
		e->posSprit.y = 630;
	}
	else
	{
		if (e->posEN.x < 100) 
		{
			e->direct = 0;
			e->posSprit.y = 785;
		}
	}
	if (e->direct == 0)
		e->posEN.x+=10;
	else
		e->posEN.x-=10;	
}

int collisionBox(SDL_Rect a, SDL_Rect b)
{ 
    if(a.x+a.h<b.x || a.x>b.x+b.w ||a .y+a.h<b.y || a.y>b.y+b.h)
        return 0;
        else 
        return 1;
}
void initialiser_audiobref(Mix_Chunk *bref){
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) ;
	bref=Mix_LoadWAV("bref.wav");
	Mix_PlayChannel(-1,bref,0);
	if(bref==NULL) printf("%s",SDL_GetError());}
	
void liberer_audiobref(Mix_Chunk *bref){
	Mix_FreeChunk(bref);} 




/////////////////////////////////////////////////////////////////////////////////////////
void init(Objet *backg  ) 
{
  SDL_WM_SetCaption("warriors", NULL);

  backg->img=IMG_Load("backg.png") ;
  backg->pos.x=0 ;
  backg->pos.y=0 ;
  
  

}
void init1(Objet *backg  ) 
{
  SDL_WM_SetCaption("level1", NULL);

  backg->img=IMG_Load("backglvl1.png") ;
  backg->pos.x=0 ;
  backg->pos.y=0 ;
  
  

}

void init2(Objet *backg  ) 
{
  SDL_WM_SetCaption("level2", NULL);

  backg->img=IMG_Load("level2.png") ;
  backg->pos.x=0 ;
  backg->pos.y=0 ;
  
  

}

void setup (SDL_Surface *screen, Objet *backg )
{
  SDL_BlitSurface(backg->img,NULL,screen, &(backg->pos));

  SDL_Flip(screen) ;
}



void scrolling_Right(SDL_Surface *screen , Objet *backg)
{
 if (backg->pos.x<=4000)
   backg->pos.x+=30;

   //SDL_BlitSurface(backg->img,&(backg->pos),screen, NULL);
}

void scrolling_Left(SDL_Surface*screen , Objet *backg)
{
 if (backg->pos.x>=0)
   backg->pos.x-=30 ;
 //SDL_BlitSurface(backg->img,&(backg->pos),screen, NULL);  
}
void eventt(SDL_Surface *screen ,Objet *backg,int *running )
{
 SDL_Event event;



 SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *running = 0;
            break;
            case SDL_KEYDOWN:

               switch(event.key.keysym.sym)

                  {
                   case SDLK_ESCAPE: // Flèche droite
            	
                *running = 0;
                          

                     break;

                     case SDLK_RIGHT: // Flèche droite
            	
                          scrolling_Right(screen ,backg) ;

                          SDL_Flip(screen);
                          

                     break;

                     case SDLK_LEFT: // Flèche gauche
                          scrolling_Left (screen ,backg) ;

                          SDL_Flip(screen);
                          

                     break;
              

                  }

            break;    
        }

}


void free_back(Objet *backg,Mix_Music *musique)
{


 SDL_FreeSurface (backg->img) ;
 Mix_FreeMusic(musique); //Libération de la musique
   Mix_CloseAudio(); //Fermeture de l'API

 SDL_Quit () ;

}//




//////////////////////////////////////////////////////////////////////////////
void init_image_bckg(image *mbackg){
mbackg->img = IMG_Load(mbackg->url);
	if(mbackg->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	mbackg->pos1.x=0;
	mbackg->pos1.y=0;
	mbackg->pos2.x=0;
	mbackg->pos2.y=0;
	mbackg->pos2.w=SCREEN_W;
	mbackg->pos2.h=SCREEN_H;
}



void init_image1(image *image){
image->img= IMG_Load(image->url);
	if(image->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	image->pos2.h=144;
	image->pos2.w=152;
	image->pos1.x=0;
	image->pos1.y=0;
}
void init_image2(image *image){
image->img= IMG_Load(image->url);
	if(image->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	image->pos2.h=100;
	image->pos2.w=100;
	image->pos1.x=10;
	image->pos1.y=0;
}
void init_image3(image *image){
image->img= IMG_Load(image->url);
	if(image->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	image->pos2.h=103;
	image->pos2.w=100; 
	image->pos1.x=0;
	image->pos1.y=0;
}
void init_image_lose(image *image){
image->img= IMG_Load(image->url);
	if(image->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	image->pos2.h=184;
	image->pos2.w=184;
	image->pos1.x=307;
	image->pos1.y=20;
}
void init_image_win(image *image){
image->img= IMG_Load(image->url);
	if(image->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	image->pos2.h=500;
	image->pos2.w=500;
	image->pos1.x=307;
	image->pos1.y=20;
}

void afficher_image_bckg(image imge , SDL_Surface *screen){
SDL_BlitSurface(imge.img , &imge.pos2, screen ,&imge.pos1);}



void afficher_image(image imge , SDL_Surface *screen){
SDL_BlitSurface(imge.img , &imge.pos2, screen ,&imge.pos1);}

void init_audio(Mix_Music *music){
if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
	    printf("Error: Unable to open audio: %s\n", Mix_GetError());
	return ;}
	music=Mix_LoadMUS("Bird.mp3");
	
	Mix_PlayMusic(music,-1);
	Mix_VolumeMusic(MIX_MAX_VOLUME);}
	
void liberer_image(image imge){
SDL_FreeSurface(imge.img);}

void liberer_audio(Mix_Music *music){
	Mix_FreeMusic(music);} 

void init_txt(texte *txte){
	TTF_Init();
	txte->police = TTF_OpenFont("Roman.ttf",50);
	txte->color_txt.r=0;
	txte->color_txt.g=255;
	txte->color_txt.b=255;
	txte->pos_txt.x=420;
	txte->pos_txt.y=30;}
	
void init_txtr(texte *txte){
	TTF_Init();
	txte->police = TTF_OpenFont("Roman.ttf",50);
	txte->color_txt.r=50;
	txte->color_txt.g=77;
	txte->color_txt.b=255;
	txte->pos_txt.x=300;
	txte->pos_txt.y=600;}
	
void init_txtq(texte *txte){
	TTF_Init();
	txte->police = TTF_OpenFont("Roman.ttf",50);
	txte->color_txt.r=255;
	txte->color_txt.g=255;
	txte->color_txt.b=255;
	txte->pos_txt.x=200;
	txte->pos_txt.y=130;}
void init_txta1(texte *txte){
	TTF_Init();
	txte->police = TTF_OpenFont("Roman.ttf",50);
	txte->color_txt.r=255;
	txte->color_txt.g=255;
	txte->color_txt.b=255;
	txte->pos_txt.x=200;
	txte->pos_txt.y=230;}
void init_txta2(texte *txte){
	TTF_Init();
	txte->police = TTF_OpenFont("Roman.ttf",50);
	txte->color_txt.r=255;
	txte->color_txt.g=255;
	txte->color_txt.b=255;
	txte->pos_txt.x=200;
	txte->pos_txt.y=330;}
void init_txta3(texte *txte){
	TTF_Init();
	txte->police = TTF_OpenFont("Roman.ttf",50);
	txte->color_txt.r=255;
	txte->color_txt.g=255;
	txte->color_txt.b=255;
	txte->pos_txt.x=200;
	txte->pos_txt.y=430;}
void afficher_txt(SDL_Surface *screen , texte txte){
	txte.txt=TTF_RenderText_Blended(txte.police,"  RIDDLE TIME",txte.color_txt);
	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);}
void afficher_txtq(SDL_Surface *screen , texte txte){
	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);}
void afficher_txta1(SDL_Surface *screen , texte txte){

	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);}
void afficher_txta2(SDL_Surface *screen , texte txte){

	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);}
void afficher_txta3(SDL_Surface *screen , texte txte){

	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);}
void afficher_txtr(SDL_Surface *screen , texte txte){
	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);}
	
void liberer_txt(texte txte){
	TTF_CloseFont (txte.police);
	TTF_Quit();} 	
/////////////////////////////////////////////////////////////////////////////
void init_menu_back(image *mbackg){
	
	mbackg->img = IMG_Load(mbackg->url);
	if(mbackg->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	mbackg->pos1.x=0;
	mbackg->pos1.y=0;
	mbackg->pos2.x=0;
	mbackg->pos2.y=0;
	mbackg->pos2.w=SCREEN_W;
	mbackg->pos2.h=SCREEN_H;
}
void init_boutton1(image *b1){
	b1->url="PLAY.png";
	b1->img= IMG_Load(b1->url);
	if(b1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	(*b1).pos2.h=100;
	b1->pos2.w=250;
	b1->pos1.x=(SCREEN_W-b1->pos2.w)/2+30;
	b1->pos1.y=(SCREEN_H-b1->pos2.h)/4;
}
void init_boutton_mute(image *b1){
	
	b1->img= IMG_Load(b1->url);
	if(b1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	(*b1).pos2.h=100;
	b1->pos2.w=250;
	b1->pos1.x=400;//(SCREEN_W-b1->pos2.w)/2+10;
	b1->pos1.y=280;//(SCREEN_H-b1->pos2.h)/2+25;
}
void init_boutton_mutenon(image *b1){
	
	b1->img= IMG_Load(b1->url);
	if(b1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	(*b1).pos2.h=100;
	b1->pos2.w=250;
	b1->pos1.x=610;//(SCREEN_W-b1->pos2.w)/2+10;
	b1->pos1.y=280;//(SCREEN_H-b1->pos2.h)/2+25;
}

void init_bouttonson(image *b1){
	
	b1->img= IMG_Load(b1->url);
	if(b1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	(*b1).pos2.h=110;
	b1->pos2.w=500;
	b1->pos1.x=(SCREEN_W-b1->pos2.w)/2+30;
	b1->pos1.y=(SCREEN_H-b1->pos2.h)/4;
}
void init_boutton2o(image *b1){
	b1->url="FULLSCREEN_WINDOWED.png";
	b1->img= IMG_Load(b1->url);
	if(b1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	(*b1).pos2.h=100;
	b1->pos2.w=250;
	b1->pos1.x=(SCREEN_W-b1->pos2.w)/2+30;
	b1->pos1.y=(SCREEN_H-b1->pos2.h)/2+190;
}
void init_boutton2co(image *b1){
	b1->url="FULLSCREEN_WINDOWEDs.png";
	b1->img= IMG_Load(b1->url);
	if(b1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	(*b1).pos2.h=100;
	b1->pos2.w=250;
	b1->pos1.x=(SCREEN_W-b1->pos2.w)/2+30;
	b1->pos1.y=(SCREEN_H-b1->pos2.h)/2+190;
}



void init_boutton2(image *b2 , image* b1){
	b2->url="options.png";
	b2->img= IMG_Load(b2->url);
	if(b1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	b2->pos2.w=250;
	b2->pos2.h=100;
	b2->pos1.x=(SCREEN_W-b2->pos2.w)/2+30;
	b2->pos1.y=b1->pos1.y + b1->pos2.h/2 + 50;
}
void init_boutton3(image *b3,image *b2){
	b3->url="QUIT.png";
	b3->img= IMG_Load(b3->url);
	if(b3->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	b3->pos1.x=0;
	b3->pos1.y=0;
	b3->pos2.w=250;
	b3->pos2.h=100;
	b3->pos1.x=((SCREEN_W-b3->pos2.w)/2+30);
	b3->pos1.y=b2->pos1.y + b2->pos2.h/2 + 50;}



void init_bouttonc1(image *bc1){
	bc1->url="PLAYC.png";
	bc1->img= IMG_Load(bc1->url);
	if(bc1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	bc1->pos2.h=100;
	bc1->pos2.w=250;
	bc1->pos1.x=(SCREEN_W-bc1->pos2.w)/2+30;
	bc1->pos1.y=(SCREEN_H-bc1->pos2.h)/4;
}
void init_bouttonc1o(image *bc1){
	bc1->url="backs.png";
	bc1->img= IMG_Load(bc1->url);
	if(bc1->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	bc1->pos2.h=100;
	bc1->pos2.w=250;
	bc1->pos1.x=(SCREEN_W-bc1->pos2.w)/2+500;
	bc1->pos1.y=(SCREEN_H-bc1->pos2.h)/2+300;
}

void init_bouttonc2(image *bc2 , image* b1){
	bc2->url="optionsc.png";
	bc2->img= IMG_Load(bc2->url);
	if(bc2->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	bc2->pos2.w=250;
	bc2->pos2.h=100;
	bc2->pos1.x=(SCREEN_W-bc2->pos2.w)/2+30;
	bc2->pos1.y=b1->pos1.y + b1->pos2.h/2 + 50;
}
void init_bouttonc3(image *bc3,image *b2){
	bc3->url="QUITC.png";
	bc3->img= IMG_Load(bc3->url);
	if(bc3->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	bc3->pos1.x=0;
	bc3->pos1.y=0;
	bc3->pos2.w=250;
	bc3->pos2.h=100;
	bc3->pos1.x=((SCREEN_W-bc3->pos2.w)/2+30);
	bc3->pos1.y=b2->pos1.y + b2->pos2.h/2 + 50;;}



void afficher_menu(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , &imge.pos2, screen ,&imge.pos1);}
void afficher_play(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , &imge.pos2, screen ,&imge.pos1);}

void afficher_b1(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , NULL , screen , &imge.pos1);}




void afficher_b2(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , NULL , screen , &imge.pos1);}
	
void afficher_mute(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , NULL , screen , &imge.pos1);}




void afficher_b3(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , NULL , screen , &imge.pos1);}



void afficher_bc1(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , NULL , screen , &imge.pos1);}




void afficher_bc2(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , NULL , screen , &imge.pos1);}




void afficher_bc3(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , NULL , screen , &imge.pos1);}





void init_txtM(texte *txte){
	TTF_Init();
	txte->police = TTF_OpenFont("COMPANY.ttf",50);
	txte->color_txt.r=50;
	txte->color_txt.g=77;
	txte->color_txt.b=255;
	txte->pos_txt.x=420;
	txte->pos_txt.y=30;}
	
void afficher_txtM(SDL_Surface *screen , texte txte){
	txte.txt=TTF_RenderText_Blended(txte.police,"     ROBOTEX",txte.color_txt);
	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);}
	
	
void init_audioM(Mix_Music *music){
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
	    printf("Error: Unable to open audio: %s\n", Mix_GetError());
	return ;}
	music=Mix_LoadMUS("music.mp3");
	Mix_PlayMusic(music,-1);
	//Mix_VolumeChunk(chunk, 96);
	Mix_VolumeMusic(MIX_MAX_VOLUME/3.5);}
	
	
	
	

	
void initialiser_audiobrefM(Mix_Chunk *bref){
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) ;
	bref=Mix_LoadWAV("bref.wav");
	Mix_PlayChannel(-1,bref,0);
	if(bref==NULL) printf("%s",SDL_GetError());}
	
 

void init_option_back(image *mbackg){
	mbackg->url="option.png";
	mbackg->img = IMG_Load(mbackg->url);
	if(mbackg->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	mbackg->pos1.x=0;
	mbackg->pos1.y=0;
	mbackg->pos2.x=0;
	mbackg->pos2.y=0;
	mbackg->pos2.w=SCREEN_W;
	mbackg->pos2.h=SCREEN_H;
}
void init_play_back(image *mbackg){
	mbackg->url="playback.png";
	mbackg->img = IMG_Load(mbackg->url);
	if(mbackg->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	mbackg->pos1.x=0;
	mbackg->pos1.y=0;
	mbackg->pos2.x=0;
	mbackg->pos2.y=0;
	mbackg->pos2.w=SCREEN_W;
	mbackg->pos2.h=SCREEN_H;
}

void afficher_option(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , &imge.pos2, screen ,&imge.pos1);}

void init_boutton1o(image *b1o){
	b1o->url="back.png";
	b1o->img= IMG_Load(b1o->url);
	if(b1o->img==NULL){
		printf("error : %s \n",SDL_GetError());
		return  ;
	}
	(*b1o).pos2.h=100;
	b1o->pos2.w=250;
	b1o->pos1.x=(SCREEN_W-b1o->pos2.w)/2+500;
	b1o->pos1.y=(SCREEN_H-b1o->pos2.h)/2+300;
}
void afficher_b1o(image imge , SDL_Surface *screen){
	SDL_BlitSurface(imge.img , NULL , screen , &imge.pos1);}




void initenemyb1(es *e)
{
	e->imgEnemy = IMG_Load ("robot_2.png");
	e->posEN.x = 600;
	e->posEN.y = 520;
	e->posEN.w = 65;
	e->posEN.h = 156;
	e->posSprit.x = 0;
	e->posSprit.y = 785;
	e->posSprit.w = 156;
	e->posSprit.h = 156;
	e->direct = 0;
}

void afficherenemyb1(es e,SDL_Surface *screen)
{
	SDL_BlitSurface(e.imgEnemy,&e.posSprit,screen,&e.posEN);
}



void deplacerb1(es *e)
{
	if(e->posEN.x > 700)
	{
		e->direct = 1;
		e->posSprit.y = 630;
	}
	else
	{
		if (e->posEN.x < 400) 
		{
			e->direct = 0;
			e->posSprit.y = 785;
		}
	}
	if (e->direct == 0)
		e->posEN.x+=10;
	else
		e->posEN.x-=10;	
}


int collisionBoxb1(SDL_Rect a, SDL_Rect b)
{ 
    if(a.x+10<b.x || a.x>b.x+10 ||a .y+a.h<b.y || a.y>b.y+b.h)
        return 0;
        else 
        return 1;
}
int collisionBoxb2(SDL_Rect a, SDL_Rect b)
{ 
    if(a.x+20<b.x || a.x>b.x+20 ||a.y+20<b.y || a.y>b.y+20)
        return 0;
        else 
        return 1;
}



void initenemym(es *e)
{
	e->imgEnemy = IMG_Load ("spm.png");
	e->posEN.x = 400;
	e->posEN.y = 520;
	e->posEN.w = 156;
	e->posEN.h = 156;
	e->posSprit.x = 0;
	e->posSprit.y = 785;
	e->posSprit.w = 156;
	e->posSprit.h = 156;
	e->direct = 0;
}

void animerenemym(es *e)
{
	switch(e->direct)
	{
		case 0 : //droite
			if(e->posSprit.x >= 1200)
				e->posSprit.x = 0;
			else
				e->posSprit.x = e->posSprit.x + e->posSprit.w;
			break;
		case 1 : //gauche
			if(e->posSprit.x >= 1200)
				e->posSprit.x = 0;
			else
				e->posSprit.x = e->posSprit.x + e->posSprit.w;
			break;
	}
}


void moveIAm(SDL_Rect a, es *e)
{
	if(e->posEN.x > a.x)
	{
		e->direct = 1;
		e->posSprit.y = 630;
	}
	else
	{
		if (e->posEN.x < a.x) 
		{
			e->direct = 0;
			e->posSprit.y = 785;
		}
	}
	if (e->direct == 0)
		e->posEN.x+=5;
	else
		e->posEN.x-=5;

}



















	
	
	
	
	
	
	
