
    #include <cmath>
    #include <string>
    using namespace std;
    
    #define PLAYER_RED 'r'
    #define PLAYER_BLUE 'b'
    #define ILOSC_SASIADOW 6 
    const int SIZE = 11;

    enum WSK {
        GORA_L,
        GORA,
        GORA_P,
        DOL_P,
        DOL,
        DOL_L
    };

    class Komorka{

    public:
        char* pole;
        bool odwiedzone;
        bool RED, BLUE;
        Komorka* SASIAD[ILOSC_SASIADOW];

        Komorka() : pole(nullptr), odwiedzone(false), RED(false), BLUE(false) {
            for (int i = 0; i < ILOSC_SASIADOW; i++) { SASIAD[i] = nullptr; }
        }

    };

    class Stos {
    private:
        Komorka*** POLE;
        Komorka** WOLNE;
        int liczbaPol;
        int liczbaWolnychPol;
        int czerwone;
        int niebieskie;
        int rozmiar;
    public:

        Stos() : liczbaPol(0), czerwone(0), niebieskie(0), rozmiar(0) {
            WOLNE = nullptr;
            POLE = new Komorka** [SIZE];
            for (int y = 0; y < SIZE; ++y) {
                POLE[y] = new Komorka* [SIZE];
                for (int x = 0; x < SIZE; ++x) {
                    POLE[y][x] = new Komorka();
                }
            }
        }

        ~Stos() {
            for (int y = 0; y < SIZE; ++y) {
                for (int x = 0; x < SIZE; ++x) {
                    delete POLE[y][x];
                }
                delete[] POLE[y];
            }
            delete[] POLE;
        }

        void Dodaj(char c, int x, int y) {
            if (c == PLAYER_RED) {
                czerwone += 1;
            }
            else if (c == PLAYER_BLUE) {
                niebieskie += 1;
            }
            liczbaPol += 1;

            if (x >= 0 && x <= SIZE && y >= 0 && y <= SIZE) {
                if (POLE[y][x]->pole == nullptr) {
                    POLE[y][x]->pole = new char(c);
                }
                else {
                    *POLE[y][x]->pole = c;
                }

                if (x < SIZE-1 && y < SIZE-1) POLE[y][x]->SASIAD[DOL] = POLE[y + 1][x + 1];
                if (x < SIZE-1) POLE[y][x]->SASIAD[DOL_P] = POLE[y][x + 1];
                if (x > 0) POLE[y][x]->SASIAD[GORA_L] = POLE[y][x - 1];

                if (y > 0) POLE[y][x]->SASIAD[GORA_P] = POLE[y - 1][x];
                if (y < SIZE-1) POLE[y][x]->SASIAD[DOL_L] = POLE[y + 1][x];
                if (y > 0 && x > 0) POLE[y][x]->SASIAD[GORA] = POLE[y - 1][x - 1];

            }
        }
        
        void Granica(){
            
            if(liczbaPol>1){ 
                rozmiar = sqrt(liczbaPol) - 1;
                for (int number= 0; number <= rozmiar; number++) { // ustalenie granic planszy
                    POLE[rozmiar][number]->BLUE = true;
                    POLE[number][rozmiar]->RED = true;
                }
            }
            else{
                POLE[0][0]->RED=true;
            }
            liczbaWolnychPol = liczbaPol -czerwone - niebieskie;
            WOLNE = new Komorka*[liczbaWolnychPol];

        }

        bool DFS( Komorka* POLE, char c ) {

            POLE->odwiedzone = true;
            int i = 0;
            if (c == PLAYER_RED && *POLE->pole == PLAYER_RED && POLE->RED == true) {
                return true;
            }
            else if (c == PLAYER_BLUE && *POLE->pole == PLAYER_BLUE && POLE->BLUE == true) {
                return true;
            }
            else {
                for (; i < ILOSC_SASIADOW; i++) {
                    Komorka* next = POLE->SASIAD[i];
                    if ( c == PLAYER_RED && next!=nullptr && next->pole!=nullptr && next->odwiedzone == false && *next->pole == PLAYER_RED) {
                        if (next->RED == true) { return true; }
                        else {
                            if (DFS(next, c)){ return true;}
                        }
                    }
                    if ( c == PLAYER_BLUE && next!= nullptr && next->pole!=nullptr && next->odwiedzone == false && *next->pole == PLAYER_BLUE) {
                        if (next->BLUE == true) { return true; }
                        else {
                            if (DFS(next, c)){ return true;}
                        }
                    }
                }
            }
            return false;
        }

        bool BoardCorrect(){
            if(getCzerwone() -1 == getNiebieskie() || getCzerwone() == getNiebieskie()){
                return true;
            }
            else{ return false;
            }
        }

        bool GameOver(char c) {
            int wspolrzedne = 0;
            
            for (; wspolrzedne <= rozmiar; wspolrzedne++) {
                if(c==PLAYER_RED){
                    if (POLE[wspolrzedne][0] != nullptr && *POLE[wspolrzedne][0]->pole == PLAYER_RED ) { // wspolrzedne == y

                        if (DFS(POLE[wspolrzedne][0], PLAYER_RED)) {
                            return true;
                        }
                    }
                }
                
                if( c == PLAYER_BLUE){
                    if (POLE[0][wspolrzedne] != nullptr && *POLE[0][wspolrzedne]->pole == PLAYER_BLUE ) { // wspolrzedne == x
                    
                        if( DFS(POLE[0][wspolrzedne], PLAYER_BLUE)) {
                            return true;
                        }
                    }
                }
            }
            return false;   
        }

        bool BoardPossible(char c){
            for(int y=0; y<=rozmiar; y++){
                for(int x=0; x<=rozmiar; x++){

                    if( *POLE[y][x]->pole == c){
                        *POLE[y][x]->pole = ' ';
                        UstawNaNieodwiedzone();
                        if (!GameOver(c)) return true;
                        *POLE[y][x]->pole = c;
                    }
                }
            }
            return false;
        }

        void WolnePola(){

            int number=0;
            for(int y=0; y<=rozmiar; y++){
                for(int x=0; x<=rozmiar; x++){
                    
                    if( *POLE[y][x]->pole == ' '){
                        WOLNE[number++] = POLE[y][x];
                    }
                }
            }
        }

        bool WinIn(char c, int n){

            if( liczbaWolnychPol - n >= 0){ // WolnePola - n >= 0 
                if( c == PLAYER_RED && getCzerwone() >= rozmiar-n){
                    return WinCheck( c, n);                
                }
                else if( c == PLAYER_BLUE && getNiebieskie() >= rozmiar-n){
                    return WinCheck( c, n);  
                }
            }
            return false;
        }

        bool WinCheck(char c, int n){   
             
            if( n == 1){
                for(int num=0; num<liczbaWolnychPol; num++){
                            
                        if( *WOLNE[num]->pole == ' '){
                            *WOLNE[num]->pole = c;
                            UstawNaNieodwiedzone();
                            if ( GameOver(c)){
                                *WOLNE[num]->pole = ' '; 
                                return true;
                            }
                            *WOLNE[num]->pole = ' ';
                        }
                    }
            }
            else{
                if( n == 2){
                    if( WinCheck( c, n-1)){ // true
                        return true;
                    }
                }
                else {
                    for(int num=0; num<liczbaWolnychPol; num++){
                    
                        if( *WOLNE[num]->pole == ' '){
                            *WOLNE[num]->pole = c;
                            UstawNaNieodwiedzone();
                            if ( !GameOver(c)){ // jesli 1 ruch nie wygrywa 

                                if( WinCheck( c, 1)){ 
                                    *WOLNE[num]->pole = ' ';
                                    return true;
                                }
                            }
                            *WOLNE[num]->pole = ' ';
                        }
                    } 
                }
            }
            return false;
        }

        bool PerfectWinIn(char c, int n){
            if( liczbaWolnychPol - n >= 0){ // WolnePola - n >= 0 
                if( c == PLAYER_RED && getCzerwone() >= rozmiar-n){
                    return PerfectWinCheck( c, n);                
                }
                else if( c == PLAYER_BLUE && getNiebieskie() >= rozmiar-n){
                    return PerfectWinCheck( c, n);  
                }
            }
            return false;
        }

        bool PerfectWinCheck(char c, int n){
            char g;
            if(c==PLAYER_RED){ g = PLAYER_BLUE; }
            else{ g = PLAYER_RED;}

            if( n == 1){
                for(int num=0; num<liczbaWolnychPol; num++){
                            
                        if( *WOLNE[num]->pole == ' '){
                            *WOLNE[num]->pole = c;
                            UstawNaNieodwiedzone();
                            if ( GameOver(c)){
                                *WOLNE[num]->pole = ' '; 
                                return true;
                            }
                            *WOLNE[num]->pole = ' ';
                        }
                    }
            }
            else{
                if( n == 2){
                    for(int num=0; num<liczbaWolnychPol; num++){    
                            
                        if( *WOLNE[num]->pole == ' '){
                            *WOLNE[num]->pole = c;
                            UstawNaNieodwiedzone();
                            if ( GameOver(c)){  // chcemy aby 1 ruch wygrywaÅ
                                *WOLNE[num]->pole = g;
                                if( PerfectWinCheck( c, 1)){ 
                                    *WOLNE[num]->pole = ' ';
                                    return true;
                                }
                            }
                            *WOLNE[num]->pole = ' ';
                        }
                    }
                }
                else if( n == 3){
                     
                     for(int num=0; num<liczbaWolnychPol; num++){
                    
                        if( *WOLNE[num]->pole == ' '){
                            *WOLNE[num]->pole = c;
                            UstawNaNieodwiedzone();
                            if ( !GameOver(c)){ // jesli 1 ruch nie wygrywa 
                                if( PerfectWinCheck( c, 2)){ 
                                    *WOLNE[num]->pole = ' ';
                                    return true;
                                }
                            }
                            *WOLNE[num]->pole = ' ';
                        }
                    } 
                }
                else if( n == 4){  // DO POPRAWY 3 i 4
                    
                    for(int num=0; num<liczbaWolnychPol; num++){
                    
                        if( *WOLNE[num]->pole == ' '){
                            *WOLNE[num]->pole = g;
                            if( PerfectWinCheck( c, 3)==false){ 
                                *WOLNE[num]->pole = ' ';
                                return false;
                            }
                        }
                        *WOLNE[num]->pole = ' ';
                    } 
                    return true;
                }
            }
            return false;
        }

        void UstawNaNieodwiedzone(){
            for (int y = 0; y < SIZE; ++y) {
                for (int x = 0; x < SIZE; ++x) {
                    POLE[y][x]->odwiedzone = false;
                }
            }
        }

        void Wyczysc() {

            liczbaPol = 0;
            czerwone = 0;
            niebieskie = 0;
            rozmiar=0;
            delete WOLNE;

            for (int y = 0; y < SIZE; ++y) {
                for (int x = 0; x < SIZE; ++x) {
                    POLE[y][x]->pole = nullptr;
                    POLE[y][x]->odwiedzone = false;
                    POLE[y][x]->RED = false;
                    POLE[y][x]->BLUE = false;
                }
            }
        }


        int getPola() {
            if (isEmpty()) {
                return 0;
            }
            else {
                return liczbaPol;
            }
        }

        int getCzerwone() {
            if (isEmpty()) {
                return 0;
            }
            else {
                return czerwone;
            }
        }

        int getNiebieskie() {
            if (isEmpty()) {
                return 0;
            }
            else {
                return niebieskie;
            }
        }

        bool isEmpty() const {
            return  POLE == nullptr;
        }

    };
