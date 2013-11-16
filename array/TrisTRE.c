//TrisTRE.c
//Gioco del tris per giocatori umani e CPU
//Creato da Erio Ruggieri

#include <stdio.h>
#define DIM 3

int ControlloTris(int t2[DIM][DIM], int giocatore);
void AutoMossa(int t2[DIM][DIM], int cv, int giocatore, int *posmigliore, int *perfetta);

int ControlloTris(int t2[DIM][DIM], int giocatore)
{
    int i, v=0, par;
    //Inizio serie di cicli che controllano lo stato del gioco:
    //Controllo righe
    for(i=0;i<3;i++)
        if(t2[i][0] == t2[i][1] && t2[i][1] == t2[i][2] && t2[i][0]!=0)
            v=1;
    //Controllo colonne
    for(i=0;i<3;i++)
        if(t2[0][i] == t2[1][i] && t2[1][i] == t2[2][i] && t2[0][i]!=0)
            v=1;
    //Controllo diagonali
    if(t2[0][0] == t2[1][1] && t2[1][1] == t2[2][2] && t2[1][1]!=0)
        v=1;
    else if (t2[0][2] == t2[1][1] && t2[1][1] == t2[2][0] && t2[1][1]!=0)
        v=1;
    //Controllo che identifica uno stato di parità
    par=0;
    for(i=0;i<3;i++)
        if(t2[i][0]!=0 && t2[i][1]!=0 && t2[i][2]!=0 && v!=1)
            par++;
        if(par==3)
            v=2;
    return v;
}

void AutoMossa(int t2[DIM][DIM], int cv, int giocatore, int *posmigliore, int *perfetta)
{
    int i, p, pos, buona;

for(*perfetta=-2,i=0;i<3;i++) //Verifico tutte le situazioni possibili di gioco
    for(p=0;p<3;p++)
        if (t2[i][p]==0) //Se la casella è vuota calcolo il susseguirsi di mosse possibili
        {
            t2[i][p]=giocatore; //Marco la casella con l'id giocatore
            if (ControlloTris(t2,giocatore)==1) //Se faccio tris la mossa è buona
                buona=cv; //ed equivale al numero di caselle vuote (così capisco qual è la migliore in assoluto)
            else if (ControlloTris(t2,giocatore)==2) //Se finisce pari non m'interessa che sia buona o meno
                buona=0;
            else
            {
                AutoMossa(t2,cv--,(giocatore%2)+1,&pos,&buona); //Richiamo la funzione stessa cambiando giocatore per continuare questo gioco "ipotetico" e valutare fin dove finisce
                buona=-buona; //Se la mossa del giocatore precedente era buona allora la cambio di segno così diventa "non-buona" per il giocatore precedente
            }
            if (buona>*perfetta) //Dopo che la partita ipotetica è terminata se la mossa buona è maggiore di perfetta (inizialmente è -2)
            {
                *perfetta=buona; //allora la mossa buona è perfetta
                *posmigliore=p+(i*10); //assegno le coordinate ad un solo valore intero che andrò a scomporre più tardi fuori dalla funzione
            }
            t2[i][p]=0; //Dopo aver finito la partita ipotetica occorrerà liberare la casella dato che di fatto non dovrebbe essere occupata
        }
}


int main()
{
    int i, p, v, a=1, b=1, giocatore=2, scelta, cv=9, qualepos, ab, *posmigliore, *migliormossa;
    char t[DIM][DIM]; //Dichiaro una matrice di caratteri (3x3) per la stampa della griglia di gioco
    int t2[DIM][DIM]; //Dichiaro una matrice di interi (3x3) per permettere all'IA di calcolare la mossa

    //Inizializzo la matrice grafica con il carattere spazio e quella logica con 0
    for(i=0;i<3;i++)
        for(p=0;p<3;p++)
        {
            t[i][p]=' ';
            t2[i][p]=0;
        }

    //Stampo il titlescreen con la matrice di gioco e un menu selezionabile
    printf("\n######### TRIS #########\n");
    printf("\nInizio del gioco:\n\n[ ][ ][ ]\n[ ][ ][ ]\n[ ][ ][ ]\nCosa vuoi fare?\n\n1. Umano vs. Umano\n2. Umano vs. CPU\n3. CPU vs. CPU\n");
    scanf("%d", &scelta);
    if(scelta==2)
            printf("\nE' inutile provarci, non puoi battere il computer ;) \n");
    //Il ciclo verifica che il gioco non sia terminato dunque cicla per l'intera durata della partita
    while(ControlloTris(t2,giocatore)==0)
    {

        //Cambio giocatore
        giocatore=(giocatore%2)+1;

        //Funzione giocatore umano
        if((scelta==2 && giocatore==1) || scelta==1)
        {
            printf("\nGiocatore %d inserisci le coordinate: ", giocatore);
            scanf("%d %d", &a, &b);
            while(a<1 || b<1 || a>3 || b>3) //Controllo che verifica l'idoneità delle coordinate
            {
                printf("\nCoordinata inesistente, riprova: ");
                scanf("%d %d", &a, &b);

                while(t2[a-1][b-1]!=0) //Controllo anti-cheat (il giocatore non può sovrascrivere una mossa già effettuata)
                {
                    printf("\nNon barare! Riprova: ");
                    scanf("%d %d", &a, &b);
                }
            }
            while(t2[a-1][b-1]!=0)
            {
                printf("\nNon barare! Riprova: ");
                scanf("%d %d", &a, &b);
            }
        }

        //Funzione giocatore automatico
        else if((scelta==2 && giocatore==2) || scelta==3)
        {
            printf("\nTurno del Cyber-giocatore %d\n", giocatore);
            AutoMossa(t2,cv,giocatore,&ab,&qualepos);
            b=(ab%10)+1;
            a=(ab/10)+1;
        }

        if (giocatore == 1) //Controllo identità del giocatore
        {
            t[a-1][b-1]='X'; t2[a-1][b-1]=1;
        }
        else
        {
            t[a-1][b-1]='O'; t2[a-1][b-1]=2;
        }

        //Nella riga di seguito stampo la matrice di gioco aggiornata
        printf("\nQuesta e' la situazione di gioco:\n\n[%c][%c][%c]\n[%c][%c][%c]\n[%c][%c][%c]\n", t[0][0], t[0][1], t[0][2], t[1][0], t[1][1], t[1][2], t[2][0], t[2][1], t[2][2]);

        for(i=0;i<3;i++)
            for(p=0;p<3;p++)
                if(t2[i][p]==0)
                    cv++;//Conteggio delle caselle vuote
    }//Fine ciclo partita
    if(ControlloTris(t2,giocatore)==1)
        printf("\nIl giocatore %d vince!\n\n", giocatore);
    else if(ControlloTris(t2,giocatore)==2)
        printf("\nParita'!\n");
}
