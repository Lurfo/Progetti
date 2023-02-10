#Considero due variabili con assegnazione multipla
a, b = 0, 1

#Esegup un ciclo while per un numero grande di volte
while b<10000:
    print (b), #Mettere la virgola, permette di stampare ogni volta sulla stessa riga, senza andare a capo
    a, b = b, a+b #Eseguo una doppia assegnazione
