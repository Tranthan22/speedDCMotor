#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<string.h>
#include<iomanip>
using namespace std;

//Funtion for Converting from string to int

int cStringToInt(char *str) 
{
	int temp = 0;
	int sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str>='0' && *str <='9') 
	{
		temp *= 10;
		temp += (int)(*str - '0');
		str++;
	}
	return temp * sign;
}

//Funtion for Generating Radom number
float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}



//Main
int main(int argc, char *argv[]) {
    
	int num_sensors=0,sampling=0, interval=0,count=0;
	
	// Analysis input

	switch(argc)
	{
		case 1:
			num_sensors = 1;
			sampling = 10;
			interval = 3600;
			break;

		case 3:
			if(strcmp(argv[1],"-n")==0 && strcmp(argv[2],"-n")==1 && strcmp(argv[2],"-st")==1 && strcmp(argv[2],"-si")==1) {num_sensors = cStringToInt(argv[2]); sampling=10; interval=3600;}
			else {if(strcmp(argv[1],"-st")==0 && strcmp(argv[2],"-n")==1 && strcmp(argv[2],"-st")==1 && strcmp(argv[2],"-si")==1) {num_sensors=1 ; sampling = cStringToInt(argv[2]); ; interval=3600;}
					else{if(strcmp(argv[1],"-si")==0 && strcmp(argv[2],"-n")==1 && strcmp(argv[2],"-st")==1 && strcmp(argv[2],"-si")==1) {num_sensors=1 ; sampling=10; interval = cStringToInt(argv[2]);}
							else cout << "Error, please try again according to intial formula !";
					}

			}
			break;

            
        case 5:
            if((strcmp(argv[1],"-n")==0 || strcmp(argv[1],"-st")==0 || strcmp(argv[1],"-si")==0) && (strcmp(argv[3],"-n")==0 || strcmp(argv[3],"-st")==0 || strcmp(argv[3],"-si")==0) && (strcmp(argv[2],"-n")==1 && strcmp(argv[2],"-st")==1 && strcmp(argv[2],"-si")==1) && (strcmp(argv[4],"-n")==1 && strcmp(argv[4],"-st")==1 && strcmp(argv[4],"-si")==1)) 
                {
                    if(strcmp(argv[1],"-n")==0) {num_sensors = cStringToInt(argv[2]);} 
                    if(strcmp(argv[1],"-st")==0) {sampling = cStringToInt(argv[2]);}
                    if(strcmp(argv[1],"-si")==0) {interval = cStringToInt(argv[2]);}

                    if(strcmp(argv[3],"-n")==0) {num_sensors = cStringToInt(argv[4]);}
                    if(strcmp(argv[3],"-st")==0) {sampling = cStringToInt(argv[4]);}
                    if(strcmp(argv[3],"-si")==0) {interval = cStringToInt(argv[4]);}

					if(num_sensors==0) num_sensors = 1;
					if(sampling==0) sampling = 10;
					if(internal==0) interval = 3600;
                }
            else cout << "Error, please try again according to intial formula !";
			break;


		case 7: num_sensors=cStringToInt(argv[2]); sampling=cStringToInt(argv[4]); interval=cStringToInt(argv[6]);
		break;


	default: cout << "Error, please try again according to intial formula !";
    }
	
	
	// time for now based on time system
	time_t now = time(0); // declare a time_t variable
    long int x; // declare a long int
    x = static_cast<int> (now); // case the time_t variable to a long int
    std::string tmp = std::to_string(x);
	
	//file
	string name = "speed_data_" + to_string(x) + ".csv";
	ofstream ofs(name);

	tm *ltm = localtime(&now);
	
	int its=interval % sampling;
	//Write into file csv
	ofs << "id" <<','<<"time"<<','<<"values"<<endl;
	for(int i=1; i<=1000; i++) {
		
		for(int j = 1; j <= num_sensors; j++) { 
		float radom = float_rand(0.0,3000.0);
		ofs << j <<','<< ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec <<','<< setprecision(1) << fixed << radom << endl;
		}
		
		if(count + sampling > interval) break;
		ltm->tm_sec += sampling;
		count += sampling;
		
		
		//Ensuring that time is right after being added 
		if(ltm->tm_sec>=60) {
			ltm->tm_min++;
			ltm->tm_sec = ltm->tm_sec % 60;
			if(ltm->tm_min==60) {
				ltm->tm_min=0;
				ltm->tm_hour++;
			}
		}

	}
	ofs.close();

	

	
	return 0;

}