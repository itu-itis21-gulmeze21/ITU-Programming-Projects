//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include "statistics.h"
#include <random>
#include <iostream>

//calico dosyası outputlarım aynı olsa da eksik puan verebiliyor, mail yoluyla sizinle iletişime geçmiştim ve bir sıkıntı olmayacağını, kontrol ederken hatırlamanız için böyle bir yorum yazmamı istemiştiniz:)

StatisticalDistribution::StatisticalDistribution(double m):mean(m){}//simple constructor
StatisticalDistribution::~StatisticalDistribution(){}//virtual destructor

std::vector<double> StatisticalDistribution::calculate_confidence_interval(std::vector<double> random_sample,int sample_size,double t_value){
    double lower_bound;
    double sample_mean;
    double upper_bound;

    double total_samples=0;

    for(int i=0;i<sample_size;i++){
        total_samples+=random_sample[i];
    }
    sample_mean=total_samples/sample_size;//calculates the sample_mean

    double standard_deviation=0.0;
    for(int i = 0; i < sample_size; ++i) {
        standard_deviation += pow(random_sample[i] - mean, 2);
    }
    standard_deviation=sqrt(standard_deviation/sample_size);//calculates the standart deviation

    lower_bound=sample_mean-(t_value*(standard_deviation/sqrt(sample_size)));//calculates the lower bound
    upper_bound=sample_mean+(t_value*(standard_deviation/sqrt(sample_size)));//calculates the upper bound

    std::vector<double> result={lower_bound,sample_mean,upper_bound};//vector containing the needed elements
    return result; 
}

NormalDistribution::NormalDistribution():StatisticalDistribution(0.0),stddev(1.0){}//simple constructor
NormalDistribution::~NormalDistribution(){}

std::vector<double> NormalDistribution::sample(int sample_size, int seed_value){//generates random numbers with the provided code and puts them in a vector that will be returned

    std::vector<double> samples;
    std::default_random_engine generator;
    generator.seed(seed_value);
    std::normal_distribution<double> distribution(mean, stddev);

    for(int i=0;i<sample_size;i++){
        double number = distribution (generator);
        samples.push_back(number);
    }

    return samples;
    
}

UniformDistribution::UniformDistribution():StatisticalDistribution(0.0),a(-1.0),b(1.0){}//simple constructor
UniformDistribution::~UniformDistribution(){}

std::vector<double> UniformDistribution::sample(int sample_size, int seed_value){//generates random numbers with the provided code and puts them in a vector that will be returned

    std::vector<double> samples;
    std::default_random_engine generator ;
    generator.seed(seed_value);
    std::uniform_real_distribution<double> distribution(a, b);

    for(int i=0;i<sample_size;i++){
        double number = distribution(generator);
        samples.push_back(number);
    }

    return samples;
}

ExponentialDistribution::ExponentialDistribution():StatisticalDistribution(1.0),lambda(1.0){}//simple constructor
ExponentialDistribution::~ExponentialDistribution(){}

std::vector<double> ExponentialDistribution::sample(int sample_size, int seed_value){//generates random numbers with the provided code and puts them in a vector that will be returned
    std::vector<double> samples;
    std::default_random_engine generator ;
    generator.seed(seed_value);
    std::exponential_distribution<double> distribution(lambda);

    for(int i=0;i<sample_size;i++){
        double number = distribution(generator);
        samples.push_back(number);
    }

    return samples;
}