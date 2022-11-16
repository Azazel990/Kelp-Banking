#include<bits/stdc++.h>
using namespace std;

//Three Basic Building Blocks of this app stored as vectors...
vector<string> code;
vector<string> name;
vector<int> amount;

//A Welcome Banner
void kelpBanner(){
    cout<<"***********************************************************************************************************************************************************************\n";
    cout<<"                                                                             Welcome to Kelp Banking                                                                   \n";
    cout<<"***********************************************************************************************************************************************************************\n";
}

//Some Description About how to provide input...
void Description(){

    cout<<"\n";
    cout<<"Create Account : CREATE <CODE> <NAME>\n";
    cout<<"Deposit Amount : DEPOSIT <CODE> <AMOUNT>\n";
    cout<<"Withdraw Amount : WITHDRAW <CODE> <AMOUNT>\n";
    cout<<"SHOW BALANCE : BALANCE <CODE> <AMOUNT>\n";
    cout<<"EXIT : EXIT\n"; 
    cout<<"\n";
}

//This function splits the entire input string into a vector of strings so it becomes easier to process the input later...
vector<string> splitInput(string str){
    
    vector<string> ans;
    
    for(int i = 0; i < str.length();i++){
        string s;
        while((i < str.length()) && (str[i] != ' ')){
            s.push_back(str[i]);
            i++;
        }
        ans.push_back(s);
    }
    return ans;
}

//This function searches if the account is present in the code vector and returns its index, if not returns -1;
int searchAccountCode(string s){
    
    for(int i = 0; i < code.size() ; i++){
        if(code[i] == s) return i;
    }
    return -1;
}

//This function checks the name entered by the user while creating account doesn't start with a number or just contain numbers...
bool alphaCheck(string str){
    
    if(str[0] >= '0' && str[0] <= '9') {
        cout<<"Name Cannot Start from a digit\n";
        return false;
    }

    return true;
}

//This function checks if the account with the same code already exist...
bool CheckifAccountExists(string str){
    
    for(int i = 0 ; i < code.size(); i++){
        if(code[i] == str){
            cout<<"An Account With the code \'"<<str<<"\' already exist\n Please try a different code\n";
            return false;
        }
    }
    return true;
}

//This function actually performs the arithmetic operations...

void operation(vector<string> v){
    
    if(v[0] == "CREATE"){
        
        
        if(!CheckifAccountExists(v[1]) || !alphaCheck(v[2])) return;
        
        code.push_back(v[1]);
        name.push_back(v[2]);
        amount.push_back(0);        //Initially create the account with 0 Rs as deposit...
    }
    
    if(v[0] == "DEPOSIT"){
        int index = searchAccountCode(v[1]);
        if(index == -1){
             cout<<"Account does not exist\n";
            return;
        }
        
        amount[index] = amount[index] + stoi(v[2]); 
    }
    if(v[0] == "WITHDRAW"){
        
        int index = searchAccountCode(v[1]);
        if(index == -1){
             cout<<"Account does not exist\n";
            return;
        }
        
        if(amount[index] < stoi(v[2])){ // Cheking if sufficient deposit is Available...
            cout<<"Insufficient Funds Available\n";
            return;
        }
        amount[index] = amount[index] - stoi(v[2]);
        
    }
    if(v[0] == "BALANCE"){
        
        int index = searchAccountCode(v[1]);
        if(index == -1){
             cout<<"Account does not exist\n";
            return;
        }
        cout<<name[index]<<" "<<amount[index]<<"\n";
    }
}

//This function does a syntax check for invalid inputs it also makes sure that the action keywords are not used in codes or names...
bool syntaxChecker(vector<string> v){
    
    if(v[0] != "CREATE" && v[0]!= "DEPOSIT" && v[0] != "WITHDRAW" && v[0] != "BALANCE"){
        cout << "\nInvalid Syntax. Please Specify an action to be made\nCorrect syntax as follows\n";
        Description();
        return false;
    }
    
    if(v[1] == "CREATE" && v[1] == "DEPOSIT" && v[1] == "WITHDRAW" && v[1] == "BALANCE"){
        
        cout<<"\n Invalid syntax. <Code> cannot be "<<v[1]<<"\n Please Follow the correct syntax";
        Description();
        return false;
    }
    
    if((v[0]!= "BALANCE") && v[2] == "CREATE" && v[2] == "DEPOSIT" && v[2] == "WITHDRAW" && v[2] == "BALANCE"){
        
        cout<<"\n Invalid Syntax. <Name>/<Amount> cannot be "<<v[2]<<"\n Please Follow the correct syntax";
        Description();
        return false;
    }
    return true;
}

//Main Function...
int main(){
    
    kelpBanner();
    
    Description();
    
    while(1){
        
        string str;
        cout<<"Please Enter your Input : ";
        getline(cin,str);
        
        vector<string> v = splitInput(str);
        
        if(v[0] == "EXIT"){
            cout<<"Thank you for choosing kelp Banking. Hope to see you soon";
            exit(0);
        }
        
        if(v.size() > 3){
            cout<<"\nInvalid Syntax, No extra Spaces/Inputs Allowed\n Please Check the Valid Syntax Below\n";
            Description();
            continue;
        }
        
        if(!syntaxChecker(v)) continue;
       
        operation(v);
       
    }
    
    return 0;
}