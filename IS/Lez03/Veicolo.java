public class Veicolo {
    
    protected Persona prop ;
    private String targa;

    public Veicolo(String nome, String cognome, int età, String targa){
        this.prop = new Persona(nome, cognome, età);
        this.targa = new String(targa);
    }

    public Veicolo(Persona proprietario, String targa){
        System.out.println("Nel costruttore di Veicolo, tento di fare equals");
        this.prop = new Persona(proprietario);
        this.targa = new String(targa);
    }

    public void info(){
        System.out.println("Proprietario: ");
        prop.chiSono();
        System.out.println("\n");
        System.out.println("Targa: "+targa+"\n");
    }




}
