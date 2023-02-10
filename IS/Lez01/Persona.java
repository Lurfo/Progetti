

public class Persona {
    //Utilizzo protected, in modo che le classi figlie possano diressamente accedere alle variabili protette della classe padre
    
    protected    String nome; 
    protected    String cognome; 
    protected    int età;
    
    //Questi sono tutti i metodi che deve contenere la struttura, impostati public in modo che tutti possano accedervi
    
    public    Persona(String nome, String cognome, int età){
            
            //Per identificare che ho a che fare con gli oggetti che appartengono a questa classe, utilizzo il puntatore this
            //un puntatore speciale che punta proprio a questa classe
            this.nome = new String(nome); 
            this.cognome = new String(cognome);
            this.età = età;
        
    
        }

        //Definisco una funzione che mi stampa a video le informazioni contenute nella classe
    public    void chiSono(){
            System.out.println("Nome: " +nome +" Cognome: "+cognome +" età: "+età);
        }
}
