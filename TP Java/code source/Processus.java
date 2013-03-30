package testJava;



public class Processus {
	
	private String nom;
	private  int Duree;
	
	private int taille ;
	
	private int TR = 0;
	private int TA=0;
	private int Date_deb;
	private int priorité;
	public Processus()
	{
}
	
	
	
	public  Processus (String x1,int D,int prio,int tail)
	{
		nom=x1;
		Duree =D;
		priorité = prio ;
		taille = tail ;
	}
	public String get_Nom()
	{
		return (nom);
	}
	public void Set_nom (String x)
	{
		nom=x;
	}
	public int get_Duree()
	{
		return(Duree);
	}
	public void set_Duree(int D1)
	{
		Duree=D1;
	}
	public int get_TR ()
	{
		return(TR);
	}
	public void set_TR (int TR1 )
	{
		TR=TR1;
	}
	public int get_TA ()
	{
		return(TA);
	}
	public void set_TA (int TA1)
	{
		TA=TA1;
	}
	public int get_Date_deb ()
	{
		return(Date_deb);
	}
	public void set_Date_deb(int Date_deb1)
	{
		Date_deb=Date_deb1;
	}
	
	public int get_priorité()
	{
		return(priorité);
	}
	public void set_get_priorité(int prioritééé)
	{
		priorité=prioritééé ;
		
	}
	public int get_taille()
	{
		return(taille) ;
	}
	public void set_get_taille(int tailleeee)
	{
		taille = tailleeee ;
	}
	
	

	
public  String ToString ()

{  return ( "le nom du processeur :" +nom+"la date de dÃ©but de processeur est:" +Date_deb+  "le durÃ©e de processus est "+Duree );
	}
}
	
	
