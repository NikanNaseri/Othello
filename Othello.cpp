#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
void menu();
void play_game(string , chrono::steady_clock::time_point start_time);
void draw_line(const char* , const char* , const char*);
void draw_game_board(string game_board[8][8]);
bool move_validation(int , int , string game_board[8][8] , string);
void play_move(int , int , string game_board[8][8] , string);
bool has_valid_move(string game_board[8][8] , string);
void show_available_moves(string game_board[8][8] , string);
void clear_available_moves(string game_board[8][8]);
void computer_move(string game_board[8][8] , string);
void count_pieces(string game_board[8][8]);

const char* TL = "┌";
const char* TM = "┬";
const char* TR = "┐";
const char* ML = "├";
const char* MM = "┼";
const char* MR = "┤";
const char* BL = "└";
const char* BM = "┴";
const char* BR = "┘";
const char* V  = "│";
const char* H  = "─";

int main(){

    menu();

    srand(time(0));       //Producing new random numbers every time we run the game

    return 0;
}
void play_game(string game_type , chrono::steady_clock::time_point start_time) {

    string white_circle = "●"; 
    string black_circle = "○"; 
    string game_board[8][8] = {
        {" "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "},
        {" "," "," ",black_circle,white_circle," "," "," "},
        {" "," "," ",white_circle,black_circle," "," "," "},
        {" "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "},
        {" "," "," "," "," "," "," "," "}
    };

    bool game_over = false;
    string player_color = "Black";
    string player_icon = "○";
    int row , column;
    int minutes = 0;
    int seconds = 0;
    while (true){
        std::cout<< "\033[2J\033[H"; //same use as system("cls") on windows
        cout<<"Othello                             Time spent playing : " << minutes << " minutes and " << seconds << " seconds\n\n";
        show_available_moves(game_board , player_icon);
        draw_game_board(game_board);
        if (!has_valid_move(game_board , "○") && !has_valid_move(game_board , "●")){
            game_over = true;
        }
        for (int i = 0 ; i < 8; i++) {
                game_over = true;
                for (int j = 0 ; j < 8; j++) {
                    if (game_board[i][j] == " " || game_board[i][j] == "*") {
                        game_over = false;
                        break;
                    }
                }
                if (!game_over)
                    break;
            }
        if (game_over) {
            std::cout<< "\033[2J\033[H";
            draw_game_board(game_board);
            count_pieces(game_board);
            cout << "\nTime spent playing : " << minutes << "  minutes and " << seconds << " seconds";
            cout << "\n\n Do you want to go to the menu(y/n)?";
            while (true) {
                char answer = _getch();
                if (answer == 'y') {
                    menu();
                    break;
                }
                else if (answer == 'n') {
                    cout << "\nGame finished!";
                    break;
                }
                else {
                    cout << "\nPlease enter y/n !";
                }
            }
            break;
        }
        if (!has_valid_move(game_board, player_icon)) {
            cout << player_color << " player" << " has no valid moves. Turn skipped!(Press enter...)\n";
            player_color = (player_color == "Black") ? "White" : "Black";
            player_icon  = (player_icon  == "○") ? "●" : "○";
            cin.get();
            continue;
        }
        cout << "\nAvailable moves are displayed with *";
        cout << "\n\n" << player_color << " player (row column): ";
        cin >> row >> column; 
        bool validation = move_validation(row-1 , column-1 , game_board , player_icon);
        if (validation) {
            if (game_type == "human") {
                play_move(row-1 , column-1 , game_board , player_icon);
                clear_available_moves(game_board);
                player_color = (player_color == "Black") ? "White" : "Black";
                player_icon = (player_icon == "○") ? "●" : "○"; 
            }
            else if (game_type == "computer") {
                play_move(row-1 , column-1 , game_board , player_icon);
                clear_available_moves(game_board);
                computer_move(game_board , "●");

            }
            auto now = chrono::steady_clock::now();
            auto time_spent = chrono::duration_cast<chrono::seconds>(now - start_time);
            minutes = time_spent.count() / 60;
            seconds = time_spent.count() % 60;
        }   
        else {
            cout << "Invalid move! Press enter...";
            cin.ignore();
            cin.get();
            continue;
        }
    }
}
void menu() {
    std::cout<< "\033[2J\033[H";     // same use as system("cls") on windows
    cout << TL << H << H << H << H << H << H << H << H << H << H << " Othello " << H << H << H << H << H << H << H << H << H  << H << H << TR << "\n";
    cout << V << "                              " << V << "\n";
    cout << V << "     [0]:Play 1v1             " << V << "\n";
    cout << V << "                              " << V << "\n";
    cout << V << "     [1]:Play with computer   " << V << "\n";
    cout << V << "                              " << V << "\n";
    cout << V << "     [2]:Exit                 " << V << "\n";
    cout << V << "                              " << V << "\n";
    cout << BL << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H << H <<  H << H << H <<  H << H << H << BR << "\n"; 
    while (true) {
        char order = _getch();
        if (order == '0') {
            auto start_time = chrono::steady_clock::now();
            play_game("human" , start_time);
            break;
        }
        else if (order == '1') { 
            auto start_time = chrono::steady_clock::now();
            play_game("computer" , start_time);
            break;
        }
        else if (order == '2') {
            cout << "\nGame finished !";
            break;
        }
        else {
            cout << "Please enter 0 or 1 or 2!\n";
        }
    }
}   
void draw_line(const char*L , const char*M , const char*R){
    cout << L;
    for (int i = 0; i < 8; i++) {
        cout << H << H << H << H << H << H;
        if (i < 7) cout << M;
    }
    cout << R << endl;
}
void draw_game_board(string game_board[8][8]){
    draw_line(TL, TM, TR);

    for (int i = 0; i < 8; i++) {
        cout << V;
        for (int j = 0; j < 8; j++) {
            cout << " " << game_board[i][j] << " ";
            cout << "   " << V;
        }
        cout << endl;

        if (i < 7)
            draw_line(ML, MM, MR);
    }

    draw_line(BL, BM, BR);
}
bool move_validation(int x , int y , string game_board[8][8] , string player_icon) {
    int direction_x[8] = {-1 , -1 , -1 , 0 , 0 , 1 , 1 , 1};
    int direction_y[8] = {-1 , 0 , 1 , -1 , 1 , -1 , 0 , 1};
    string opponet_icon = (player_icon == "●") ? "○" : "●";

    if (x < 0 || x > 7 || y < 0 || y > 7 || game_board[x][y] ==  "○" || game_board[x][y] == "●")
        return false;
    
    for (int d = 0; d < 8; d++) {
        int i = x + direction_x[d];
        int j = y + direction_y[d];
        bool seen = false;

        while (i>=0 && i<8 && j>=0 && j<8 && game_board[i][j] == opponet_icon) {
            seen = true;
            i += direction_x[d];
            j += direction_y[d];
        }

        if (seen && i>=0 && i<8 && j>=0 && j<8 && game_board[i][j] == player_icon)
            return true;
        }
    return false;
    
}
void play_move(int x , int y , string game_board[8][8] , string player_icon){
    int direction_x[8] = {-1 , -1 , -1 , 0 , 0 , 1 , 1 , 1};
    int direction_y[8] = {-1 , 0 , 1 , -1 , 1 , -1 , 0 , 1};
    string opponet_icon = (player_icon == "●") ? "○" : "●";
    game_board[x][y] = player_icon;

    for (int d = 0; d < 8; d++) {
        int i = x + direction_x[d];
        int j = y + direction_y[d];
        bool seen = false;

        while (i>=0 && i<8 && j>=0 && j<8 && game_board[i][j] == opponet_icon) {
            seen = true;
            i += direction_x[d];
            j += direction_y[d];
        }

        if (seen && i>=0 && i<8 && j>=0 && j<8 && game_board[i][j] == player_icon) {
            i -= direction_x[d];
            j -= direction_y[d];
            while (game_board[i][j] == opponet_icon) {
                game_board[i][j] = player_icon;
                i -= direction_x[d];
                j -= direction_y[d];
            }
        }
    } 
}

bool has_valid_move(string game_board[8][8] , string player_icon) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            if (move_validation(i , j , game_board , player_icon))
                return true;
        }
    return false;
}

void show_available_moves(string game_board[8][8] , string player_icon) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) 
            if (move_validation(i , j , game_board , player_icon))
                game_board[i][j] = "*";
}

void clear_available_moves(string game_board[8][8]) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) 
            if (game_board[i][j] == "*")
                game_board[i][j] = " ";
}
void computer_move(string game_board[8][8] , string player_icon) {
    int x, y;
    while (true) {
        x = rand() % 8; // pick a random numeber, devide it by 8 and put the remainder in x
        y = rand() % 8; 

        if (move_validation(x, y, game_board, player_icon)) {
            play_move(x, y, game_board, player_icon);
            break;
        }
    }
}
void count_pieces(string game_board[8][8]) {
    int number_of_black_pieces = 0 , number_of_white_pieces = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            if (game_board[i][j] == "○")
                number_of_black_pieces ++;
            else if (game_board[i][j] == "●")
                number_of_white_pieces ++;
        }
    cout << "Black : " << number_of_black_pieces;
    cout << "\nWhite : " << number_of_white_pieces;
    if (number_of_black_pieces > number_of_white_pieces)
        cout << "\nBlack Wins!";
    else if (number_of_white_pieces > number_of_black_pieces)
        cout << "\nWhite Wins!";
    else 
        cout << "\nDraw!";
}
    