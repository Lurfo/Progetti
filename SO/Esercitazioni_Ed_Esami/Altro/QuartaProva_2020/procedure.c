#include "header.h"

void inizializza(struct monitor *m)
{

    m->molo = 0;
    m->id_nave = 0;
    /* TBD: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */
    m->num_lettori = 0;
    m->num_scrittori = 0;

    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cv_lettore, NULL);
    pthread_cond_init(&m->cv_scrittore, NULL);
}

void rimuovi(struct monitor *m)
{
    /* TBD: Disattivare mutex e variabili condition */
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->cv_lettore);
    pthread_cond_destroy(&m->cv_scrittore);
}

//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_molo(struct monitor *m, int molo)
{
    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della SCRITTURA
     */
    int rc = pthread_mutex_lock(&m->mutex);
    if (rc != 0)
    {
        printf("pthread_mutex_lock failed %d - Quit\n", rc);
        exit(1);
    }

    while (m->num_scrittori > 0 || m->num_lettori > 0)
        pthread_cond_wait(&m->cv_scrittore, &m->mutex);

    m->num_scrittori++;

    rc = pthread_mutex_unlock(&m->mutex);
    if (rc != 0)
    {
        printf("pthread_mutex_unlock failed %d - Quit\n", rc);
        exit(1);
    }

    m->molo = molo;

    rc = pthread_mutex_lock(&m->mutex);
    if (rc != 0)
    {
        printf("pthread_mutex_lock failed %d - Quit\n", rc);
        exit(1);
    }
    m->num_scrittori--;

    pthread_cond_broadcast(&m->cv_lettore);

    rc = pthread_mutex_unlock(&m->mutex);
    if (rc != 0)
    {
        printf("pthread_mutex_unlock failed %d - Quit\n", rc);
        exit(1);
    }
}

//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_molo(struct monitor *m)
{
    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della LETTURA
     */
    pthread_mutex_lock(&m->mutex);
    while (m->num_lettori > 0)
        pthread_cond_wait(&m->cv_lettore, &m->mutex);

    m->num_lettori++;
    pthread_mutex_unlock(&m->mutex);

    int pos = m->molo;

    pthread_mutex_lock(&m->mutex);

    m->num_lettori--;

    if (m->num_lettori == 0)
        pthread_cond_signal(&m->cv_scrittore);

    pthread_mutex_unlock(&m->mutex);

    return pos;
}
