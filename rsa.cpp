#include <iostream>
#include <string>
#include <vector>
#define lli long long int
using namespace std;

lli exp_mod(lli n, lli e, lli m){
    if(e==0)
        return 1;
    else if (e==1)
        return (n%m);
    else{
        lli q = e/2, r = e%2;
        lli m1 = exp_mod(n, q, m), m2;
        if(r==1)
            m2 = n%m;
        else
            m2 = 1;
        return (m1*m1*m2)%m;
    }    
}

lli gcd(lli a, lli b){
    if (a==0)
        return b;
    else
        return gcd(b%a, a);
}

int main(){
    lli p, q, n, phi_n, e, d;
    cout << "Enter two prime numbers separated with a space: "; cin >> p >> q;
    n=p*q; phi_n=(p-1)*(q-1);
    for(int i=2; i<phi_n; i++){
        if(gcd(i,phi_n)==1){
            e=i; break;
        }
    }
    for (int i=1; i>0; i++){
        if ((1+(i*phi_n))%e==0) {
            d = (1+(i*phi_n))/e;
            break;
        }
    }

    cout << "\nThe encryption key (public): (" << e << ", " << n << ")" << endl;
    cout << "The decryption key (private): (" << d << ", " << n << ")" << endl;

    int choice;
    while(true){
        bool encrypt = true; 
        cout << "\nWhat do you want to do?\n";
        cout << "1. Encrypt a message\n";
        cout << "2. Decrypt a message\n";
        cout << "3. Exit\n";
        cout << "Enter your choice number: "; cin >> choice;

        if(choice==3)
            break;
        else if(choice==2)
            encrypt=false;
        
        if(choice!=1 && choice!=2 && choice!=3){
            cout << "\nSelect valid option only!\n"; 
            continue;
        }
        else{
            if(encrypt){
                string message; 
                cout << "\nEnter the message: "; 
                getline(cin >> ws, message);
                vector <lli> ciphered_digits;
                for (int i=0; i<message.length(); i++){
                    int ascii = message[i];
                    ciphered_digits.push_back(exp_mod(ascii, e, n));
                }
                
                cout << "Each character of the text is converted into a digit using the RSA algorithm, and they are follows: \n";
                for (int i=0; i<ciphered_digits.size(); i++)
                    cout << ciphered_digits[i] << " ";
                cout << endl;
            }
            else{
                int digits;
                vector <lli> ciphered_digits;
                cout << "\nEnter the number of ciphered digits: "; cin >> digits;
                cout << "Enter the ciphered digits (space separated):" << endl;

                for(int i=0; i<digits; i++) {
                    lli temp; cin >> temp;
                    ciphered_digits.push_back(temp);
                }

                string plaintext = "";
                for(int i=0; i<digits; i++){
                    char c = exp_mod(ciphered_digits[i],d,n);
                    plaintext+=c;
                }
                cout << "Decrypted message: " << plaintext << endl;
            }
        }
    }
}