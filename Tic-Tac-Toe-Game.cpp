#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <chrono>
#include <thread>
using namespace std;

struct stinfo
{
    char cumouterchoice = 'X';
    char userchoice = 'O';
    char arrbox[9] = { '1','2','3','4','5','6','7','8','9' };
    short times = 0;
};

short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;
}

short readNum(string m) {
    short n = 0;
    cout << m;
    cin >> n;
    while (cin.fail() || n < 1 || n > 20)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        cout << "ERORR enter again :";
        cin >> n;
    }
    return n;
}

string readYN(string m)
{
    string a;
    cout << m;
    cin >> a;
    while (a != "yes" && a != "no" && a != "NO" && a != "YES")
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        cout << m;
        cin >> a;
    }
    return a;
}

short getrandomchoice(stinfo& data)
{
    short num = RandomNumber(1, 9);
    while (data.arrbox[num - 1] == 'O' || data.arrbox[num - 1] == 'X')
    {
        num = RandomNumber(1, 9);
    }
    data.arrbox[num - 1] = data.cumouterchoice;
    return num;
}

short readuserchoice(string m, string g, string h, stinfo& data)
{
    short boxnum;
    cout << m;
    cin >> boxnum;
    while (cin.fail() || boxnum < 1 || boxnum > 9 ||
        data.arrbox[boxnum - 1] == 'O' || data.arrbox[boxnum - 1] == 'X')
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << g;
        cin >> boxnum;
    }
    data.arrbox[boxnum - 1] = data.userchoice;
    return boxnum;
}

char userorcum(char b1)
{
    if (b1 == 'O')
        return 'O';
    else if (b1 == 'X')
        return 'X';
    return ' ';
}

char winorlossalg(stinfo& data, short /*times*/)
{
    if (data.arrbox[0] == data.arrbox[1] && data.arrbox[1] == data.arrbox[2])
        return userorcum(data.arrbox[0]);
    if (data.arrbox[3] == data.arrbox[4] && data.arrbox[4] == data.arrbox[5])
        return userorcum(data.arrbox[3]);
    if (data.arrbox[6] == data.arrbox[7] && data.arrbox[7] == data.arrbox[8])
        return userorcum(data.arrbox[6]);

    if (data.arrbox[0] == data.arrbox[3] && data.arrbox[3] == data.arrbox[6])
        return userorcum(data.arrbox[0]);
    if (data.arrbox[1] == data.arrbox[4] && data.arrbox[4] == data.arrbox[7])
        return userorcum(data.arrbox[1]);
    if (data.arrbox[2] == data.arrbox[5] && data.arrbox[5] == data.arrbox[8])
        return userorcum(data.arrbox[2]);

    if (data.arrbox[0] == data.arrbox[4] && data.arrbox[4] == data.arrbox[8])
        return userorcum(data.arrbox[0]);
    if (data.arrbox[2] == data.arrbox[4] && data.arrbox[4] == data.arrbox[6] )
        return userorcum(data.arrbox[2]);

    bool full = true;
    for (int i = 0; i < 9; i++)
    {
        if (data.arrbox[i] != 'O' && data.arrbox[i] != 'X')
        {
            full = false;
            break;
        }
    }
    if (full)
        return 'd';

    return ' ';
}

void printBoard(char arr[9])
{
    cout << "    -------------------" << endl;
    cout << "    |     |     |     |" << endl;
    cout << "    |  " << arr[0] << "  |  " << arr[1] << "  |  " << arr[2] << "  |" << endl;
    cout << "    |     |     |     |" << endl;
    cout << "    |-----------------|" << endl;
    cout << "    |     |     |     |" << endl;
    cout << "    |  " << arr[3] << "  |  " << arr[4] << "  |  " << arr[5] << "  |" << endl;
    cout << "    |     |     |     |" << endl;
    cout << "    |-----------------|" << endl;
    cout << "    |     |     |     |" << endl;
    cout << "    |  " << arr[6] << "  |  " << arr[7] << "  |  " << arr[8] << "  |" << endl;
    cout << "    |     |     |     |" << endl;
    cout << "    -------------------" << endl << endl;
}

void gameinfo()
{
    cout << "1_ this is the board of X/O game you are O cumputer is X \n";
    cout << "2_ it is not choice :) \n";
    cout << "3_ just enter the number of the box and otomaticly will fill with O \n";
}

void result(stinfo& data, short times)
{
    char winner = winorlossalg(data, times);
    system("cls");
    printBoard(data.arrbox);

    if (winner == 'O') {
        cout << "you win :)" << endl;
        system("Color 2F");
    }
    else if (winner == 'X') {
        cout << "you loss :(" << endl;
        system("Color 4F");
    }
    else if (winner == 'd') {
        cout << "no wins :0" << endl;
        system("Color 6F");
    }
    this_thread::sleep_for(chrono::seconds(3));
}

void resetBoard(stinfo& data)
{
    for (int i = 0; i < 9; i++)
        data.arrbox[i] = '1' + i;
}

void playOneGame(stinfo& data)
{
    resetBoard(data);
    short moves = 0;
    bool gameOver = false;

    cout << "New Game" << endl;
    printBoard(data.arrbox);
    gameinfo();
    this_thread::sleep_for(chrono::seconds(3));
    system("cls");

    while (moves < 9 && !gameOver)
    {
        printBoard(data.arrbox);
        cout << "Your turn(O) - ";
        readuserchoice("number of the box : ", "the box has taken : ", "the number is valid :", data);
        moves++;

        char winner = winorlossalg(data, moves);
        if (winner == 'O' || winner == 'X' || winner == 'd')
        {
            result(data, moves);
            gameOver = true;
            break;
        }

        if (moves >= 9)
            break;
        cout << "Computer turn (X)... ";
        short compMove = getrandomchoice(data);
        cout << "Computer chose box " << compMove << endl;
        moves++;

        winner = winorlossalg(data, moves);

        if (winner == 'O' || winner == 'X' || winner == 'd')
        {
            result(data, moves);
            gameOver = true;
        }
    }

    if (!gameOver)
    {
        result(data, moves);
    }
}

void oneround()
{
    stinfo data;
    char playAgainAnswer = 'Y';

    while (playAgainAnswer == 'Y' || playAgainAnswer == 'y')
    {
        system("cls");
        system("Color 07");
        data.times = readNum("enter how many times you want to play : ");
        system("cls");

        for (short g = 1; g <= data.times; g++)
        {
            cout << "Game " << g << " of " << data.times << endl;
            playOneGame(data);
            system("cls");
            system("Color 0F");
        }

        playAgainAnswer = 'n';
        string s = readYN("Do you want to play all rounds again ? (yes/no) : ");
        if (s == "yes" || s == "YES")
            playAgainAnswer = 'Y';
    }
}

int main()
{
    srand((unsigned)time(NULL));
    oneround();
    return 0;
}
