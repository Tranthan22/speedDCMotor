# speedDCMotor

**Project description:**
 - Design and write programs C+ to simulate a speed sensor mounted on a DC motor with the following specification:
+ Measurement range: 0 ÷ 3000 rpm (revolution per minutes)
+ Resolution: 0.2 rpm

**generate data of speed sensors**
- Write a program which allows user to provide the number of sensors (corresponding to number of DC 
motors which need to be monitored), the sampling time and measurement duration (simulation interval) and 
the starting time. These inputs should be provided by using command-line as below:
C:\\speed_sim –n [num_sensors] –st [sampling] –si [interval]

**analyze data**
- Write another program to process the data in “speed_data_TIMESTAMP.csv” with the content followed 
the one generated in task 1. The program should be run by using a command-line as below:
C:\\speed_process [data_filename.csv]
Where:
+ speed_process: is the execution file name without extension.
+ [data_filename.csv] is the csv file which consists of the speed data set. If the user does not 
provide the filename, the program will use the default name which is “speed_data.csv”.
For example: C:\\speed_sim speed_data_1653985800.csv
The program should be able to handle at least 1000 data points which may be included in the data file. 
This program should implement the following sub-tasks:

a. Tasks 2.1:
Assuming that the speed of the motor in normal operation are varied within 900 ÷ 1600 rpm (lower 
bound and upper bound are included). The program needs to validate the speed data in the data file, data 
points with the speed values which are not in the valid range have to be filtered as outliers. The outlier data 
points are stored in a file named “outlier_data.csv” which should follow the below format:
The first line is “number of outliers: X” where X is the number of invalid data points, e.g. 4 in the above 
example.

b. Tasks 2.2:
Identify the largest, smallest, and average speed for each sensor id (apply to the valid data points only), 
and store the results in a file named “data_summary.csv”. The example is as the following:
The time of the max and min values in the file above are the earliest timestamps those values appear. 
Meanwhile the time of the mean is the simulation interval.

c. Task 2.3:
We assume that the motor can change (increase or decrease) the speed by maximum 100 rpm per second. 
Please count the number of times that speed increment and decrement between two consecutive data points 
exceed 100 rpm per second for each speed sensor (motor). Hint: the acceleration/deceleration between two 
consecutive data points should be calculated first.

The results should be stored in a csv file named “data_statistics.csv” with the following format:
d. Task 2.4
Choose a sorting algorithm and sort the valid data in the data_file.csv if the argument –s is added as 
below.
C:\\speed_process [data_filename.csv] –s
The sorted data should be stored in a file name “sorted_data.csv”. The data should be sorted ascendingly 
by id and values, i.e. the smallest sensor id should appear first, and all the values of the same sensor id 
should be sorted from the smallest to the largest. The time taken to run the algorithm should be measured and 
display on the screen as “sorting duration: X seconds” where X is a specific number of the time measured.
An example of sorted data file is given as below
