#include "connect.h"

void statisticsData(){
    ifstream rfile("speed_data.csv");
    ofstream wfile("data_statistics.csv");

    // condition to run program
    if(rfile.is_open() && wfile.is_open()){
        wfile << "id, direction, frequency" << endl;
        string text, work;
        vector<string> row;
        float a[1000], b[1000];

        float lower = 900, upper = 1600;
        int num_outlier = 0;
        getline(rfile, text); // skip the first line
        
        
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
            int p = 0; //number of times a sensor id appearing = j + 1
            int j = 0; //number of times a sensor id appearing that satisfying
            int inc = 0, dec = 0;

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

            // count time decreasing and increasing
            for(int k = 0; k < j - 1; k++){
                if(a[k] < a[k+1]) inc++;
                if(a[k] > a[k+1]) dec++;
            }
            wfile << i << ",increment," << inc << endl;
            wfile << i << ",decrement," << dec << endl;

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