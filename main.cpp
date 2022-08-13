//
// linecode - cplusplus - SDL
// try drawing a line from dots
//

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

std::vector<int> pixelxy(int pixelnumber, int screenWidth)
{
   std::vector<int> result {};
   int resultx=0; 
   int resulty=0; 
    
   resulty=int(pixelnumber/screenWidth); 
   resultx=pixelnumber-(screenWidth*resulty); 
    
   result[0]=resultx; 
   result[1]=resulty; 
  
   return result; 
 }
 
std::vector<int> width_and_height(int startPos,int endPos, int screenWidth)
{
 
   std::vector<int> result {};
    
   int thisHeight=0; 
   int newEndPos=endPos-startPos; 
    
   thisHeight = int(newEndPos / screenWidth); 
    
   if(pixelxy(startPos, screenWidth)[0] > pixelxy(endPos, screenWidth)[0])
   { 
     thisHeight++; 
   } 
    
   result[0]=std::abs(startPos+(screenWidth*(thisHeight))-endPos); 
 
   result[1]=thisHeight; 
  
   return result; 
 }
 
void setup_drawing(int startPos, int endPos, int screenWidth) 
 {   
     int lineStartPos {};
     int lineEndPos {};
     
     int rectWidth {};
     int rectHeight {};
     
     int longestSide {};
     int shortestSide {};
     
     int advanceLine {};
     int extendLine {};
     
   //if we want to left/right click anywhere in the grid 
   //possibly mixing up th start and endPos 
   //keep the start and end clear direction in the code 
   if(startPos > endPos) 
   { 
     lineStartPos = endPos; 
     lineEndPos = startPos; 
   } 
   else 
   { 
     lineStartPos = startPos; 
     lineEndPos = endPos; 
   } 
    
   //rectHeight=myheight(lineStartPos,lineEndPos); 
   //rectWidth=mywidth(lineStartPos,lineEndPos); 
   rectWidth=width_and_height(lineStartPos,lineEndPos, screenWidth)[0];
   rectHeight=width_and_height(lineStartPos,lineEndPos, screenWidth)[1];
   //which side is larger 
   longestSide=std::max(rectWidth, rectHeight); 
   shortestSide=std::min(rectWidth, rectHeight); 
  
   int rightPixel=-1; 
   int leftPixel=+1; 
   int upperLeftPixel=screenWidth+1; 
   int upperRightPixel=screenWidth-1; 
   int upperPixel=screenWidth; 
    
   // is the line being draw upleft or upright 
   int startXColumn = pixelxy(lineStartPos, screenWidth)[0]; 
   int endXColumn = pixelxy(lineEndPos, screenWidth)[0]; 
    
   if(rectWidth>rectHeight) 
   { 
     if(startXColumn <= endXColumn) 
     { 
       advanceLine=upperLeftPixel; 
       extendLine=leftPixel; 
     } 
     else 
     { 
       advanceLine=upperRightPixel; 
       extendLine=rightPixel; 
     } 
   } 
   else 
   { 
     if(startXColumn <= endXColumn) 
     { 
       advanceLine=upperLeftPixel; 
       extendLine=upperPixel; 
     } 
     else 
     { 
       advanceLine=upperRightPixel; 
       extendLine=upperPixel; 
     } 
   } 
 }
 
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }


// code

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    SDL_Renderer *renderer = NULL;
    /*
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        */
        SDL_Surface *surface = NULL;
        surface = SDL_GetWindowSurface(window);
        
        renderer = SDL_CreateSoftwareRenderer(surface);

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    if (renderer == NULL)
    {
        fprintf(stderr, "renderer error: %s", SDL_GetError());
    }

    /*
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xAA, 0xAA));
*/

  //  SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect rectangle;

    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 50;
    rectangle.h = 50;
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_RenderDrawPoint(renderer, 100, 100);

    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
