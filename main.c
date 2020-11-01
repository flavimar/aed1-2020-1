#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MOV 0.3
#define alturatela 720
#define larguratela 1280
int contx = 0;
int conty = 0;
time_t t;
typedef struct{
 	int x;
 	int y;
 	int largura;
 	int altura;
}Model;
typedef struct
{
	SDL_Rect a;
	int cor[3];
	int ativo;
}Objeto;
void call_render(SDL_Renderer*, SDL_Rect*);
int call_events(SDL_Rect*);
int gerarAlimento(SDL_Renderer*,Objeto*);
int colisaoAlimento(SDL_Renderer *renderer,Objeto *alimento,SDL_Rect *cobra);
Objeto* criaAlimento();
void inicializaAlimento(Objeto *alimento);
void inicializaCobra(Objeto *cobra);
void liberaAlimento(Objeto *alimento);
int main(int argc, char **argv){
   
	int flag;
 //Posicao inicial da cobra
	Objeto cobra;
	inicializaCobra(&cobra);
	Objeto *alimento = criaAlimento();
	inicializaAlimento(alimento);
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	SDL_Init(SDL_INIT_EVERYTHING);

	

	window = SDL_CreateWindow("SnakeC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, larguratela, alturatela, SDL_WINDOW_OPENGL);

	if(!window){
		SDL_Log("Erro na inicialização: %s", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer){
		SDL_Log("Erro ao cirar renderizacao! %s", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	SDL_Event event;

	flag = 0;

	 while(!flag){
	 	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	    SDL_RenderClear(renderer);	
		flag = call_events(&cobra.a);
		gerarAlimento(renderer, alimento);
		call_render(renderer, &cobra.a);
		colisaoAlimento(renderer,alimento,&cobra.a);
		SDL_Delay(10);
		SDL_RenderPresent(renderer);		
	}
    liberaAlimento(alimento);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void call_render(SDL_Renderer *renderer, SDL_Rect *modelo){

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, modelo);
	
	
}

void inicializaCobra(Objeto *cobra){
	cobra->a.x = 100;
	cobra->a.y = 100;
	cobra->a.w = 20;
	cobra->a.h = 20;
	cobra->cor[0] = 255;
	cobra->cor[1] = 0;
	cobra->cor[2] = 0;
	cobra->ativo = 1;
}

int call_events(SDL_Rect *cobra){

	int flag = 0;

	SDL_Event event;

	const Uint8 *state = SDL_GetKeyboardState(NULL);
    
	//printf("%ld ",sizeof(SDL_GetKeyboardState));

	while(SDL_PollEvent(&event)){

		if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)){
			flag = 1;
		}
	}
    
	if(state[SDL_SCANCODE_LEFT]){		
   		contx = -1;
   		conty = 0;
	}

	if(state[SDL_SCANCODE_RIGHT]){
   	  contx = 1;
   	  conty = 0;
   		
	}

	if(state[SDL_SCANCODE_UP]){
   		conty = -1;
   		contx = 0;
   		
	}

	if(state[SDL_SCANCODE_DOWN]){
   		conty = 1;
   		contx = 0;
	}
    if((cobra->x + cobra->w) >= larguratela)
      cobra->x = 1;
    if(cobra->x == 0)
      cobra->x = larguratela - cobra->w;
    if((cobra->y + cobra->h) >= alturatela)
      cobra->y = 1;
    if(cobra->y == 0)
      cobra->y = alturatela - cobra->h;
	cobra->x += contx;
	cobra->y += conty;
    //SDL_Log("%d %d %d",model->x + model->largura,model->y + model->altura,larguratela);
    

	return flag;
}
Objeto* criaAlimento(){
	Objeto *alimento = (Objeto*)malloc(sizeof(Objeto));
	if(alimento == NULL)
	  printf("Erro\n");
	return alimento;
}
void inicializaAlimento(Objeto *alimento){
   alimento->a.w = 20;
   alimento->a.h = 20;
   alimento->ativo = 0;
}
void liberaAlimento(Objeto *alimento){
   free(alimento);
}
int gerarAlimento(SDL_Renderer *renderer,Objeto *alimento){
    if(alimento->ativo == 0){
    srand((unsigned) time(&t));
    int x = (((rand() % (larguratela / 20)) + 1) * 20) - 20;
    int y = (((rand() % (alturatela / 20)) + 1)* 20) - 20;
    printf("%d %d\n",x,y);
    alimento->a.x = x;
    alimento->a.y = y;
    alimento->ativo = 1;
    }
        call_render(renderer,&alimento->a);
        //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        //SDL_RenderFillRect(renderer, &alimento->a);
	  
 }

 int colisaoAlimento(SDL_Renderer *renderer,Objeto *alimento,SDL_Rect *cobra){
 	int CobraMeioLar = cobra->x + cobra->w/2, CobraMeioAlt = cobra->y + cobra->w/2;
 	int AlimMaxLar = alimento->a.x + alimento->a.w, AlimMaxAlt = alimento->a.h + alimento->a.h;
    printf(" %d com %d // %d com %d\n",CobraMeioLar,(alimento->a.x + alimento->a.w),CobraMeioAlt,(alimento->a.y + alimento->a.h));

    if((CobraMeioLar >= alimento->a.x && CobraMeioLar <= (AlimMaxLar)) && (CobraMeioAlt >= alimento->a.y) && (CobraMeioAlt <= AlimMaxLar)){
         
    	printf("OIIIIIIIIIIOIIIIIIII\n");
    	inicializaAlimento(alimento);
        return 1;
    }
   return 0;
 }

