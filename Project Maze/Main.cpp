#include "SDL.h" 

bool hasWon(int titleID);
SDL_Surface* LoadImage(const char* path);

int main( int argc, char* args[] ) 
{ 
	int mouseX,mouseY;
	bool LMB=false;
	bool RMB=false;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EventState( SDL_MOUSEMOTION , SDL_IGNORE );
	bool keysHeld[323]={false};
	SDL_Event event;
	SDL_Surface *A1=NULL;
	SDL_Surface *ghost=NULL;
	SDL_Surface *Win=NULL;
	A1=SDL_LoadBMP("Res/wall.bmp");
	ghost=SDL_LoadBMP("Res/ghost.bmp");
	Win=LoadImage("Res/win.bmp");
	SDL_Surface *screen=NULL;
	screen=SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);






	bool window=true;
	SDL_Rect wall,character,win,blocked;
	int x=0,y=20,positionX,positionY;
	character.w=20;
	character.h=20;
	win.w=120;
	win.h=50;
	win.x=360;
	win.y=300;

	wall.w=20;
	wall.h=20;
	SDL_Rect sclip;
	sclip.x=0;
	sclip.y=0;
	sclip.w=20;
	sclip.h=20;

	int row=0,col=0;

	int Maze[30][40]=
	{
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1},
		{1,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
		{1,0,0,0,1,0,0,1,1,1,1,0,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,1,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
		{1,0,1,1,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1},
		{1,0,0,0,0,1,1,1,0,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,1,0,1,1,0,0,0,1},
		{1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,1,1,0,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,1,1,1},
		{1,0,1,1,1,0,1,1,0,1,0,0,0,0,1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,1,0,1},
		{1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,1},
		{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,0,1},
		{1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,1},
		{1,0,1,0,1,1,0,0,0,1,0,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,0,1,1,0,1,1,1},
		{1,0,0,0,1,0,0,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1,1,1,1,1,1,0,1,1,1},
		{1,0,1,1,1,0,1,1,0,1,0,0,1,1,0,1,1,1,0,1,1,1,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1},
		{1,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1},
		{1,0,1,1,1,0,0,0,0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,1,0,1,1,1,0,1,0,1,0,0,1},
		{1,0,1,1,1,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,0,1,1,0,0,1,0,0,0,1,1},
		{1,0,0,0,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,0,0,0,1,0,0,1,0,1,1,1,1,0,0,0,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1},
		{1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,0,1,1,0,0,0,1,0,1,1},
		{1,0,0,0,1,0,0,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,1,0,1,1,0,1,0,1,1},
		{1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,1},
		{1,0,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1},
		{1,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0,1,0,0,0,1,1,0,1,1},
		{1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,0,1,1,1,1,1,0,1,0,1,1,0,1,1},
		{1,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1}

	};

	while(window==true)
	{
		SDL_GetMouseState(&mouseX, &mouseY);
		if(SDL_PollEvent(&event)!=0)
		{
			if(event.type==SDL_QUIT)
			{
				window=false;
			}
		}

		if( event.type == SDL_KEYDOWN) 
		{
			keysHeld[event.key.keysym.sym] = true; 
		}
		if( event.type == SDL_KEYUP) 
		{
			keysHeld[event.key.keysym.sym] = false; 
		}
		if ( keysHeld[SDLK_ESCAPE] ) 
		{
			window = false; 
		}
		if(keysHeld[SDLK_w])
		{
			if(Maze[x/20-1][y/20]!=1)
				x-=20;

		}
		if(keysHeld[SDLK_s])
		{
			if(Maze[x/20+1][y/20]!=1)
				x+=20;
		}
		if(keysHeld[SDLK_a])
		{
			if(Maze[x/20][y/20-1]!=1)
				y-=20;
		}
		if(keysHeld[SDLK_d])
		{
			if(Maze[x/20][y/20+1]!=1)
				y+=20;
		}
		
		/*if( event.type == SDL_MOUSEMOTION ) 
		{ 
			mouseX = event.motion.x;
			mouseY = event.motion.y; 
		}*/
		

		if( event.type == SDL_MOUSEBUTTONDOWN )
		{
			if( event.button.button == SDL_BUTTON_LEFT ) 
			{
				LMB = true; 
			} 
			if(event.button.button==SDL_BUTTON_RIGHT)
			{
				RMB=true;
			}
		}
		if( event.type == SDL_MOUSEBUTTONUP ) 
		{
			if( event.button.button == SDL_BUTTON_LEFT ) 
			{
				LMB = false; 
			} 
			if(event.button.button==SDL_BUTTON_RIGHT)
			{
				RMB=false;
			}
		}
		//Left click to make wall, Right click to make path
		/*if(RMB)
		{
			Maze[mouseY/20][mouseX/20]=0;
		}
		if(LMB)
		{
			Maze[mouseY/20][mouseX/20] = 1; 
		}*/


		character.x=y;
		character.y=x;
		SDL_FillRect( screen, NULL , 0x00000000);
		//SDL_FillRect(screen,&character,0xbc314e);
		SDL_BlitSurface(ghost,NULL,screen,&character);





		for(int i=0;i<30;i++)
		{
			for(int j=0;j<40;j++)
			{

				if(Maze[i][j]==1)
				{
					wall.x=j*20;
					wall.y=i*20;
					//SDL_FillRect(screen,&wall,0x565654);
					SDL_BlitSurface(A1,&sclip,screen,&wall);

				}







			}
		}





		if(hasWon(Maze[x/20][y/20])==true)
		{
			SDL_BlitSurface(Win,NULL,screen,&win);
		}






		SDL_Flip(screen);
		SDL_Delay(66);



	}



	SDL_FreeSurface(Win);
	SDL_FreeSurface(ghost);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(A1);
	SDL_Quit();
	return 0;

}
SDL_Surface* LoadImage(const char* path)
{
	SDL_Surface * image = NULL;
	image = SDL_LoadBMP(path);
	if(image==NULL)
		printf("ERROR: Cannot load %s",path);


	return image;
}



bool hasWon(int titleID)
{
	return (titleID==2);
}