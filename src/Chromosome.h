//
//  Chromasome.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/16/14.
//
//
#pragma once

#include "ofMain.h"
#include "Chromatid.h"
#include "Transcriptor.h"
#include "Nucleotide.h"
#include "Chromosome.h"

//A Chromosome is basically one (sometimes 2) Chromatids
class Chromosome{
private:
    
public:
    Chromatid* chromatidA = NULL;
    Chromatid* chromatidB = NULL;
    
    Chromosome(){}
    
    void setChromatid(Chromatid* _a){
        chromatidA = _a;
    }
    
	void replicate() {
		Transcriptor t;
		chromatidB = t.transcribe(chromatidA);
	}
    
	void crossover(Chromosome other) {
		chromatidA->crossover(other.chromatidA);
		chromatidA->crossover(other.chromatidB);
		chromatidB->crossover(other.chromatidA);
		chromatidB->crossover(other.chromatidB);
	}
    
	vector<Nucleotide>* getNucleotides() {
		return chromatidA->getNucleotides();
	}
    
	Chromosome* split() {
		if (chromatidB == NULL) {
			return NULL;
		}
		Chromatid* temp;
		if (ofRandomf() < 0.5) {
			temp = chromatidA;
			chromatidA = chromatidB;
		} else {
			temp = chromatidB;
		}
		chromatidB = NULL;
        Chromosome* output = new Chromosome();
        output->setChromatid(temp);
		return output;
	}
};
