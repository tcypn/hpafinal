#include<stdio.h>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<omp.h>

using namespace std;
string line;
string a,b;

vector<int> vec[128];
int color[128]; //2=gen 1=has power 0=no power
int cho[128];
int out[128];
int pass[128];
int answer[128];
int minnum,siz;
void go(int ch[],int o[],int pa[],int index,int num){
    
        /*cout<<"color=";
        for(int i=0;i<siz;i++) cout<<color[i];
        cout<<" ";

        cout<<"out=";
        for(int i=0;i<siz;i++) cout<<out[i];
        cout<<" ";
        
        cout<<"pass=";
        for(int i=0;i<siz;i++) cout<<pass[i];
        cout<<" ";
        cout<<endl;*/
        
        if(pa[index]==1) {
            return;
            }//ถ้าเคยผ่านแล้วจะไม่ทำอีก
        if (num>minnum) {
            return;
            }

        bool allgotpower=true;
        for(int i=0; i < siz; i++){
            if(ch[i]==0) {
                allgotpower=false;
                break;
                }
        }

        if(allgotpower) {
            if(num<minnum){
                minnum=num;//ถ้ามีไฟทุกอันแล้วจะปรับค่าminใหม่
                copy(o,o+siz,answer);
                copy(ch,ch+siz,cho);
                /*cout<<"check power area=";
                for(int i=0;i<siz;i++) cout<<ch[i];
                cout<<endl;*/
            }
            return;
        }
        
        else{
            int pa2[128];
            int o2[128];
            int ch2[128];
            copy(o,o+siz,o2);
            copy(pa,pa+siz,pa2);
            copy(ch,ch+siz,ch2);

            pa2[index]=1;//ผ่านไปแล้ว

            o2[index]=0;//case not plant
            #pragma omp parallel for
            for(auto i:vec[index]){//ไปทุกอันที่เชื่อมกับnodeนี้
                go(ch2,o2,pa2,i,num);
            }

            o2[index]=1;//case plant
            ch2[index]=2;
            num++;
            #pragma omp parallel for
            for(auto i:vec[index]){
                //เข้ามานี่แล้ว
                if(ch2[i]==0) { //ทำไมไม่เข้าifเฉย
                    ch2[i]=1;
                    }//ทุกอันที่ยังไม่มีไฟบอกว่ามีไฟแล้ว
                
                go(ch2,o2,pa2,i,num);
            }
        }

    }

int main(int argc,char *argv[])
{
    string filename=argv[1];
    ifstream file(filename);
    ofstream outfile(argv[2]);
    
    if(file.is_open()){
        getline(file,line);
        int n=stoi(line); //num node
        minnum=n;
        siz=n;
        getline(file,line);
        int l=stoi(line); //num line

        while(getline(file,a,' ')&&getline(file,b)){ 
            vec[stoi(a)].push_back(stoi(b));
            vec[stoi(b)].push_back(stoi(a));
        }
        file.close();
    }
    for(int i=0;i<siz;i++){
        #pragma omp parallel
        {
    
        #pragma omp single nowait
            go(color,out,pass,i,0);
        }
    }
    /*for(int i=0;i<siz;i++){
        cout<<answer[i];
    }
    cout<<" ";
    for(int i=0;i<siz;i++){
        cout<<cho[i];
    }*/

    if(outfile.is_open()){
        for(int i=0;i<siz;i++){
            outfile<<answer[i];
        }   
        outfile.close();
    }
}