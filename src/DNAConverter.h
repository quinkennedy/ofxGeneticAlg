//
//  DNAConverter.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 4/6/14.
//
//
#pragma once

#include "ofMain.h"
#include "Nucleotide.h"

template<class T>
//for now this will randomly assign nucleotide sequences to indices,
//later it may try to group indices to neighboring nucleotide sequences
//to mimic http://upload.wikimedia.org/wikipedia/en/d/d6/GeneticCode21-version-2.svg
class DNAConverter{
private:
    //lookup by codon index, returns Amino Acid index
    vector<int> codonToAminoAcid;
    
    //lookup by Amino Acid index, returns vector of possible codon indices
    vector<vector<int>*> aminoAcidToCodons;
    vector<T> aminoAcids;
    int codonLength;
    int numCodons;
    int numAminoAcids;
	
public:
    
    ~DNAConverter(){
        //TODO: clean up vectors!
    }
    
    //essentially a base conversion from base(10) -> base(Nucleotide.NUM)
    vector<int>* codonToNucleotides(int codon){
        vector<int>* result = new vector<int>();
        for(int i = 0; i < codonLength; i++){
            result->insert(result->begin(), codon % Nucleotide::NUM);
            codon /= Nucleotide::NUM;
        }
        return result;
    }
    
    //essentially a base conversion from base(Nucleotide.NUM) -> base(10)
    int nucleotideSequenceToCodon(vector<int> sequence){
        int result = 0;
        for (int i = sequence.size() - 1, m = 1; i >= 0; i--, m *= Nucleotide::NUM){
            result += sequence.at(i) * m;
        }
        return result;
    }
    
    /**
     * initializes this DNA converter to convert DNA to/from 
     * the specific number of "chunks".
     * A chunk can be thought of as an Amino Acid.
     * For example, Earth life uses 20 Amino Acids (chunks)
     * which are encoded by 64 possible sequences 
     * (4 nucleotides, in sequences of 3 (a codon) => 4^3 = 64).
    **/
    void init(vector<T> _aminoAcids){
        aminoAcids = _aminoAcids;
        numAminoAcids = aminoAcids.size();
		codonLength = (int)ceil(log(numAminoAcids)/log(Nucleotide::NUM));
        numCodons = pow((double)Nucleotide::NUM, (double)codonLength);
        
        //populate lookup "table" with all Amino Acids
        codonToAminoAcid.reserve(numCodons);
        int i;
        for (i = 0; i < numAminoAcids; i++){
            codonToAminoAcid.push_back(i);
        }
        for (; i < numCodons; i++) {
            codonToAminoAcid.push_back((int)ofRandom(numAminoAcids));
        }
        
        //shuffle the Amino Acids
        ofRandomize(codonToAminoAcid);
        
        //create the reverse-lookup "table" from Amino Acids to Codons
        for(i = 0; i < numAminoAcids; i++){
            aminoAcidToCodons.push_back(new vector<int>());
        }
        for(i = 0; i < codonToAminoAcid.size(); i++){
            aminoAcidToCodons.at(codonToAminoAcid.at(i))->push_back(i);
        }
	}
	
    //takes in a vector of "Amino Acids" and returns a vector of Nucleotides
    vector<Nucleotide>* aminoAcidsToNucleotides(vector<T>* _aminoAcids){
        vector<Nucleotide>* output = new vector<Nucleotide>();
        int aaIndex;
        for(int i = 0; i < _aminoAcids->size(); i++){
            T currAminoAcid = _aminoAcids->at(i);
            for(aaIndex = 0; aaIndex < numAminoAcids; aaIndex++){
                if (currAminoAcid == aminoAcids.at(aaIndex)){
                    break;
                }
            }
            if (aaIndex >= numAminoAcids){
                //an un-declared "Amino Acid" was used
                continue;
            }
            vector<int>* codonOptions = aminoAcidToCodons.at(aaIndex);
            int codon = codonOptions->at((int)ofRandom(codonOptions->size()));
            vector<int>* nucleotideSequence = codonToNucleotides(codon);
            for(int j = 0; j < nucleotideSequence->size(); j++){
                output->push_back(Nucleotide(nucleotideSequence->at(j)));
            }
        }
        return output;
	}
	
    vector<T>* nucleotidesToAminoAcids(vector<Nucleotide>* nucleotides){
        vector<T>* output = new vector<T>();
        vector<int> sequence;
        sequence.resize(codonLength);
        for(int i = 0; i < nucleotides->size(); ){
            int j;
            for(j = 0; j < codonLength && i < nucleotides->size(); i++, j++){
                sequence.at(j) = nucleotides->at(i).getData();
            }
            if (j == codonLength){
                //edge case, this makes sure the final codon is a complete codon
                //  convert the nucleotide sequence to a codon index
                //  convert the codon index to an amino acid index
                //  convert the amino acid index to an amino acid object
                output->push_back(aminoAcids.at(codonToAminoAcid.at(nucleotideSequenceToCodon(sequence))));
            }
        }
		return output;
	}
};
