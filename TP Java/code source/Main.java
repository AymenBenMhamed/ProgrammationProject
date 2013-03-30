package testJava;


public class Main {
	public static void main(String[] args) {
		
		
		
		Processus p[]=new Processus[4];
		p[0]=new Processus("Pross0",3,0,200);
		p[1]=new Processus("Pross1",9,2,150);
		p[2]=new Processus("Pross2",31,1,100);
		p[3]=new Processus("Pross3",5,3,300);
		
        Ordonnanceur fifo = new Ordonnanceur(p);
		fifo.run();
		
		Memoire m = new Memoire();
		m.donnermemoire(p);
		
		
		
		
	
		
	
	}

}
