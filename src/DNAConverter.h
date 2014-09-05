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

//for now this will randomly assign nucleotide sequences to indices,
//later it may try to group indices to neighboring nucleotide sequences
//to mimic http://upload.wikimedia.org/wikipedia/en/d/d6/GeneticCode21-version-2.svg
public class DNAConverter{
private:
    //lookup by codon index, returns Amino Acid index
    vector<int> codonToAminoAcid;
    
    //lookup by Amino Acid index, returns vector of possible codon indices
    vector<vector<int>*> aminoAcidToCodons;
    
    int codonLength;
    int numCodons;
    int numAminoAcids;
	
public:
    
    ~DNAConverter(){
        //TODO: clean up vectors!
    }
    
    //essentially a base conversion from base(10) -> base(Nucleotide.NUM)
    vector<int> codonToNucleotides(int codon){
        vector<int> result;
        for(int i = 0; i < codonLength; i++){
            result.emplace(result.begin(), codon%Nucleotide.NUM);
            codon /= Nucleotide.NUM;
        }
        return result;
    }
    
    //essentially a base conversion from base(Nucleotide.NUM) -> base(10)
    int nucleotidesSequenceToCodon(vector<int> sequence){
        int result = 0;
        for (int i = sequence.size() - 1, m = 1; i >= 0; i--, m *= Nucleotide.NUM){
            result += *(sequence.at(i)) * m;
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
    void init(int numberAminoAcids){
        numAminoAcids = numberAminoAcids;
		codonLength = (int)Math.ceil(Math.log(numAminoAcids)/Math.log(Nucleotide.NUM));
        numCodons = pow(Nucleotide.NUM, codonLength);
        
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
        for (i = codonToAminoAcid.size() - 1; i > 0; i--){
            int swapWith = (int)ofRandom(i + 1);
            int temp = *(codonToAminoAcid.at(i));
            *(codonToAminoAcid.at(i)) = *(codonToAminoAcid.at(swapWith));
            *(codonToAminoAcid.at(swapWith)) = temp;
        }
        
        //create the reverse-lookup "table" from Amino Acids to Codons
        for(i = 0; i < numAminoAcids; i++){
            aminoAcidToCodons.push_back(new vector<int>());
        }
        for(i = 0; i < codonToAminoAcid.size(); i++){
            aminoAcidToCodons.at(*(codonToAminoAcid.at(i)))->push_back(i);
        }
	}
	
    //takes in a vector of "Amino Acids" and returns a vector of Nucleotides
    vector<Nucleotide>* aminoAcidsToNucleotides(vector<int>* aminoAcids){
        //		System.out.print("sequence in:");
        //		for(int i : a_narrSequence){
        //			System.out.print(i+",");
        //		}
        //		System.out.println();
        
        
        vector<Nucleotide>* output = new vector<Nucleotide>();
        for(int i = 0; i < aminoAcids->size(); i++){
            vector<int>* codonOptions = *(aminoAcidToCodons.at(*(aminoAcids.at(i))));
            int codon = *(codonOptions->at((int)ofRandom(codonOptions->size())));
            vector<int>* nucleotideSequence = codonToNucleotides(codon);
            for(int j = 0; j < nucleotideSequence->size(); j++){
                output->push_back(Nucleotide(*(nucleotideSequence->at(j))));
            }
        }
        
        //		System.out.print("sequence out:");
        //		for(Nucleotide n : arrOutput){
        //			System.out.print(n.m_Data+",");
        //		}
        //		System.out.println();
        return output;
	}
	
    vector<int>* nucleotidesToAminoAcids(vector<Nucleotide>* nucleotides){
        //		System.out.print("sequence in:");
        //		for(Nucleotide n : a_arrSequence){
        //			System.out.print(n.m_Data+",");
        //		}
        //		System.out.println();
        
        
        vector<int>* output = new vector<int>();
        vector<int> sequence;
        sequence.resize(codonLength);
        for(int i = 0; i < nucleotides.size(); ){
            int j;
            for(j = 0; j < codonLength && i < nucleotides.size(); i++, j++){
                *(sequence.at(j)) = *(nucleotides->at(i))
            }
            if (j == codonLength){
                //edge case, this makes sure the final codon is a complete codon
                output->push_back(*(codonToAminoAcid->at(nucleotideSequenceToCodon(sequence))));
            }
        }
        
        //		System.out.print("sequence out:");
        //		for(int n : narrOutput){
        //			System.out.print(n+",");
        //		}
        //		System.out.println();
		return output;
	}
};
