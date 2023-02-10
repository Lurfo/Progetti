#Prova di un piccolo programma in python

#definisco una variabile

#Nota che una funzione non deve specificare il tipo di ritorno
def max(x, y) :
  
    if(x>y):
        return x

    else:
        return y


a=4
print("Ho definito un valore %d\n" % a)

print(type(a))

print("Posso magicamente far diventare a una stringa\n")

#Devo usare questa funzione di input per prendere in ingresso una stringa!
a=raw_input("Dimmi una stringa che devo affibbiare ad a\n")

print("Ora, a e' infatti una stringa: %s" %a)
print(type(a))

#In questo modo va sfruttata la funzione di inserimento
b = raw_input("Dimmi sto cazz di valore\n")

print("hai defninto un valore: %s" %b)

c=max(a,b)

print("Il massimo tra i due valori che ti ho fatto vedere e' %s\n" %c)