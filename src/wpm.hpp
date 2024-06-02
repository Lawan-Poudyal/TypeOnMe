#include"dependencies.h"
using namespace std;

float start_timer(bool truth_value){
  if(truth_value){  
  int start_time = GetTime();
    //Only starts the timer when the first character is pressed.
    return start_time;}
  else{
    return -1;
  }
}
int calculate_wpm(float start_time){
      
        vector<int> wpm_list_vector;  
        //average nikalna sakxas,sab wpm ko sum garera,store all the wpms in a vector
        //and push_back to push to the very vector and finally final wpm vanera dekhauna sakiyo,damnn
        const float end_time = GetTime();
        float wpm = (float)3/(end_time-start_time) *(float) 60 ;    
        wpm_list_vector.push_back(wpm);
        
        int avg_wpm = accumulate(wpm_list_vector.begin(),wpm_list_vector.end(),0) / wpm_list_vector.size(); 
        return wpm;
}
