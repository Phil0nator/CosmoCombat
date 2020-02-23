//linux compatibility functions and features


#include <iostream>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//converts a windows file path to a linux file path when ran on linux, and vise-versa when on shit computers
//examples :file_fix("a\\b\\c\\d") would return a/b/c

char* file_fix(string file){ 
  #ifdef __linux__
    replace( file.begin(), file.end(), '\\', '/');
  #else
    replace( file.begin(), file.end(), '/', '\\');
  #endif
  //cout << file <<"\n";
  int n = file.length();
  char* char_array = new char[n + 1];

  strcpy(char_array, file.c_str());
  //cout << char_array <<"\n";
  return(char_array);
}
