//Tramite l'uso di extends, posso dire che Persona deriva direttamente dalla classe Persona

public class Studente extends Persona {
    
    
    private    String matricola;
    private    String facoltà;

    

    public    Studente(String nome, String cognome, int età, String matricola, String facoltà){
            //Utilizzo una funzione speciale, "super" che permette di andare a richiamare le funzionalità della classe padre
            super(nome, cognome, età);

            //Inizializzo poi i valori della classe studente
            this.matricola = new String(matricola); 
            this.facoltà = new String(facoltà);
        }

    public    void chiSono(){
            super.chiSono(); 
            System.out.println("Matricola: "+matricola+", Facoltà:"+facoltà+"\n");
        }
    

}
