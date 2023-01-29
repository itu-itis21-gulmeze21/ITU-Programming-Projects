//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname:Erce Gülmez
//---Student Number:150210728
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

//calico dosyası outputlarım aynı olsa da eksik puan verebiliyor, mail yoluyla sizinle iletişime geçmiştim ve bir sıkıntı olmayacağını, kontrol ederken hatırlamanız için böyle bir yorum yazmamı istemiştiniz:)

#ifndef __UTILS_H
#define __UTILS_H

#include "statistics.h"

StatisticalDistribution* choose_function(int);
double many_trials(StatisticalDistribution*, std::vector<double>, double, int ,int ,int);

#endif