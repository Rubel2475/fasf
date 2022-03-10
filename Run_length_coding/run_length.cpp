#include<bits/stdc++.h>
using namespace std;

char msg[10000];
string en="", de=""; 

string to_string(int count){

    string tmp="";
    while(count){
        tmp += char(count%10 + 48);
        count /= 10;
    }
    reverse(tmp.begin(), tmp.end());

    return tmp;
}

int main(){

    int count=0, i,j;
    
    ifstream in("run_in.txt");
    in >> msg;

    ofstream encoded, decoded;
    encoded.open("encoded.txt");
    decoded.open("decoded.txt");


    //encryption
    for(i=0; msg[i]; i++){
        count =0;
        for(j=i; msg[j] && (msg[i]==msg[j]); j++){
            count++;
        }
        i = j-1;
        en += msg[i];
        en += '(' + to_string(count) + ')';

    }
    cout << "encoded: " << en << endl;
    encoded << "encoded: " << en << endl;



    //decryption

    // encoded.open("run_encoded.txt");
    // encoded>>en1;

    for(i =0; en[i]; i++){
        if(en[i]=='('){
            count =0;
            for(j=i+1; en[j] && (en[j]!=')'); j++){
                count = count*10 + int(en[j]-'0');
            }

            for(int k=0; k<count; k++){
                de += en[i-1];
            }
        }
    }
    cout << "decoded: " << de << endl;
    decoded << "decoded: " << de << endl;


    in.close();
    encoded.close();
    decoded.close();


    return 0;
}