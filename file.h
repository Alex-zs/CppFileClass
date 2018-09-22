//
//  file.h
//  filetest
//
//  Created by alex on 2018/9/1.
//  Copyright © 2018年 alex. All rights reserved.
//

#ifndef file_h
#define file_h

#include <vector>
#include <string>

using namespace std;

class File {
public:
    File(string);
    ~File();
    int search(int, string);
    vector<string> search(int);
    bool insert(vector<string>);
    bool line_delete(int);
    bool line_change(int, vector<string>);
    bool line_change(int, int, string);
private:
    string fileName;
    vector<string> content;
    
};

#endif /* file_h */
