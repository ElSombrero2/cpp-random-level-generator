#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include "Map.h"
#define WIDTH  40
#define HEIGHT 20
#define SECOND 1000.0
#define FRAME 60.0
#define SIZE 30
#define COINC_CHANCE 60

const Node EMPTY(VOID,0,HEIGHT-1,40,20,40,
    vector<Neighbour>({})      
);

const Node LEFT_NODE(LEFT,5,8,40,60,60,
    vector<Neighbour>({
            {2,60},
            {3,50}
        })      
);

const Node MIDDLE_NODE(MIDDLE,5,8,0,0,-20,
    vector<Neighbour>({
            {2,70},
            {3,50}
        })      
);

const Node RIGHT_NODE(RIGHT,5,8,20,20,0,
    vector<Neighbour>({
            {0,100}
        })      
);

Node* GetNode(vector<Node>& nodes,int id)
{
    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i].id==id)return &nodes[i];
    }

    return NULL;
}

int GetFirstVal(vector<Node> nodes,int chance)
{
    for(int i=0;i<nodes.size();i++)
    {
        if(chance<=nodes[i].end_chance)return nodes[i].id;
    }
    return nodes[nodes.size()-1].id;
}

int GetMiddleVal(vector<Node> nodes,int chance)
{
    for(int i=0;i<nodes.size();i++)
    {
        if(chance<nodes[i].middle_chance)return nodes[i].id;
    }
    return 0;
}

int GetEndVal(vector<Node> nodes,int chance)
{
    for(int i=0;i<nodes.size();i++)
    {
        if(chance<=nodes[i].end_chance)return nodes[i].id;
    }
    return nodes[nodes.size()-1].id;
}

int GetNeighbourVal(vector<Neighbour> neighbours,int chance)
{
    for(int i=0;i<neighbours.size();i++)
    {
        if(chance<=neighbours[i].chance)return neighbours[i].id;
    }
    return neighbours[neighbours.size()-1].id;
}

int* generateMap(vector<Node>& nodes,int w,int h)
{
    int **m=new int*[h];
    for(int i=0;i<h;i++)
    {
        m[i]=new int[w];
        for(int j=0;j<w;j++)
        {
            int val=-1;
            Node* prec=NULL;
            if(j>0)prec=GetNode(nodes,m[i][j-1]);
            if(i<5 || i%2!=0)val=0;
            else if(j==0)val=GetFirstVal(nodes,rand()%100);
            else if(prec!=NULL && prec->id==0){
                val=GetMiddleVal(nodes,rand()%100);
            }
            else val=GetNeighbourVal(prec->neighbours,rand()%100);
            m[i][j]=val;
        }
    }
    return (int*)m;
}

int* generateMapRandom(vector<Node>& nodes,int w,int h)
{
    int **m=new int*[h];
    for(int i=0;i<h;i++)
    {
        m[i]=new int[w];
        for(int j=0;j<w;j++)
        {
            int r=rand()%100;
            if(r<=20)m[i][j]=nodes[0].id;
            else if(r<=40)m[i][j]=nodes[1].id;
            else if(r<=50)m[i][j]=nodes[2].id;
            else if(r<=60)m[i][j]=nodes[3].id;
        }
    }
    return (int*)m;
}

int quit=0,now=0,current=0;

int main(int argc,char ** argv)
{
    srand(time(NULL));
    vector<Node> nodes({EMPTY,LEFT_NODE,RIGHT_NODE,MIDDLE_NODE});
    int **m=(int**)generateMap(nodes,WIDTH,HEIGHT);
    int c[HEIGHT][WIDTH];
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            c[i][j]=0;
            if(m[i][j]==2 && rand()%100<=COINC_CHANCE)
                c[i-1][j]=1;
        }
    }


    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

    SDL_Window*WINDOW=SDL_CreateWindow("Map Generator",
    SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
    SDL_Renderer*RENDERER=SDL_CreateRenderer(WINDOW,0,SDL_RENDERER_TARGETTEXTURE);

    SDL_Surface *tmp=IMG_Load("bin/img/1.png");
    SDL_Texture* tx1=SDL_CreateTextureFromSurface(RENDERER,tmp);
    SDL_QueryTexture(tx1,NULL,NULL,NULL,NULL);
    SDL_FreeSurface(tmp);

    tmp=IMG_Load("bin/img/2.png");
    SDL_Texture* tx2=SDL_CreateTextureFromSurface(RENDERER,tmp);
    SDL_QueryTexture(tx2,NULL,NULL,NULL,NULL);
    SDL_FreeSurface(tmp);

    tmp=IMG_Load("bin/img/3.png");
    SDL_Texture* tx3=SDL_CreateTextureFromSurface(RENDERER,tmp);
    SDL_QueryTexture(tx3,NULL,NULL,NULL,NULL);
    SDL_FreeSurface(tmp);

    tmp=IMG_Load("bin/img/5.png");
    SDL_Texture* tx5=SDL_CreateTextureFromSurface(RENDERER,tmp);
    SDL_QueryTexture(tx5,NULL,NULL,NULL,NULL);
    SDL_FreeSurface(tmp);
    
    while(!quit)
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type==SDL_QUIT)quit=1;
        now=SDL_GetTicks();
        if(now-current>=SECOND/FRAME)
        {
            SDL_SetRenderDrawColor(RENDERER,100,200,220,255);
            SDL_Rect screen={0,0,800,600};
            SDL_RenderFillRect(RENDERER,&screen);
            for(int i=0;i<HEIGHT;i++)
            {
                for(int j=0;j<WIDTH;j++)
                {
                    SDL_Rect rect={j*SIZE,i*SIZE,SIZE,SIZE};
                    if(m[i][j]==1)SDL_RenderCopy(RENDERER,tx1,NULL,&rect);
                    if(m[i][j]==2)SDL_RenderCopy(RENDERER,tx2,NULL,&rect);
                    if(m[i][j]==3)SDL_RenderCopy(RENDERER,tx3,NULL,&rect);
                    if(c[i][j])SDL_RenderCopy(RENDERER,tx5,NULL,&rect);
                }
            }
            current=now;
        }else SDL_Delay(SECOND/FRAME-(now-current));
        SDL_RenderPresent(RENDERER);
    }
    SDL_DestroyTexture(tx1);
    SDL_DestroyTexture(tx2);
    SDL_DestroyTexture(tx3);
    SDL_DestroyTexture(tx5);
    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
    return 0;
}

