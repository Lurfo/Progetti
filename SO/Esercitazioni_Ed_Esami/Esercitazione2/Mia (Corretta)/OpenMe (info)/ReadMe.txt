Correzzione della prova di autovalutazione, andando a modificare l'ingresso al monitor da parte dei produttori e dei consumatori
inoltre, ho anche la necessità di andare a modificare la variabile condition, in modo da poter sfruttare in modo
più efficiente le possibilità del buffer circolare!


In particolare: 
    -Inserisco solo un valore che mi permette di andare a tenere traccia del numero di elementi presenti nel buffer circolare
    che viene poi sfruttata da produttori e consumatori come condizione
    
    -Modifico le modalità di accesso al monitor, da parte di procuttori e consumatori, in modo che il produttore e il consumatore
    quando devono produrre si trovino sempre all'interno del monitor!