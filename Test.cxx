#include "tensorflow.h"
#include <iomanip>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;
void plotLoss(const Array<float>& history, int width = 50, int height = 10) {
    float maxL = -1e9, minL = 1e9;
    for(float l : history) {
        if(l > maxL) maxL = l;
        if(l < minL) minL = l;
    }

    std::cout << "\nLoss Curve (" << minL << " to " << maxL << "):\n";
    for (int i = height; i >= 0; i--) {
        float threshold = minL + (maxL - minL) * (float)i / height;
        std::cout << (threshold < 10 ? " " : "") << std::fixed << std::setprecision(2) << threshold << " | ";
        for (int j = 0; j < history.len(); j++) {
            if (history[j] >= threshold) std::cout << "*";
            else std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "       " << std::string(history.len(), '-') << "\n";
}
class Mat{
	private:
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture *screenTexture;
	public:
	void init(int,int);
	void matLoss(const Array<float>& history,int width,int height);
};
void Mat::init(int width=1000,int height=1000){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());return;}
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());return;}
	SDL_Rect bounds;
	SDL_GetDisplayBounds(0,&bounds);
	int sidebar_x = bounds.w - width - 50;
	window = SDL_CreateWindow("Loss",sidebar_x,100 , width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL){fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());return;}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL){fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());return;}
	screenTexture = SDL_CreateTexture(
						renderer,
						SDL_PIXELFORMAT_RGBA8888,
						SDL_TEXTUREACCESS_STREAMING,
						width,height
					);
	SDL_RenderSetLogicalSize(renderer,width,height); 
}
void Mat::matLoss(const Array<float>& history,int width=1000,int height=700){
	//initialize
	init(width,height);	
	static SDL_Event e;
	bool running=true;
	float min=-99,max=99;
    for(float val : history){
    	min = min>val ? val : min;
    	max = max<val ? val : max;
    }
    int h = height-100, w = width-100;
    float yinter = h /(max-min);
    float xinter = w / history.len();
    while(running){
		while(SDL_PollEvent(&e)!=0){
			if(e.type==SDL_QUIT) running=false;
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
 	   SDL_RenderClear(renderer);

	   for(int i=0;i<history.len();i++){
    		SDL_Rect fillRect = { (int)(i*xinter + 100), (int)(yinter*(max-history[i]) + 100), (int)xinter,(int)(history[i]*yinter) };
	
	        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
 	       SDL_RenderFillRect(renderer, &fillRect);
  	  }

		SDL_RenderPresent(renderer);
		SDL_Delay(30);
	}
	SDL_DestroyTexture(screenTexture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
int main(int argc, char *argv[])
{
	int size = 32;
	Array2d<float> a(size, size,{-5,5});
	Array2d<float> t = a * a;
	Array2d<float> in = a;
	Sequential sq(0.005, size);
	sq.add(64,"relu",true);
	sq.add(64,"relu",true);
	sq.add(32,"relu",true);
	sq.add(size,"linear",true);
	Array<float> ls = sq.train(50,12,in,t);
	float acc = sq.test(in,t,12);
	cout<<"Accuracy : "<<acc*100.0f<<" % "<<endl;
	Mat m;
	m.init();
	m.matLoss(ls,1500,1200);
	return 0;
}