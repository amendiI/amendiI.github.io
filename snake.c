#include "graphics.h"

// Définition des différentes formes

#define VIDE 0
#define CERCLE 100
#define CARRE 101
#define CROIX 102

// Définition des types

struct elem {
  int i,j; // position sur le quadrillage de l'élément
  int forme; // vaut VIDE, CERCLE, CARRE ou CROIX
  COULEUR coul; // vaut bleu, rouge, jaune ou vert
};


struct serpent {
  int longueur; // nombre d'éléments dans le corps du serpent
  struct elem A[200]; // les éléments constitutifs du serpent
  POINT direction;
};

// Fonctions à écrire
void init_objet(struct elem J[40][60])
{
	int i,j,coul,f;
	i=alea_int(40);
	j=alea_int(60);
	f=alea_int(3);
	coul=alea_int(4);
	if(coul==1){J[i][j].coul=bleu;}
	if(coul==2){J[i][j].coul=rouge;}
	if(coul==3){J[i][j].coul=jaune;}
	if(coul==0){J[i][j].coul=vert;}
	if(f==0){J[i][j].forme=CARRE;}
	if(f==1){J[i][j].forme=CERCLE;}
	if(f==2){J[i][j].forme=CROIX;}	
}

void init_jeu(struct elem J[40][60])
{
	int c,v;
	for (c=0;c<40;c++)
	{
		for (v=0;v<60;v++)
		{
			J[c][v].forme=VIDE;
			}
	}
	for (c=0;c<24;c++){init_objet(J);}
}

struct serpent init_serpent()
{
	struct serpent S;
	int c;
	S.longueur=0;
	for(c=0;c<200;c++)
	{
		S.A[c].i=0;
		S.A[c].j=0;
		S.A[c].coul=noir;
		S.A[c].forme=VIDE;
	}
	S.A[0].i=alea_int(40);
	S.A[0].j=alea_int(60);
	S.longueur=1;
	return S;
}

void dessine_carre(int i,int j,COULEUR coul)
{
	POINT p,p2;
	p.x=i*10;p.y=j*10;p2.x=p.x+10;p2.y=p.y+10;
	draw_fill_rectangle(p,p2,coul);
}

void dessine_cercle(int i,int j,COULEUR coul)
{
	POINT p;
	p.x=i*10+5;p.y=j*10+5;
	draw_fill_circle(p,5,coul);
}

void dessine_croix(int i,int j,COULEUR coul)
{
	POINT p,p2;
	p.x=i*10;p.y=j*10;
	p2.x=p.x+10;p2.y=p.y+10;
	draw_line(p,p2, coul);
	p.x=i*10;p.y=j*10+10;
	p2.x=p.x+10;p2.y=p.y-10;
	draw_line(p,p2,coul);
}

void dessin_case(int i,int j, struct elem J[40][60])
{
	COULEUR coul;
	coul=J[i][j].coul;
	if(J[i][j].forme==CARRE){dessine_carre(i,j,coul);}
	if(J[i][j].forme==CERCLE){dessine_cercle(i,j,coul);}
	if(J[i][j].forme==CROIX){dessine_croix(i,j,coul);}
}

void affiche_jeu(struct elem J[40][60])
{
	int i,j;
	for (i=0;i<40;i++)
	{
		for (j=0;j<60;j++)
		{
			dessin_case(i,j,J);
		}
	}
}

void affiche_serpent(struct serpent S,struct elem J[40][60])
{
	POINT p;
	int c;
	p.x=S.A[0].i*10+5;p.y=S.A[0].j*10+5;
	draw_fill_circle(p,5,blanc);
	for(c=S.longueur;c>0;c--)
	{
		COULEUR coul;
		int i,j;
		i=S.A[c].i;
		j=S.A[c].j;
		coul=S.A[c].coul;
		if(S.A[c].forme==CARRE){dessine_carre(i,j,coul);}
		if(S.A[c].forme==CERCLE){dessine_cercle(i,j,coul);}
		if(S.A[c].forme==CROIX){dessine_croix(i,j,coul);}
	}
}

struct serpent valeur_serpent( struct serpent S)
{
	int c;
	for(c=S.longueur;c>=1;c--)
	{
		S.A[c].i=S.A[c-1].i;
		S.A[c].j=S.A[c-1].j;
	}
	return (S);
}

struct serpent deplace_serpent (struct serpent S, POINT p)
{
	S=valeur_serpent(S);
	if (p.x!=0 || p.y != 0){S.direction=p;}
	if (S.direction.x>0){S.A[0].i++;}
	if (S.direction.x<0){S.A[0].i--;}
	if (S.direction.y>0){S.A[0].j++;}
	if (S.direction.y<0){S.A[0].j--;}
	return (S);
}

struct serpent manger(struct serpent S,struct elem E[40][60])
{
	int i,j;
	i=S.A[0].i;
	j=S.A[0].j;

	if(E[i][j].forme != 0)
	{
		S.A[S.longueur].forme=E[i][j].forme;
		S.A[S.longueur].coul=E[i][j].coul;
		S.longueur++;
		E[i][j].forme=VIDE;
	}
	return(S);
}

void mort(struct serpent S)
{
	if(S.A[0].i>40){exit(1);}
	if(S.A[0].i<0){exit(2);}
	if(S.A[0].j<0){exit(3);}
	if(S.A[0].j>60){exit(4);}
}

int main()
{
		struct elem J[40][60];
	struct serpent S;
	POINT p;

	init_graphics(400,600);
	init_jeu(J);
	S = init_serpent();
	affiche_auto_off();
	while (1)
	{
		p = get_arrow();
		S = deplace_serpent(S,p);
		mort(S);
		S=manger(S,J);

		affiche_jeu(J);
		affiche_serpent(S,J);
		affiche_all();
		attendre(80);
		fill_screen(noir);
	}
	wait_escape();
	  exit(0);
}


