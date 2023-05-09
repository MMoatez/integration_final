#include "header.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
int main(int argc, char **argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Event event;

	SDL_Surface *screen = NULL ;
	Objet backg,backg1,wood,boat,backg2 ;
 	background back,exp;

	int running=1 ;	
	screen= SDL_SetVideoMode(1215, 680, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	int jimp=0;
	init(&backg) ;
//level 1 
	init1(&backg1) ;
	init2(&backg2) ;
	setup (screen,&backg) ;
	setup (screen,&backg1) ;
	setup (screen,&backg2) ;
	SDL_EnableKeyRepeat(10, 10);

/*  etat  */ 
	int etat;
	etat=0;
	es E1,E2,E3,Eb,Em;
	initenemyb1(&Eb);
	initenemym(&Em);
	
//minimap 
	 SDL_Rect camera = {0, 0, 1215, 680};
	int redimensionnement =17;
	minimap m ,m3,m2 ;
	SDL_Rect position_personnage ;
	initialiser_mini_map(&m);
	initialiser_mini_map2(&m2); 
	initialiser_mini_map3(&m3); 
	int det ;
	int temp;
	Temps temps ; 
	temp=0;
	int tempss;
	initTemps(&temps,screen );
        SDL_Surface *mask=IMG_Load("backgroundMasque1.png");

//// initialisation   MENU   /////
image loadback,backgr,imge0,imge1,imge2,imge3,imge4,lose,win,menu,saveload,backgmulti, b1, b2,b3,bc1,bc2,bc3,bc1o,b2o,b2co,bs0,bs1,bs2,bs3,son,backplay,mute,mutenon;
imge0.url="3.png";
loadback.url="loadback.png";
	imge1.url="1.png";
	imge2.url="2.png";
	imge3.url="0.png";
	imge4.url="4.png";
	backgr.url="ebckg.jpg";
	win.url="happy.png";
	lose.url="saad.png";
	backplay.url="playback.png";
	bs0.url="son0.png";
	bs1.url="son1.png";
	mute.url="mute.png";
	mutenon.url="mutenon.png";
	bs2.url="son2.png";
	bs3.url="son3.png";
	son.url=bs3.url;
	menu.url="background.png";
	backgmulti.url="playersback.png";
	saveload.url="save.png";
	image option,b1o;
	init_option_back(&option);
	init_menu_back(&menu);
	init_menu_back(&loadback);
	init_menu_back(&backgmulti);
	init_menu_back(&saveload);
	init_play_back(&backplay);

	int etatmenu;
	etatmenu=0;

	//intialisation des boutons  
	init_boutton1(&b1);
	init_boutton1o(&b1o);
	init_boutton2o(&b2o);
	init_boutton2co(&b2co);
	init_bouttonson(&bs0);
	init_bouttonson(&bs1);
	init_bouttonson(&bs2);
	init_bouttonson(&bs3);
	init_boutton2(&b2,&b1);

	init_boutton3(&b3,&b2);
	init_bouttonc1(&bc1);
	init_bouttonc1o(&bc1o);
	init_bouttonc2(&bc2,&b1);
	init_bouttonc3(&bc3,&b2);

	init_boutton_mute(&mute);
	init_boutton_mutenon(&mutenon);

	//music 
	Mix_Music *music = NULL;
	init_audio(music);
	int volume=MIX_MAX_VOLUME;
	Mix_PlayMusic(music, -1);
	Mix_Chunk *brefM = NULL;
	//Mix_VolumeChunk(chunk, 96);
	initialiser_audiobref(brefM);
	Mix_PlayChannel(-1, brefM , 0);
	texte txteM;
	init_txtM(&txteM);


	//enigme // 

	init_image_bckg(&backgr);
	init_image1(&imge0);
	init_image2(&imge1);
	init_image2(&imge3);
	init_image3(&imge2);
	init_image3(&imge4);
	init_image_win(&win);
	init_image_win(&lose);
	texte txte,question,answer1,answer2,answer3,rep;
	init_txt(&txte);
	int r=0,i,answer,timee,a,reponse;
	answer=4;
	reponse=1;
	timee=0;
	a=0;
	char *nomfichier="file.txt";
	char ch[50];
	enigme e;
	srand(time(NULL));
	r=random()%3;
	FILE *fp=NULL;
    	char buffer[255];
	fp=fopen(nomfichier,"r");
	if (fp == NULL) {
        printf("Error opening file.\n");}
	int line_num = 1;
	switch(r)
    {

    case 0:
    	fgets(buffer, 255, fp);
        strcpy(e.quest,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep1,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep2,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep3,buffer);
        e.answer=1;
        break;
    case 1:
    	while (line_num!=6) {
    	fgets(buffer, 255, fp);
    	line_num++;}
        if (line_num == 6){
        strcpy(e.quest,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep1,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep2,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep3,buffer);
        e.answer=2;}

        break;
    case 2:
        while (line_num!=10) {
    	fgets(buffer, 255, fp);
    	line_num++;}
        if (line_num == 10){
        strcpy(e.quest,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep1,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep2,buffer);
        fgets(buffer, 255, fp);
        strcpy(e.rep3,buffer);
        e.answer=3;}
        break;}
        fclose(fp);

        strcpy(ch,e.quest);
        question.txt=TTF_RenderText_Blended(txte.police,ch,txte.color_txt);
        strcpy(ch,e.rep1);
        answer1.txt=TTF_RenderText_Blended(txte.police,ch,txte.color_txt);
        strcpy(ch,e.rep2);
        answer2.txt=TTF_RenderText_Blended(txte.police,ch,txte.color_txt);
        strcpy(ch,e.rep3);
        answer3.txt=TTF_RenderText_Blended(txte.police,ch,txte.color_txt);
        init_txtq(&question);
	init_txta1(&answer1);
	init_txta2(&answer2);
	init_txta3(&answer3);
	rep.txt=TTF_RenderText_Blended(txte.police,"",txte.color_txt);
	init_txtr(&rep);

///entite secondaire ///
es E;
int cont = 1;
exp.img = IMG_Load ("");  // image enemy 
exp.pos.x = 200;
	exp.pos.y = 500;
	exp.pos.w = 150;
	exp.pos.h = 150;
initenemy(&E);
initenemy1(&E1);
initenemy2(&E2);
initenemy3(&E3);

 	Mix_Chunk *bref = NULL;
	initialiser_audiobref(bref);
	Mix_PlayChannel(-1, bref , 0);
////perso ///
personnage p;
p.score=0;
int showperso=0;
int action=0,att=0,jum=0,retl=0,retr=0,jump;
Uint32 dt, t_prev;
initPerso(&p);
p.vie=3;
int enigme;
enigme=0;
int lvl=1;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
savestate s;
char *nomfichierr="savegame";
int o=0;











int x ;












/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

  while(running){
//-----------------------menu----------------------------------
  switch (etat){
      case 0:

	Mix_VolumeMusic(volume);
	int x , w=0,y,v=0 ;
	switch(etatmenu){
	case 0:

 		afficher_menu(menu, screen);
		afficher_b1(b1, screen);
		afficher_b2(b2, screen);
		afficher_b3(b3, screen);

		SDL_GetMouseState(&x,&y);
		if( x <= 700  && x >= 570 && y <= 210 && y >= 155 ) {
			afficher_bc1(bc1, screen);
			}


		if( x <= 700  && x >= 570 && y <= 310 && y >= 255 ) {
			afficher_bc2(bc2, screen);
			}


		if( x <= 700  && x >= 570 && y <= 410 && y >= 355 ) {
				afficher_bc3(bc3, screen);
			}
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					etat=7;
					break;
				case SDL_KEYDOWN :
					if(event.key.keysym.sym==SDLK_ESCAPE){
						running=0;}
					break;
				case SDL_MOUSEMOTION :
					//int x , w=0,y;
		SDL_GetMouseState(&x,&y);

		if( x <= 700  && x >= 570 && y <= 210 && y >= 155 ) {

				w=1;

			}


		if( x <= 700  && x >= 570 && y <= 310 && y >= 255 ) {
				w=1;
			}


		if( x <= 700  && x >= 570 && y <= 410 && y >= 355 ) {
				w=1;
			}
			if (w==1 )
			{
				initialiser_audiobref(bref);

			}
			break;

			case SDL_MOUSEBUTTONDOWN:

					   if(event.button.button==SDL_BUTTON_LEFT  &&  event.motion.x <= 700&& event.motion.x >= 570 && event.motion.y <= 310 && event.motion.y >= 255) {

     					   etatmenu=1;

						//option
     				   }
     				  else if(event.button.button==SDL_BUTTON_LEFT && event.motion.x <= 700&& event.motion.x >= 570 && event.motion.y <= 210 && event.motion.y >= 155) {

						   etat=6;

                            //play
   						}



					   else if(event.button.button==SDL_BUTTON_LEFT &&  event.motion.x <= 700&& event.motion.x >= 570 && event.motion.y <= 410 && event.motion.y >= 355) {
     					  initialiser_audiobref(bref);
						  running=0;


    				   break;
			}
		}



		afficher_txtM(screen, txteM);
		SDL_Flip(screen);

	}
	break;





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////option

	case(1):
	afficher_menu(option ,screen);
	afficher_b1o(b1o, screen);
	afficher_b1o(b2o, screen);
	init_bouttonson(&son);
	afficher_b1(son, screen);
	afficher_mute(mute,screen);
	afficher_mute(mutenon,screen);


	SDL_GetMouseState(&x,&y);
		if( x >= 1007  && x <= 1200 && y >= 593 && y <= 686) {
			afficher_bc1(bc1o, screen);
			}
		if( x <= 700  && x >= 570 && y <= 576 && y >= 483 ) {
			afficher_bc1(b2co, screen);
			}
		if( x <= 523  && x >= 357 && y <= 210 && y >= 155 ) {
			afficher_bc1(bs1, screen);
			}
		if( x <= 689  && x >= 523 && y <= 210 && y >= 155 ) {
			afficher_bc1(bs2, screen);
			}
		if( x <= 855  && x >= 689 && y <= 210 && y >= 155 ) {
			afficher_bc1(bs3, screen);
			}
	while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					etat=7;
					break;
				case SDL_KEYDOWN :
					if(event.key.keysym.sym==SDLK_m){
					etatmenu=0;
					}
					break;
				case SDL_MOUSEMOTION :
				SDL_GetMouseState(&x,&y);

		if( x >= 1007  && x <= 1200 && y >= 593 && y <= 686) {

				w=1;

			}
		if( x <= 700  && x >= 570 && y <= 576 && y >= 483 ) {
				w=1;
			}
		if (w==1 )
			{
				initialiser_audiobref(bref);

			}
			break;

		case SDL_MOUSEBUTTONDOWN:
     				   if(event.button.button==SDL_BUTTON_LEFT && event.motion.x <= 1200&& event.motion.x >= 1007 && event.motion.y <= 686 && event.motion.y >= 539) {
     				   etatmenu=0;
     				   }
     				   if(event.button.button==SDL_BUTTON_LEFT && event.motion.x <= 523&& event.motion.x >= 357 && event.motion.y <= 210 && event.motion.y >=155) {
     				   son.url=bs1.url;
     				   volume=50;
     				   }
     				   if(event.button.button==SDL_BUTTON_LEFT && event.motion.x <= 689&& event.motion.x >= 523 && event.motion.y <= 210 && event.motion.y >=155) {
     				   son.url=bs2.url;
     				   volume=100;
     				   }
     				   if(event.button.button==SDL_BUTTON_LEFT && event.motion.x <= 855&& event.motion.x >= 689 && event.motion.y <= 210 && event.motion.y >=155) {
     				   son.url=bs3.url;
     				   volume=128;
     				   }
     				   if(event.button.button==SDL_BUTTON_LEFT && event.motion.x <= 580&& event.motion.x >= 400 && event.motion.y <= 450 && event.motion.y >=280) {
     				   son.url=bs3.url;
     				   volume=0;
     				   }
     				   if(event.button.button==SDL_BUTTON_LEFT && event.motion.x <= 790&& event.motion.x >= 610 && event.motion.y <= 450 && event.motion.y >=280) {
     				   son.url=bs3.url;
     				   volume=128;
     				   }




     				   if(event.button.button==SDL_BUTTON_LEFT && event.motion.x <= 700&& event.motion.x >= 570 && event.motion.y <= 576 && event.motion.y >= 483) {
     				   screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32,SDL_FULLSCREEN);
     				   }
     			break;

			}
			}
	SDL_Flip(screen);
		break;}

break;




	case (2):
	
	
	
	switch(reponse){
	case 1:
	while(timee<40&&reponse==1&&running==1){
	afficher_image_bckg(backgr,screen);
	afficher_txt(screen, txte);
	afficher_txtq(screen, question);
	afficher_txta1(screen, answer1);
	afficher_txta2(screen, answer2);
	afficher_txta3(screen, answer3);

	afficher_txtr(screen, rep);
	
	
	
	
	   
	
	
	
	
	switch (a){
	case (0):
	afficher_image(imge4,screen);
	break;
	case (1):
	afficher_image(imge1,screen);
	break;
	case (2):
	afficher_image(imge3,screen);
	break;
	case (3):
	afficher_image(imge3,screen);
	break;
	case (4):
	afficher_image(imge4,screen);
	break;
	}
	x=afficher_temps(&temps,15,screen);
	while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
					etat=7;
					break;

			case SDL_KEYDOWN :
					if(event.key.keysym.sym==SDLK_ESCAPE){
						running=0;}
					else if(event.key.keysym.sym==SDLK_a){
					answer=1;}
					else if(event.key.keysym.sym==SDLK_b){
					answer=2;}
					else if(event.key.keysym.sym==SDLK_c){
					answer=3;}

						break;}}
	if (e.answer==answer){
	rep.txt=TTF_RenderText_Blended(txte.police,"correct",txte.color_txt);
	reponse=2;
	p.score+=50;
				}
	else if(answer==1 || answer==2 || answer==3){
	rep.txt=TTF_RenderText_Blended(txte.police,"incorrect",txte.color_txt);
	reponse=3;
	}
	SDL_Delay(250);
	timee++;
	a++;
	if (a>4)
	a=0;

	SDL_Flip(screen);
	}
	if(running==1 && answer==4){
	timee=0;
	while(timee<10&&running==1){
	afficher_image_bckg(backgr,screen);

	rep.txt=TTF_RenderText_Blended(txte.police,"time is up",txte.color_txt);
	afficher_txtr(screen, rep);
	afficher_image(lose,screen);

	while(SDL_PollEvent(&event)) {
	switch(event.type) {
			case SDL_QUIT:
					etat=7;
					break;}}
	SDL_Delay(250);
	timee++;}
	initPerso(&p);
	if (lvl==3){
	etat=3;}
	else if (lvl==2){
	etat=5;
	}
	SDL_Flip(screen);}
	break;
	
	
	
	case 2:
	timee=0;
	while(timee<10&&reponse==2&&running==1){
	afficher_image_bckg(backgr,screen);
	afficher_txtr(screen, rep);
	afficher_image(win,screen);

	while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
					etat=7;
					break;}}
	SDL_Delay(250);
	timee++;
	
	SDL_Flip(screen);}
	initPerso(&p);
	if (lvl==3){
	etat=3;
	}
	else if (lvl==2){
	etat=5;
	}
 
	break;
	
	
	
	case 3://enigme 
	timee=0;
	while(timee<10&&reponse==3&&running==1){
	afficher_image_bckg(backgr,screen);
	afficher_txtr(screen, rep);
	afficher_image(lose,screen);

	while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
					etat=7;
					break;}}
					SDL_Delay(250);
	timee++;
	SDL_Flip(screen);}
	initPerso(&p);
	if (lvl==3){
	etat=3;}
	
	else if (lvl==2){
	etat=5;
	}
	break;}
	break;
	
	
	//////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	
	case 6:
	
	
	afficher_menu(backgmulti,screen);
	
	while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running=0;
					break;
				case SDL_KEYDOWN :
					if(event.key.keysym.sym==SDLK_s){
					etat=8;}
					break;
					}}
	
	SDL_Flip(screen);
	
	
	
	break;
	case 7:
	
	
	afficher_menu(saveload,screen);
	
	while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					etat=7;
					break;
				case SDL_KEYDOWN :
					if(event.key.keysym.sym==SDLK_a){
					sauvegarder (s,nomfichierr);
					running=0;}
					if(event.key.keysym.sym==SDLK_b){
					running=0;}
					break;
					}}
	
	SDL_Flip(screen);
	
	
	
	break;
	case 8:
	
	
	afficher_menu(loadback,screen);
	
	while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					etat=7;
					break;
				case SDL_KEYDOWN :
					if(event.key.keysym.sym==SDLK_a){
					o=charger(&s,nomfichierr);
					lvl=s.levl;
					etat=s.level;
					}
					if(event.key.keysym.sym==SDLK_b){
					etat=4;}
					break;
					}}
	
	SDL_Flip(screen);
	
	
	
	break;
	
	
	
	///////////////////////////////////////////////
	//////////////////////////////
	case 5:
	
      //eventt(screen ,&backg,&running  ) ;
      if(p.position_personnage.x>800){
      timee=0;
      p.score+=100;
      answer=4;
      lvl=3;
      reponse=1;
      etat=2;}
      afficher_minimap(m2,screen);
     /* afficher_minimap(m,screen);
      temp=SDL_GetTicks();
	afficherTemps(temp,screen);*/
	
      
      moveIA(p.position_personnage, &E);
		moveIA(p.position_personnage, &E1);
		moveIA(p.position_personnage, &E2);
		moveIA(p.position_personnage, &E3);
      if (collisionBoxb2(p.position_personnage,E.posEN)){
	printf("massiit");
	p.vie--;}
	else{
	printf("noooon");}
	printf("%dyyyyyyyyyyyy",p.vie);
	if (collisionBoxb2(p.position_personnage,E1.posEN)){
	printf("massiit");
	p.vie--;}
	else{
	printf("noooon");}
	printf("%dyyyyyyyyyyyy",p.vie);
	if (collisionBoxb2(p.position_personnage,E2.posEN)){
	printf("massiit");
	p.vie--;}
	else{
	printf("noooon");}
	printf("%dyyyyyyyyyyyy",p.vie);
	if (collisionBoxb2(p.position_personnage,E3.posEN)){
	printf("massiit");
	p.vie--;}
	else{
	printf("noooon");}
	printf("%dyyyyyyyyyyyy",p.vie);
	if (p.vie==0){
	action=8;
	etat=7;}
      
      
      
     
		//animerenemy(&E);
		deplacerdrone(&E);
		deplacerdrone(&E1);
		//SDL_Delay(100);
		if (collisionBox(p.position_personnage,E.posEN))
		{
			printf("cc");
			initialiser_audiobref(bref);
		}
		else
			printf("ss");
			SDL_PollEvent(&event);
		
		if (collisionBox(p.position_personnage,E1.posEN))
		{
			printf("cc");
			initialiser_audiobref(bref);
		}
		else
			printf("ss");
			SDL_PollEvent(&event);
		
		SDL_PollEvent(&event);
			switch(event.type) {
				case SDL_QUIT:
					etat=7;
					break;}
	t_prev=SDL_GetTicks();
while (SDL_PollEvent(&event)){


SDL_Flip(screen);}
dt=0;
do{
dt=SDL_GetTicks()-t_prev;
}while(dt<50);
//if (jum>2) jum=0;
//if (/*backg.pos.x<=4000 &&*/ action==4){
scrolling_Right(screen ,&backg2) ;
SDL_Flip(screen);//}
//if(action==5){
//scrolling_Left (screen ,&backg) ;
//SDL_Flip(screen);//}
temp=SDL_GetTicks();

SDL_BlitSurface(backg2.img,&(backg2.pos),screen, NULL);
afficher_minimap(m2,screen);
afficherenemy(E,screen);
afficherenemy(E1,screen);
afficherenemy(E2,screen);
afficherenemy(E3,screen);
afficherTemps(temp,screen);
afficherscore(p.score,screen);

MAJMinimap(p.position_personnage, &m,camera,redimensionnement,&backg2);
if (backg2.pos.x>4000){
	if (event.type==SDL_KEYDOWN ){
	if(event.key.keysym.sym==SDLK_RIGHT)
	action=2;}}
SDL_PollEvent(&event);
if (event.type==SDL_KEYDOWN ){
	switch(event.key.keysym.sym){


/*case SDLK_DOWN:
	action=1;
break;


case SDLK_UP:

	action=2;
	//jump=1;
	if(jum==0)
	p.posSprit.x=0;
while(jum<5){
	t_prev=SDL_GetTicks();
	dt=0;
		do{
		dt=SDL_GetTicks()-t_prev;
		}while(dt<80);

Saute(&p,action);
animerPerso (action,&p);
SDL_BlitSurface(backg.img,&(backg.pos),screen, NULL);
deplacer(&E);
deplacer(&E1);
afficher_minimap(m,screen);
afficherenemy(E,screen);
afficherenemy(E1,screen);
afficherTemps(temp,screen);
afficher_personnage(p,screen);

SDL_Flip(screen);

jum++;
}
break;*/




case SDLK_DOWN:
	action=4;

break;

case SDLK_UP:
	action=5;

break;


	}
}



	else if (event.type==SDL_QUIT){
		showperso=1;
		break;
		}


	else if (event.type==SDL_KEYUP){
		if((event.key.keysym.sym==SDLK_RIGHT) && (p.sens==1)){
			if(retr<3){
				action=6;
				}
		}
		if((event.key.keysym.sym==SDLK_LEFT) && (p.sens==0)){
			if(retl<3){
				action=8;
				}
		}
	}
s.level=etat;
s.time=temp;
s.perso=1;
s.levl=lvl;
/*if(jum==0)
	p.posSprit.x=0;
if (jump<6){


if(jum<5){
	t_prev=SDL_GetTicks();
	dt=0;
		do{
		dt=SDL_GetTicks()-t_prev;
		}while(dt<80);

Saute(&p,action);
SDL_Flip(screen);
jum++;
jump++;
}}
if(jum==5) jum=0;
*/
vitesse_perso(&p,action,dt);
deplacerPerso1 (&p,action,dt);
//if(jum<2)
//animerPerso (action,&p);
afficher_personnage(p,screen);
SDL_Flip(screen);
mis_a_jour(&p,&action,&att,&jum,&retl,&retr);
SDL_Flip(screen);


mis_a_jour(&p,&action,&att,&jum,&retl,&retr);

SDL_Flip(screen);
	
	
	break;


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
  case 4://lvl1   

        //eventt(screen ,&backg,&running  ) ;
      if(backg1.pos.x>4000){
      lvl=2;
      answer=4;
      timee=0;
      reponse=1;
      p.score=p.score+100;
      etat=2;}
      afficher_minimap(m,screen);
      temp=SDL_GetTicks();
	afficherTemps(temp,screen);
	afficherscore(p.score,screen);
	deplacerb1(&Eb);
	if (collisionBoxb1(p.position_personnage,Eb.posEN)){
	printf("massiit");
	p.vie--;}
	else{
	printf("noooon");}
	printf("%dyyyyyyyyyyyy",p.vie);
	if (p.vie==0){
	etat=7;}
      /*if(p.position_personnage.x>800){
      SDL_BlitSurface(exp.img,NULL,screen,&exp.pos);
		afficherenemy(E,screen);
		animerenemy(&E);
		deplacer(&E);
		SDL_Delay(100);
		if (collisionBox(p.position_personnage,E.posEN))
		{
			printf("cc");
			initialiser_audiobref(bref);
		}
		else
			printf("ss");
			SDL_PollEvent(&event);
		if ((event.type == SDL_QUIT)||(event.key.keysym.sym == SDLK_ESCAPE))
				cont = 0;

		}*/
		SDL_PollEvent(&event);
			switch(event.type) {
				case SDL_QUIT:
					etat=7;
					break;}
	t_prev=SDL_GetTicks();
	while (SDL_PollEvent(&event)){


		SDL_Flip(screen);}
	

	dt=0;
	do{
	 dt=SDL_GetTicks()-t_prev;
	}while(dt<50);
//if (jum>2) jum=0;
	if (/*backg.pos.x<=4000 &&*/ action==4){
	scrolling_Right(screen ,&backg1) ;
	SDL_Flip(screen);}
	if(action==5){
	scrolling_Left (screen ,&backg1) ;
	SDL_Flip(screen);}
	SDL_BlitSurface(backg1.img,&(backg1.pos),screen, NULL);
 	afficher_minimap(m,screen);
	temp=SDL_GetTicks();
	afficherenemyb1(Eb,screen);
	afficherTemps(temp,screen);
	afficherscore(p.score,screen);
	MAJMinimap(p.position_personnage, &m,camera,redimensionnement,&backg1);
	SDL_PollEvent(&event);
if (event.type==SDL_KEYDOWN ){
	switch(event.key.keysym.sym){


case SDLK_DOWN:
	action=1;
break;


case SDLK_UP:

	action=2;
	jimp=1;
	if(jum==0)
	p.posSprit.x=0;
while(jum<5){
	t_prev=SDL_GetTicks();
	dt=0;
		do{
		dt=SDL_GetTicks()-t_prev;
		}while(dt<80);

	Saute(&p,action);
	animerPerso (action,&p);
	if (/*backg.pos.x<=4000 &&*/ action==4){
	scrolling_Right(screen ,&backg1) ;
	SDL_Flip(screen);}
	if(action==5){
	scrolling_Left (screen ,&backg1) ;
	SDL_Flip(screen);}
	SDL_BlitSurface(backg1.img,&(backg1.pos),screen, NULL);
 	afficher_minimap(m,screen);
 	afficher_personnage(p,screen);
	temp=SDL_GetTicks();
	afficherenemyb1(Eb,screen);
	afficherTemps(temp,screen);
	afficherscore(p.score,screen);
	SDL_Flip(screen);
	

	jum++;
}
break;


case SDLK_RIGHT:
	if (backg1.pos.x!=-180){
	scrolling_Right(screen ,&backg1) ;
	action=4;
	}

break;

case SDLK_LEFT:
	if (collisionmap(mask,position_personnage,det)==0)
	action=5;

break;


	}
}

	else if (event.type==SDL_QUIT){
		showperso=1;
		break;
		}


	else if (event.type==SDL_KEYUP){
		if((event.key.keysym.sym==SDLK_RIGHT) && (p.sens==1)){
			if(retr<3){
				action=6;
				}
		}
		if((event.key.keysym.sym==SDLK_LEFT) && (p.sens==0)){
			if(retl<3){
				action=8;
				}
		}
	}
	s.level=etat;
s.time=temp;
s.perso=1;
s.levl=lvl;
/*if(jum==0)
	p.posSprit.x=0;
if (jump<6){


if(jum<5){
	t_prev=SDL_GetTicks();
	dt=0;
		do{
		dt=SDL_GetTicks()-t_prev;
		}while(dt<80);

Saute(&p,action);
SDL_Flip(screen);
jum++;
jump++;
}}
if(jum==5) jum=0;
*/
vitesse_perso(&p,action,dt);
deplacerPerso (&p,action,dt);
if(jum<2)
animerPerso (action,&p);
afficher_personnage(p,screen);
SDL_Flip(screen);
mis_a_jour(&p,&action,&att,&jum,&retl,&retr);
SDL_Flip(screen);


mis_a_jour(&p,&action,&att,&jum,&retl,&retr);

SDL_Flip(screen);
	
	
	break;

  
  case 3:
  ///lvl3///////////////

      //eventt(screen ,&backg,&running  ) ;
      if(backg.pos.x>=4000){
      reponse=1;
      answer=4;
      timee=0;
      p.score+=100;
      etat=2;}
      
      lvl=3;
      animerenemym(&Em);
      
      moveIAm(p.position_personnage, &Em);
      if (collisionBoxb1(p.position_personnage,Em.posEN)){
	printf("massiit");
	p.vie--;}
	else{
	printf("noooon");}
	printf("%dyyyyyyyyyyyy",p.vie);
	if (p.vie==0){
	action=8;
	etat=7;}
     /* afficher_minimap(m,screen);
      temp=SDL_GetTicks();
	afficherTemps(temp,screen);*/
      /*if(p.position_personnage.x>800){
      SDL_BlitSurface(exp.img,NULL,screen,&exp.pos);
		afficherenemy(E,screen);
		animerenemy(&E);
		deplacer(&E);
		SDL_Delay(100);
		if (collisionBox(p.position_personnage,E.posEN))
		{
			printf("cc");
			initialiser_audiobref(bref);
		}
		else
			printf("ss");
			SDL_PollEvent(&event);
		if ((event.type == SDL_QUIT)||(event.key.keysym.sym == SDLK_ESCAPE))
				cont = 0;

		}*/
		SDL_PollEvent(&event);
			switch(event.type) {
				case SDL_QUIT:
					etat=7;
					break;}
	t_prev=SDL_GetTicks();
while (SDL_PollEvent(&event)){


SDL_Flip(screen);}
dt=0;
do{
dt=SDL_GetTicks()-t_prev;
}while(dt<50);
//if (jum>2) jum=0;
if (/*backg.pos.x<=4000 &&*/ action==4){
scrolling_Right(screen ,&backg) ;
SDL_Flip(screen);}
if(action==5){
scrolling_Left (screen ,&backg) ;
SDL_Flip(screen);}
SDL_BlitSurface(backg.img,&(backg.pos),screen, NULL);
afficher_minimap(m3,screen);
afficherenemy(Em,screen);
temp=SDL_GetTicks();

afficherTemps(temp,screen);
afficherscore(p.score,screen);
MAJMinimap(p.position_personnage, &m3,camera,redimensionnement,&backg);
SDL_PollEvent(&event);
if (event.type==SDL_KEYDOWN ){
	switch(event.key.keysym.sym){


case SDLK_DOWN:
	action=1;
break;


case SDLK_UP:

	action=2;
	//jump=1;
	if(jum==0)
	p.posSprit.x=0;
while(jum<5){
	t_prev=SDL_GetTicks();
	dt=0;
		do{
		dt=SDL_GetTicks()-t_prev;
		}while(dt<80);

	Saute(&p,action);
	animerPerso (action,&p);
	if (/*backg.pos.x<=4000 &&*/ action==4){
	scrolling_Right(screen ,&backg) ;
	SDL_Flip(screen);}
	if(action==5){
	scrolling_Left (screen ,&backg) ;
	SDL_Flip(screen);}
	SDL_BlitSurface(backg.img,&(backg.pos),screen, NULL);
	afficher_minimap(m3,screen);
	afficher_personnage(p,screen);
	afficherenemy(Em,screen);
	temp=SDL_GetTicks();

afficherTemps(temp,screen);
afficherscore(p.score,screen);
	
	SDL_Flip(screen);

	jum++;
}
	
break;


case SDLK_RIGHT:
	action=4;

break;

case SDLK_LEFT:
	action=5;

break;


	}
}
	else if (event.type==SDL_QUIT){
		showperso=1;
		break;
		}


	else if (event.type==SDL_KEYUP){
		if((event.key.keysym.sym==SDLK_RIGHT) && (p.sens==1)){
			if(retr<3){
				action=6;
				}
		}
		if((event.key.keysym.sym==SDLK_LEFT) && (p.sens==0)){
			if(retl<3){
				action=8;
				}
		}
	}
	s.level=etat;
s.time=temp;
s.levl=lvl;
s.perso=1;
/*if(jum==0)
	p.posSprit.x=0;
if (jump<6){


if(jum<5){
	t_prev=SDL_GetTicks();
	dt=0;
		do{
		dt=SDL_GetTicks()-t_prev;
		}while(dt<80);

Saute(&p,action);
SDL_Flip(screen);
jum++;
jump++;
}}
if(jum==5) jum=0;
*/


vitesse_perso(&p,action,dt);
deplacerPerso (&p,action,dt);
if(jum<2)
animerPerso (action,&p);
afficher_personnage(p,screen);
SDL_Flip(screen);
mis_a_jour(&p,&action,&att,&jum,&retl,&retr);
SDL_Flip(screen);


mis_a_jour(&p,&action,&att,&jum,&retl,&retr);

SDL_Flip(screen);
	
	
	break;

	}


	}




liberer_image(menu);
	liberer_image(option);
	liberer_image(b1);
	
	liberer_image(b2);
	
	liberer_image(b3);
	liberer_image(bc2);
	liberer_image(bc3);
	liberer_image(bc1o);
	liberer_image(b2co);
	liberer_image(b1o);
	liberer_image(b2o);
	liberer_image(bs0);
	liberer_image(bs2);
	liberer_image(bs3);
	liberer_image(bc1);
	liberer_audio(music);
	liberer_audiobref(bref);
	liberer_txt(txte);
	
	TTF_Quit();
	SDL_Quit();
	
	liberer_audiobref(bref);

   	liberer_perso(&p);




    return 0;
}




