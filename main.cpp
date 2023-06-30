#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;


/* Reads in all of the questions and puts them into a 2D array of strings, checks to make sure that
   it is not putting in blank lines into the array and when it fines a question it continues
   to put the answer choices into the array, keeps track of how many questions are entered
   into the array and sends that number back to allow it to compare it to how many answers their
   are, making sure they match
*/
int read_questions(int argc, char *argv[], string questions[][6], int questCount) {
        ifstream fin;
    fin.open(argv[1]);
    if(!fin.is_open()){
    cout << "Could not open file: " << argv[1] << endl;
        return -1;
    }
    int i=0;
    string temp;
    getline(fin, temp);
    if(fin.eof()){
        return -2;
    }
    while ( !fin.eof()){
        if(i > 0){
        getline(fin, temp);
        }
        while(temp.size() == 0){
        getline(fin, temp);
        }
        questions[i][0] = temp;
        for(int j=1; j < 5; j++){
                getline(fin, temp);
                questions[i][j] = temp;
    }
    i++;
    questCount++;
        }
    return questCount;
    }

/*This function reads in all of the answers into an array of char, if the file does not
  open it returns -1, this function keeps track of how many answers there are in order
  to compare that number to how many questions there are which is why the function is int
*/
int read_answers(int argc, char *argv[], char answers[]) {
    ifstream fin;
    fin.open(argv[2]);

    if(!fin.is_open()){
    cout << "Could not open file: " << argv[2] << endl;
        return -1;
    }
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

/*This function displays the questions along with the users name and it checks to see
  if the answer choice is length 0 or not and whether to display it, it also checks to see
  if this is the users second try which will display 2nd try if needed, then if it is a retry
  it compares the users previous answer with all of the answer choices so that it does
  not redisplay what the user put prior
*/
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
/*This function checks whether the user choice is within A-D using a switch and will prompt the user
  to continue input until the usage case is correct, it also checks whether the answer choice is correct
  or not and if it is not correct it prompts the asking whether they want to retry the question or not,
  in which case the function will call upon itself and everything prior, this function also checks whether
  the user has missed 2 problems and will end the game if that is the case, the function gives points to the
  user based on whether they got it right the first try or not, this function is in bool because it sends back
  true to the game function in order for it to add points or not
*/
bool player_try(string questions[][6], char answers[], int ind[], int& num, int& right,
                     int& points, int& wrong, string userName, int retry, int& retryPass, char userChar){
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
        if (retryPass == 1)
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
            retryPass =1;
            player_try(questions, answers, ind, num, right, points, wrong, userName, retry, retryPass, userChar);
        }
        else{
            num++;
            add = false;
        }
    }}


    return add;
}
/*This function checks to make sure there is a summary file and if there is not makes a new one
  in the new one it puts the user in the file and sense they are the only one in the file it gives
  the user Rank 1, if there are other scores in the file then it appends the users score to the end
  of the file, then it closes it and reads in all of the user scores, and sorts them using selection sort
  it then scans the file to find a match with the userName and the score that was passed through the function
  in order to give that rank to the user
*/
void sort_score(string userName, int total) {
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
/*This is the play game function which sets up everything including initializing all of the values that
  are needed for this code to work, it assignments everyhing to 0 and userChar to "l" essentially just
  to allow a random letter that wont get used to be passed through so that the function displaying the
  questions does not get confused and not display an answer choice that is needed, it promps the user for
  their name, and then using a while loop it will give up to 6 questions unless the user misses 2 in which
  it ends the game. This while loop also adds the points only if in the player it sends back "true" for the bool
  value "add". if the user game overs it sets all of the points to 0 and then it sends that 0 to the summary file
  if the user made it through all 6 then it displays a message saying they made it through all of the questions
*/
void play_game(string questions[][6],char answers[], int ind[]) {
    int num=0;
    int points=0;
    int total=0;
    int right=0;
    int wrong=0;
    int retry=0;
    int retryPass=0;
    char userChar ='l';
    bool add;
    string userName;
    cout << "What is your name? > ";
    getline(cin, userName);
    while(num < 6 && wrong != 2){
        add = player_try(questions, answers, ind, num, right, points, wrong, userName, retry, retryPass,userChar);
        if (add == true)
        total = points + total;
    }
    if (wrong > 1 && num < 6){
        cout << endl;
        cout << "Sorry you have missed two questions, Game Over" << endl;
        total = 0;
    }


    if (num == 6){
        cout << endl;
        cout << "That's the end of the game, there are no more questions!" << endl;
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
    if (argc != 4){
        cout << endl;
        cout << "Incorrect program usage. " <<endl;
        cout << "Please read the program description and try again. Exiting. " << endl;
        return 1;
        }

    ////////////////////////////QUESTIONS////////////////////////////////////////

    cout << endl;
    int questCount = 0;
    string questions[50][6];
    questCount = read_questions(argc, argv, questions, questCount);
    if (questCount == -1){
        return 1;
    }

    /////////////////////////////ANSWERS//////////////////////////////////

    int answerCount;
    char answers[questCount];
    answerCount = read_answers(argc, argv, answers);

    if (answerCount == -1){
        return 1;
    }

    /////////////////////////ERROR CHECKING//////////////////////////////
    if (answerCount == 0 || questCount == -2){
        cout << "The question file or the answer file is empty." << endl;
        cout << "Please check the files and try again. Exiting." <<endl;
        return 1;
    }
    if (answerCount != questCount){
        cout << "The question and answer files have different number of items." << endl;
        cout << "Please check the files and try again. Exiting" << endl;
        return 1;
    }


    /////////////////// RANDOM NUM GENERATOR ///////////////////////

    int fixed_seed;
    int random_number;
    bool used[questCount];
    int randIndex[questCount];

    srand(fixed_seed);
    fixed_seed = atoi(argv[3]);

    for(int i = 0; i < questCount; i++)
        used[i] = false;

    for(int i = 0; i < 6; i++){
        random_number = rand()%(questCount);
        while(used[random_number] == true)
            random_number = rand()%(questCount);
        used[random_number] = true;
        randIndex[i] = random_number;
    }
    ////////////////////////GAME//////////////////////////////

    play_game(questions, answers, randIndex);


   return 0;
}
