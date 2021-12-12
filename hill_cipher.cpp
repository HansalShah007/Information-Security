#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Hansal Shah - 19BCP043 (Hill Cipher)


void display_matrix(int matrix[3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }        
}

string hillCipher(vector <vector<int>>& caesar_equivalent, int matrix[3][3]){
    string conv_message = "";

    for(int pair=0; pair<caesar_equivalent.size(); pair++){
        int column = 0;
        for (int times=0; times<3; times++){
            int sum = 0;
            for (int j=0; j<3; j++){
                sum += caesar_equivalent[pair][j]*matrix[j][column];
            }
            sum%=26; sum+=97;
            char c = sum;
            // cout << c << endl;
            conv_message= conv_message+c;
            column++;
        }
    }
    return conv_message;
}

int main(){
    // initializing the variables to be used for the en/deciphering algorithm
    int e_matrix[3][3] = {{6,24,1},{13,16,10},{20,17,15}};
    int d_matrix[3][3] = {{8,5,10},{21,8,21},{21,12,8}};

    cout << "\nEncryption & Decryption using Hill Cipher\n";

    cout << "\nMatrix used for encryption" << endl;
    display_matrix(e_matrix);

    cout << "\nMatrix used for decryption" << endl;
    display_matrix(d_matrix);

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

            // removing spaces and converting the message into lower case characters and stuffing 
            // it with character 'x' if required

            string clean_message = "";
            for (int i=0; i<message.length(); i++){
                if(message[i]!=' '){
                    int temp = message[i];
                    if(temp>=65 && temp<=90){
                        temp+=32;
                        char c = temp;
                        clean_message += c;
                    }
                    else{
                        clean_message += message[i];
                    }
                }
            }

            int remainder = clean_message.length()%3;
            if(remainder!=0)
                remainder=3-remainder;
            for (int i=0; i<remainder; i++){
                clean_message+='x';
            }

            // dividing the message into pairs of three characters each and converting them into
            // their ceasar cipher equivalent shift number
            vector <vector<int>> caeasar_equivalent;
            for (int i=0; i<clean_message.length(); i+=3){
                int temp_1 = clean_message[i], temp_2 = clean_message[i+1], temp_3 = clean_message[i+2];
                temp_1-=97; temp_2-=97; temp_3-=97;
                vector<int> temp = {temp_1,temp_2,temp_3};
                caeasar_equivalent.push_back(temp);
            }

            if(encrypt){
                cout << "Encrypted message: " << hillCipher(caeasar_equivalent, e_matrix) << endl;
            }
            else{
                cout << "Decrypted message: " << hillCipher(caeasar_equivalent, d_matrix) << endl;
            }
        }
    }
}