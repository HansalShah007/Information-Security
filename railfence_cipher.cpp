#include <iostream>
#include <string>
#include <map>
using namespace std;

// Hansal Shah - 19BCP043 (Rail Fence Cipher)

string encrypt_message(string s, int numRows) {
    if(numRows==1){
        return s;
    }
    int max_diff = (numRows-1)*2;
    string final_str = "";
    for(int i=0; i<numRows; i++){
        int first_diff = max_diff - (2*i), second_diff;
        
        if(first_diff==max_diff){
            second_diff = first_diff;
        }
        else{
            second_diff = max_diff - first_diff;
        }
        if(second_diff==max_diff){
            first_diff=second_diff;
        }
        
        int diff_in_use = first_diff;
        int j=i;
        while(j<s.length()){
            final_str+=s[j];
            j+=diff_in_use;
            if(diff_in_use==first_diff){
                diff_in_use=second_diff;
            }
            else{
                diff_in_use=first_diff;
            }
        }
    }
    return final_str;
}

string decrypt_message(string s, int numRows) {
    if(numRows==1){
        return s;
    }
    int max_diff = (numRows-1)*2;
    
    string final_str = "";
    for(int i=0; i<s.length(); i++){
        final_str+="_";
    }
    int index = 0;
    for(int i=0; i<numRows; i++){
        int first_diff = max_diff - (2*i), second_diff;
        
        if(first_diff==max_diff){
            second_diff = first_diff;
        }
        else{
            second_diff = max_diff - first_diff;
        }
        if(second_diff==max_diff){
            first_diff=second_diff;
        }
        
        int diff_in_use = first_diff;
        int j=i;
        while(j<s.length()){
            final_str[j]=s[index]; index++;
            j+=diff_in_use;
            if(diff_in_use==first_diff){
                diff_in_use=second_diff;
            }
            else{
                diff_in_use=first_diff;
            }
        }
    }
    return final_str;
}

int main(){
    cout << "\nEncryption & Decryption using Rail Fence Cipher\n";
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
            string s; 
            int key;
            cout << "\nEnter the message: "; 
            getline(cin>>ws,s);
            cout << "Enter the key: ";
            cin >> key;

            if(encrypt){
                cout << "The encrypted message is: " << encrypt_message(s, key) << endl;
            }
            else{
                cout << "The decrypted message is: " << decrypt_message(s, key) << endl;
            }

        }
    }
}
