#include "connect.h"
void sortData()
{
  string text, work;
  vector<string> row;
  clock_t start, end;
  start = clock(); 
  float a[1000], b[1000];
  float lower = 900, upper = 1600;

  ifstream rfile("speed_data.csv");
  ofstream wfile("sorted_data.csv");

  wfile << "sorting duration:      seconds" <<endl;
  getline(rfile, text);
  wfile << text << endl;

  //find number of sensors
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
        getline(rfile, text);//skip first text

  // work for each sensor id
  for (int i = 1; i <= n ; i++){
    int p = 0; //number of times a sensor id appearing = j + 1
    int j = 0; //number of times a sensor id appearing that satisfying

    // store in id, time and value in row and filter satisfying values
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

    //toSort
    for(int k = 0; k < j - 1; k++){
        for (int h = k; h < j; h++){
            if(a[k] > a[h]){
                float temp = a[k];
                a[k] = a[h];
                a[h] = temp;
            }
        }
    }

    // to put poiter at beginning
    rfile.close();
    rfile.open("speed_data.csv");
    getline(rfile, text); //skip first text

    // write data to sorted file
    for(int k = 0; k < j; k++){
      while(getline(rfile, text)){
        row.clear();
        istringstream ss(text);

        while(getline(ss, work, ',')){
          row.push_back(work);
        }

        float speed = stod(row[2]);

        if(speed == a[k]){
          wfile << text << endl;
        }
      }
        rfile.close();
        rfile.open("speed_data.csv");
        getline(rfile, text);
    }  

    
    rfile.close();
    rfile.open("speed_data.csv");
    getline(rfile, text);
      
  }  
  end = clock();
  double time_use = (double)(end-start)/ CLOCKS_PER_SEC;
  wfile.seekp(17);
  wfile << time_use;

  rfile.close();
  wfile.close();
}