#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;

//  questions.txt answers.txt

string read_questions(int argc, char *argv[], string questions[][6], int questCount) {
    ifstream fin;
    fin.open(argv[1]);
    int i=0;
    string temp;
    while ( i < questCount){
        for(int j=0; j < 5; j++){
                getline(fin, temp);
            if (temp.size() > 0) {
                questions[i][j] = temp;
    }}
    getline(fin, temp);
    i++;
        }

    fin.close();
    return questions[0][0];
  
    }


int read_answers(int argc, char *argv[], char answers[], int questCount) {
    ifstream fin;
    fin.open(argv[2]);

    if(!fin.is_open()){
    cout << "Could not open file: " << argv[2] << endl;
        return -1;
    
    else{
    int i=0;
    int answerCount =-1;
    while(!fin.eof()){
        fin >> answers[i];
        answerCount++;
        i++;
    }

    fin.close();
    return answerCount;
    }

}
void show_question(string questions[][6], int ind[], int num, string userName, char userChar, int retry) {

    cout << endl;
    cout << userName << " > " << "Here's question number " << num + 1;
    if (retry == 1)
        cout << " (2nd try)" << endl;
    else{
    cout << ":" << endl;
    }
    cout << questions[ind[num]][0] << endl;
    if (questions[ind[num]][1].size() != 0){
        if (tolower(userChar) != 'a'){
            cout << "A. " << questions[ind[num]][1] << endl;
        }else
        cout << endl;
    if (questions[ind[num]][2].size() != 0){
        if (tolower(userChar) != 'b'){
            cout << "B. " << questions[ind[num]][2] << endl;
        }else
        cout << endl;
    if (questions[ind[num]][3].size() != 0){
        if (tolower(userChar) != 'c'){
        cout << "C. " << questions[ind[num]][3] << endl;
        }else
        cout << endl;
    if (questions[ind[num]][4].size() != 0){
        if (tolower(userChar) != 'd'){
        cout << "D. " << questions[ind[num]][4] << endl;
        }else
        cout << endl;

    }}}}

}
bool player_try(string questions[][6], char answers[], int ind[], int& num, int& right, int& points, int& wrong, string userName, int retry, char userChar){
    bool add = true;
    show_question(questions, ind, num, userName, userChar, retry);
    cout << endl << "Your choice? > ";
    cin >> userChar;
    bool userCheck = false;
    while(userCheck == false){
        switch (userChar){
        case 'A':
        case 'a':
        case 'B':
        case 'b':
        case 'C':
        case 'c':
        case 'D':
        case 'd':
            userCheck = true;
        break;
        default:
            userCheck = false;
        }
        if(userCheck == false){
            cout << "Please enter a letter between A-D > ";
            cin >> userChar;
        }
    }
    if (tolower(answers[ind[num]]) == tolower(userChar)){
            points = pow(10, right+1);
        if (retry == 1)
            points = points/2;

        cout << endl;
        cout << "You got that one right, for " << points << " points." << endl;
        num++;
        right++;
    }
    else {
    wrong ++;
    if(wrong == 1){
        cout << endl;
        cout << "Thats an incorrect answer" << endl;
        cout << "Would you like to try again for 1/2 points?(Y/N) > ";
        char userAns;
        cin >> userAns;
        while (tolower(userAns) != 'y' && tolower(userAns) != 'n'){
            cout << endl;
            cout << "Please enter (Y/N) > ";
            cin >> userAns;
        }
        if (userAns == 'y' || userAns =='Y'){
            retry = 1;
            player_try(questions, answers, ind, num, right, points, wrong, userName, retry, userChar);
        }
        else{
            num++;
            add = false;
        }
    }}
    if (num == 6){
        cout << endl;
        cout << "That's the end of the game, there are no more questions!" << endl;
    }

    return add;
}
void sort_score(string userName, int total) {
    //fout.open(argv[2], );
    ofstream fout;
    fout.open("summary.txt", std::ios_base::app);
    if (!fout){
        ofstream fout("summary.txt");
        fout << userName << " " << total << endl;;
        fout.close();
 	cout << "The current record holder is " << userName << " with " << total << " points." << endl;
    	cout << "You have achieved rank 1 with " << total << " points." << endl << endl;
	return;
    }
	else{
        fout << userName << " " << total << endl;;
        fout.close();
    }
    ifstream fin;
    int line = 0;
    fin.open("summary.txt");
    while(!fin.eof()){
        string temp;
        getline(fin, temp);
	if(temp.size() != 0)
            line++;
    }

    fin.close();
    fin.open("summary.txt");
    string names[line];
    int scores[line];
    int i=0;
    while(!fin.eof()){
        fin >> names[i] >> scores[i];
        i++;
    }
    fin.close();
    int ranking[line];
    for(int i = 0; i < line; i++) {
            int index = i;
        for (int j = i + 1; j < line; j++) {
            if (scores[index] < scores[j]) {
                index = j;
        }
    }
        if (index != i) {
                int temp = scores[index];
                scores[index] = scores[i];
                scores[i] = temp;
                string temp2 = names[index];
                names[index] = names[i];
                names[i]= temp2;
                ranking[i]=i+1;

            }}
    int userRank;
    fout.open("summary.txt");
    for(int i=0; i < line ; i++){
        fout << names[i] << " " << scores[i] << endl;
    if(names[i] == userName && scores[i] == total){
            userRank = i +1;
        }
    }

    cout << "The current record holder is " << names[0] << " with " << scores[0] << " points." << endl;
    cout << "You have achieved rank " << userRank <<  " with " << total << " points." << endl << endl;

}

void play_game(string questions[][6],char answers[], int ind[]) {
    int num=0;
    int points=0;
    int total=0;
    int right=0;
    int wrong=0;
    int retry=0;
    char userChar ='l';
    bool add;
    string userName;
    cout << "What is your name? > ";
    getline(cin, userName);
    while(num < 6 && wrong != 2){
        add = player_try(questions, answers, ind, num, right, points, wrong, userName, retry, userChar);
        if (add == true)
        total = points + total;
    }
    if (wrong > 1 && num < 6){
        cout << endl;
        cout << "Sorry you have missed two questions, Game Over" << endl;
        total = 0;
    }


        cout << endl;
        cout << userName << ", your final score was: " << total << endl;
        cout << "this will be recorded to the game history file" << endl;
        cout << endl;
        sort_score(userName, total);


        cout << "Thanks for playing, we hope you'll send all your friends to play." << endl << endl;

}



//////////////////////////////////MAIN///////////////////////////////////////////

int main(int argc, char* argv[])
{
    ////////////////////////CHECKING FOR PROPER USEAGE//////////////////////////
    if (argc != 3){
	cout << endl;
        cout << "Usage: myprog questions.txt answers.txt" << endl << endl;
        return 1;
        }

    ////////////////////////////QUESTIONS////////////////////////////////////////
	
    cout << endl;

    ifstream fin;
    fin.open(argv[1]);

    if(!fin.is_open()){
    cout << "Could not open file: " << argv[1] << endl;
        return 1;
    }
    int questCount = 0;
    while(!fin.eof()){
        string temp;
        getline(fin, temp);
        if(temp.size() == 0){
            questCount++;
    }}
    questCount++;
    fin.close();
    string questions[questCount][6];
    read_questions(argc, argv, questions, questCount);

    /////////////////////////////ANSWERS//////////////////////////////////

    int answerCount;
    char answers[questCount];
    answerCount = read_answers(argc, argv, answers, questCount);

    if (answerCount == -1){
        return 1;
    }
    if (answerCount != questCount){
        cout << "answers.txt and questions.txt do not match" << endl;
        return 1;
    }


    /////////////////// RANDOM NUM GENERATOR ///////////////////////

    int fixed_seed;
    int random_number;
    bool used[questCount];
    int randIndex[questCount];
    srand((unsigned)time(NULL));

    for(int i = 0; i < questCount; i++)
        used[i] = false;

    for(int i = 0; i < 6; i++){
        random_number = rand()%(questCount);
        while(used[random_number] == true)
            random_number = rand()%(questCount);
        used[random_number] = true;
        randIndex[i]=random_number;
    }
    ////////////////////////GAME//////////////////////////////

    play_game(questions, answers, randIndex);


   return 0;
}
