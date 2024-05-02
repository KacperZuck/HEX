
    #include <iostream>
    #include "Stos.cpp"

    using namespace std;

    void Possible(string& linia, Stos& stos){
        if ( stos.BoardCorrect() ) { // spr czy wgl. mozna uruchomic
            if(stos.GameOver(PLAYER_RED)){
                if( stos.getCzerwone() == stos.getNiebieskie()+1){ 
                    if( stos.BoardPossible(PLAYER_RED)){ 
                        cout<< "YES" << endl;
                    }
                    else{ 
                        cout << "NO" <<endl; 
                    }
                }
                else{ 
                    cout << "NO" <<endl;
                }
            }
            else if(stos.GameOver(PLAYER_BLUE)){
                if( stos.getCzerwone() == stos.getNiebieskie() ){ 
                    if( stos.BoardPossible(PLAYER_BLUE)){ 
                        cout<< "YES" << endl;
                    }
                    else{ 
                        cout << "NO" <<endl; 
                    }
                }
                else{ 
                    cout << "NO" <<endl;
                }
            }
            else{ 
                cout << "YES" << endl; 
            }
        }
        else {
            cout << "NO" << endl;
        }
    }

    void Naive( string& linia, Stos& stos ){
        
        getline(cin, linia);getline(cin, linia);getline(cin, linia);

        if ( stos.BoardCorrect() ) { 
            if(stos.GameOver(PLAYER_RED)){
            cout << "NO" << endl << "NO" << endl << "NO" << endl << "NO" << endl;
            }
            else if(stos.GameOver(PLAYER_BLUE)){
            cout << "NO" << endl << "NO" << endl << "NO" << endl << "NO" << endl;
            }
            else if(stos.getCzerwone() == stos.getNiebieskie() ){ 

                stos.WolnePola();

                if( stos.WinIn(PLAYER_RED,1) ){ 
                    cout<< "YES"<< endl;
                }
                else{ cout << "NO"<<endl;}
                
                if( stos.WinIn(PLAYER_BLUE,2)){ 
                    cout<< "YES"<< endl;
                }
                else{ cout << "NO"<<endl;}
                
                if(stos.WinIn(PLAYER_RED,3)){  
                    cout<< "YES"<< endl;
                }
                else{ cout << "NO"<<endl;}
                
                if( stos.WinIn(PLAYER_BLUE,4)){
                    cout<< "YES"<< endl;
                }
                else{ cout << "NO"<<endl;}

                
            }
            else if(stos.getCzerwone() == stos.getNiebieskie()+1){  // KOLEJ NIEBIESKIEGO 

                stos.WolnePola();

                if(stos.WinIn(PLAYER_RED,2)){
                    cout<< "YES"<< endl;
                }
                else{ cout << "NO"<<endl;}

                if(stos.WinIn(PLAYER_BLUE,1)){
                    cout<< "YES"<< endl;
                }
                else{ cout << "NO"<<endl;}

                if(stos.WinIn(PLAYER_RED,4)){   
                    cout<< "YES"<< endl;
                }
                else{ cout << "NO"<<endl;}

                if(stos.WinIn(PLAYER_BLUE,3)){
                    cout<< "YES"<< endl;
                }
                else{ cout << "NO"<<endl;}
                
            }
                
        }
        else {
            cout << "NO" << endl << "NO" << endl << "NO" << endl << "NO" << endl;
        }
    }

    void Funkcje(Stos& stos, string& linia) {

        if (linia == "BOARD_SIZE") {    // OK
            cout << sqrt(stos.getPola()) << endl;
            getline(cin, linia); // Wczytuje pustą linie po poleceniu
        }
        else if (linia == "PAWNS_NUMBER") {
            int board = stos.getCzerwone() + stos.getNiebieskie();
            cout << board << endl;
            getline(cin, linia); // Wczytuje pustą linie po poleceniu
        }
        else if (linia == "IS_BOARD_CORRECT") {
            if (stos.BoardCorrect()) { // true
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
            
            getline(cin, linia); // Wczytuje pustą linie po poleceniu
        }
        else if (linia == "IS_GAME_OVER") {
            if (stos.BoardCorrect() ) { // prawidlowy rozklad
                if(stos.GameOver(PLAYER_RED)){
                    cout << "YES RED" << endl;

                }
                else if(stos.GameOver(PLAYER_BLUE)){
                    cout << "YES BLUE" << endl;
                }
                else{ cout << "NO" << endl; }
            }
            else {
                cout << "NO" << endl;
            }
            
            getline(cin, linia); // Wczytuje pustą linie po poleceniu
        }
        else if (linia == "IS_BOARD_POSSIBLE") {
            
            Possible(linia,stos);
            getline(cin, linia); // Wczytuje pustą linie po poleceniu
        
        }
        else if ( linia == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT"){
            
            Naive(linia,stos);
        }
        else if( linia == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT"){

            getline(cin, linia);getline(cin, linia);getline(cin, linia);

            if ( stos.BoardCorrect() ) { 
                if(stos.GameOver(PLAYER_RED)){
                cout << "NO" << endl << "NO" << endl << "NO" << endl << "NO" << endl;
                }
                else if(stos.GameOver(PLAYER_BLUE)){
                cout << "NO" << endl << "NO" << endl << "NO" << endl << "NO" << endl;
                }
                else if(stos.getCzerwone() == stos.getNiebieskie() ){ // Kolej czerwonego 

                    stos.WolnePola();

                    if( stos.PerfectWinIn(PLAYER_RED,1) ){ 
                        cout<< "YES"<< endl;
                    }
                    else{ cout << "NO"<<endl;}
                    
                    if( stos.PerfectWinIn(PLAYER_BLUE,2)){ 
                        cout<< "YES"<< endl;
                    }
                    else{ cout << "NO"<<endl;}
                    
                    if(stos.PerfectWinIn(PLAYER_RED,3)){  
                        cout<< "YES"<< endl;
                    }
                    else{ cout << "NO"<<endl;}
                    
                    if( stos.PerfectWinIn(PLAYER_BLUE,4)){
                        cout<< "YES"<< endl;
                    }
                    else{ cout << "NO"<<endl;}

                    
                }
                else if(stos.getCzerwone() == stos.getNiebieskie()+1){  // KOLEJ NIEBIESKIEGO 

                    stos.WolnePola();

                    if(stos.PerfectWinIn(PLAYER_RED,2)){
                        cout<< "YES"<< endl;
                    }
                    else{ cout << "NO"<<endl;}

                    if(stos.PerfectWinIn(PLAYER_BLUE,1)){
                        cout<< "YES"<< endl;
                    }
                    else{ cout << "NO"<<endl;}

                    if(stos.PerfectWinIn(PLAYER_RED,4)){   
                        cout<< "YES"<< endl;
                    }
                    else{ cout << "NO"<<endl;}

                    if(stos.PerfectWinIn(PLAYER_BLUE,3)){
                        cout<< "YES"<< endl;
                    }
                    else{ cout << "NO"<<endl;}
                    
                }
                    
            }
            else {
                cout << "NO" << endl << "NO" << endl << "NO" << endl << "NO" << endl;
            }
        }
        cout << endl;
    }

    void Przydziel(string& linia, Stos& stos, int& i, int& x, int& y){
        while (i < linia.length()) {
            if (linia[i] == '<') {
                i++;
                if (i + 1 < linia.length()) {
                    stos.Dodaj(linia[i + 1], x, y - x);  
                    x++;
                }
            }
            i++;
        }
    }

    void ZrobGraf(string& linia, Stos& stos){
         int stop = 0, y = 0, dlugosc = 0, buf = 0;
            while (getline(cin, linia) && stop == 0) {  // 1 linia

                int i = 0, x = 0;
                if (linia.length() < dlugosc) {
                    ++buf;
                    x += buf;
                }

                // TU WRZUCIC DO FUNKCJI 
                if (linia[i] == '<') {
                    Przydziel(linia, stos, i, x, y);
                }
                else {
                    while (i < linia.length()) { // OK
                        i++;
                        if (i < linia.length() && linia[i] == '-') {
                            i++;
                            if (i < linia.length() && linia[i] == '-') {
                                i++;
                                if (i < linia.length() && linia[i] == '-') {
                                    stop = 1000;
                                    break; // Nie tą petle
                                }
                                else {
                                    Przydziel(linia, stos, i, x, y);
                                }
                            }
                        }
                    }
                }
                y++;
                dlugosc = linia.length();
            }

    }

    int main() {

        string linia;
        Stos stos;

        while (getline(cin, linia)) {   // do konca wejscia  ew. linia[0] != EOF // (c = getchar() ) != EOF 
            
            ZrobGraf(linia, stos);
           
            stos.Granica();
            Funkcje(stos, linia);

            stos.Wyczysc();
        }

        return 0;
    }


    /*

    WYJSCIA :


        IS_BOARD_POSSIBLE (czy mozliwy taki stan planszy, bez pominiecia wczesniejszej wygranej ktoregos z graczy )   YES/NO

        CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
        CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
        CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
        CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

        CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
        CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
        CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
        CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT


    */