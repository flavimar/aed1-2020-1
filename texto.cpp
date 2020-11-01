#include <SDL.h>
#include <SDL_ttf.h>
SDL_Surface* screen;
SDL_Surface* fontSurface;
SDL_Color fColor;
SDL_Rect fontRect;

SDL_Event Event;

TTF_Font* font;

//Initialize the font, set to white
void fontInit(){
TTF_Init();
font = TTF_OpenFont("arial.ttf", 12);
fColor.r = 255;
fColor.g = 255;
fColor.b = 255;
}

//Print the designated string at the specified coordinates
void printF(char *c, int x, int y){
fontSurface = TTF_RenderText_Solid(font, c, fColor);
fontRect.x = x;
fontRect.y = y;
SDL_BlitSurface(fontSurface, NULL, screen, &fontRect);
SDL_Flip(screen);
}

int main(int argc, char** argv)
{
// Initialize the SDL library with the Video subsystem
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);

//Create the screen
screen = SDL_SetVideoMode(320, 480, 0, SDL_SWSURFACE);

//Initialize fonts
fontInit();

//Print to center of screen
printF("Hello World", screen->w/2 - 11*3, screen->h/2);

do {
// Process the events
while (SDL_PollEvent(&Event)) {
switch (Event.type) {

case SDL_KEYDOWN:
switch (Event.key.keysym.sym) {
// Escape forces us to quit the app
case SDLK_ESCAPE:
Event.type = SDL_QUIT;
break;

default:
break;
}
break;

default:
break;
}
}
SDL_Delay(10);
} while (Event.type != SDL_QUIT);

// Cleanup
SDL_Quit();

return 0;
}
