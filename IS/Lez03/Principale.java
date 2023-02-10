import java.util.Scanner;

public class Principale {
    
    public static void main(String[] args) {
        
        //Privo con il richiamo della struttura persona
        Persona uomo;
        String nome, cognome; 
        int età, cilindrata;
        String modello, targa, costruttore;
        Moto nuova;

        Scanner sc = new Scanner(System.in);
        Scanner sc1 = new Scanner(System.in);

        System.out.println("Dimmi il nome:");
            nome  = sc.nextLine();
        
        System.out.println("Dimmi il cognome:");
            cognome = sc.nextLine();

        System.out.println("Dimmi età:");
            età = sc1.nextInt();

        System.out.println("Definisco la persona:");
            uomo = new Persona(nome, cognome, età);

        System.out.println("Mi hai specificato: ");
        uomo.chiSono();
        
        System.out.println("Dimmi Modello, Costruttore, Targa e Cilindrata:");
            modello=sc.nextLine();
            costruttore = sc.nextLine();
            targa = sc.nextLine();
            cilindrata = sc1.nextInt();

        //Inizializzo quindi la Moto
        System.out.println("Definisco la moto\n");
        nuova = new Moto(uomo, targa, modello, costruttore, cilindrata);
    

        System.out.println("La moto inserita è:");
        nuova.info();

        sc.close();
        sc1.close();

    }

}
