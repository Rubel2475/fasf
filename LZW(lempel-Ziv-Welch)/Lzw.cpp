#include<bits/stdc++.h>
using namespace std;

void lzw_encoding(){

    int i,j,m,n,code, tmp_code, mx_code=0;
    string msg, tmp;
    char ch;

    vector<int> code_vec;
    map<string, int> mp;

    ofstream encode("encoded.txt");
    //ofstream decode("decoded.txt");

    ifstream in("in.txt");
    getline(in, msg);

    in >> n;

    for(i=0; i<n; i++){
        in >> ch >> code;
        cout << ch << " " << code << endl;
        encode << int(ch) << " " <<  code << endl;

        tmp = "";
        tmp += ch;
        mp[tmp] = code;
        mx_code = max(mx_code, code);
    }
    encode << -1 << " " << -1 << endl;


    tmp ="";
    for(i=0; i<msg.size(); i++){

        tmp_code = mp[tmp];
        tmp += msg[i];

        if(!mp[tmp]){

            code_vec.push_back(tmp_code);  //output the code(for s -> according algo)
            mp[tmp] = ++mx_code;          //new code for new string(output)

            cout << tmp << endl;

            tmp=""; 
            tmp += msg[i];  //s = c ( according algo)
        }
    }
    tmp_code = mp[tmp];
    code_vec.push_back(tmp_code);

    encode << code_vec.size() << endl;
    cout << "encoding: ";
    for(i=0; i<code_vec.size(); i++){

        if(i+1 == code_vec.size()){
            cout<<code_vec[i]<<endl;
            encode<<code_vec[i]<<endl;
        }
        else{
            cout << code_vec[i] << " ";
            encode << code_vec[i] << " ";
        }
    }

    in.close();
    encode.close();
}



void lzw_decoding(){

    int i, j, n, k ,m, inc=0;
    map<int, string>mp;
    vector<int>code;
    string decd, tmp, str;
    char ch;

    ifstream in;
    in.open("encoded.txt");

    ofstream out;
    out.open("decoded.txt");

    for(i = 0; ; i++){
        in>>k>>n;
        //cout<<k<<" "<<n<<endl;
        if(n==-1) break;
        tmp = "";
        tmp += (char)k;
        mp[n] = tmp;
        inc++;
    }

    in>>n;
    decd = "";
    for(i = 0; i < n; i++){
        in>>m;
        //code.push_back(m);
        //cout<<m<<endl;
        decd += mp[m];

        if(i == 0){
            tmp = mp[m];
            continue;
        }

        tmp += mp[m][0];
        mp[++inc] = tmp;

        tmp = mp[m];
    }

    cout<<"Decoded String : "<<decd<<endl;
    out<<decd<<endl;

    out.close();
    in.close();

    // return decd;
}


int main(){


    lzw_encoding();

    lzw_decoding();

    return 0;
}