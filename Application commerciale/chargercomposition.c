#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
int code_compose;
int code_composant ;
int quantite ;
};typedef struct data DATA ;

struct arbre
{
struct arbre* fils ;
struct arbre* frere ;
DATA d ;
};typedef struct arbre ARBRE ;



//chargement de fichier composition.txt dans l'arbre
ARBRE* seek_noeud(ARBRE* racine ,int code_compose)
{
if (racine)
{
if (racine->d.code_compose==code_compose)
return(racine);
return(NULL) ;
}
}

void insere_noeud_arbre_composition(ARBRE** racine,char s[])
{
ARBRE* pere;
int code_compose,code_composant,quantite ;



sscanf(s,"%2d%3d%2d",&code_compose,&code_composant,&quantite);
//sscanf(s,"%2d",&code_compose);
//sscanf(s+3,"%2d",&code_composant);
//sscanf(s+5,"%2d",&quantite);
if(!(pere=seek_noeud(*racine,code_compose)))
{
pere=(ARBRE*)malloc(sizeof(ARBRE));
pere->d.code_compose=code_compose;
pere->d.quantite=quantite ;
pere->frere=*racine ;
pere->fils=NULL ;
*racine=pere;
}
else
{
ARBRE* p=(ARBRE*)malloc(sizeof(ARBRE)) ;
p->d.code_composant=code_composant ;
p->d.quantite=quantite ;
p->frere = pere->fils ;
pere->fils=p ;
p->fils = NULL ;
}
}



ARBRE* chargement_composition()
{
FILE* fp;
char s[10];
ARBRE* racine;

if (!(fp=fopen("composition.txt","r")))
return(NULL);
for(racine=NULL;fgets(s,10,fp);)
insere_noeud_arbre_composition(&racine,s);

fclose(fp);
return(racine);
}

void affichage_arbre(ARBRE* racine)
{
if (racine)
{
printf("compose: %2d\n",racine->d.code_compose);
printf("composant: %2d\n",racine->d.code_composant);
printf("quantite: %2d\n",racine->d.quantite);

affichage_arbre(racine->fils);
affichage_arbre(racine->frere);
}
}



void main()
{

ARBRE* racine = chargement_composition();
affichage_arbre(racine);


}
