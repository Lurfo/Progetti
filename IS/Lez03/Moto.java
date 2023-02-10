public class Moto extends Veicolo {
    
    private String modello;
    private String costruttore;
    private int cilindrata;

    public Moto(String nome, String cognome, int età, String targa, String modello, String costruttore, int cilindrata){
        super(nome, cognome, età, targa);
        this.modello = new String(modello);
        this.costruttore = new String(costruttore);
        this.cilindrata = cilindrata;
    }

    public Moto(Persona proprietario, String targa, String modello, String costruttore, int cilindrata){
        super(proprietario, targa);
        System.out.println("Nel costruttore moto, chiamato il costruttore di veicolo");
        this.modello = new String(modello);
        this.costruttore = new String(costruttore);
        this.cilindrata = cilindrata;
    }


    public void info(){
        super.info();
        System.out.println("Modello: "+modello+" Costruttore: "+costruttore+" Cilindrata:"+cilindrata+"\n");
    }

}
