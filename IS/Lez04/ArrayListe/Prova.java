package ArrayListe;

import ArrayListe.Provo.Persona;

//Importo la libreria necessaria che contiene gli elementi che mi interessano
//Con l'asterisco finale, vado ad importare tutti gli strumenti che sono al suo interno
import java.util.*;

public class Prova {
    
    public static void main(String[] args) {
        
        //Mi dichiaro un arraylist di persone, lo vado anche ad inzializzare!
        ArrayList<Persona> vett = new ArrayList<Persona>();

        //Mi creo una serie di persone!
        Persona p1 = new Persona("mario", "rossi", 123);
        Persona p2 = new Persona("michele", "Gianmaria", 1234);
        Persona p3 = new Persona("stefano", "d'onofrio", 1304);
        Persona p4 = new Persona("piero", "angela", 2354);

        //Inserisco le persone nella lista
        vett.add(p1);
        vett.add(p2);
        vett.add(p3);
        vett.add(p4);

        //Inserite le persone nella lista, le stampo a video
        System.out.println("Provo stampa con il for\n");;
        for(int i=0; i<vett.size(); i++){
            vett.get(i).chiSono();
        }
    
        


    
    }




}
