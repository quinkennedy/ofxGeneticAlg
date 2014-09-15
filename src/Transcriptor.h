//
//  Transcriptor.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/16/14.
//
//
#pragma once

#include "Chromatid.h"
#include "ofMain.h"
#include "Nucleotide.h"

//A Transcriptor is responsible for replicating Chromatids
class Transcriptor{
public:
    Transcriptor(){}
    
    Chromatid* transcribe(Chromatid* from){
        vector<Nucleotide>* newData = NULL;
		float pMutation = 1.0f / 5.0f;
		int nMutationSize = (int) ((pow(ofRandomf(), 2) * 8)) + 1;// mutation size range is [1,8]
		float pActual = ofRandomf();
		if (pActual < pMutation)// deletion
		{
			int nSkip = (int) (ofRandom(from->getLength()));
			if (((int)from->getLength()) - nMutationSize < nSkip) {
				nMutationSize = from->getLength() - nSkip;
			}
			size_t nNewSize = from->getLength() <= nMutationSize ? 0 : from->getLength() - nMutationSize;
			newData = new vector<Nucleotide>(nNewSize);
			for (int i = 0; i < from->getLength(); i++) {
				if (i < nSkip || i >= nSkip + nMutationSize) {
                    newData->at(i < nSkip ? i : i - nMutationSize).setData(from->getNucleotides()->at(i).getData());
				}
			}
		} else if (pActual < pMutation * 2)// addition
		{
			newData = new vector<Nucleotide>(from->getLength() + nMutationSize);
			int nAdd = (int) ofRandom(from->getLength() + 1);
			for (int i = 0; i < newData->size(); i++) {
				if (i >= nAdd && i < nAdd + nMutationSize) {
                    newData->at(i).setData(ofRandom(4));
				} else {
                    newData->at(i).setData(from->getNucleotides()->at(i < nAdd ? i : i - nMutationSize).getData());
				}
			}
		} else if (pActual < pMutation * 3)// inversion
		{
			if (from->getLength() >= 2) {
				if (nMutationSize < 2) {
					nMutationSize = 2;
				}
				if (from->getLength() < nMutationSize) {
					nMutationSize = from->getLength();
				}
				newData = new vector<Nucleotide>(from->getLength());
				int nStart = (int) ofRandom(from->getLength() - nMutationSize);
				int nReversalOffset = nMutationSize - 1;
				for (int i = 0; i < newData->size(); i++) {
					if (i < nStart || i >= nStart + nMutationSize) {
						newData->at(i).setData(from->getNucleotides()->at(i).getData());
					} else {
						newData->at(i).setData(from->getNucleotides()->at(i + nReversalOffset).getData());
						nReversalOffset -= 2;
					}
				}
			}//else caught at end by checking newData == NULL
		} else if (pActual < pMutation * 4)// substitution
		{
            if (nMutationSize > from->getLength()) {
                nMutationSize = from->getLength();
            }
            newData = new vector<Nucleotide>(from->getLength());
            int nSub = (int) ofRandom(newData->size() - nMutationSize);
            for (int i = 0; i < newData->size(); i++) {
                if (i >= nSub && i < nSub + nMutationSize) {
                    newData->at(i).setData(ofRandom(4));
                } else {
                    newData->at(i).setData(from->getNucleotides()->at(i).getData());
                }
            }
		}
		if (newData == NULL)// "else" copy it exactly
		{
			newData = new vector<Nucleotide>(from->getLength());
			for (int i = 0; i < newData->size(); i++) {
				newData->at(i).setData(from->getNucleotides()->at(i).getData());
			}
		}
        
		return new Chromatid(newData);
    }
};
