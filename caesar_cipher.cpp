#include <iostream>
#include <string>
#include <map>
using namespace std;

// Hansal Shah - 19BCP043 (Caesar Cipher)

string convert(string s, map <char,char> mapping_capital, map <char,char> mapping_small){
    string message = "";
    for(int i=0; i<s.length(); i++){
        int temp = s[i];
        if(temp>=66 && temp<=90){
            message+=mapping_capital[s[i]];
        }
        else if(temp>=97 && temp<=122){
            message+=mapping_small[s[i]];
        }
        else{
            message+=s[i];
        }
    }
    return message;
}

int main(){
    int caesar_key, choice;
    cout << "\nEnter the key to be used for caesar cipher: "; cin >> caesar_key;

    bool encrypt = true; 
    cout << "\nWhat do you want to do?\n";
    cout << "1. Encrypt a message\n";
    cout << "2. Decrypt a message\n";
    cout << "Enter your choice number: "; cin >> choice;

    if(choice==2){
        encrypt=false;
    }

    if(choice!=1 && choice!=2){
        cout << "\nSelect valid option only! The program will be terminated now\n"; 
    }
    else{
        string s; 
        cout << "\nEnter the message: "; 
        getline(cin>>ws,s);

        map <char, char> encrypt_small, encrypt_capital, decrypt_small, decrypt_capital;

        for(int i=65; i<=90; i++){
            char key = char(i);
            int temp = i+caesar_key;
            char value;
            if(temp<=90){
                value = char(temp);
            }
            else{
                temp-=26;
                value = char(temp);
            }
            encrypt_capital[key] = value;
            decrypt_capital[value] = key;
        }

        for(int i=97; i<=122; i++){
            char key = char(i);
            int temp = i+caesar_key;
            char value;
            if(temp<=122){
                value = char(temp);
            }
            else{
                temp-=26;
                value = char(temp);
            }
            encrypt_small[key] = value;
            decrypt_small[value] = key;
        }

        if(encrypt)
            cout << "\nEncrypted message: " << convert(s, encrypt_capital, encrypt_small) << "\n" << endl;
        else
            cout << "\nDecrypted message: " << convert(s, decrypt_capital, decrypt_small) << "\n" << endl;
    }
}