//Magli Francesco | GENERATORE DI LABIRINTI
//Qusto programma è basato sull'algoritmo di backtracking ricorsivo per generare un labirinto casuale della dimensioni date

#include <iostream>
#include <time.h>
#include<windows.h>

using namespace std;
void clearscreen(); //Funzione per posizionare il cursore all'angolo sinistro dello schermo e quidni scrivere sopra il contenuto presente senza dover usare system("cls")
int rando(int x, int y);//Funzione per generare numeri casuali compresi tra due numeri


struct blocco{	//Struct con le caratteristiche delle celle del labirinto: Se hanno un passaggio verso SUD, EST e se è stata visitata
	bool path_S;
	bool path_E;
	bool visitata;
};

struct coord{	//Struct per le coordinate di una cella
	int x;
	int y;
};

int main(int argc, char** argv) {	
	srand((unsigned) time(NULL));
	
	int rig=14, col=27;	//Modifica questi valori per cambiare le dimensioni del labirinto (sono espresse in righe e colonne)
	
	blocco cella[200][200]; //Matrice delle celle
	coord prec[9999];	//Dove vengono salvate le coordinate delle celle precendentemente visitate 
	int prec_i;		//Indice dell'ultima cella visitata
	coord c_cor;	//Coordinate cella corrente
	coord visitabili[4];	//Coordinate celle adiacenti a quella corrente non ancora visitate
	int n_visitabili=0;		//Numero di celle adiacenti visitabili
	int scelta;	
	int visitate=0;		//Tiene conto di quante celle sono state visitate per confrontarlo col numero totale
	string buffer="", buffer2[2]=""; //Buffer per accelerare la stampa
	
	for(int i=0;i<rig;i++){		//Inizializzazione celle
		for(int j=0;j<col;j++){
			cella[i][j].visitata=false;
			cella[i][j].path_E=false;
			cella[i][j].path_S=false;
		}
	}
	cella[rig-1][col-1].path_E=true; //L'ultima cella è quella di uscita quindi deve avere il passaggio a EST
	prec[0].x=0; prec[0].y=0;	//La cella 0,0 deve essere considerata già visitata in quanto è quella iniziale
	prec_i=0;
	cella[0][0].visitata=true;
	visitate=1;
	c_cor.x=0; c_cor.y=0;
	
	while(visitate<rig*col){	//Il ciclo continua fino a quando tutte le celle sono state visitate
		n_visitabili=0;	//Azzero le variabili all'inizio di ogni ciclo
		buffer="##"; 
		for(int k=0; k<col; k++){ //Bordo superiore
			buffer+="######";
		}
		buffer+="\n";
		buffer2[0]="  ";buffer2[1]="##";  //Serve a lasciare lo spazio per l'entrata
		Sleep(50);	//Pausa per 50 millisecondi in modo da rendere l'animazione visibile (Cambiare il valore per accelerarla o rallentarla)
		clearscreen();	//Posiziona il cursore all'angolo sinistro dello schermo e permette di riscrivere sopra al contenuto
		for(int i=0;i<rig;i++){		//Ciclo che controlla ogni cella
			for(int j=0;j<col;j++){
				if(cella[i][j].visitata==true){
					if(i==c_cor.y && j==c_cor.x){	//Se è la cella corrente la mostra in modo diverso
						buffer2[0]+="++++";
					}
					else{
						buffer2[0]+="    ";		//Se è stata visitata risulta un corridoio altrimenti un muro
					}
				}
				else{
					buffer2[0]+="####";
				}
				if(cella[i][j].path_E==true){	//Se ha il passaggio a est stampa lo spazio altrimenti #
					buffer2[0]+="  ";
				}
				else{
					buffer2[0]+="##";
				}
				if(cella[i][j].path_S==true){ 	//Stessa cosa per quello a sud
					buffer2[1]+="    ##";
				}
				else{
					buffer2[1]+="######";
				}			
			}
			buffer=buffer+(buffer2[0]+"\n"+buffer2[0]+"\n"+buffer2[1]+"\n");	//Ogni cella è spessa tre caratteri e lunga sei
			buffer2[0]="##";buffer2[1]="##";	//Azzero i buffer tranna che per il bordo sinistro
		}
		cout<<buffer;	//Stampo il buffer completo
	
	
		if(c_cor.x-1>=0 && !(cella[c_cor.y][c_cor.x-1].visitata)){	//Questa parte serve a verificare se le celle adiacenti siano visitabili
			visitabili[n_visitabili].x=c_cor.x-1;					//In tal caso le loro coordinate sono aggiunte a una lista
			visitabili[n_visitabili].y=c_cor.y;
			n_visitabili+=1;
		}
		if(c_cor.x+1<col && !(cella[c_cor.y][c_cor.x+1].visitata)){
			visitabili[n_visitabili].x=c_cor.x+1;
			visitabili[n_visitabili].y=c_cor.y;
			n_visitabili+=1;
		}
		if(c_cor.y-1>=0 && !(cella[c_cor.y-1][c_cor.x].visitata)){
			visitabili[n_visitabili].x=c_cor.x;
			visitabili[n_visitabili].y=c_cor.y-1;
			n_visitabili+=1;
		}
		if(c_cor.y+1<rig && !(cella[c_cor.y+1][c_cor.x].visitata)){
			visitabili[n_visitabili].x=c_cor.x;
			visitabili[n_visitabili].y=c_cor.y+1;
			n_visitabili+=1;
		}
		
		if(n_visitabili>0){		//Se c'è almeno una cella visitabile ne viene scelta una a caso dalla lista
			scelta=rando(1,n_visitabili);
			cella[visitabili[scelta-1].y][visitabili[scelta-1].x].visitata=true; //Questa viene poi marcata come visitata
			visitate++;
			prec[prec_i]=c_cor;	//Quella che prima era la cella corrente viene messa nella lista di precedenti
			prec_i++;
			c_cor=visitabili[scelta-1];	//Mentre quella appena scelta diventa quella corrente
 
			if(c_cor.x>prec[prec_i-1].x){				//Qui viene verificata la posizione relativa della cella nuova a quella precedente
				cella[c_cor.y][c_cor.x-1].path_E=true;	//e quindi dove deve essere aperto il passaggio
			}
			if(c_cor.x<prec[prec_i-1].x){
				cella[c_cor.y][c_cor.x].path_E=true;
			}
			if(c_cor.y>prec[prec_i-1].y){
				cella[c_cor.y-1][c_cor.x].path_S=true;
			}
			if(c_cor.y<prec[prec_i-1].y){
				cella[c_cor.y][c_cor.x].path_S=true;
			}
		}
		else{						//Se non vi sono celle visitabili adiacenti ma non tutte le celle sono state visitate la cella precedente
			c_cor=prec[prec_i-1];	//diventa quella corrente, il programma torna sui sui passi fino a quando non trova una cella adiacente visitabile
			prec_i--;
		}
	}		
	for(int i=0;i<rig;i++){		//Inizializzazione celle
		for(int j=0;j<col;j++){
			cella[i][j].visitata=false;
		}
	}
	c_cor.x=0;c_cor.y=0;cella[0][0].visitata=true;
	
	Sleep(250);
	
	//Questa parte del codice attua la risoluzione del labirinto sfruttando lo stesso algoritmo
	while(c_cor.x!=col-1 || c_cor.y!=rig-1){	//Il ciclo continua fino a quando la cella corrente non giunge all'uscita
		n_visitabili=0;	//Azzero le variabili all'inizio di ogni ciclo		
			
		if(c_cor.x-1>=0 && !(cella[c_cor.y][c_cor.x-1].visitata)  && cella[c_cor.y][c_cor.x-1].path_E){	
			visitabili[n_visitabili].x=c_cor.x-1;			//Questa parte serve a verificare se le celle adiacenti siano visitabili
			visitabili[n_visitabili].y=c_cor.y;				//In tal caso le loro coordinate sono aggiunte a una lista
			n_visitabili+=1;								//Oltre che a non essere ancora state visitate devono anche avere un passaggio che le collega
		}
		if(c_cor.x+1<col && !(cella[c_cor.y][c_cor.x+1].visitata) && cella[c_cor.y][c_cor.x].path_E){
			visitabili[n_visitabili].x=c_cor.x+1;
			visitabili[n_visitabili].y=c_cor.y;
			n_visitabili+=1;
		}
		if(c_cor.y-1>=0 && !(cella[c_cor.y-1][c_cor.x].visitata) && cella[c_cor.y-1][c_cor.x].path_S){
			visitabili[n_visitabili].x=c_cor.x;
			visitabili[n_visitabili].y=c_cor.y-1;
			n_visitabili+=1;
		}
		if(c_cor.y+1<rig && !(cella[c_cor.y+1][c_cor.x].visitata) && cella[c_cor.y][c_cor.x].path_S){
			visitabili[n_visitabili].x=c_cor.x;
			visitabili[n_visitabili].y=c_cor.y+1;
			n_visitabili+=1;
		}
		
		if(n_visitabili>0){		//Se c'è almeno una cella visitabile ne viene scelta una a caso dalla lista
			scelta=rando(1,n_visitabili);
			cella[visitabili[scelta-1].y][visitabili[scelta-1].x].visitata=true; //Questa viene poi marcata come visitata
			visitate++;
			prec[prec_i]=c_cor;	//Quella che prima era la cella corrente viene messa nella lista di precedenti
			prec_i++;
			c_cor=visitabili[scelta-1];	//Mentre quella appena scelta diventa quella corrente
		}
		else{						//Se non vi sono celle visitabili adiacenti ma non tutte le celle sono state visitate la cella precedente
			c_cor=prec[prec_i-1];	//diventa quella corrente, il programma torna sui sui passi fino a quando non trova una cella adiacente visitabile
			prec_i--;
		}
		
		buffer="##";
		for(int k=0; k<col; k++){
			buffer+="######";
		}
		buffer+="\n";
		buffer2[0]="  ";buffer2[1]="##";
		Sleep(50);	//Pausa per 50 millisecondi in modo da rendere l'animazione visibile (Cambiare il valore per accelerarla o rallentarla)
		clearscreen();
		//La stampa è eseguita in modo pressochè analogo a quello precedente
		for(int i=0;i<rig;i++){		//Ciclo che controlla ogni cella
			for(int j=0;j<col;j++){
				if(i==c_cor.y && j==c_cor.x){	//Se è la cella corrente la mostra in modo diverso
					buffer2[0]+="++++";
				}
				else{
					buffer2[0]+="    ";	
				}
				if(cella[i][j].path_E==true){	//Se ha il passaggio a est stampa lo spazio altrimenti #
					buffer2[0]+="  ";
				}
				else{
					buffer2[0]+="##";
				}
				if(cella[i][j].path_S==true){ 	//Stessa cosa per quello a sud
					buffer2[1]+="    ##";
				}
				else{
					buffer2[1]+="######";
				}			
			}
			buffer=buffer+(buffer2[0]+"\n"+buffer2[0]+"\n"+buffer2[1]+"\n");
			buffer2[0]="##";buffer2[1]="##";
		}
		cout<<buffer;	//Stampo il buffer completo
	}
	return 0;
}


void clearscreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

int rando(int x, int y){
	return x+rand()%(-x+y+1);
}
