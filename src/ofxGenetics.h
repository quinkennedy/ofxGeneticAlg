//
//  ofxGenetics.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 4/6/14.
//
//
#pragma once

#include "Gamete.h"
#include "DNAConverter.h"

struct GameteFitness{
    Gamete* gamete;
    long long fitness;
};

enum MatingType {//m <-> f
    Monogamy,//1 <-> 1
    Polygynandry,//n <-> n
    Polygyny,//1 <-> n
    Polyandry,//n <-> 1
    Harem,//1 <-> f (no other males may mate)
    Hermaphrodite//? <-> ? (no distinction between m and f, can mate with self)
    //Asexual -- possible addition. Need to investigate lateral gene transfer
};


enum LifeCycle{
    Gametic,//humans (species is diploid)
    Zygotic,//protozoa (species is haploid)
    Sporic//(species alternates)
};

template<class T>
class ofxGenetics{
private:
    MatingType matingType;
    LifeCycle lifeCycle;
    vector<Gamete> children;
    int generationSize;
    vector<GameteFitness> fitnessList;
    DNAConverter<T> dnaConverter;
public:
    ofxGenetics(MatingType _matingType, LifeCycle _lifeCycle, vector<T> _aminoAcids, int _generationSize){
        matingType = _matingType;
        lifeCycle = _lifeCycle;
        generationSize = _generationSize;
        dnaConverter.init(_aminoAcids);
    }
    
    /**
     *  pass in pointers to parents and children vectors.
     *  This method will mate parents according to the MatingType
     *  of this instance, and the ordering of the parents (0 = most fit).
     *  This method will fill the children vector with the offspring.
     *  The number of children produced will exactly fill the children vector.
     */
    void mate(vector<vector<T>*>* children, vector<vector<T>*>* parents){
        int nHusband, nWife;
        for(int i = 0; i < children->size(); ){
            switch(m_Mating){
                case Harem:
                case Monogamy:
                case Polyandry:
                case Polygynandry:
                case Polygyny:
                case Hermaphrodite://default to Herm. for now
                default:
                    double rand = ofRandomf();
                    nHusband = (int)(rand*rand*parents->size());
                    rand = ofRandomf();
                    nWife = (int)(rand*rand*parents->size());
                    //translate object to Nucleotide vector
                    //convert Nucleotide vector to Chromatid
                    //convert Chromatid to Chromosome
                    //put Chromosome in vector
                    //convert Chromosome vector to Gamete
                    vector<Nucleotide>* nuc = dnaConverter.aminoAcidsToNucleotides(parents->at(nHusband));
                    Chromatid* chroma = new Chromatid(nuc);
                    vector<Chromosome> chromosH;
                    chromosH.push_back(Chromosome());
                    chromosH.at(0).setChromatid(chroma);
                    Gamete husband(&chromosH);
                    
                    nuc = dnaConverter.aminoAcidsToNucleotides(parents->at(nWife));
                    chroma = new Chromatid(nuc);
                    vector<Chromosome> chromosW;
                    chromosW.push_back(Chromosome());
                    chromosW.at(0).setChromatid(chroma);
                    Gamete wife(&chromosW);
                    
                    //mate gametes
                    //add children to vector
                    Zygote* egg = husband.fertilize(wife);
                    vector<Gamete*>* kids = egg->split();
                    vector<Chromosomes>* chromos;
                    for(int j = 0; j < kids->size() && i < children->size(); j++){
                        //translate Gamete -> vector
                        //  Gamete -> Chromosomes -> nucleotide list -> "amino acids"
                        chromos = kids->at(j)->getChromosomes();
                        if (chromos->size() == 0){
                            continue;
                        }
                        *(children->at(i)) = dnaConverter.nucleotidesToAminoAcids(chromos->at(0).getNucleotides());
                        i++;
                    }
            }
        }
    }

};