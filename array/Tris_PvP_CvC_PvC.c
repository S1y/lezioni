//Esempio di esercizio sull'utilizzo degli array
//Tris.c
//Erio Ruggieri 30/10/2013

#include <stdio.h>
#include <time.h>
int main()
{
    int i, p, m, md1, md2, v=0, a=1, b=1, giocatore=0, par, ok, scelta;
    char t[3][3]; //Dichiaro una matrice di caratteri 3x3 per la stampa della griglia di gioco
    int t2[3][3]; //Dichiaro una matrice di interi 3x3 per permettere all'IA di calcolare la mossa

    //Inizializzo la funzione random
    int rand(void);
    srand(time(NULL));

    //Inizializzo la matrice grafica con il carattere spazio e quella logica con 1
    for(i=0;i<3;i++)
    {
        for(p=0;p<3;p++)
        {
            t[i][p]=' ';
            t2[i][p]=1;
        }
    }

    //Stampo il titlescreen con la matrice di gioco e un menu selezionabile
    printf("\n######### TRIS #########\n");
    printf("\nInizio del gioco:\n\n[ ][ ][ ]\n[ ][ ][ ]\n[ ][ ][ ]\nCosa vuoi fare?\n\n1. Umano vs. Umano\n2. Umano vs. CPU\n3. CPU vs. CPU\n");
    scanf("%d", &scelta);

    //Il ciclo verifica che il gioco non sia terminato dunque cicla per l'intera durata della partita
    while(v == 0)
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

                        while(t2[a-1][b-1]!=1) //Controllo anti-cheat (il giocatore non può sovrascrivere una mossa già effettuata)
                        {
                            printf("\nNon barare! Riprova: ");
                            scanf("%d %d", &a, &b);
                        }
                    }
                }

                //Funzione giocatore automatico (il comando "sleep" serve solo a dare un tocco di realismo e umaintà)
                else if((scelta==2 && giocatore==2) || scelta==3)
                {
                    printf("\nTurno del Cyber-giocatore %d\n", giocatore);
                    sleep(1);
                    printf("\nFammi riflettere...\n");
                    sleep(2);

                    do{
                        ok=0; //Azzero la variabile "ok", servirà a sapere se il giocatore automatico ha già scelto quale mossa eseguire oppure no

                        //Controllo se è possibile fare tris oppure ostacolare l'avversario su una riga
                        for(i=0;i<3;i++)
                        {
                            m=t2[i][0]*t2[i][1]*t2[i][2]; //Moltiplico i valori della riga "i" della matrice logica "t2", dato a X valore 2 e a O valore 3 (*), i risultati mi aiuteranno a capire lo stato della riga.
                            if(m==4||m==9)
                            {
                                for(p=0;p<3;p++) //Ciclo che assegna le coordinate della cella vuota della riga selezionata in precedenza
                                {
                                    if(t2[i][p]==1)
                                    {
                                        a=i+1;
                                        b=p+1;
                                        ok=1;
                                        p=3;
                                        i=3;
                                    }
                                }
                            }
                        }

                        //Controllo se è possibile fare tris oppure ostacolare l'avversario su una colonna
                        for(i=0;i<3;i++)
                        {
                            m=t2[0][i]*t2[1][i]*t2[2][i]; //Analogo controllo per le colonne
                            if(m==4||m==9)
                            {
                                for(p=0;i<3;p++) //Assegnazione coordinate
                                {
                                    if(t2[p][i]==1)
                                    {
                                        a=i+1;
                                        b=p+1;
                                        ok=1;
                                        p=3;
                                        i=3;
                                    }
                                }
                            }
                        }

                        //Controllo se è possibile fare tris oppure ostacolare l'avversario su una diagonale
                        md1=1;
                        md2=1;
                        for(m=0;m<3;m++) //La moltiplicazione delle celle diagonali è più complessa e va fatta separatamente
                            md1*=t2[m][m];
                        md2=t2[2][0]*t2[1][1]*t2[0][2];

                        if(md1==4||md1==9||md2==4||md2==9) //Assegnazione cooordinate
                        {
                            for(i=0;i<3;i++)
                            {
                                    if(t2[i][i]==1)
                                    {
                                        a=i+1;
                                        b=p+1;
                                        ok=1;
                                        i=3;
                                    }
                                    else if(t2[0][2]==1)
                                    {
                                        a=1;
                                        b=3;
                                        ok=1;
                                        i=3;
                                    }
                                    else if(t2[2][0]==1)
                                    {
                                        a=3;
                                        b=1;
                                        ok=1;
                                        i=3;
                                    }
                            }
                        }

                        if(t[a-1][b-1]!=' ') //Nel caso nessuna mossa si stata selezionata (es. gioco appena iniziato) viene azzerata la variabile "ok"
                            ok=0;

                        if(ok==0) //Se nessuna mossa è stata selezionata, il giocatore automatico selezionerà una cella casuale
                        {
                            a=(rand()%3)+1;
                            b=(rand()%3)+1;
                        }
                    }while(t[a-1][b-1]!=' '); //Controllo anti-cheat (anche il PC avrebbe voglia di sostituire una potenziale mossa se ne avesse la possibilità)

                }//Fine funzione giocatore automatico

            if (giocatore == 1) //Controllo identità del giocatore
            {
                t[a-1][b-1]='X';
                t2[a-1][b-1]=2;
            }
            else
            {
                t[a-1][b-1]='O';
                t2[a-1][b-1]=3;
            }
            giocatore+=2; //Alterno il contatore giocatore

            //Nella riga di seguito stampo la matrice di gioco aggiornata
            printf("\nQuesta e' la situazione di gioco:\n\n[%c][%c][%c]\n[%c][%c][%c]\n[%c][%c][%c]\n", t[0][0], t[0][1], t[0][2], t[1][0], t[1][1], t[1][2], t[2][0], t[2][1], t[2][2]);

            //Inizio serie di cicli che controllano lo stato del gioco:
            //Controllo righe
            for(i=0;i<3;i++)
            {
                if(t[i][0] == t[i][1] && t[i][1] == t[i][2] && t[i][0] != ' ')
                {
                    printf("\nC'e' un tris di %c sulla riga %d!", t[i][0], i+1);
                    printf("\nIl giocatore %d vince!\n\n", giocatore-2);
                    v=1;
                }
            }

            //Controllo colonne
            for(i=0;i<3;i++)
            {
                if(t[0][i] == t[1][i] && t[1][i] == t[2][i] && t[0][i] != ' ')
                {
                    printf("\nC'e' un tris di %c sulla colonna %d!", t[0][i], i+1);
                    printf("\nIl giocatore %d vince!\n\n", giocatore-2);
                    v=1;
                }
            }

            //Controllo diagonali
                if(t[0][0] == t[1][1] && t[1][1] == t[2][2] && t[1][1]!=' ')
                {
                    printf("\nC'e' un tris diagonale di %c!", t[1][1]);
                    printf("\nIl giocatore %d vince!\n\n", giocatore-2);
                    v=1;
                }
                else if (t[0][2] == t[1][1] && t[1][1] == t[2][0] && t[1][1]!=' ')
                {
                    printf("\nC'e' un tris diagonale di %c!", t[1][1]);
                    printf("\nIl giocatore %d vince!\n\n", giocatore-2);
                    v=1;
                }

            //Controllo che identifica uno stato di parità
            par=0;
            for(i=0;i<3;i++)
            {
                if(t[i][0]!=' ' && t[i][1]!=' ' && t[i][2]!=' ' && v!=1)
                par++;
                if(par==3)
                {
                    printf("\nParita'!\n\n");
                    v=1;
                }
            }
    }//Fine ciclo partita
}
