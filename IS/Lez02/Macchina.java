 
//Definisco la classe macchina, come una classe astratta, quindi come un'interfaccis che viene poi usata dalle altre classi
public abstract class Macchina {

    //public enum marcia{prima, seconda, terza, quarta, quinta, sesta, folle};
    //public enum stato{ACCESO, SPENTO};

    //Inserimento di tutti gli attributi della classe!
    protected String marca; 
    protected String modello;
    protected int velocità;
    protected int accelerazione;
    protected String marcia;
    protected String stato;

    //Definizione del costruttore che contiene i valori iniziali
    public Macchina(String marca, String modello, int v, int a, String myGear, String myStatus){

    }
}


