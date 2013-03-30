package testJava;


public class Priorité
{
	
	public Priorité (Processus[] pro)
	{
	//super()
		 int Horloge=0;
                //this.pro = pro;
                  
                  
		for(int i=0;i<pro.length;i++){
			for(int j=1;j<pro.length;j++)
			{ 
				
			if(pro[i].get_priorité() > pro[j].get_priorité()){
  
				System.out.println(i+ "est plus prioritaire que" + pro);
				
			}
	       int a=pro[i].get_Duree();
				{
				Horloge=Horloge+a;
				int TR=Horloge+a;
				int TA=TR-a;
				pro[i].set_TA(TA);
				pro[i].set_TR(TR);
				System.out.println(pro[i].toString());
				  
				}
		}
}
}

}
