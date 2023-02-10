In questo caso, implemento un file su più eseguibili, che vanno a creare una serie di messaggi all'interno della coda
e un solo processo che li va a leggere

Implemento una soluzione asincrona, in modo che vado ad inserire una serie di messaggi senza bisogno di sincronizzazione
solo il processo che legge usa una receive bloccante, in modo che se non ci sono messaggi nella coda, allora vado a sospendermi
