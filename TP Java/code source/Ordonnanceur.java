package testJava;


public class Ordonnanceur extends Thread{
	
	//tableau des proccessus
		public Processus pro[];
		//horloge
		int horloge=0;
		int trr=0,taa=0;

		public Ordonnanceur(Processus[] pro) {
			super();
			this.pro = pro;
		}

		public void run(){
			for(int i=0;i<pro.length;i++){
				//parcour des tableau
				
				pro[i].set_Date_deb(horloge);
				pro[i].set_TA(horloge);
				taa+=horloge;
				horloge=horloge+pro[i].get_Duree();
				pro[i].set_TR(horloge);
				trr+=horloge;
				
				
			}
						
			
		}
}
		
