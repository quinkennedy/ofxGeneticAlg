//
//  Nucleotide.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/16/14.
//
//
#pragma once

class Nucleotide{
private:
    int data = 0;
public:
    const static int NUM = 4;
    
    Nucleotide(){}
    
    char setData(int _data){
        if (_data <= 0){
            data = 0;
        } else if (_data >= NUM - 1){
            data = NUM - 1;
        } else {
            data = _data;
        }
    }
    
    int getData(){
        return data;
    }
    
    Nucleotide* copy(){
        return new Nucleotide(data);
    }
    
    Nucleotide(int _data){
        setData(_data);
    }
};
