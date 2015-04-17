#include "graphics.h"

#define haut 10
#define large 10
#define taille_case 50

//11=rouge
//12=bleu
//13=vert
//14=jaune

int score;
int T[large][haut];

void test_tab(int T[large][haut])
{
	int i,j;
	for (i=0;i<haut;i++)
	{
		printf("\n");
		for (j=0;j<large;j++)
		{
			printf("%d  ",T[i][j]);
		}
		
	}
	printf("\n");printf("\n");
}

//ok
void init_jeu()
{
	int i,j;
	
	for (i=0;i<haut;i++)
	{
		for (j=0;j<large;j++)
		{
			T[i][j]=alea_int(4)+11;
		}
		
	}
}

//ok
void affiche_quadrillage()
{
	int i;
	POINT p1,p2;
	
	for(i=1;i<large;i++)
	{
		p1.y=0;				p2.y=haut*taille_case;
		p1.x=i*taille_case;	p2.x=i*taille_case;
		
		draw_line(p1,p2,blanc);
		
	}
	
	for(i=1;i<haut;i++)
	{
		p1.x=0;				p2.x=large*taille_case;
		p1.y=i*taille_case;	p2.y=i*taille_case;
		
		draw_line(p1,p2,blanc);
		
	}
	
}
//ok
void affiche_jeu()
{
		int i,j;
		POINT p;
		COULEUR c;
		
		for (i = 0; i < haut; i++)
		{
			for (j = 0; j < large; j++)
			{
				p.x=(taille_case/2)+j*taille_case;
				p.y=(taille_case/2)+i*taille_case;
				
				if(T[j][i]==11){c=rouge;}
				if(T[j][i]==12){c=bleu;}
				if(T[j][i]==13){c=vert;}
				if(T[j][i]==14){c=jaune;}
				if(T[j][i]==0 ){c=noir;}
				
				draw_fill_circle(p,taille_case/2,c);
				
			}
			
		}
		
}
//ok
void affiche()
{
	fill_screen(noir);
	affiche_quadrillage();
	affiche_jeu();
	affiche_all();	
}
//ok
int test_case(int x, int y)
{
	int c,b;
	
	c=T[x][y];
	
	b=T[x+1][y];
	if(c==b){return 1;}
	
	b=T[x][y+1];
	if(c==b){return 1;}
	
	b=T[x-1][y];
	if(c==b){return 1;}
	
	b=T[x][y-1];
	if(c==b){return 1;}
	  
	return 0;
}

void effacer(int x,int y,int val)
{
	
	if(T[x][y]!=val){return ;}
	if(x<0)			{return ;}
	if(x>=haut)		{return ;}
	if(y<0)			{return ;}
	if(y>=large)	{return ;}
	

	T[x][y]=0;

	effacer(x+1,y,val);
	effacer(x-1,y,val);
	effacer(x,y+1,val);
	effacer(x,y-1,val);
}

void clic()
{
	int x,y;
	POINT p;
	
	p=wait_clic();
	x=(p.x/taille_case);
	y=(p.y/taille_case);
	

	if(T[x][y]!=0 && test_case(x,y)==1) {effacer(x,y,T[x][y]);}
	
}

void descendre_une_boule(int x,int y)
{
	
	if(T[x][y]==0){return;}
	while((T[x][y-1]==0) && (y>0))
	{
		T[x][y-1]=T[x][y];
		T[x][y]=0;
		y--;
	}
	
	
}

void decale_gauche()
{
	int y,x,i;
	
	for(y=large-1;y<0;y--)
	{
		if(T[0][y]==0 )
		{
			i=y;
			while (i<large-1 && T[0][i+1]==0)
			{
				for(x=0;x<haut;x++)
				{
					T[x][y+1]=T[x][y];
					T[x][y]=0;
				}
			}
			
		}
	}
}

void descendre ()
{
	int x,y;
	
	for (y = 0; y < haut; y++)
	{
		for (x = 0; x < large; x++)
		{
			descendre_une_boule(x,y);
		}
		
	}
	decale_gauche();
	
}

int main ()
{

init_graphics (large*taille_case,haut*taille_case);
affiche_auto_off();

int perdu ;


init_jeu();

perdu=1;


while (perdu)
{
		
	affiche();
	clic();
	descendre();

}


wait_escape();
exit(0);
}
