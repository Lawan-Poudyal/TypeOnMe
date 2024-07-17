#pragma once
#include "../main.hpp"

float accuracy(vector<string> typedWords,vector<string> totWords){ 
  int incorWordCount=0;   
  for(int i=0;i<typedWords.size();i++){
    if(strcmp(typedWords[i].c_str(),totWords[i].c_str()) !=0){ 
           incorWordCount+=1;       
            cout << typedWords[i] <<"||"<< totWords[i]<<"||" <<endl;
    }
  }
  return (float)(typedWords.size() - incorWordCount )/ totWords.size() * 100;

}
