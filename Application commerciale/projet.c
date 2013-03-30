#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct liste_w
{
    int code_composant;
    int quantite;
    struct liste_w* next ;
};typedef struct liste_w LISTE_W;

struct data3
{
char designation[20] ;
float cout;
int code_fournisseur ;
int stock ;
int code_produit;
};typedef struct data3 DATA3;

struct abr_produit
{
struct abr_produit* gauche ;
struct abr_produit* droite ;
DATA3 d;
};typedef struct abr_produit ABR_PRODUIT ;

struct data4
{
    int code_compose;
    float cout ;
};typedef struct data4 DATA4 ;

struct liste_prix
{
    DATA4 d;
    struct liste_prix* next ;
};typedef struct liste_prix LISTE_PRIX;



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

//Methode de la fonction main()
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



int get_menu()
{
    int a;
    printf("Pour avoir la liste de la matiere necessaire pour la composition d'un produit tapez 1 \n pour avoir la liste des prix de composé tapez 2Pour avoir la liste des fournisseurs neceaire pour un produit tapez 3Pour tester votre programme de lancement tapez 4 \n ");

           scanf("%d",&a);
           return(a) ;
}

//attention à cette methode
void suppression_fournisseur( ABR_FOURNISSEUR** racine)
{
    int code ;
    printf("\n\n ** Fournisseur Necessaires **\ndonner le code de produit\n");
    //printf("donner le code de produit");
    scanf("%-2d.2d",&code);
    supprime_fournisseur(& racine,code);
    affiche_fournisseur(racine);
}

void supprime_fournisseur(ABR_FOURNISSEUR**racine,int key)
{
    ABR_FOURNISSEUR* p;
    ABR_FOURNISSEUR** t;

    if (racine)
    {
        p=*racine ;
        if (key>(*racine)->d.code)
        supprime_fournisseur(&((*racine)->droite),key);

        if (key<(*racine)->d.code)
        supprime_fournisseur(&((*racine)->gauche),key);

        if (key==(*racine)->d.code)
        {
            if ((*racine)->gauche==NULL)
            *racine=(*racine)->droite ;
            else
        {
            if((!(*racine)->gauche) && (!(*racine)->droite) )
            {
                p=*racine;
                *racine=NULL;
                free(p);
            }
            else
            {
                if(!(*racine)->gauche)
                {
                    p=*racine;
                    *racine=((*racine)->droite);
                    free(p);
                }

                else if(!(*racine)->droite)
                {
                  p=*racine;
                 (*racine)=(*racine)->gauche;
                 free(p);
                }
                else
                {
                    for(p=(*racine)->gauche;p->droite;p=p->gauche);
                    (*racine)->d=p->d;
                    supprime(&(*racine)->gauche,key);
                }
            }
          }
        }
    }
}

ABR_FOURNISSEUR* seek_gauche(ABR_FOURNISSEUR * racine)
{
    for (;racine && racine->droite; racine=racine->droite);
    return(racine);
}

void prix(ABR_PRODUIT* racine)
{
    LISTE_PRIX* listeprix= NULL ;
    printf("\n ** Prix de composé **\n");
    listeprix = charger_liste_prix(racine);

    if (listeprix)
    {
        for (;listeprix;listeprix=listeprix->next)
        printf("Le composé dont le code: %d est de prix %d \n\n",listeprix->d.code_compose,listeprix->d.cout);
    }
    else printf("erreur");
}
ARBRE* seek_noeud1(ARBRE* racine,int compose)
{   ARBRE* p=NULL ;
    if (racine)
    {
        if(racine->d.code_compose=compose)
        return(racine);
        if(p=seek_noeud1(racine->frere,compose))  return(p);
        return(seek_noeud1(racine->fils,compose));
    }
    return(NULL);
}
void r_get_composant(ARBRE* racine,LISTE_W** work,int facteur)
{
    if(racine)
    {
        if(!racine->fils)
        insere_work(work,racine->d.code_compose,racine->d.quantite*facteur);

        r_get_composant(racine->frere,work,facteur);
        r_get_composant(racine->fils,work,facteur*(racine->d.quantite));
    }
}
void lister(ARBRE* racine,LISTE_W** q)
{
    ARBRE* p = NULL ;
    int code,quantite;
    LISTE_W* work=NULL ;

    printf("code:\n");  scanf("%-2d.2d",code);
    printf("quantité:");  scanf("%d",quantite);

    if (!(p=seek_noeud1(racine,code)))
    printf("\ncomposé n existe pas");
    else
    {
        r_get_composant(p->fils,&work,1);
        structurer(work,q);
    }
}


void prog_lancement(ARBRE* racine)
{
    char option ;
    LISTE_W* q=NULL ;

    while (option=get_option())
    {
        switch(option)
        {
            case'L':lister(racine,&q);  break;
            case'T':affiche_prog(q,racine); break;
            case'Q':exit(0);
            default:printf("touche invalide!\n");
        }
    }
}
void print_data(LISTE_W* work ,LISTE_W** q)
{ LISTE_W* a=(LISTE_W*)malloc(sizeof(LISTE_W));
  a->code_composant= work->code_composant;
  a->quantite=work->quantite;
  a->next=NULL;
  *q=work;
}

void structurer(LISTE_W* work , LISTE_W** q)
{
    if (!*q)
        for(;work;work=work->next) print_data(*q,work) ;
    else
    {
        for (;*q && (*q)->next ;(*q)=(*q)->next)
        {
            for (;work;work=work->next)
            {
                if ((*q)->code_composant != work->code_composant)
                insere_tete(q,work);
                (*q)->quantite+=work->quantite;
            }
        }
    }
}

void insere_tete(LISTE_W** first ,LISTE_W* a)
{
    LISTE_W* p;
    p=(LISTE_W*)malloc(sizeof(LISTE_W));
    p->code_composant=a->code_composant ;
    p->quantite=a->quantite;
    p->next=*first ;
    *first=p;
}

/*void affiche_prog(LISTE_W* q ,ARBRE* racine)
{
    int quantite ;
    for (;q;q->next)
    {
        quantite=calcul_stock(racine,q->code_composant,1);
        printf("\n code:%-2d.2d quantité:%d stock:%d",q->code_composant,q->quantite,quantite);

        if (quantite>q->quantite)
        printf("Stock insuffisant");
    }
}*/

int calcul_stock(ARBRE* racine,int key,int qnt)
{
    if (racine)
    {
        if (racine->d.quantite!=key)
          return(calcul_stock(racine->frere,key,qnt) + calcul_stock(racine->fils,key,qnt*racine->d.quantite));
          return(racine->d.quantite);
    }
    return(0);
}
