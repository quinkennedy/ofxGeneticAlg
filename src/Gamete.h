//
//  Gamete.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 4/6/14.
//
//

#pragma once

#include "Zygote.h"

class Gamete {
private:
	vector<Chromosome>* chromosomes;
public:
    
    Gamete(vector<Chromosome>* _chromosomes) {
		chromosomes = _chromosomes;
	}
    /*
    string toString() {
		return (*chromosomes)[0].getDataAsInt() + " : "
        + (*chromosomes)[1].getDataAsString();
	}*/
    
    Zygote* fertilize(Gamete m_Gamete) {
		return new Zygote(m_arrChromosomes, m_Gamete.GetChromosomes());
	}
    
    vector<Chromosome>* getChromosomes() {
		return chromosomes;
	}
    
    Gamete* copy() {
		vector<Chromosome>* duplicate = new vector<Chromosome>(chromosomes->size());
		for (int i = 0; i < chromosomes->size(); i++) {
			duplicate[i] = (*chromosomes)[i].copy();
		}
		return new Gamete(duplicate);
	}
};
