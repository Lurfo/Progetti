Implementazione del problema lettore/scrittore con starvation di entrambi, usando il monitor di Hoare!
In questo caso, siccome ho un signal and wait, allora devo andare a controllare la condizione usando un if
considerando che: 
    -Ogni scrittore può accedere in mutua esclusione alla risorsa
    -Lettori e scrittori devono sincronizzarsi nell'accesso alla risorsa 
    -Tutti i lettori possono accedere contemporaneamente alla risorsa!