#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc , char *argv[]){
    //bound
    float lower = 900, upper = 1600;
    int num_outlier = 0;

    //from terminal to get name text file
    string filename;
    if(argc == 2) filename = argv[1];
    else filename = "speed_data.csv"; // namefile default

    //create a variable to store string
    string text;

    //work with file
    //open file
    ifstream rfile(filename);
    ofstream wfile("outlier_data.csv");

    
    //working 
    if(rfile.is_open() && wfile.is_open()){
        getline(rfile, text); // skip the first line
        wfile << "number of outliers: " << num_outlier << endl; 
        wfile << "id,time,values" << endl;

        while(getline(rfile, text)){
            //process each line
            int ln = text.length(), cnt = 0;
            char reverse_data[10], data[10];
            //cout << text << endl;
            for(int i = ln - 1; i >= 0; i--){
                if(text[i] == ','){
                    break;
                }
                reverse_data[cnt] = text[i];
                //cout << reverse_data[cnt] <<" ";
                cnt++;
            }
            int ln_data = cnt;
            //cout << ln_data;
            
            
            for(int j = 0; j < ln_data; j++){
                data[j] = reverse_data[(ln_data -1) - j];
                //cout << data[j] << " ";
            }
            
            float speed = stod(data);
            
            if(speed < lower || speed > upper){
                wfile << text << endl;
                num_outlier += 1;
            }
        }
        wfile.seekp(20);
        wfile << num_outlier;
        
       
        //close file
        rfile.close();
        wfile.close();
        cout << "Process successfully";
    }
    else cout << "can not open file" << endl;
    
    return 0;
}