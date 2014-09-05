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
    vector<Chromosome>* maternal;
    vector<Chromosome>* paternal;
    
	void replicate() {
		for (int i = 0; i < maternal->size(); i++) {
			(*maternal)[i].replicate();
			(*paternal)[i].replicate();
		}
	}
    
	void crossover() {
		for (int i = 0; i < maternal->size(); i++) {
			(*maternal)[i].crossover((*paternal)[i]);
		}
	}
    
	void intermediateSplit(vector<Chromosome>* ao_Intermediate1,
                                   vector<Chromosome>* ao_Intermediate2) {
		for (int i = 0; i < maternal->size(); i++) {
			if (ofRandomf() < 0.5) {
				(*ao_Intermediate1)[i] = (*maternal)[i];
				(*ao_Intermediate2)[i] = (*paternal)[i];
			} else {
				(*ao_Intermediate2)[i] = (*maternal)[i];
				(*ao_Intermediate1)[i] = (*paternal)[i];
			}
		}
	}
    
	void finalSplit(vector<Chromosome>* ao_Intermediate1,
                            vector<Chromosome>* ao_Intermediate2,
                            vector<Chromosome>* ao_Intermediate3,
                            vector<Chromosome>* ao_Intermediate4) {
		for (int i = 0; i < ao_Intermediate1->size(); i++) {
			(*ao_Intermediate3)[i].setChromatid(new Chromatid((*ao_Intermediate1)[i].split().getNucleotides()));
			(*ao_Intermediate4)[i].setChromatid(new Chromatid((*ao_Intermediate2)[i].split().getNucleotides()));
		}
	}
public:
	Zygote(vector<Chromosome>* _maternal, vector<Chromosome>* _paternal) {
		maternal = _maternal;
		paternal = _paternal;
	}
    
	vector<Gamete>* split() {
        long maternalLength = maternal->size();
		replicate();
		crossover();
		vector<Chromosome>* Intermediate1 = new vector<Chromosome>(maternalLength);
		vector<Chromosome>* Intermediate2 = new vector<Chromosome>(maternalLength);
		intermediateSplit(Intermediate1, Intermediate2);
		vector<Chromosome>* Intermediate3 = new vector<Chromosome>(maternalLength);
		vector<Chromosome>* Intermediate4 = new vector<Chromosome>(maternalLength);
		finalSplit(Intermediate1, Intermediate2, Intermediate3, Intermediate4);
		Gamete[] output = new Gamete[] { new Gamete(Intermediate1),
            new Gamete(Intermediate2), new Gamete(Intermediate3),
            new Gamete(Intermediate4) };
		return output;
	}
};
