#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "file.h"
#include "split.h"

using namespace std;

//构造函数
File::File(string fileName):fileName(fileName){
}

//析构函数
File::~File(){
}


//利用列数和关键词查找，返回查找到的列数，否则返回0
int File::search(int column, string keyword){
    ifstream infile;
    infile.open(this->fileName.data());
    
    int lineNum = 0;
    string s;
    while (getline(infile,s)) {
        lineNum++;
        vector<string> v = split(s, "&");
        if (v[column] == keyword) {
            return lineNum;
        }
    }
    
    return 0;
}

//利用行数查找，返回该行的所有数据，必须保证行数确实存在
vector<string> File::search(int lineNum){
    ifstream infile;
    infile.open(this->fileName.data());
    string s;
    
    for (int i = 0; i < lineNum; i++) {
        getline(infile, s);
    }
    
    this->content = split(s, "&");
    
    return this->content;
}

//在文件尾部插入数据
bool File::insert(vector<string> content){
    this->content = content;
    
    ofstream outfile;
    outfile.open(this->fileName.data(),ios::app);
    string s;
    
    for (int i = 0; i < content.size(); i++) {
        s += this->content[i] + "&";
    }
    
    s.pop_back();
    outfile << s << endl;
    outfile.close();
    
    return true;
}

//删除行
bool File::line_delete(int lineNum){
    ifstream infile;
    infile.open(this->fileName.data());
    string s;
    string new_content;
    int now_line = 0;
    
    while (getline(infile, s)) {
        now_line++;
        if (now_line != lineNum) {
            new_content += s + "\n";
        }
    }
    infile.close();
    
    ofstream outfile;
    outfile.open(this->fileName.data(),ios::trunc);
    outfile << new_content;
    outfile.close();
    
    return true;
}

//修改行
bool File::line_change(int lineNum, vector<string> content){
    this->content = content;
    
    ifstream infile;
    infile.open(this->fileName.data());
    string s;
    string new_content;
    int now_line = 0;
    
    while (getline(infile, s)) {
        now_line++;
        if (now_line != lineNum) {
            new_content += s + "\n";
        }else{
            s = "";
            for (int i = 0; i < this->content.size(); ++i) {
                s += this->content[i] + "&";
            }
            s.pop_back();
            new_content += s + "\n";
        }
    }
    infile.close();
    
    ofstream outfile;
    outfile.open(this->fileName.data(),ios::trunc);
    outfile << new_content;
    outfile.close();
    
    return true;
}

//修改行中某列
bool File::line_change(int lineNum, int column, string newtext){
    ifstream infile;
    infile.open(this->fileName.data());
    string s;
    string new_content;
    int now_line = 0;
    
    while (getline(infile, s)) {
        now_line++;
        if (now_line != lineNum) {
            new_content += s + "\n";
        }else{
            this->content = split(s, "&");
            s = "";
            for (int i = 0; i < this->content.size(); ++i) {
                if (i != column) {
                    s += this->content[i] + "&";
                }else{
                    s += newtext + "&";
                }
            }
            s.pop_back();
            new_content += s + "\n";
        }
    }
    infile.close();
    
    ofstream outfile;
    outfile.open(this->fileName.data(),ios::trunc);
    outfile << new_content;
    outfile.close();
    
    return true;
}


