#include<bits/stdc++.h>
using namespace std;

// symbol table
double a, probability[256];
char ch[256];
int in;


double arithmetic_coding(string str){

    int i,j,n,m;

    //cout<<str<<endl;

    ofstream encode;
    encode.open("arithmetic_encoded.txt");

    double range = 1.0, point = 0, tmp_range = 0;

    // point is the high point value of a tmp_range
    for(i = 0; i < str.size(); i++){
        point = point - tmp_range;
        for(j = 0; j < in; j++){
            tmp_range = range*probability[j];
            point = point + tmp_range;
            if(str[i] == ch[j]){
                //printf("%lf %lf\n",point-tmp_range, point);
                range = tmp_range;
                //printf("%c %lf\n",str[i],point);
                break;
            }
        }
    }
    double tag = (point + (point - tmp_range))/2.0;


    encode<<in<<endl;
    for(i = 0; i < in; i++){
        encode<<(int)ch[i]<< " "<<probability[i]<<endl;
    }

    cout<<"\nEncrypted data : ";
    cout<<tag<<endl;
    encode<<tag<<endl;

    encode.close();

    return tag;
}

string arithmetic_decoding(){

    int i,j,k,x;
    double tag;

    ifstream encoded;
    ofstream decoded;

    encoded.open("arithmetic_encoded.txt");
    decoded.open("arithmetic_decoded.txt");

    encoded>>in;
    for(i = 0; i < in ; i++){
        encoded>>x>>probability[i];
        ch[i] = (char)x;
    }

    encoded>>tag;

    double range = 1.0, point = 0, tmp_range = 0;
    string decd = "";

    // point is the high point value of a tmp_range
    while(decd[decd.size()-1] != '$'){
        point = point - tmp_range;
        for(j = 0; j < in; j++){
            tmp_range = range*probability[j];
            point = point + tmp_range;
            //printf("%lf %lf\n",curr, probability[j]);
            if(((point - tmp_range) < tag && point > tag) || tmp_range<0.000001){
                range = tmp_range;
                //printf("%lf %lf\n",point-tmp_range, point);
                decd += ch[j];
                break;
            }
        }
    }

    cout<<"Decrypted data : ";
    cout<<decd<<endl;
    decoded<<decd<<endl;

    encoded.close();
    decoded.close();

    return decd;
}

int mark[300];

int main(){

    int i,j,n,m,a,b;
    double enc;
    string decd, str;

    ifstream input;
    input.open("arithmetic_coding_in.txt");

    getline(input, str);

    /// probability calculation
    for(i = 0; i < str.size(); i++){
        mark[(int)str[i]]++;
    }

    in = 0;
    for(i = 0; i <= 255; i++){
        if(mark[i]){
            ch[in] = (char)i;
            probability[in] = (float)mark[i]/(float)str.size();
            in++;
        }
    }


    enc = arithmetic_coding(str);

    cout<<"Original string: "<<str<<endl;

    decd = arithmetic_decoding();


    input.close();

    return 0;
}
