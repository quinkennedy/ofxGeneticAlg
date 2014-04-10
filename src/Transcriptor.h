//
//  Transcriptor.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/16/14.
//
//

#ifndef GeneticAlgTest_Transcriptor_h
#define GeneticAlgTest_Transcriptor_h

#include "Chromatid.h"
#include "ofMain.h"

class Transcriptor{
public:
    Transcriptor(){}
    
    Chromatid* transcribe(Chromatid* from){
        vector<Nucleotide>* newData;
		float pMutation = 1.0f / 5.0f;
		int nMutationSize = (int) ((pow(ofRandomf(), 2) * 8)) + 1;// mutation size range is 1-4
		float pActual = (float) ofRandomf();
		if (pActual < pMutation)// deletion
		{
			int nSkip = (int) (ofRandom(from->getLength()));
			if (from->getLength() - nMutationSize < nSkip) {
				nMutationSize = from->getLength() - nSkip;
			}
			int nNewSize = max(0, from->getLength() - nMutationSize);
			newData = new vector<Nucleotide>(nNewSize);
			for (int i = 0; i < from->getLength(); i++) {
				if (i < nSkip || i >= nSkip + nMutationSize) {
					(*newData)[i < nSkip ? i : i - nMutationSize].setData((*from->getNucleotides())[i].getData());
				}
			}
		} else if (pActual < pMutation * 2)// addition
		{
			newData = new vector<Nucleotide>(from->getLength() + nMutationSize);
			int nAdd = (int) (ofRandomf() * (from->getLength() + 1));
			for (int i = 0; i < newData->size(); i++) {
				if (i >= nAdd && i < nAdd + nMutationSize) {
					(*newData)[i] = Nucleotide((char) (ofRandomf() * 4));
				} else {
					(*newData)[i].setData((*from->getNucleotides())[i < nAdd ? i : i - nMutationSize].getData());
				}
			}
		} else if (pActual < pMutation * 3)// inversion
		{
			if (from->getLength() > 1) {
				if (nMutationSize < 2) {
					nMutationSize = 2;
				}
				if (from->getLength() < nMutationSize) {
					nMutationSize = from->getLength();
				}
				newData = new vector<Nucleotide>(from->getLength());
				int nStart = (int) (ofRandomf() * (from->getLength() - (nMutationSize - 1)));
				int nReversalOffset = nMutationSize - 1;
				for (int i = 0; i < newData->size(); i++) {
					if (i < nStart || i >= nStart + nMutationSize) {
						(*newData)[i].setData((*from->getNucleotides())[i].getData());
					} else {
						(*newData)[i].setData((*from->getNucleotides())[i + nReversalOffset].getData());
						nReversalOffset -= 2;
					}
				}
			}
		} else if (pActual < pMutation * 4)// substitution
		{
			if (from->getLength() > 0) {
				if (nMutationSize > from->getLength()) {
					nMutationSize = from->getLength();
				}
				newData = new vector<Nucleotide>(from->getLength());
				int nSub = (int) (ofRandomf() * (newData->size() - (nMutationSize - 1)));
				for (int i = 0; i < newData->size(); i++) {
					if (i >= nSub && i < nSub + nMutationSize) {
						(*newData)[i].setData((char) (ofRandomf() * 4));
					} else {
						(*newData)[i].setData((*from->getNucleotides())[i].getData());
					}
				}
			}
		}
		if (newData == NULL)// else
		{
			newData = new vector<Nucleotide>(from->getLength());
			for (int i = 0; i < newData->size(); i++) {
				(*newData)[i].setData((*from->getNucleotides())[i].getData());
			}
		}
		return new Chromatid(newData);
    }
};

#endif
