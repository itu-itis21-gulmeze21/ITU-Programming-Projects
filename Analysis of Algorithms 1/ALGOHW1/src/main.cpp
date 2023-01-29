#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <chrono>

int numberOfSwaps=0;//to count swaps
int partitionCalls=0;//to count partitions

using namespace std;
using namespace std::chrono;

//the quicksort has a partition function which is given with a psuedocode in the pdf. 

int partition1(vector<pair<string,double>> &array,int low,int high){
    int i=low;
    int j=low;
    double pivot=array[high].second;


    if(j>=i){
        while(array[i].second<=pivot && array[j].second<=pivot){
            if(j==high){//pivot control
                break;
            }
            j++;
            i++;
        }
        while(array[j].second>pivot){
            j++;
            if(j==high){//pivot control
                swap(array[i],array[high]);
                numberOfSwaps++;
                break;
            }
            swap(array[i],array[j]);
            numberOfSwaps++;
            if(array[i].second<=pivot){
                i++;
            }
        }
    }
    return i;
}

//the quicksort function with recursive calls to itself.

void QS1(vector<pair<string,double>> &array,int low, int high){
    if(high-low<=1){
        return;
    }
    int i=partition1(array,low,high);//gives the index of the pivot.
    partitionCalls++;
    QS1(array,low,i-1);
    QS1(array,i+1,high);
}



int main(){

vector<string> averagesString;
vector<string> idsString;
vector<string> row;
string line, word;

 
fstream inputfile;
inputfile.open("../include/books.csv", ios::in);

//getting the data from csv file and putting them into vectors as strings
while(getline(inputfile, line))
{
    stringstream str(line);
    while(getline(str, word, ','))
        row.push_back(word);
        idsString.push_back(row[0]);
        averagesString.push_back(row[3]);
        row.clear();
}
vector<double> averagesDouble;
vector<pair<string,double>> idAveragePairs;//in order to keep ids and averages, declared a vector of pairs. the qs function takes this as a parameter.

cout<<"MENU:"<<endl;
cout<<"A:SORT THE WHOLE ARRAY"<<endl;
cout<<"B:SORT ONLY THE HALF OF THE ARRAY"<<endl;
cout<<"C:SORT ONLY THE QUARTER OF THE ARRAY"<<endl;
char choice;
cin>>choice;

if(choice=='A' || choice=='a'){
    for(int i=1;i<averagesString.size();i++){
        averagesDouble.push_back(stod(averagesString[i]));//casting the averages to doubles in order to make the comparisons
        idAveragePairs.push_back(pair<string,double>(idsString[i],averagesDouble[i-1]));//pushing id,average pairs into the vector which will be given to qs as a parameter
    }
    auto start = high_resolution_clock::now();//start of the execution time
    QS1(idAveragePairs,0,idAveragePairs.size()-1);
    auto stop = high_resolution_clock::now();//stop the chronometer to measure the execution time
    auto duration = duration_cast<microseconds>(stop - start);
    ofstream outputFile;
    outputFile.open("../include/sorted_books.txt");//write the sorted data to a txt file
    for(auto iterator = idAveragePairs.begin(); iterator!=idAveragePairs.end();iterator++){
        outputFile<<iterator->first<<" "<<iterator->second<<endl;
    }
    cout<<"STATISTICS"<<endl;//print the statistics
    cout<<"NUMBER OF SWAPS:"<<numberOfSwaps<<endl;
    cout<<"NUMBER OF TIMES WHEN PARTITION IS CALLED:"<<partitionCalls<<endl;
    cout<<"EXECUTION TIME:"<<duration.count() << " microseconds" << endl;
}
//same process for b and c with half and quarter of the data
if(choice=='B' || choice=='b'){
    for(int i=1;i<(averagesString.size())/2;i++){
        averagesDouble.push_back(stod(averagesString[i]));
        idAveragePairs.push_back(pair<string,double>(idsString[i],averagesDouble[i-1]));
    }
    auto start = high_resolution_clock::now();
    QS1(idAveragePairs,0,idAveragePairs.size()-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    ofstream outputFile;
    outputFile.open("../include/sorted_books.txt");
    for(auto iterator = idAveragePairs.begin(); iterator!=idAveragePairs.end();iterator++){
        outputFile<<iterator->first<<" "<<iterator->second<<endl;
    }
    cout<<"STATISTICS"<<endl;
    cout<<"NUMBER OF SWAPS:"<<numberOfSwaps<<endl;
    cout<<"NUMBER OF TIMES WHEN PARTITION IS CALLED:"<<partitionCalls<<endl;
    cout<<"EXECUTION TIME:"<<duration.count() << " microseconds" << endl;
}
if(choice=='C' || choice=='c'){
    for(int i=1;i<(averagesString.size())/4;i++){
        averagesDouble.push_back(stod(averagesString[i]));
        idAveragePairs.push_back(pair<string,double>(idsString[i],averagesDouble[i-1]));
    }
    auto start = high_resolution_clock::now();
    QS1(idAveragePairs,0,idAveragePairs.size()-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    ofstream outputFile;
    outputFile.open("../include/sorted_books.txt");
    for(auto iterator = idAveragePairs.begin(); iterator!=idAveragePairs.end();iterator++){
        outputFile<<iterator->first<<" "<<iterator->second<<endl;
    }
    cout<<"STATISTICS"<<endl;
    cout<<"NUMBER OF SWAPS:"<<numberOfSwaps<<endl;
    cout<<"NUMBER OF TIMES WHEN PARTITION IS CALLED:"<<partitionCalls<<endl;
    cout<<"EXECUTION TIME:"<<duration.count() << " microseconds" << endl;
}
    return EXIT_SUCCESS;
}