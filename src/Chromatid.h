//
//  Chromatid.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/16/14.
//
//

#ifndef GeneticAlgTest_Chromatid_h
#define GeneticAlgTest_Chromatid_h

#include "ofMain.h"
#include "Nucleotide.h"

class Chromatid{
private:
    vector<Nucleotide>* data;
public:
    Chromatid(){}
    
    /**
     * Create a Chromatid from a pre-made Nucleotide array
     */
    Chromatid(vector<Nucleotide>* _data){
        data = _data;
    }
    
    /**
     * Create a Chromatid from a byte array
     */
    Chromatid(char *_data, long _length){
        if (_length > 0){
            //byte is 8-bits right?
            //TODO: stop assuming Nucleotides are 2 bits
            //TODO: stop assuming bytes are 8-bits
            long dataLength = _length * 4;
            data = new vector<Nucleotide>(dataLength);
            int k = 0;
            for(int i = 0; i < _length; i++){
                char curr = _data[i];
                for(int j = 6; j >= 0 ; j-=2, k++){
                    (*data)[k].setData((curr >> j) & 0xff);
                }
            }
        }
    }
    
    Chromatid* copy(){
        vector<Nucleotide>* newData = new vector<Nucleotide>(data->size());
        for(int i = 0; i < data->size(); i++){
            (*newData)[i].setData((*data)[i].getData());
        }
        return new Chromatid(newData);
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
    
    char* getDataAsString(){
        int outLength = (data->size()+3)/4;
        char *output = new char[outLength+1];
        int k = 0;
        for(int i = 0; i < outLength; i++){
            output[i] = 0;
            for(int j = 6; j >= 0 && k < data->size(); j-=2, k++){
                output[i] |= ((*data)[k].getData() << j);
            }
        }
        output[outLength] = 255;
        return output;
    }
};

#endif
