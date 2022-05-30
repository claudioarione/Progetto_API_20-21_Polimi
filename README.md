# Progetto di API anno accademico 2020/21
*Prova finale del corso di Algoritmi e Principi di Informatica del Polutecnico di Milano, anno scolastico 2020/2021.*   
***Valutazione***: *30L/30*

## Specifiche
L'obiettivo del progetto di quest'anno è la gestione di una classifica
tra grafi diretti pesati che tenga traccia dei k "migliori" grafi.   
Il programma riceve in ingresso due parametri, una sola volta (sulla prima riga del file, separati da spazio)  

- d: il numero di nodi dei grafi
- k: la lunghezza della classifica

La restante parte dell'input è una sequenza arbitraria delle seguenti due istruzioni, di due soli tipi:

- *AggiungiGrafo* [matrice di adiacenza]
- *TopK*

La matrice di adiacenza del grafo è fornita per righe e ogni valore in posizione (i,j) rappresenta il *peso* dell'arco
tra i nodi i e j.

L’obiettivo è stampare ad ogni comando *TopK* i migliori *k* grafi, in ordine crescente in base alla
somma dei cammini più brevi tra il nodo 0 e tutti gli altri nodi del grafo **raggiungibili**
da 0. Assuznione: se un nodo non è raggiungibile dal nodo 0, il peso del cammino corrispondente è nullo.

## Esempio
**Input**   
3,2   
AggiungiGrafo       
0 4 3   
0 2 0   
2 0 0   
AggiungiGrafo    
0 0 2   
7 0 4   
0 1 0   
AggiungiGrafo   
3 1 8   
0 0 5   
0 9 0   
TopK   

---

**Output**  

0, 1 *oppure* 1, 0 (l'ordine è irrilevante)
La somma dei cammini minimi del primo grafo è pari a 7, quella del secondo è 5 mentre il terzo grafo ha peso 7.   
Come si può vedere, a parità di peso viene inserito nella classifica il grafo con indice minore
