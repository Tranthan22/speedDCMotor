#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(){
    ifstream rfile("speed_data.csv");
    ofstream wfile("data_summary.csv");

    // condition to run program
    if(rfile.is_open() && wfile.is_open()){
        wfile << "id, parameters, time, values" << endl;
        string text, work;
        vector<string> row;
        float a[5000], b[5000];

        float lower = 900, upper = 1600;
        int num_outlier = 0;
        getline(rfile, text); // skip the first line
        
        float max, min, mean;
        //finding number of sensors
        int n = 0;
        while(getline(rfile, text)){
            row.clear();
            istringstream ss(text);
            while(getline(ss, work, ',')){
                row.push_back(work);
            }
            int id = stod(row[0]);
            if(id > n) n = id;
        }
        rfile.close();
        rfile.open("speed_data.csv");
        getline(rfile, text);//skip first line

        for(int i = 1; i <= n; i++){
            float sum = 0;
            int p = 0; //number of times a sensor id appearing = j + 1
            int j = 0; //number of times a sensor id appearing that satisfying
            // store speed value
            while(getline(rfile, text)){
                row.clear();
                istringstream ss(text);
                while(getline(ss, work, ',')){
                    row.push_back(work);
                }
                if(stod(row[0]) == i){
                    b[p] = stod(row[2]);
                    p++;
                }
            }
            for(int q = 0; q < p; q++){
                if(b[q] >= lower && b[q] <= upper){
                    a[j] = b[q];
                    j++;
                }
            }
            

            // find min max and mean
            max = a[0];
            min = a[0];
            for(int k = 1; k < j; k++){
                if(max < a[k]) max = a[k];
                if(min > a[k]) min = a[k];
                
            }
            for(int k = 0; k < j; k++) sum += a[k];

            rfile.close();
            rfile.open("speed_data.csv");
            getline(rfile, text);//skip first line
            //print out 
            vector <string> sMax,sMin,sMean,timeT;
            string startT,endT;
            int begin,finish;
            while(getline(rfile, text)){
                row.clear();
                istringstream ss(text);
                while(getline(ss, work, ',')){
                    row.push_back(work);
                }
                if(stod(row[0]) == i){
                    float speed = stod(row[2]);
                    if(speed == max) sMax = row;
                    if(speed == min) sMin = row;

                    //find mean excluding outlier data
                    if(speed == b[0]){
                        startT = row[1];
                        istringstream ss(startT);
                        while(getline(ss, work, ':')){
                            timeT.push_back(work);
                        }
                        begin = stod(timeT[0])*3600 + stod(timeT[1])*60 + stod(timeT[2]);
                    }
                    timeT.clear();
                    if(speed == b[p-1]){
                        endT = row[1];
                        istringstream ss(endT);
                        while(getline(ss, work, ':')){
                            timeT.push_back(work);
                        }
                        finish = stod(timeT[0])*3600 + stod(timeT[1])*60 + stod(timeT[2]);
                    }
                }
            }
            
            wfile << i << "," << "max" << "," << sMax[1] << "," << sMax[2] << endl;
            wfile << i << "," << "min" << "," << sMin[1] << "," << sMin[2] << endl;
            //wfile << i << "," << "mean" << "," << "unknown" << "," << sum/j << endl;
            int hour = 0, second = 0, minute = 0;
            second = finish - begin;

            cout << finish << " " << begin << " " << second << endl;
            if(second<10)
                wfile << i <<"," <<"mean"<<"," <<"0"<<hour <<":" <<"0"<<minute << ":" <<"0"<<second << "," << sum/j <<endl;
            else if(second<60)
                wfile << i <<"," <<"mean"<<"," <<"0"<<hour <<":" <<"0"<<minute << ":"<<second << "," <<sum/j <<endl;
            else if(second>=60&&second<3600){
                minute=(second-second%60)/60;
                second%=60;
                wfile << i <<"," <<"mean"<<"," <<hour <<":" << minute << ":" <<second << "," <<sum/j <<endl;
            }
            else{
                hour=(second-second%3600)/3600;
                minute=((second%3600)-(second%3600)%60)/60;
                second=second-minute*60-hour*3600;
                wfile << i <<"," <<"mean"<<"," <<hour <<":" << minute << ":" <<second << "," <<sum/j <<endl;
            }

            rfile.close();
            rfile.open("speed_data.csv");
            getline(rfile, text);//skip first line

        }
        rfile.close();
        wfile.close();
        cout << "Process successfully";   
    }
    else cout << "can not open file";
}