#pragma once
#include "./../dependencies.hpp"
using namespace std;
time_t start_timer(){
  
    time_t start_time = time(NULL);
    //Only starts the timer when the first character is pressed.
    return start_time;
}
int calculate_wpm(time_t start_time){
      
        vector<int> wpm_list_vector;  
        //average nikalna sakxas,sab wpm ko sum garera,store all the wpms in a vector
        //and push_back to push to the very vector and finally final wpm vanera dekhauna sakiyo,damnn
        time_t end_time = time(NULL);
        cout << difftime(start_time,end_time) <<endl;
        int wpm = 4.0/difftime(end_time,start_time) *60.0 ;    

        wpm_list_vector.push_back(wpm);
        
        int avg_wpm = accumulate(wpm_list_vector.begin(),wpm_list_vector.end(),0) / wpm_list_vector.size(); 
        return wpm;
}
