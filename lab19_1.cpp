#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream fin(filename);
    string textline;
    while(getline(fin,textline)){
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int a,b,c,sum = 0;
        sscanf(textline.c_str(),format,name,&a,&b,&c);
        sum = a + b + c;
        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
    fin.close();
}

void getCommand(string &command, string &key){
    string text;
    cout << "Please input your command: ";
    getline(cin,text);
    int start = 0;
    int end = text.find_first_of(" ");
    command = text.substr(start,end-start);
    start = end + 1;
    end = text.find_last_of(" ",start);
    key = text.substr(start,end-start);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool Found = false;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0;i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            Found = true;
            break;
        }
    }
    if(Found == false) cout << "Cannot found.\n";
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool Found = false;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0;i < grades.size(); i++){
        if(grades[i] == *key.c_str()){
            cout << names[i] << " (" << scores[i] << ")\n";
            Found = true;
        }
    }
    if(Found == false) cout << "Cannot found.\n";
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
