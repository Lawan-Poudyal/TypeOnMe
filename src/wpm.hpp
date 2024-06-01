#include"dependencies.h"
using namespace std;

int calculate_wpm(){
        vector<int> wpm_list_vector;  
        //average nikalna sakxas,sab wpm ko sum garera,store all the wpms in a vector
        //and push_back to push to the very vector and finally final wpm vanera dekhauna sakiyo,damnn
        const float end_time = GetTime();
        float wpm = (float)3/(end_time) * 60 ;    
        wpm_list_vector.push_back(wpm);
        
        int avg_wpm = accumulate(wpm_list_vector.begin(),wpm_list_vector.end(),0) / wpm_list_vector.size(); 
        return avg_wpm;
}
