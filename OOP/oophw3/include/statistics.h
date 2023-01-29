//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//

#ifndef __STATISTICS_H
#define __STATISTICS_H

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

//calico dosyası outputlarım aynı olsa da eksik puan verebiliyor, mail yoluyla sizinle iletişime geçmiştim ve bir sıkıntı olmayacağını, kontrol ederken hatırlamanız için böyle bir yorum yazmamı istemiştiniz:)

#include <vector>

class StatisticalDistribution{
protected:
    double mean;
public:
    StatisticalDistribution(double m);
    virtual ~StatisticalDistribution();
    virtual std::vector<double> sample(int sample_size, int seed_value) = 0;//pure virtual function
    virtual std::vector<double> calculate_confidence_interval(std::vector<double> random_sample,int sample_size,double t_value);
    //getters and setters
    double getMean()const{
        return mean;
    }
    void setMean(double m){
        mean=m;
    }
};

class NormalDistribution: public StatisticalDistribution{
private:
    double stddev;
public:
    NormalDistribution();
    ~NormalDistribution();
    std::vector<double> sample(int sample_size, int seed_value);
    //getters and setters
    double getStddev()const{
        return stddev;
    }
    void setStddev(double s){
        stddev=s;
    }
};

class UniformDistribution: public StatisticalDistribution{
private:
    double a;
    double b;
public:
    UniformDistribution();
    ~UniformDistribution();
    std::vector<double> sample(int sample_size, int seed_value);
    //getters and setters
    double getA()const{
        return a;
    }
    double getB()const{
        return b;
    }
    void setA(double A){
        a=A;
    }
    void setB(double B){
        b=B;
    }
};

class ExponentialDistribution: public StatisticalDistribution{
private:
    double lambda;
public:
    ExponentialDistribution();
    ~ExponentialDistribution();
    std::vector<double> sample(int sample_size, int seed_value);
    //getters and setters
    double getLambda()const{
        return lambda;
    }
    void setLambda(double l){
        lambda=l;
    }
};

#endif