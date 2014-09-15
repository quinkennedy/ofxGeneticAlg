//
//  Zygote.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/30/14.
//
//
#pragma once

#include "Chromosome.h"
#include "ofMain.h"
#include "Gamete.h"

//A fertilized Gamete pair
class Zygote {
private:
    vector<Chromosome>* maternal = NULL;
    vector<Chromosome>* paternal = NULL;
    
	void replicate() {
		for (int i = 0; i < maternal->size(); i++) {
            maternal->at(i).replicate();
            paternal->at(i).replicate();
		}
	}
    
	void crossover() {
		for (int i = 0; i < maternal->size(); i++) {
            maternal->at(i).crossover(paternal->at(i));
		}
	}
    
	void intermediateSplit(vector<Chromosome>* ao_Intermediate1,
                                   vector<Chromosome>* ao_Intermediate2) {
		for (int i = 0; i < maternal->size(); i++) {
			if (ofRandomf() < 0.5) {
                ao_Intermediate1->push_back(maternal->at(i));
                ao_Intermediate2->push_back(paternal->at(i));
			} else {
                ao_Intermediate2->push_back(maternal->at(i));
                ao_Intermediate1->push_back(paternal->at(i));
			}
		}
	}
    
	void finalSplit(vector<Chromosome>* ao_Intermediate1,
                            vector<Chromosome>* ao_Intermediate2,
                            vector<Chromosome>* ao_Intermediate3,
                            vector<Chromosome>* ao_Intermediate4) {
		for (int i = 0; i < ao_Intermediate1->size(); i++) {
            ao_Intermediate3->push_back(*(ao_Intermediate1->at(i).split()));
            ao_Intermediate4->push_back(*(ao_Intermediate2->at(i).split()));
		}
	}
public:
    Zygote(Gamete _maternal, Gamete _paternal){
        maternal = _maternal.getChromosomes();
        paternal = _paternal.getChromosomes();
    }
    
	vector<Gamete*>* split() {
		replicate();
		crossover();
		vector<Chromosome>* Intermediate1 = new vector<Chromosome>();
		vector<Chromosome>* Intermediate2 = new vector<Chromosome>();
		intermediateSplit(Intermediate1, Intermediate2);
		vector<Chromosome>* Intermediate3 = new vector<Chromosome>();
		vector<Chromosome>* Intermediate4 = new vector<Chromosome>();
		finalSplit(Intermediate1, Intermediate2, Intermediate3, Intermediate4);
        vector<Gamete*>* output = new vector<Gamete*>();
        output->push_back(new Gamete(Intermediate1));
        output->push_back(new Gamete(Intermediate2));
        output->push_back(new Gamete(Intermediate3));
        output->push_back(new Gamete(Intermediate4));
		return output;
	}
};
