//
//  Chromatid.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/16/14.
//
//
#pragma once

#include "ofMain.h"
#include "Nucleotide.h"

//A Chromatid is essentially an arbitrary length sequence of Nucleotides
class Chromatid{
private:
    vector<Nucleotide>* data;
public:
    Chromatid(){}
    ~Chromatid(){
        //clean up the Nucleotide list!
    }
    
    /**
     * Create a Chromatid from a pre-made Nucleotide array
     */
    Chromatid(vector<Nucleotide>* _data){
        data = _data;
    }
    
    /**
     *  return a copy of this Chromatid
     */
    Chromatid* copy(){
        return new Chromatid(new vector<Nucleotide>(*data));
    }
    
    vector<Nucleotide>* getNucleotides(){
        return data;
    }

    int getLength(){
        return data->size();
    }

    void crossover(Chromatid* other){
        int minLength = (data->size() <= other->getLength() ? data->size() : other->getLength());
        int maxLength = (data->size() >= other->getLength() ? data->size() : other->getLength());
        int start = ofRandom(minLength);
        int end = ofRandom(maxLength);
        if (end >= start) {
            //swapping the ends is basically the same as swapping the beginnings
            if (end >= minLength){
                end = start-1;
                start = 0;
            }
            char temp;
            Nucleotide *nOther = &(*(*other).getNucleotides())[start];
            Nucleotide *nThis = &(*data)[start];
            for(int i = start; i <= end; i++){
                temp = nOther->getData();
                nOther->setData(nThis->getData());
                nThis->setData(temp);
                nOther++;
                nThis++;
            }
        }
    }
};
