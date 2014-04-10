//
//  Chromasome.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/16/14.
//
//

#ifndef GeneticAlgTest_Chromasome_h
#define GeneticAlgTest_Chromasome_h

#include "ofMain.h"
#include "Chromatid.h"
#include "Transcriptor.h"

class Chromosome{
private:
    
public:
    Chromatid* chromatidA;
    Chromatid* chromatidB;
    
    Chromosome(){}
    
    void setChromatid(Chromatid* _a){
        chromatidA = _a;
    }
    
	void replicate() {
		Transcriptor t = Transcriptor();
		chromatidB = t.transcribe(chromatidA);
	}
    
	void crossover(Chromosome chromosome) {
		chromatidA->crossover(chromosome.chromatidA);
		chromatidA->crossover(chromosome.chromatidB);
		chromatidB->crossover(chromosome.chromatidA);
		chromatidB->crossover(chromosome.chromatidB);
	}
    
	string getDataAsString() {
		return chromatidA->getDataAsString();
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

#endif
