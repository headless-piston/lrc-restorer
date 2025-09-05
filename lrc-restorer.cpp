#include<iostream>
#include<fstream>
using namespace std;
bool f=1;
int main(){
    ifstream in(".lrc",ios::binary);
    ofstream out("fixed.lrc",ios::binary);
    out<<char(0xEF)<<char(0xBB)<<char(0xBF);//防中文乱码
    string line,last_time;
    while(getline(in,line)){
        if(line.empty()){
            out<<last_time<<'\n';
            continue;
        }
        auto it=--line.end();
        while(it!=line.begin()&&*it==' ')
            line.erase(it--);//去除行末空格
        string s;
        int pos=0;
        if(line[pos]=='['){
            s.push_back(line[pos++]);
            while(pos<(int)line.length()&&line[pos]!=']')
                s.push_back(line[pos++]);
            if(pos<(int)line.length())
                s.push_back(line[pos++]);
        }//截取时间戳
        if(s.length()>9)
            s.erase(9),s.push_back(']');//限制时间戳长度
        string content;
        while(pos<(int)line.length())
            content.push_back(line[pos++]);
        if(f){//第一行
            out<<"[00:00.0]"<<content<<'\n';
            f=0;
        }
        else if(!last_time.empty()||!content.empty())
            out<<last_time<<content<<'\n';
        last_time=s;
    }
    return 0;
}
