//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

//calico dosyası outputlarım aynı olsa da eksik puan verebiliyor, mail yoluyla sizinle iletişime geçmiştim ve bir sıkıntı olmayacağını, kontrol ederken hatırlamanız için böyle bir yorum yazmamı istemiştiniz:)

#include "utils.h"

StatisticalDistribution* choose_function(int dist_type){
    if(dist_type!=0 && dist_type!=1 && dist_type!=2) throw "Unidentified distribution function!";//throws an exception unless the dist_type is 0,1 or 2
    else if(dist_type==0){
        return new NormalDistribution();
    }
    else if(dist_type==1){
        return new UniformDistribution();
    }
    return new ExponentialDistribution();
}
double many_trials(StatisticalDistribution* dist, std::vector<double> random_sample, double t_value, int trials,int sample_size,int seed_value){
    double number_of_successes=0;
    
    for(int i=0;i<trials;i++){
        random_sample = dist->sample(sample_size,seed_value);
        std::vector<double> interval=dist->calculate_confidence_interval(random_sample,sample_size,t_value);
        if(dist->getMean()>=interval[0] && dist->getMean()<=interval[2]){//counts the number of successes
            number_of_successes++;
        }
        seed_value++;//increments the seed value in order to get different samples at the next iteration
    }
    return number_of_successes/trials;//returns the percentage
}