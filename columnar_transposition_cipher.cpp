#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

// Author: Hansal Shah

string encrypt_message(char** matrix, int rows, map <int,int> key){
    string encrypted_message = "";
    for(int i=1; i<=key.size(); i++){
        int column = key[i]-1;
        for(int r=0; r<rows; r++){
            encrypted_message+=matrix[r][column];
        }
    }
    return encrypted_message;
}

string decrypt_message(char** matrix, int rows, int columns, map <int, int> key){
    string decrypted_message="";
    char** temp_matrix = (char**)malloc(rows*sizeof(char*));
    for(int i=0; i<rows; i++){
        temp_matrix[i] = (char*)malloc(columns*sizeof(char));
    }

    int matrix_column = 0;
    for(int i=1; i<=key.size(); i++){
        int actual_column = key[i]-1;
        for(int r = 0; r<rows; r++){
            temp_matrix[r][actual_column] = matrix[r][matrix_column];
        }
        matrix_column++;
    }

    for(int r=0; r<rows; r++){
        for(int c=0; c<columns; c++){
            decrypted_message+=temp_matrix[r][c];
        }
    }

    // Removing the garbage character ('q') from the end of the message
    int end = decrypted_message.length()-1;
    while(decrypted_message[end]=='q'){
        decrypted_message.pop_back();
        end--;
    }

    return decrypted_message;
}

int main(){

    cout << "\nEncryption & Decryption using Column Transposition Cipher\n";
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

            // Receiving the message to be converted (for both)
            string message; 
            cout << "\nEnter the message: "; 
            getline(cin>>ws,message);

            // Receiving the key to be used for conversion
            string key;
            cout << "Enter the key: ";
            cin >> key;

            //Converting the key into a usable format
            map <int, int> encrypt_key;
            vector <int> decrypt_key;
            for(int i=0; i<key.length(); i++){
                int temp = key[i];
                encrypt_key[temp-48] = i+1;
                decrypt_key.push_back(temp-48);
            }

            if(encrypt){

                //This program does not ignore space characters and uses 'q' as a garbage character
                int garbage_characters = key.length()-(message.length()%key.length());
                for(int i=0; i<garbage_characters; i++){
                    message+='q';
                }

                //Forming the row transposition matrix 
                int rows = message.length()/key.length();
                char **matrix = (char**)malloc(rows*sizeof(char*));
                for(int i=0; i<rows; i++){
                    matrix[i] = (char*)malloc(key.length()*sizeof(char));
                }

                //Filling the matrix
                int message_index = 0;
                for(int r=0; r<rows; r++){
                    for(int c = 0; c<key.length(); c++){
                        matrix[r][c] = message[message_index];
                        message_index++;
                    }
                }

                cout << "The encrypted message is: " << encrypt_message(matrix, rows, encrypt_key) << endl;
            }
            else{

                //Forming the row transposition matrix
                int rows = message.length()/key.length();
                char **matrix = (char**)malloc(rows*sizeof(char*));
                for(int i=0; i<rows; i++){
                    matrix[i] = (char*)malloc(key.length()*sizeof(char));
                }

                // Filling the matrix
                int message_index = 0;
                for(int c=0; c<key.length(); c++){
                    for(int r = 0; r<rows; r++){
                        matrix[r][c] = message[message_index];
                        message_index++;
                    }
                }

                cout << "The decrypted message is: " << decrypt_message(matrix, rows, key.length(), encrypt_key) << endl;
            }

        }
    }
}
