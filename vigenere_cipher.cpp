#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Hansal Shah - 19BCP043 (Vigenere Cipher)

string encrypt_message(vector <int> key, string message){
    int key_length = key.size();
    string encrypted_message = ""; 
    for(int i=0; i<message.length(); i++){
        int temp = message[i];
        if(temp>=65 && temp<=90){
            temp-=65;
            char final_character =  char(((temp+(key[i%key_length]))%26)+65);
            encrypted_message+=final_character;
        }
        else if(temp>=97 && temp<=122){
            temp-=97;
            char final_character =  char(((temp+(key[i%key_length]))%26)+97);
            encrypted_message+=final_character;
        }
        else{
            encrypted_message+=message[i];
        }
    }
    return encrypted_message;
}

string decrypt_message(vector <int> key, string message){
    int key_length = key.size();
    string decrypted_message = "";
    for(int i=0; i<message.length(); i++){
        int temp = message[i];
        if(temp>=65 && temp<=90){
            temp-=65;
            int diff = temp-(key[i%key_length]);
            if(diff<0){
                diff+=26;
            }
            char final_character =  char(diff+65);
            decrypted_message+=final_character;
        }
        else if(temp>=97 && temp<=122){
            temp-=97;
            int diff = temp-(key[i%key_length]);
            if(diff<0){
                diff+=26;
            }
            char final_character =  char(diff+97);
            decrypted_message+=final_character;
        }
        else{
            decrypted_message+=message[i];
        }
    }
    return decrypted_message;
}

int main(){
    cout << "\nEncryption & Decryption using Vigenere Cipher\n";
    int choice;
    while(true){
        bool encrypt = true; 
        cout << "\nWhat do you want to do?\n";
        cout << "1. Encrypt a message\n";
        cout << "2. Decrypt a message\n";
        cout << "3. Exit\n";
        cout << "Enter your choice number: "; cin >> choice;

        if(choice==3){
            break;
        }
        else if(choice==2){
            encrypt=false;
        }

        if(choice!=1 && choice!=2 && choice!=3){
            cout << "\nSelect valid option only!\n"; 
            continue;
        }
        else{

            string message; 
            cout << "\nEnter the message: "; 
            getline(cin>>ws,message);

            // Receiving the key to be used for conversion
            string key_string;
            cout << "Enter the key: ";
            cin >> key_string;

            vector <int> key_mapping;
            for(int i=0; i<key_string.length(); i++){
                int temp = key_string[i];
                if(temp>=65 && temp<=90){
                    key_mapping.push_back(temp-65);
                }
                else{
                    key_mapping.push_back(temp-97);
                }
            }

            if(encrypt){
                cout << "Encrypted message: " << encrypt_message(key_mapping, message) << endl;
            }
            else{
                cout << "Decrypted message: " << decrypt_message(key_mapping, message) << endl;
            }
        }
    }
}
