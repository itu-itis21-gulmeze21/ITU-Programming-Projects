#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string.h>
#include <algorithm>//only used for string formatting, nothing to do with requested algorithms
#include <chrono>
#include "pQueueMax.h"
#include "pQueueMin.h"


using namespace std;
using namespace std::chrono;

int randomizedPartition (vector<float> &array,int low,int high){
    srand(time(NULL));
    int randompivot= rand() % (high-low+1) + low;//random pivot index
    swap(array[randompivot],array[high]);//put the pivot at the end 
    randompivot=high;
    int i=low;
    int j=low;
    if(j>=i){
        while(array[i]<=array[randompivot] && array[j]<=array[randompivot]){
            if(j==high){//pivot control
                break;
            }
            j++;
            i++;
        }
        while(array[j]>array[randompivot]){
            j++;
            if(j==high){//pivot control
                swap(array[i],array[high]);
                
                break;
            }
            swap(array[i],array[j]);
            
            if(array[i]<=array[randompivot]){
                i++;
            }
        }
    }
    return i;
}

float randomizedSelect(vector<float> &array,int low,int high,int index){
    if(low==high){//base case
        return array[low];
    }
    int q= randomizedPartition(array,low,high);//pivots index
    int k= q-low+1;//found index
    if(index==k){//found and desired check
        return array[q];
    }
    else if(index<k){
        return randomizedSelect(array,low,q-1,index);
    }
    else{
        return randomizedSelect(array,q+1,high,index-k);
    }
}


float firstQuartile(vector<float> array){
    //some simple cases for size of 2,3,4
    int size = array.size();
    if(size==2){
        return randomizedSelect(array,0,1,1)*0.75 +randomizedSelect(array,0,1,2)*0.25;
    }
    else if(size==3){
        return randomizedSelect(array,0,2,1)*0.5 +randomizedSelect(array,0,2,2)*0.5;
    }
    else if(size==0){
        return randomizedSelect(array,0,3,1)*0.25 +randomizedSelect(array,0,3,2)*0.75;
    }
    
    else{//cases for bigger arrays
       float position;
       position = 0.25*(size+1);
       float difference = position - floor(position);
       float first = randomizedSelect(array,0,size-1,floor(position));
       float second = randomizedSelect(array,0,size-1,floor(position)+1);
       float value = second - first;
       return (value*difference) + first;
    }
    
}

float thirdQuartile(vector<float> array){//similar with firstq, 75 instead of 25
    
    int size = array.size();
    if(size==2){
        return randomizedSelect(array,0,1,2)*0.75 +randomizedSelect(array,0,1,1)*0.25;
    }
    else if(size==3){
        return randomizedSelect(array,0,2,2)*0.5 +randomizedSelect(array,0,2,3)*0.5;
    }
    else if(size==4){
        return randomizedSelect(array,0,3,3)*0.75 +randomizedSelect(array,0,3,4)*0.25;
    }
    else{
        float position;
        position = 0.75*(size+1);
        float difference = position - floor(position);
        float first = randomizedSelect(array,0,size-1,floor(position));
        float second = randomizedSelect(array,0,size-1,floor(position)+1);
        float value = second - first;
        return (value*difference) + first;
    }
    
}

float median(vector<float> array){
    int size = array.size();
    if(size%2==1){//odd numbered lists have the median as an element
        return randomizedSelect(array,0,size-1,(size+1)/2);
    }//odd numbered lists have the median as the mean of 2 elements
    return randomizedSelect(array,0,size-1,(size)/2)*0.5 + randomizedSelect(array,0,size-1,(size/2)+1)*0.5;
    
}

vector<float> attributeValues;
vector<string> dayValues;
vector<string> timeValues;
pQueueMax maxPQueue;
pQueueMin minPQueue;


int main(int argc, char* argv[]){


    

    vector<string> column;
    vector<string> row;
    string line, word;
    int numberOfAttributes;
    vector<string> attributes;

    fstream inputfile;
    inputfile.open(argv[1], ios::in);

    ofstream outputFile("output.txt");


    inputfile>>numberOfAttributes;

    for(int i=0;i<numberOfAttributes;i++){//attribute read
        inputfile>>word;
        attributes.emplace_back(word);
    }

    string linesLeft;
    string attribute;
    string a;
    vector<string> words;
    string newLine;
    inputfile>>newLine;
    stringstream str(newLine);
    
    while (getline(str,a,','))
    {
        words.emplace_back(a);
    }
    linesLeft = words[0];
    attribute = words[1];
    words.clear();
    
    int printNo=0;
    
    
     
    string choice;
    int linecount=0;//flag for given number of lines
    string gap,grp,v,gi;
    while((linecount)!=stoi(linesLeft)){
        inputfile>>choice;
        linecount++;
        if(choice=="add"){//in case of add command
            string e;
            string newLine1;
            inputfile>>newLine1;
            stringstream str(newLine1);
            while (getline(str,a,','))
            {
                words.emplace_back(a);
            }
            dayValues.emplace_back(words[0]);
            timeValues.emplace_back(words[1]);
            if(attribute=="gap"){
                gap = words[2];
                attributeValues.emplace_back(stold(gap));
                maxPQueue.insert(stold(gap));
                minPQueue.insert(stold(gap));
            }
            if(attribute=="grp"){
                grp = words[3];
                attributeValues.emplace_back(stold(grp));
                maxPQueue.insert(stold(grp));
                minPQueue.insert(stold(grp));
            }
            if(attribute=="v"){
                v = words[4];
                attributeValues.emplace_back(stold(v));
                maxPQueue.insert(stold(v));
                minPQueue.insert(stold(v));
            }
            if(attribute=="gi"){
                gi = words[5];
                attributeValues.emplace_back(stold(gi));
                maxPQueue.insert(stold(gi));
                minPQueue.insert(stold(gi));
            }
            linecount++;//1 more incrementation for added line
            words.clear();
           
        }
        else if(choice=="print"){//printing values
            printNo++;
            vector<float> printingValues;
            for(int i=0;i<numberOfAttributes;i++){//checks the desired attributes from attributes vector and calculates them only
                if(attributes[i]=="mean"){
                    auto start = high_resolution_clock::now();
                    printingValues.emplace_back((maxPQueue.mean()));
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout<<"Duration: "<<duration.count()<<" microseconds"<<endl;
                }
                if(attributes[i]=="std"){
                    auto start = high_resolution_clock::now();
                    printingValues.emplace_back((maxPQueue.standardDeviation()));
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout<<"Duration: "<<duration.count()<<" microseconds"<<endl;
                }
                if(attributes[i]=="max"){
                    auto start = high_resolution_clock::now();
                    printingValues.emplace_back((maxPQueue.max()));
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout<<"Duration: "<<duration.count()<<" microseconds"<<endl;
                }
                if(attributes[i]=="firstq"){
                    auto start = high_resolution_clock::now();
                    printingValues.emplace_back((firstQuartile(attributeValues)));
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout<<"Duration: "<<duration.count()<<" microseconds"<<endl;
                }
                if(attributes[i]=="median"){
                    auto start = high_resolution_clock::now();
                    printingValues.emplace_back(median(attributeValues));
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout<<"Duration: "<<duration.count()<<" microseconds"<<endl;
                }
                if(attributes[i]=="thirdq"){
                    auto start = high_resolution_clock::now();
                    printingValues.emplace_back((thirdQuartile(attributeValues)));
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout<<"Duration: "<<duration.count()<<" microseconds"<<endl;
                }
                if(attributes[i]=="min"){
                    auto start = high_resolution_clock::now();
                    printingValues.emplace_back((minPQueue.min()));
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout<<"Duration: "<<duration.count()<<" microseconds"<<endl;
                }
            }
            
            //writing the values to the outputfile
            outputFile<<dayValues[0]<<","<<timeValues[0]<<","<<dayValues.back()<<","<<timeValues.back()<<",";
            for(int i=0;i<numberOfAttributes;i++){
                if(i!=numberOfAttributes-1){
                    outputFile<<printingValues[i]<<",";
                }
                else{
                    outputFile<<printingValues[i]<<endl;
                }
            }
        }
    }


    

    return EXIT_SUCCESS;
}