//
//  Nucleotide.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 3/16/14.
//
//

#ifndef GeneticAlgTest_Nucleotide_h
#define GeneticAlgTest_Nucleotide_h

class Nucleotide{
private:
    char data;
public:
    const static int NUM = 4;
    
    Nucleotide(){}
    
    char setData(char _data){
        if (_data <= 0){
            data = 0;
        } else if (_data >= NUM - 1){
            data = NUM - 1;
        } else {
            data = _data;
        }
    }
    
    char getData(){
        return data;
    }
    
    Nucleotide* copy(){
        Nucleotide *copy = new Nucleotide();
        copy->setData(data);
        return copy;
    }
    
    Nucleotide(char _data){
        setData(_data);
    }
};

#endif
