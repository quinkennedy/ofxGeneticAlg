//
//  DNAConverter.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 4/6/14.
//
//

#ifndef GeneticAlgTest_DNAConverter_h
#define GeneticAlgTest_DNAConverter_h

#import "ofMain.h"
#import "Nucleotide.h"

//for now this will randomly assign nucleotide sequences to indices,
//later it may try to group indices to neighboring nucleotide sequences
//to mimic http://upload.wikimedia.org/wikipedia/en/d/d6/GeneticCode21-version-2.svg
public class DNAConverter{
private:
    int[] nucleotideToChunk;
    int[][] chunkToNucleotides;
    int numNucleotidesPerChunk;
	
public:
    DNAConverter(int numberChunks){
		//m_bIAmRoot = true;
		//m_nNumberChunks = a_nNumberChunks;
		numNucleotidesPerChunk = (int)Math.ceil(Math.log(numberChunks)/Math.log(4));
        //		System.out.println("nucleotides per chunk:" + m_nNucleotidesPerChunk);
		//m_nMyDepth = 1;
		//BuildTree();
		//PopulateTree(a_nNumberChunks);
		m_narrNucleotideToChunk = new int[(int)Math.pow(4, m_nNucleotidesPerChunk)];
		m_narrChunkToNucleotides = new ArrayList<ArrayList<Integer>>(a_nNumberChunks);
		
		//create an array that is a randomly permuted list
		int[] narrAssignments = GeneticAlg.GetPermutation(m_narrNucleotideToChunk.length);
        //		int[] narrAssignments = new int[m_narrNucleotideToChunk.length];
        //		narrAssignments[narrAssignments.length - 1] = narrAssignments.length - 1;
        //		int nSecondNum;
        //		int nWindowSize = narrAssignments.length;
        //		for(int i = 0; i < narrAssignments.length - 1; i++){
        //			nSecondNum = i + ((int)(Math.random() * nWindowSize));
        //			narrAssignments[nSecondNum] = i;
        //			if (nSecondNum != i){
        //				narrAssignments[i] = nSecondNum;
        //			}
        //			nWindowSize--;
        //		}
		
		//use randomly permuted list to assign chunks to sequences
		//first make sure one of each chunk gets in
		//then randomly assign the remaining spots.
		int i = 0;
		ArrayList<Integer> arrTemp;
        //		System.out.println("creating map:");
		for(; i < a_nNumberChunks; i++){
            //			System.out.println(i+") nucleotide:"+narrAssignments[i]+" chunk:"+i);
			m_narrNucleotideToChunk[narrAssignments[i]] = i;
			arrTemp = new ArrayList<Integer>();
			arrTemp.add(narrAssignments[i]);
			m_narrChunkToNucleotides.add(arrTemp);
		}
		int nCurrChunk;
		for(; i < m_narrNucleotideToChunk.length; i++){
			nCurrChunk = (int)(Math.random() * a_nNumberChunks);
            //			System.out.println(i+") nucleotide:"+narrAssignments[i]+" chunk:"+nCurrChunk);
			m_narrNucleotideToChunk[narrAssignments[i]] = nCurrChunk;
			m_narrChunkToNucleotides.get(nCurrChunk).add(narrAssignments[i]);
		}
	}
	
    vector<Nucleotide>* ConvertSequence(int[] a_narrSequence){
        //		System.out.print("sequence in:");
        //		for(int i : a_narrSequence){
        //			System.out.print(i+",");
        //		}
        //		System.out.println();
		Nucleotide[] arrOutput = new Nucleotide[a_narrSequence.length * m_nNucleotidesPerChunk];
		ArrayList<Integer> narrNucleotideBag;
		int nNucleotide;
		int nOutputIndex = 0;
		for(int i = 0; i < a_narrSequence.length; i++){
			narrNucleotideBag = m_narrChunkToNucleotides.get(a_narrSequence[i]);
			nNucleotide = narrNucleotideBag.get((int)(Math.random() * narrNucleotideBag.size()));
			for(int j = 0; j < m_nNucleotidesPerChunk; j++){
				arrOutput[nOutputIndex] = new Nucleotide((byte)(nNucleotide & 3));
				nNucleotide >>= 2;
				nOutputIndex++;
			}
		}
        //		System.out.print("sequence out:");
        //		for(Nucleotide n : arrOutput){
        //			System.out.print(n.m_Data+",");
        //		}
        //		System.out.println();
		return arrOutput;
	}
	
    vector<int>* ConvertSequence(Nucleotide[] a_arrSequence){
        //		System.out.print("sequence in:");
        //		for(Nucleotide n : a_arrSequence){
        //			System.out.print(n.m_Data+",");
        //		}
        //		System.out.println();
		int[] narrOutput = new int[(a_arrSequence.length)/m_nNucleotidesPerChunk];
		int nOutputIndex = 0;
		int nInputIndex = 0;
		int nReferenceIndex;
		while (nOutputIndex < narrOutput.length){
			nReferenceIndex = 0;
			for(int i = 0; i<m_nNucleotidesPerChunk; i++){
				nReferenceIndex >>= 2;
				nReferenceIndex += (a_arrSequence[nInputIndex].GetData() << ((m_nNucleotidesPerChunk - 1) * 2));
				nInputIndex++;
			}
			narrOutput[nOutputIndex] = m_narrNucleotideToChunk[nReferenceIndex];
			nOutputIndex++;
		}
        //		System.out.print("sequence out:");
        //		for(int n : narrOutput){
        //			System.out.print(n+",");
        //		}
        //		System.out.println();
		return narrOutput;
	}
}

#endif
