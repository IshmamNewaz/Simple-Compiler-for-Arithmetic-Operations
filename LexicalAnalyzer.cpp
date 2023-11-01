#include<iostream>
#include<string>
#include<cctype>
#include<ctype.h>
using namespace std;
int main(){
    char Statement[120]; //Character Array for storing the Inputs as seperate chars
    int id=0; //index value for syntax table for each character
    int x=0;
    int var=0;
    int var2=-1;
    int var3=0;
    string variable; //String Variable for storing the input
    getline(cin, variable);

    for(int i=0; i<120;i++){ //Loop for Storing chars from the string input
        Statement[i]=variable[i];
        //cout<<Statement[i]<<" ";
        x++;
    }

    for(int i=0; i<x+1; i++){ //Loop for checking
        if(isalpha(Statement[i])){ //Checks if the current iteration has an alphabet
            if(isalpha(Statement[i+1])){ //checks if the next iteration has an alphabet
            }
            else{ //If there is no alphabet for next iteration it will output
                cout<<"<id"<<id<<">";
                id++;
            }
        }
        else if(isdigit(Statement[i])){
            var=i;
            var2++;
            if(isdigit(Statement[i+1])){}
            else{
               if(isdigit(Statement[i-1])){
                    var=var-var2;
                    var3=var+var2;
                    cout<<"<";
                    for(int x=var; x<var3+1; x++){

                        cout<<Statement[x];
                    }
                    cout<<">";
                    var=0;
                    var2=-1;
                    var3=0;
               }
               else{
                    cout<<"<"<<Statement[i]<<">";

               }
            }
        }
        else if (Statement[i] == '%' || Statement[i] == '/' || Statement[i] == '*' || Statement[i] == '+' || Statement[i] == '-' || Statement[i] == '=' || Statement[i] == '%') {
            cout<<"<"<<Statement[i]<<">";
        }
        else if( Statement[i] == ';'){
            cout<<"<"<<Statement[i]<<">";
            break;
        }

    }
}