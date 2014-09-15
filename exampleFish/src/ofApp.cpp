#include "ofApp.h"

struct mycompare{
    static const int answerLength = 12;
    int answer[mycompare::answerLength] = {0,1,0,1,0,1,0,1,0,1,0,1};
    bool operator()(vector<int>* A, vector<int>* B){
        
        int sizeDiffA = abs(mycompare::answerLength - ((int)A->size()));
        int sizeDiffB = abs(mycompare::answerLength - ((int)B->size()));
        if (sizeDiffA != sizeDiffB){
            return sizeDiffB > sizeDiffA;
        } else {
            int matchA = 0;
            int matchB = 0;
            for(int i = 0; i < mycompare::answerLength; i++){
                if (i < A->size() && A->at(i) == answer[i]){
                    matchA++;
                }
                if (i < B->size() && B->at(i) == answer[i]){
                    matchB++;
                }
            }
            return matchA > matchB;
        }
    }
} mycompareO;

//--------------------------------------------------------------
void ofApp::setup(){
    Chromosome c;
    Chromatid ch;
    Transcriptor t;
    Nucleotide n;
    vector<int> vecAnswer(mycompareO.answer, mycompareO.answer+mycompare::answerLength);
    vector<int> items;
    items.push_back(0);
    items.push_back(1);
	ofxGenetics<int> genetics(Polygyny, Gametic, items);
    vector<vector<int>*>* children;
    vector<vector<int>*>* parents = new vector<vector<int>*>();
    parents->push_back(new vector<int>(1, 1));
    parents->push_back(new vector<int>(1, 0));
    ofLogNotice()<<"start:";
    for(auto it : *parents){
        for(auto it2 : *it){
            cout << it2;
        }
        cout<<endl;
    }
    ofLogNotice()<<"running:";
    do{
        children = new vector<vector<int>*>(100);
        genetics.mate(children, parents);
        ofSort(*children, mycompareO);
        //if the best parent is better than the best child
        //  put the parent at the front
        //  and remove the last child
        if (mycompareO(parents->at(0), children->at(0))){
            children->insert(children->begin(), parents->at(0));
            children->resize(children->size() - 1);
        }
        //TODO: delete old parents
        parents = children;
        for(auto it : **(children->begin())){
            cout<<it;
        }
        cout<<endl;
        if (mycompareO(&vecAnswer, children->at(0))){
            continue;
        }
        break;
    }while(TRUE);
    
    ofLogNotice()<<"end:";
    for(auto it : *children){
        for(auto it2 : *it){
            cout << it2;
        }
        cout<<endl;
    }
    ofExit();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
