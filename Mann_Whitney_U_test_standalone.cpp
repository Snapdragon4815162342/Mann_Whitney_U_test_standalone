#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <time.h>

/* 

AUTHOR: Lorenzo Benatti

This is a test script that performs a Mann-Whitney U test whithout external libraries.
It's just a feasibility test, it's not optimized whatsoever

*/

using namespace std;

//#########################################################################################################################################
// function declarations:


void mannwhitneyutest( 
    vector<double> X,
    vector<double> Y,
    double& bothtails,
    double& lefttail,
    double& righttail
    );

//#########################################################################################################################################


int main(){

    //vector<double> male = {45, 33, 35, 39, 42};
    //vector<double> female = {34, 36, 41, 43, 44, 37};


    //generate random values
    auto f = []() -> int { return rand() % 10000; };

    vector<double> male(10000);
    vector<double> female(10000);

    generate(male.begin(), male.end(), f);
    generate(female.begin(), female.end(), f);

    //p values:
    double p_bothTails;   
    double p_rightTail;
    double p_leftTail;

    //timing function execution
    int start = 0, end = 0;
    double mean_exec_time = 0;
    int n_cycles = 25;
    for(int i = 0; i < n_cycles; i++){
        start = clock();

        mannwhitneyutest( 
        male,
        female,
        p_bothTails,
        p_leftTail,
        p_rightTail
        );

        end = clock();
        mean_exec_time += end-start;
    }

    std::cout << "it took an average of " << float(mean_exec_time)/n_cycles << " ticks, or " << float(mean_exec_time)/n_cycles/CLOCKS_PER_SEC << "seconds." << std::endl;
    
    
    std::cout<<"\n\n############################################################\n\n";
    std::cout<<"p both tails: "<<p_bothTails<<"\n";
    std::cout<<"p left tail: "<<p_leftTail<<"\n";
    std::cout<<"p right tail: "<<p_rightTail<<"\n";
    std::cout<<"\n############################################################\n\n";

    // //system("pause");

    return 0;
}

//#########################################################################################################################################
// function implementations:



void mannwhitneyutest( 
    vector<double> X,
    vector<double> Y,
    double& bothtails,
    double& lefttail,
    double& righttail
    )
    {
        int X_size = size(X);

        //attaching Y to the end of X
        X.reserve(X.size() + Y.size());
        X.insert(X.end(), Y.begin(), Y.end());
        
        int n = size(X);
        vector <double> RankVec(n,0);
        

        // ranking X (with Y attached)
        for (int i = 0; i < size(X); i++) {
            int r = 1, s = 1;
         
            for (int j = 0; j < size(X); j++) {
                if (j != i && X[j] < X[i] )
                    r += 1; 
                }
            
            RankVec[i] = r;
        }
        // std::cout<<"Rank vector: ";
        // for (int i = 0; i < n; i++)
        //     std::cout << RankVec[i] << ' ';
        
        int T0 = 0, T1 = 0; //ranked sums

        for(int i=0; i< size(X);i++){
            if(i<=X_size){
                T0 += RankVec[i];
            }else{
                T1 += RankVec[i];
            }

        }

        int n0 = X_size, n1 = size(X)-X_size;
        // std::cout<<"n0: "<<n0<<"\n";
        // std::cout<<"n1: "<<n1<<"\n";
        // std::cout<<"T0: "<<T0<<"\n";
        // std::cout<<"T1: "<<T1<<"\n\n";
        
        //Calculating U values:

        double U0, U1;

        U0 = n0*n1 + (n0*(n0+1)/(2))-T0;
        U1 = n0*n1 + (n1*(n1+1)/(2))-T1;

        double U; // U= min(U0, U1)

        U0<U1 ? U = U0 : U = U1;
        // std::cout<<"U: "<<U<<"\n\n";

        double muU; //Expected value of U

        muU = (double(n0)*double(n1))/2;
        // std::cout<<"muU: "<<muU;

        double sigmaU; //standard error of U

        sigmaU = (sqrt(n0)*sqrt(n1)*sqrt((n0+n1+1)))/sqrt(12);
        // std::cout<<"sigmaU: "<<sigmaU;

        double z;   //Z value

        z = (U-muU)/sigmaU;
        //std::cout<<"Z value: "<<z<<"\n";


        bothtails = (1+erf(z/sqrt(2)));   //c'ho messo una vita per trovare sta ***** di formula

        lefttail = (1+erf(z/sqrt(2)))/2;

        righttail = 1-lefttail;
    }


