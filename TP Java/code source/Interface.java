package testJava;



import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;

public class Interface extends JFrame implements ActionListener {
	JPanel p1;
	Processus p[]=new Processus[0];
	JTable t1=new JTable();
	JTable t2=new JTable();
	
	JButton ajout=new JButton("Ajouter");
	JTextField nom=new JTextField();
	JTextField dure=new JTextField();
	JTextField priorité=new JTextField();
	JTextField taille=new JTextField();
	JLabel ne=new JLabel("Nouveau Processus: ");
	JLabel n=new JLabel("Nom: ");
	JLabel d=new JLabel("Durée:");
	JLabel k=new JLabel("Priorité: ");
	JLabel l=new JLabel("Taille:");
	
	JButton fifo=new JButton("Gestion file d'attente Memoire FIFO");

	JLabel ta=new JLabel("Temps Moyenne d'attente:");
	
	JLabel tr=new JLabel("Temps Moyenne de Repponse:");	
	DefaultTableModel model1;
	
	DefaultTableModel model2;
	public Interface() throws HeadlessException {
		super();
		p1=(JPanel)this.getContentPane();
		p1.setLayout(null);
		this.setSize(700,800);
		this.setTitle("Projet");
		this.setLocationRelativeTo(null);
		// *
		model1=(DefaultTableModel)t1.getModel();
		model1.setRowCount(0);
		model1.setColumnCount(4);
		Object[] row=new Object[4];
		
		row[0]="Nom";
		row[1]="Durée";
		row[2]="Priorité";
		row[3]="taille";
		
		model1.addRow(row);
		t1.setModel(model1);
		// mise en place
		
		p1.add(ne);
		ne.setBounds(10, 10, 500, 30);
		p1.add(n);
		n.setBounds(10,40, 100, 30);
		p1.add(d);
		d.setBounds(10, 100, 100, 30);
		p1.add(k);
		k.setBounds(290,40, 100, 30);
		p1.add(l);
		l.setBounds(290, 100, 100, 30);
		
		p1.add(nom);
		nom.setBounds(120, 40, 100, 30);		
		p1.add(dure);
		dure.setBounds(120, 100, 100, 30);
		p1.add(priorité);
		priorité.setBounds(350, 40, 100, 30);	
		p1.add(taille);
		taille.setBounds(350, 100, 100, 30);	
		
		p1.add(ajout);
		ajout.setBounds(10, 160, 100, 30);
		
		p1.add(t1);
		t1.setBounds(10, 200, 650, 200);
		p1.add(fifo);
		fifo.setBounds(360, 400, 289, 30);
		
		p1.add(t2);
		t2.setBounds(10, 450, 650, 200);
		
		p1.add(ta);
		ta.setBounds(10, 670, 650, 30);
		
		p1.add(tr);
		tr.setBounds(10, 720, 650, 30);
		ajout.addActionListener(this);
		fifo.addActionListener(this);
	
		
		//***
		
		model2=(DefaultTableModel)t2.getModel();
		model2.setRowCount(0);
		model2.setColumnCount(5);
		
		Object[] row2=new Object[5];
		row2[0]="Nom";
		row2[1]="Durée";
		row2[2]="Date debut";
		row2[3]="TR";
		row2[4]="TA";
		
		model2.addRow(row2);
		t2.setModel(model2);
		
		
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {  
		// TODO Auto-generated method stub
		if(arg0.getSource()==ajout){
			
			Object[] row=new Object[4];
			row[0]=nom.getText();
			row[1]=dure.getText();
			row[2]=priorité.getText();
			row[3]=taille.getText();
			
			model1.addRow(row);
			t1.setModel(model1);
			Processus pp[]=new Processus[p.length+1];
			for(int i=0;i<p.length;i++){
				pp[i]=p[i];
			}
			pp[p.length]=new Processus(row[0].toString(),Integer.parseInt(row[1].toString()),Integer.parseInt(row[2].toString()),Integer.parseInt(row[3].toString()));
			p=pp;
		}
		if(arg0.getSource()==fifo){
			Ordonnanceur fi=new Ordonnanceur(p);
			fi.run();
			model2=(DefaultTableModel)t2.getModel();
			model2.setRowCount(0);
			model2.setColumnCount(5);
			Object[] row2=new Object[5];
			row2[0]="Nom";
			row2[1]="Durée";
			row2[2]="Date debut";
			row2[3]="TR";
			row2[4]="TA";
			
			model2.addRow(row2);
			for(int i=0;i<p.length;i++){
				
				row2=new Object[5];
				row2[0]=p[i].get_Nom();
				row2[1]=p[i].get_Duree();
				row2[2]=p[i].get_Date_deb();
				row2[3]=p[i].get_TR();
				row2[4]=p[i].get_TA();
				
				model2.addRow(row2);
				t2.setModel(model2);
				
			}
			ta.setText("Temps Moyenne d'attente: "+fi.taa/p.length);
			tr.setText("Temps Moyenne de Repponse:"+fi.trr/p.length);
	
			
		}
		
		
	}
	public static void main(String[] args) {
		Interface i=new Interface();
		i.setVisible(true);
	}
	

}
