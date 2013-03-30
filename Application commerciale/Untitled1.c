
#include<stdio.h>
struct data2
{
int code ;
char raison[20];
};typedef struct data2 DATA2 ;

struct abr_fournisseur
{
DATA2 d ;
struct abr_fournisseur* droite ;
struct abr_fournisseur* gauche ;
};typedef struct abr_fournisseur ABR_FOURNISSEUR ;

void insere_noeud_abr(ABR_FOURNISSEUR** racine,int code,char* raison)
{
if (*racine)
{
if( code <= (*racine)->d.code)
insere_noeud_abr(&((*racine)->gauche),code,raison);
insere_noeud_abr(&((*racine)->droite),code,raison);
}
else
{
racine=(ABR_FOURNISSEUR*)malloc(sizeof(ABR_FOURNISSEUR));
(*racine)->d.code=code ;
strncpy((*racine)->d.raison,raison,15);
((*racine)->gauche)=NULL ;
((*racine)->droite)=NULL ;
}
}

int main()
{ ABR_FOURNISSEUR * p;


}
