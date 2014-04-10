//
//  ofxGenetics.h
//  GeneticAlgTest
//
//  Created by Quin Kennedy on 4/6/14.
//
//

#ifndef GeneticAlgTest_ofxGenetics_h
#define GeneticAlgTest_ofxGenetics_h

#import "Gamete.h"

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

class ofxGenetics{
private:
    MatingType matingType;
    LifeCycle lifeCycle;
    vector<Gamete> children;
    int generationSize;
    vector<GameteFitness> fitnessList;
    DNAConverter dnaConverter;
public:
    ofxGenetics(MatingType _matingType, LifeCycle _lifeCycle, int _numChunks, int _generationSize){
        matingType = _matingType;
        lifeCycle = _lifeCycle;
        generationSize = _generationSize;
        dnaConverter(_numChunks);
    }
	
	public ArrayList<int[]> GetCurrentOrganisms(){
		Gamete[] organisms = m_CurrGeneration.GetList();
		ArrayList<int[]> output = new ArrayList<int[]>(organisms.length);
		for(Gamete g : organisms){
			output.add(m_Converter.ConvertSequence(g.GetChromosomes()[0].GetData()));
		}
		return output;
	}
	
	public void AddOrganism(int[] a_narrData, BigInteger a_nFitness){
		Gamete tempG = new Gamete(new Chromosome[]{
            new Chromosome(new Chromatid(m_Converter.ConvertSequence(a_narrData)))});
		tempG.SetFitness(a_nFitness);
		m_CurrGeneration.Insert(tempG);
	}
	
	//max num children = 4;
	//min num children = 1;
	public ArrayList<int[]> Mate(int a_nNumChildren){
		Gamete[] arrChildren;
		switch (m_Mating){
			case Harem:
			case Monogamy:
			case Polyandry:
			case Polygynandry:
			case Polygyny:
			case Hermaphrodite://default to Herm. for now
			default:
				BigInteger nHusband = Multiply(m_CurrGeneration.TotalFitness(), Math.random());
				BigInteger nWife = Multiply(m_CurrGeneration.TotalFitness(), Math.random());
				//System.out.println("totalfitness:"+m_CurrGeneration.TotalFitness()+", husband:"+nHusband+", wife:"+nWife);
				arrChildren = m_CurrGeneration.GetByFitness(nHusband).Copy().Fertilize(m_CurrGeneration.GetByFitness(nWife).Copy()).Split();
		}
		if (m_arrChildren == null){
			m_arrChildren = new ArrayList<Gamete>();
		}
		int nNormalizedNumChildren = Math.max(1, Math.min(4, a_nNumChildren));
		ArrayList<int[]> output = new ArrayList<int[]>(nNormalizedNumChildren);
		int[] narrPermutation = (output.size() < 4 ? GetPermutation(4) : new int[]{0,1,2,3});
		for(int i = 0; i<nNormalizedNumChildren; i++){
			m_arrChildren.add(arrChildren[narrPermutation[i]]);
			output.add(m_Converter.ConvertSequence(arrChildren[narrPermutation[i]].GetChromosomes()[0].GetData()));
		}
		return output;
	}
	
	public static BigInteger Multiply(BigInteger a_nFitness, double a_nFraction){
		double nMaxIntPrecision = Math.pow(2, 53);
		BigInteger nMaxSection;
		BigInteger nResult;
		if (a_nFraction > 1){
			nMaxSection = BigInteger.valueOf((long)nMaxIntPrecision);
			BigInteger nFractionedPart =
            BigInteger.valueOf((long)(nMaxIntPrecision * a_nFraction));
			nResult = nFractionedPart
            .multiply(a_nFitness
                      .divide(nMaxSection))
            .add(BigInteger
                 .valueOf((long)(a_nFitness
                                 .mod(nMaxSection)
                                 .doubleValue()
                                 * a_nFraction)));
		} else if (a_nFraction <= nMaxIntPrecision) {
			nMaxSection =
            BigInteger.valueOf((long)(nMaxIntPrecision / a_nFraction));
			BigInteger nFractionedPart =
            BigInteger.valueOf((long)(nMaxSection.doubleValue() * a_nFraction));
			nResult = nFractionedPart
            .multiply(a_nFitness
                      .divide(nMaxSection))
            .add(BigInteger
                 .valueOf((long)(a_nFitness
                                 .mod(nMaxSection)
                                 .doubleValue()
                                 * a_nFraction)));
		} else {
			nResult = BigInteger.valueOf((long)(a_nFitness.doubleValue()*a_nFraction));
		}
		return nResult;
	}
    
	//this will mate the current generation and bypass selection,
	//afterwards you must call ChildrenFitness(double[])
	//to advance a generation
	public ArrayList<int[]> GetChildren(int a_nAmount){
		ArrayList<int[]> output = new ArrayList<int[]>(a_nAmount);
		for(int i = 0; i<a_nAmount;)
		{
			ArrayList<int[]> currChildren = Mate(((int)(Math.pow(Math.random(), 2)*4))+1);
			for(int j = 0; j < currChildren.size() && i<a_nAmount; j++){
				output.add(currChildren.get(j));
				i++;
			}
		}
		return output;
	}
	
	public void SetChildrenFitness(BigInteger[] a_narrFitness){
		FitnessSortedList sortedChildren = new FitnessSortedList();
		for(int i = 0; i<m_arrChildren.size(); i++){
			m_arrChildren.get(i).SetFitness(i < a_narrFitness.length ? a_narrFitness[i] : BigInteger.ZERO);
			sortedChildren.Insert(m_arrChildren.get(i));
		}
		m_arrChildren = null;
		if (m_nGenerationSize >= sortedChildren.Length()){
			m_CurrGeneration = sortedChildren;
		} else {
			m_CurrGeneration = new FitnessSortedList();
			for(int i = 0; i<m_nGenerationSize; i++){
				m_CurrGeneration.Insert(sortedChildren.RemoveByFitness(Multiply(sortedChildren.TotalFitness(), Math.random())));
			}
		}
	}
    
    static int[] getPermutation(int size){
        int permutation[size];
        for (int i = 0; i++; i < size) {
            permutation[i] = [i];
        }
        int temp;
        int secondIndex;
        int windowSize = size;
        for(int i = 0; i < size; i++, windowSize--){
            secondIndex = i + (int)(ofRandomf()*windowSize);
            if (secondIndex != i){
                temp = permutation[secondIndex];
                permutation[secondIndex] = permutation[i];
                permutation[i] = temp;
            }
        }
        return permutation;
    }
};

#endif
