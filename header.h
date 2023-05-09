 #ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include<time.h>
#include <string.h>
#define weight 1214
#define height 680
#define SCREEN_W 1214
#define SCREEN_H 680

typedef struct {
int level;
int time ;
int perso;
int levl;
}savestate;
void sauvegarder (savestate s, char * nomfichier) ;
int charger (savestate *s, char * nomfichier) ;



typedef struct TEMPS
{

TTF_Font *font0,*font1;
SDL_Color colorChrono,colorMsg;
SDL_Surface *chrono,*msg;
SDL_Rect PositionChrono,PositionMsg;

}Temps;



typedef struct 
{
  SDL_Surface *img ;
  SDL_Rect pos ; 

}Objet;
typedef struct 
{
	SDL_Surface * map ; 
	SDL_Surface * robot [3];
	SDL_Surface * gps ; 

	SDL_Rect  pos_map ;
	SDL_Rect  pos_gps;

}minimap; 
void initialiser_mini_map(minimap * m);
void initialiser_mini_map2(minimap*m);
void initialiser_mini_map3(minimap*m); 
void MAJMinimap(SDL_Rect pos_perso, minimap *m, SDL_Rect camera, int redimensionnement,Objet *backg);
void afficher_minimap(minimap m ,SDL_Surface * screen );

void liberer(minimap m);
void initTemps(Temps * temps, SDL_Surface *screen);
void afficherTemps (int temps, SDL_Surface *screen);
int afficher_temps(Temps *temps, int duree_en_seconde, SDL_Surface *screen);
int collisionmap(SDL_Surface *masque, SDL_Rect position_personnage, int det);
void afficherscore (float score, SDL_Surface *screen);



//////////////////////////////////////////
typedef struct  personnage
{
	int vie;
	float vitesse;
        float acceleration;
	SDL_Rect position_personnage; 
	SDL_Rect posSprit;
	SDL_Surface *imgperso;
	float score;
	SDL_Rect pos_score;
        int sens;        
        int crouch;
        int up;
	SDL_Rect posrel;        
}personnage;

void initPerso(personnage *p);
void afficher_personnage(personnage p,SDL_Surface *ecran);
void animerPerso (int action,personnage* p);
void deplacerPerso (personnage *p,int action,Uint32 dt);
void Saute(personnage *p,int action);
void vitesse_perso(personnage *p,int action,Uint32 dt);
void mis_a_jour(personnage *p,int *action,int *att,int *jum,int *retl,int *retr);
void liberer_perso(personnage *p);



void init1(Objet *backg  );

int collisionBoxb2(SDL_Rect a, SDL_Rect b);

/////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	SDL_Surface *imgEnemy; 		
	
	SDL_Rect posEN,posSprit; 
	int direct; 
	 
}es;
void initenemy(es *e);
void afficherenemy(es e,SDL_Surface *screen);
void animerenemy(es *e);
void deplacer(es *e);
int collisionBox(SDL_Rect a, SDL_Rect b);
typedef struct
{
	SDL_Surface *img;	 
	SDL_Rect pos; 	
}background;
void initialiser_audiobref(Mix_Chunk *bref);
void liberer_audiobref(Mix_Chunk *bref);

/////////////////////////////////////////////////////////////////////




void init(Objet *backg  )  ;
void setup (SDL_Surface *screen, Objet *backg ) ;
void scrolling_Right (SDL_Surface *screen , Objet *backg) ;
void scrolling_Left (SDL_Surface*screen , Objet *backg) ;
void eventt(SDL_Surface *screen ,Objet *boat ,int *running) ;
void free_back(Objet *backg, Mix_Music *musique) ;




/////////////////////////////////////////////////////////////////////


typedef struct {
char quest[30];
char rep1[30];
char rep2[30]; 
char rep3[30];
int answer;

}enigme;

typedef struct {
	char *url;
	SDL_Rect pos1 ; 
	SDL_Rect pos2 ;
	SDL_Surface * img ;
}image;
typedef struct {
	SDL_Surface *txt;
	SDL_Rect pos_txt ;
	SDL_Colour color_txt;
	TTF_Font *police ;
	}texte;

void initenemy1(es *e);

void deplacerdrone(es *e);
void moveIA(SDL_Rect a, es *e);
void initenemy2(es *e);
void initenemy3(es *e);
void deplacerPerso1 (personnage *p,int action,Uint32 dt);

void init_image_bckg(image *mbackg);
void init_image1(image *image);
void init_image2(image *image);
void init_image3(image *image);
void init_image_lose(image *image);
void init_image_win(image *image);


void afficher_image_bckg(image imge , SDL_Surface *screen);
void afficher_image(image imge , SDL_Surface *screen);

void init_audio(Mix_Music *music);

void liberer_image(image imge);
void liberer_audio(Mix_Music *music);

////

void genererEnigme(enigme *e, char *nomfichier);
void afficherEnigme(enigme e, SDL_Surface * screen);

void init_txt(texte *txte);
void init_txtq(texte *txte);
void init_txta1(texte *txte);
void init_txta2(texte *txte);
void init_txta3(texte *txte);
void init_txtr(texte *txte);
void afficher_txt(SDL_Surface *screen , texte txte);
void afficher_txtq(SDL_Surface *screen , texte txte);
void afficher_txta1(SDL_Surface *screen , texte txte);
void afficher_txta2(SDL_Surface *screen , texte txte);
void afficher_txta3(SDL_Surface *screen , texte txte);
void afficher_txtr(SDL_Surface *screen , texte txte);
void liberer_txt(texte txte);
/////////////////////////////////////////////////////////////////////////////////////
void init_audioM(Mix_Music *music);
void init_menu_back(image *menu);
void init_play_back(image *backplay);
void init_option_back(image *option);
void init_boutton1(image *b1);
void init_boutton1o(image *b1o);
void init_boutton2o(image *b2o);
void init_bouttonson(image *b3o);

void init_boutton2co(image *b2co);

void init_boutton2(image *b2,image *b1);
void init_boutton3(image *b3,image *b2);

void init_bouttonc1(image *b1);
void init_bouttonc1o(image *bc1);
void init_bouttonc2(image *bc2,image *b1);
void init_bouttonc3(image *bc3,image *b2);


void init_boutton_mute(image *mute);
void init_boutton_mutenon(image *mute);

void afficher_menu(image imge , SDL_Surface *screen);
void afficher_play(image imge , SDL_Surface *screen);
void afficher_mute(image imge , SDL_Surface *screen);
void afficher_b1(image imge , SDL_Surface *screen);
void afficher_b1o(image imge , SDL_Surface *screen);
void afficher_b2(image imge , SDL_Surface *screen);

void afficher_b3(image imge , SDL_Surface *screen);

void afficher_option(image imge , SDL_Surface *screen);
void afficher_bc1(image imge , SDL_Surface *screen);

void afficher_bc2(image imge , SDL_Surface *screen);

void afficher_bc3(image imge , SDL_Surface *screen);

void liberer_image(image imge);

void init_audio3(Mix_Music *music);
void init_audio2(Mix_Music *music);
void init_audio1(Mix_Music *music);
void init_audio0(Mix_Music *music);

void liberer_audio(Mix_Music *music);
void initialiser_audiobref(Mix_Chunk *bref);
void liberer_audiobrefM(Mix_Chunk *bref);
void init_txtM(texte *txte);
void afficher_txtM(SDL_Surface *screen , texte txte);
void liberer_txt(texte txte);


void init2(Objet *backg  ) ;

void initenemyb1(es *e);
void afficherenemyb1(es e,SDL_Surface *screen);
void deplacerb1(es *e);
int collisionBoxb1(SDL_Rect a, SDL_Rect b);

void initenemym(es *e);
void moveIAm(SDL_Rect a, es *e);
void animerenemym(es *e);


#endif // HEADER_H_INCLUDED
