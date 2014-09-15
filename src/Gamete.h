//
//  Gamete.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 4/6/14.
//
//

#pragma once

#include "Chromosome.h"

class Gamete {
private:
	vector<Chromosome>* chromosomes = NULL;
public:
    
    Gamete(vector<Chromosome>* _chromosomes) {
		chromosomes = _chromosomes;
	}
    
    ~Gamete(){
        //TODO: clean up chromosomes!
    }
    
    vector<Chromosome>* getChromosomes() {
		return chromosomes;
	}
    
    Gamete* copy() {
		vector<Chromosome>* duplicate = new vector<Chromosome>();
        duplicate->reserve(chromosomes->size());
		for (int i = 0; i < chromosomes->size(); i++) {
            duplicate->push_back(Chromosome());
            (duplicate->end()--)->setChromatid(chromosomes->at(i).chromatidA->copy());
		}
		return new Gamete(duplicate);
	}
};
