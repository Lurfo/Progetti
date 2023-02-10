package PrimaProva;

import java.util.Scanner;

public class Riferimento {
    public static void main(String[] args){
        //Programma che va a fare un controllo tra gli oggetti
        Scanner sc = new Scanner(System.in);
        
        //Per andare ad prendere un input dal terminale, vaso ad usare un metodo apposito della classe sc
        System.out.println("Inserisci una stringa s1:");
        String s1 = sc.nextLine();


        System.out.println("Inserisci una stringa s2:");
        String s2 = sc.nextLine(); 

        //Inserendo un +, tra i vari elementi, vado ad eseguire una concatenazione di stirnghe
        System.out.print("s1 Uguale a:" +s1 +"\n");
        System.out.print("s2 Uguale a: " +s2 +"\n");

        //Utilizzo una classe apposita che permette di utilizzare l'inseriemento da tastiera
        if(s1.equals(s2)){
            System.out.println("Sono uguali\n");
        }

        else{
            System.out.println("Sono Differenti\n");
        }
        
        //Al termine dell'utilizzo di ciò che mi occorre, devo andare a chiudere la classe scanner
        sc.close();

    }
}
