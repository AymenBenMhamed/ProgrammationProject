package testJava;


import java.io.*;
import javax.swing.*;

public class Memoire {
	
	public Processus p[];

	
	public void donnermemoire(Processus[] p)
	{
	//declaration de variable
	JOptionPane jop3 = new JOptionPane();
	JOptionPane jop4 = new JOptionPane();
	//saisie de donnée
	
	//Processus p[]=new Processus[0];

	String b = jop3.showInputDialog(null, "DONNER LA TAILLE DE LA MEMOIRE EN ko", "tp", JOptionPane.QUESTION_MESSAGE);
	int taille = Integer.parseInt(b);

	String c = jop3.showInputDialog(null, "DONNER LE NOMBRE DE PARTITIONNEMENT", "tp", JOptionPane.QUESTION_MESSAGE);
	int nbp = Integer.parseInt(c);


	jop4.showMessageDialog(null,"LE NOMBRE DE PROCESSUS:" + p.length  +"\n" + "LA TAILLE DE LA MEMOIRE EN ko:" + taille +"\n"  + "DONNER LE NOMBRE DE PARTITIONNEMENT:"+ nbp ,"LECTURE DE DONNER", JOptionPane.INFORMATION_MESSAGE);



	int tp[][]=new int[100][100];

	
	for (int i=1;i<=nbp;i++)
	{

	String tailpart = jop3.showInputDialog(null, "DONNER LA TAILLE DE LA PARTITION Numero " + i, "tp", JOptionPane.QUESTION_MESSAGE);
	int X = Integer.parseInt(tailpart);
	tp[i][1] = X ;  //0 si l'espace est libre sinon contient le numero de processus
	tp[i][2] = 0 ;
	}
	
	/*Une autre vision de voir le chose est de conciderer une matrice dans le nombre de ligne est le nombre de 
	 * processus et le nombre de colonne est 6 :
	 * 1ere col : Nom de processus
	 * 2eme col : taille de processus
	 * 3eme col : temps d'arrivée 
	 * 4eme col : temps d'execution
	 * 5eme col :temps estimer pour la fin de processus
	 * 6eme col : priorité
	 * 
	int info[][]=new int[100][100];

	for (int i=1;i<=p.length;i++)
	{
	info[i][1] = i ;
	//jop4.showMessageDialog(null,"Processus Numero " + i, JOptionPane.INFORMATION_MESSAGE);
	String tail1 = jop3.showInputDialog(null, "TAILLE EN ko" , "Processus" + i, JOptionPane.QUESTION_MESSAGE);
	int XX = Integer.parseInt(tail1);
	info[i][2] = XX ;

	String tail2 = jop3.showInputDialog(null, "DATE D ARRIVER : " , "Processus" + i, JOptionPane.QUESTION_MESSAGE);
	int XXX = Integer.parseInt(tail2);
	info[i][3] = XXX;

	String tail3 = jop3.showInputDialog(null, "LE TEMPS D EXCUTION :  ", "Processus" + i, JOptionPane.QUESTION_MESSAGE);
	int XXXX = Integer.parseInt(tail3);
	info[i][4] = XXXX ;

	info[i][5] = info[i][3]+info[i][4] ;

	String tail4 = jop3.showInputDialog(null, "PRIORITEE " , "Processus" + i, JOptionPane.QUESTION_MESSAGE);
	int XXXXX = Integer.parseInt(tail4);
	info[i][6] = XXXXX ;

	jop4.showMessageDialog(null,"TAILLE DE PROCESSUS:" + XX  +"\n" + "DATE D'ARRIVEE:" + XXX +"\n"  + "TEMPS D'EXCUTION :"+ XXXX + "\n" + "TEMPS DE FIN D'EXCUTION :"+ info[i][5] + "\n" + "PRIORITEE :" + XXXXX ,"Information sur le Processus" + i, JOptionPane.INFORMATION_MESSAGE);
	}

	//s:Temps total de Connexion
	int s=0;
	for (int i=1;i<=p.length;i++)
	{
	s+=info[i][4];
	}
	
	*/
	
  	int s=0 ;
	for (int ii=0 ; ii <= p.length ;ii++)
	{
		s= s+ p[ii].get_Duree() ;
	}

	
	//System.out.println(s);
	int L=1;
	int k=1;
	int memoireattend[]=new int[100];
	int tabproc[]=new int[100];



	for (int t=0;t<s;t++)
	{
		for (int i=1;i<= p.length;i++)  
		{
			if ( p[i].get_Date_deb() == t)
			{
				for (int j=1;j<=nbp;j++)
				{
					if (tp[j][1]<p[i].get_taille())
					{
						jop4.showMessageDialog(null,i+ "Ne peut pas étre allouer dans la partition " + j + "de la memoire à cause de la taille" ,"traitement", JOptionPane.INFORMATION_MESSAGE);
						//System.out.println( i+ "Ne peut pas étre executé");// i sera differer 
					}
				}
			boolean test=true ;	
			for (int j=1;j<=nbp && test ;j++)
			 {
				if((tp[j][1]>=p[i].get_taille()) && (tp[j][2]==0))
				{
					tp[j][2]=i;
					test= false ;// si on a cette condition on sort definitivement de la boucle pour !!!!!
				}
			  }
				
			}
		}
		
		int lib ;
		for (int i1=1;i1<=p.length;i1++)
		{
			if ( p[i1].get_Date_deb() == t)
			{
				for (int j1=1;j1<=nbp;j1++)
				{
					lib = tp[j1][2] ;
					if (lib!=0)
					{
						if ((p[i1].get_taille()<=tp[j1][1]) && (p[lib].get_priorité() < p[i1].get_priorité()))
						{
							memoireattend[L]=tp[j1][2];
							tp[j1][2]=i1 ;
							L++ ;
						}
					}
				}
			}
	
			
for (int i2=1;i2<=p.length;i2++)		
{
	for (int compt=1;compt<=nbp;compt++)
		{
			if ((tp[compt][2]==i2))
			{
		if (t==p[i2].get_TR())
		{
			System.out.println( i2+ " va étre allouer par le processeur ");
			tabproc[k]=i2 ;
			k++;
		}
		
	}
		}
}
	
		for (int c0=1;c0<=p.length;c0++)
			{
				for (int c1=1;c1<=nbp;c1++)
				{
					if ((tp[c1][2]==0) && (tp[c1][1]>=p[c0].get_taille()))
							{
						tp[c1][1]=memoireattend[c0];
						//L++;			
				}
			}
		}
	}
}

	jop4.showMessageDialog(null,"Le Processus par ordre d'excution dans le Processeur :","traitement", JOptionPane.INFORMATION_MESSAGE);
	//System.out.println("Le Processus par ordre d'excution dans le Processeur :");
	for (int c2=1;c2<=p.length;c2++)
	{
		//System.out.println(tabproc[c2]);
		jop4.showMessageDialog(null,tabproc[c2],"traitement", JOptionPane.INFORMATION_MESSAGE);
	}

	
	
}
}
