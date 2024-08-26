#pragma once
#include "./../dependencies.hpp"
float accuracy(vector<string> typedWords,vector<string> totWords){ 
  int incorWordCount=0;   
  for(int i=0;i<typedWords.size();i++){
    if(strcmp(typedWords[i].c_str(),totWords[i].c_str()) !=0){ 
           incorWordCount+=1;       
    }
  }
  return (float)(typedWords.size() - incorWordCount )/ totWords.size() * 100;
}
