#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<conio.h>


//*******************les structs de notre prog **********************
struct data
{
        int code;
        int q;
};typedef struct data DATA;


struct arbre
{
 DATA d;
 struct arbre*frere;
 struct arbre*fils;
};typedef struct arbre ARBRE;
   //********************
struct data_p
{
       int codep;
       char designation[21];
       int codef;
       float stock;
       float cout;
       ;
};typedef struct data_p DATA_P;


struct liste_w
{
    int code;
    int qt;
    struct liste_w * next;
};
typedef struct liste_w LISTE_W;

struct liste_t
{
    int code;
    float ca;
    struct liste_t * next;
};
typedef struct liste_t LISTE_T;

struct abr_p
{
       DATA_P d;
       struct abr_p * droite;
       struct abr_p * gauche;
}; typedef struct abr_p ABR_P;

    //*******************
struct data_f
{
 int code;
 char raison_social[21];
 };typedef struct data_f DATA_F;


 struct abr_f
{
       DATA_F d;
       struct abr_f * droite;
       struct abr_f *gauche;
};typedef struct abr_f ABR_F;
/////////////////////////////////////////////////////:::::::


//*****************chargement des arbres binaire de recherche***********************

//************arbre produit ***


 void insert_abr_p(char*s,ABR_P**racine)
  {    int code;
       sscanf(s,"%2d ",&code);
       if(*racine)
       {
                  if(code<=(*racine)-> d.codep)
                        insert_abr_p(s,&((*racine)->gauche));
                  else
                        insert_abr_p(s,&((*racine)->droite));
       }
       else
       {
           *racine=(ABR_P*)malloc (sizeof(ABR_P));
           sscanf(s,"%2d %21s %2d %4d %f ",&((*racine)->d.codep),(*racine)->d.designation,&((*racine)->d.codef),&((*racine)->d.stock),&((*racine)->d.cout));
           (*racine)->gauche=NULL;
           (*racine)->droite=NULL;
        }
  }


ABR_P* load_produit()
{
FILE* fp;
char  s[100];
ABR_P* racine ;
int codeproduit,codefournisseur,stock;
char designation[20];
float cout;

if (!(fp=fopen("produit.txt","r")))
{
    printf("erreur");
return(NULL) ;
}

for (racine=NULL ; fgets(s,100,fp);)
{
  insert_abr_p(s,&racine);
}

fclose(fp);
return(racine);
}

void affichage_produit(ABR_P* racine)
{
   if(racine)
   {  printf("code produit:%d \n",racine->d.codep);
      printf("designation:%20s \n",racine->d.designation);
      printf("le cout du produit:%6f \n",racine->d.cout);
      printf("le code fournisseur:%d \n",racine->d.codef);
      printf("stock:%-4.4d \n",racine->d.stock);

      affichage_produit(racine->gauche);
      affichage_produit(racine->droite);
   }
}

//*****************************


//********abr fournisseur ******

  void insert_abr_f(char*s,ABR_F**racine)
  {
  	   int code;
       sscanf(s,"%2d ",&code);
       if(*racine)
       {
                  if(code<=(*racine)->d.code)
                        insert_abr_f(s,&((*racine)->gauche));
                  else
                        insert_abr_f(s,&((*racine)->droite));
       }
       else
       {
           *racine=(ABR_F*)malloc (sizeof(ABR_F));
           sscanf(s,"%2d %21s ",&((*racine)->d.code),(*racine)->d.raison_social);
           (*racine)->gauche=NULL;
           (*racine)->droite=NULL;
        }
  }


 ABR_F* load_fournisseur()
{   FILE*fp;
    char s[100] ;
    ABR_F*racine;
       if(!(fp=fopen("fournisseur.txt","r")))
          {
              printf("erreur \n ");
              return(NULL);
          }
       for(racine=NULL ; fgets(s,100,fp) ;  )
            insert_abr_f(s,&racine);
       fclose(fp);
       return(racine);
}


void affichage_fournisseur(ABR_F* racine)
{
    if (racine)
    {
        printf("code fournisseur: %d\n",racine->d.code);
        printf("raison sociale: %20s\n",racine->d.raison_social);

       affichage_fournisseur(racine->gauche);
       affichage_fournisseur(racine->droite);

    }
}

//*******************************

//**********arbre composition****

void  copy_arbre(ARBRE*racine,ARBRE**destination)
{
 	  if(racine)
 	  {
            (*destination)=(ARBRE*)malloc(sizeof (ARBRE));
            (*destination)->d=racine->d;
	   		copy_arbre(racine->frere,&((*destination)->frere));
	   		copy_arbre(racine->fils,&((*destination)->frere));
   	  }
	  else
	  (*destination)=NULL;
}

void  MAJ(ARBRE*racine,ARBRE*tete)
{
	  if(tete)
 	  {
	   		if((tete->d.code==racine->d.code)&& (tete->fils))
	   		copy_arbre(tete->fils,&(racine->fils));
      }
      else
      MAJ(racine->fils,tete);
      MAJ(racine->frere,tete);
}


void  r_normaliser(ARBRE*racine,ARBRE* tete)
{
 	  if (racine)
 	  {
             if(!(racine->fils))
 		       {
			       MAJ(racine,tete);
                   r_normaliser(racine->fils,tete);
                   r_normaliser(racine->frere,tete);
			   }
	  }
}

void normaliser_arbre (ARBRE *racine)
{
	r_normaliser(racine,racine);
}

ARBRE* seek_noeud(ARBRE* racine,int key)
{
ARBRE* p;
 if(racine)
   {
          if((racine->d.code=key))
          return(racine);
          if( p=(seek_noeud(racine->frere,key)))
          return(p);
          return(seek_noeud(racine->fils,key));
    }
 return(NULL);
}

void  insert_noeud(char*s,ARBRE**racine)
  {
      ARBRE*p ,*pere;
      int compose;
      int composant;
      int q;
      p=(ARBRE*)malloc (sizeof(ARBRE));
      sscanf( s,"%2d %2d %4d",&(compose),&(composant),&(q));
      if(!(pere=seek_noeud((*racine),compose)))
        {
             pere=(ARBRE*)malloc(sizeof(ARBRE));
             pere->d.code=compose;
             pere->d.q=1;
             pere->frere=(*racine);
             pere->fils=NULL;
             *racine=pere;
        }
        p->d.code=composant;
        p->d.q=q;
        p->frere=pere->fils;
        p->fils=NULL;
        pere->fils=p;
 }


 ARBRE* load_composition()
{
   	   FILE* fp ;
       char s[100] ;
       ARBRE*racine;
       if(!(fp=fopen("composition.txt","r")))
          {
              printf("erreur \n");
              return(NULL);
          }
       for(racine=NULL ; fgets(s,100,fp) ;  )
              insert_noeud(s,&racine);
       fclose(fp);
       normaliser_arbre(racine);
       return(racine);
       getch();
}


void affichage_arbre(ARBRE* racine)
{
if (racine)
{
printf("compose: %2d\n",racine->d.code);
printf("quantite: %4d\n",racine->d.q);

affichage_arbre(racine->fils);
affichage_arbre(racine->frere);
}
}

//*******************************
void filtrer(LISTE_W**work,int compose)
{

}
//*********

LISTE_W* seek_work(LISTE_W* work,int key)
{
    if(work)
    {
        if(work->code==key)
           return(work);
        return(seek_work(work->next,key));

    }
}

void insere_work(LISTE_W** work ,int code,int qt)
 {
    LISTE_W *p;

	   	if (p=seek_work(*work,code))
          p->qt+=qt;
	  else
	    {
	  	   p=(LISTE_W*)malloc(sizeof( LISTE_W));
		    p->code=code;
		     p->qt=qt;
		     p->next=*work;
		     *work=p;
	   }
 }


void r_get_composant(ARBRE *racine,LISTE_W**work,int facteur )
 {
      if(racine)
      {
          if(!racine->fils)
          insere_work(work,racine->d.code ,racine->d.q*facteur);
          r_get_composant(racine->frere,work, facteur );
          r_get_composant(racine->fils,work,facteur*racine->d.q );
      }
}

ABR_P*	seek_abr_p(ABR_P* racine ,int key)
{
      if(racine)
      {
          if( racine->d.codep==key)
          return(racine);
          if(key<racine->d.codep)
          return(seek_abr_p(racine->gauche,key));
          return(seek_abr_p(racine->droite,key));
      }
      return(NULL);
}

void view_work (LISTE_W *work,ABR_P * racinep)
{
	   	 //ABR_P* p;
 		 if (work)
 		 {
		 	//p=seek_abr_p(racinep ,work->code);
			//printf("composant : %21.21s quantite:%5d \n",p->d.designation,work->qt);
			printf("composant : %d \n quantité : %d \n ", work->code,work->qt);
			view_work (work->next,racinep);
  	     }

}

void free_liste_w( LISTE_W* *work)
{                   LISTE_W*p;
  	     if(*work)
  	     {
		  	p=(*work);
		  	(*work)=(*work)->next;
		  	free(work);
         }
}

void get_composants (ARBRE * racine, ABR_P *racinep )
 {
       ARBRE*p;
       int compose;
       LISTE_W * work=NULL;
       printf("compose :");
       scanf ("%d",&compose);
       if(p=seek_noeud (racine,compose))
       r_get_composant(p->fils,&work,1);filtrer(&work,compose);
       view_work(work,racinep);
       free_liste_w(&work);
  }

  //*****************cout d'achat**************


float get_pa_composant(ABR_P* racine,int code)
{
 	  if(racine)
 	  {
	   		if(racine->d.codep==code)
      	    return(racine->d.cout);
      	    else
			if(racine->d.codep> code)
			return(get_pa_composant(racine->gauche,code));
			else
			return(get_pa_composant(racine->droite,code));
      }
      return(0);
}

void cout_achat(ARBRE* racine,ABR_P* racinep)
{
	 LISTE_W*work=NULL;
	  LISTE_W*save;
	 LISTE_T*travail=NULL;
	 float ca;
	 int code;
     ARBRE*p;
	 printf("donner le code de votre compose\n");
	 scanf("%2d",& code);

	 if(!(p=seek_noeud(racine,code)))
	    printf("pas de composé avec ce code\n");
	 else
	    r_get_composant(p->fils,&work,1);
	    save=work;
	    for(ca=0;work ;work=work->next)
			{


			ca+= get_pa_composant(racinep,work->code)*(work->qt);
			}
		printf("le cout d'achat de votre compose est:%f\n",ca);
	  free_liste_w(&save);
      //printf("votre liste est suprime\n\n");


}

//********************delete fournisseur ****


void supprime_fournisseur(ABR_F**racine,int code)
{
	 ABR_F*p;
     if(*racine)
     {
           if(((*racine)->d.code)>code)
           supprime_fournisseur(&((*racine)->gauche),code);
           else
           if(((*racine)->d.code)<code)
           supprime_fournisseur(&((*racine)->droite),code);
           else
           {
		   	   if(!((*racine)->droite) && !((*racine)->gauche))
		   	   {
	                  p=*racine;
	                  *racine=NULL;
	                  free(p);
			   }
			   else
			   {
			   	      if (!((*racine)->gauche))
					  {
					   	   p=(*racine);
					   	   (*racine)=((*racine)->droite);
					   	   free(p);
				      }
				       if (!((*racine)->droite))
					  {
					   	   p=(*racine);
					   	   (*racine)=((*racine)->gauche);
					   	   free(p);
				      }
				      else
				      {
					   	  for(p=((*racine)->gauche);p->droite;p=p->droite);
					   	  (*racine)->d=p->d;
					   	  supprime_fournisseur(&((*racine)->gauche),code);


					  }
			   }

           }
     }
     printf("les fournisseurs redendants sont suprimé");
}
void supprime_produit(ABR_P** racine,int code)
{
	 ABR_P*p,*q;
     if(*racine)
     {
           if(((*racine)->d.codef)>code)
           supprime_produit(&((*racine)->gauche),code);
           else
           if(((*racine)->d.codef)<code)
           supprime_produit(&((*racine)->droite),code);
           else
           {
		   	   if((!(*racine)->droite) &&( !(*racine)->gauche))
		   	   {
	                  p=*racine;
	                  *racine=NULL;
	                  free(p);
			   }
			   else
			   {
			   	      if (!((*racine)->gauche))
					  {
					   	   p=(*racine);
					   	   (*racine)=((*racine)->droite);
					   	   free(p);
				      }
				       if (!((*racine)->droite))
					  {
					   	   p=(*racine);
					   	   (*racine)=((*racine)->gauche);
					   	   free(p);
				      }
				      else
				      {
					   	  for(p=((*racine)->gauche);p->droite;p=p->droite);
					   	  ((*racine)->d)=p->d;
					   	  supprime_produit(&((* racine)->gauche), code);
					  }
			   }

           }
     }
      printf("les produits redendants sont suprimé");
}


void delete_fournisseur (ARBRE*racine,ABR_P**racine_p,ABR_F**racine_f)
{
 	 if(*racine_f)
 	 {
	  	  if(!(seek_noeud(racine,((*racine_f)->d.code))))
	  	  {
      		   		supprime_fournisseur(racine_f,((*racine_f)->d.code));
      		   		if(!(seek_noeud(racine,((*racine_p)->d.codep))))
      		   	    	supprime_produit(racine_p,((*racine_f)->d.code));
          }
		   delete_fournisseur (racine,racine_p,&((*racine_f)->gauche));
	       delete_fournisseur (racine,racine_p,&((*racine_f)->droite));
     }

}
//*************programme production
int lire_data(int *code,int*qt)
{
 	scanf(" %d %d",code,qt);
 	return((*code)!=-1);
}


LISTE_W* lire_programme ()
{
	 int code,qt;
     LISTE_W*w,*p;
     for(w=NULL;lire_data(&code,&qt); )
     {
	  		p=(LISTE_W*)malloc(sizeof (LISTE_W));
			p->code=code;
			p->qt=qt;
			p->next=w;
			w=p;
			return(w);
     }
}

void view_prog(LISTE_W*w,ABR_P *racine_p,char*s)
{
   ABR_P* p;int c;
 		 if (w)
 		 {
		 	p=seek_abr_p(racine_p ,w->code);
			printf("la matiere necessaire pour realiser le compose %21.21s est : %21.21s  \n",s,p->d.designation);
			if ((p->d.stock) < (w->qt))
			printf("SORRY cette matiere est de stock insuffisant !!!");
			//printf("SORRY cette matiere %21.21s est de stock insuffisant !!!", p->d.designation);
			view_prog(w->next,racine_p,s);
  	     }
  	     printf("ecrire 1");
  	     scanf("%d",c);
}

void get_programme_production (ARBRE*racine,ABR_P* racine_p)
{
	 char s[24];
	 ABR_P*q;
	 ARBRE*t;
	 LISTE_W*prog,*w,*p;
	 printf("donner votre programme\n");
 	 prog=lire_programme();
 	 for(p=prog ,w=NULL;p;p=p->next)
 	 {
           if(t=seek_noeud (racine,p->code))
           r_get_composant(t->fils,&w,p->qt);
           q=seek_abr_p( racine_p ,p->code);
           strcpy(s,q->d.designation);
           view_prog(w,racine_p,s);
           free_liste_w(&prog);
           free(p);
     }
}


int main()
{
     ABR_P* produit;
     ABR_F* fournisseur;
     ARBRE* composition;
     int option;


printf("***********************contenu de ABR Produit***********************************");
    produit = load_produit();
    affichage_produit(produit);
    printf("l'ABR produit est charge\n");
printf("***********************contenu de ABR fournisseur***********************************");
    fournisseur = load_fournisseur();
    affichage_fournisseur(fournisseur);
    printf("l'ABR fournisseur est charge\n");

printf("***********************contenu de ARBRE composition***********************************");
     composition = load_composition();
     affichage_arbre(composition);
     printf("l'ARBRE composition est charge\n\n");

    //  while(option=get_option())
     //{
       //           switch(option)
         //         {
           //                    case(1):
                               get_composants (composition, produit );
             //                  break;
               //                case(2):
                              cout_achat(composition,produit);
                 //             break;
                  //             case(3):
                              delete_fournisseur (composition,&produit,&fournisseur) ;
                    //           break;
                      //         case(4):
                               get_programme_production (composition,produit);
                    /*           break;
                               default:
							   printf("erreur l'option est compris entre 1 et 4!!!! \n");
                 }
     }
*/
     getch();
     system("pause");
     return(1);

}
