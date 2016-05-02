#include "ofApp.h"
#include "particle.h"

#define NUMBERS 30

int width = 1280;
int height = 800;
int counter;
int caseState;
unsigned long long pTime;
string opening="";
string final="";

// resolution of live video
int vidX = 480;
int vidY = 360;

// setup blob pointer
int pointerX = 0;
int pointerY = 0;
int pointerRad = 20;
int camState = 1;
int contour=1;




James james[NUMBERS];
Jessie jessie[NUMBERS];

//--------------------------------------------------------------
void ofApp::setup(){
    myFont.load("Bohemian typewriter.ttf",20);
    sound.loadSound("typer.wav");
    cat1.load("cat1.wav");
    cat2.load("cat2.wav");
    eat.load("eat.wav");
    ofHideCursor();
    ofBackground(255);
    face.load("face.png");
    niko.load("niko.png");
    jen.load("jen.png");
    food.load("food.png");
    video.loadMovie("video.mp4");
    ofDrawBitmapString("HI hIHIHIHIHIHI", 300,300);
    for (int i = 0; i < NUMBERS; i++) {
    james[i].setup();
    }
    
    for (int j = 0; j < NUMBERS; j++) {
        jessie[j].setup();
    }
    
    
    
    
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(vidX,vidY);  // setup live video grabbing
    
    colorImg.allocate(vidX,vidY);  // color image display
    grayImage.allocate(vidX,vidY); // grayscale display
    grayBg.allocate(vidX,vidY);	   // contour image
    grayDiff.allocate(vidX,vidY);  // b/w differencing image
    
    bLearnBakground = true;
    threshold = 80;

}

//--------------------------------------------------------------
void ofApp::update(){
    

    
    unsigned long long cTime = ofGetElapsedTimeMillis();

    //-------- typer effect start--------
    
    if(final.length() < opening.length()){
        
        if(cTime-pTime > ofRandom(100, 500)){
            counter++;
            cout << counter <<endl; //debug
            final += opening[counter-1];
            sound.setVolume(ofRandom(0.1,1.2));
            sound.play();
            pTime = cTime;
        }
    }
    //-------- typer effect end--------
    
    
    if(caseState == 0) opening= "Hi, please setup the contour.";

    if(caseState == 1) opening= "Deep inside the concrete jungle of New York,\n\n lives a young Asian boy named James. ";
    
    if(caseState == 2) opening= "           James has two cats.\n\n One named Jenny and one named Niko. ";
    
    if(caseState == 3) opening= "They like to eat, play, and poop. \n\nThey spend most of their day sleeping. \n\nSometimes it makes James wonder \n\nwhat do cats dream about \n\nwhen they are sleeping. ";
    
    if(caseState == 4) opening= "Maybe their dreams are about food? ";
    
    if(caseState == 5) {
        opening= "Maybe they dream about their masters. ";
        for (int i = 0; i < NUMBERS; i++) {
            james[i].update();
        }
        for (int j = 0; j < NUMBERS; j++) {
            jessie[j].update();
        }
        
            }
    
    if(caseState == 6) opening= "Or maybe they dream about \n\nsomething more intense..... ";
    
    if(caseState == 7){
        video.play();
     video.update();
    }

    if(caseState == 8) opening= "Maybe the cats do not dream about \n\nanything when they are sleeping. \n\nIt was all James's imagination. \n\nHe has been coding for awhile \n\nand he needs to get some rest. \n\nSo yah, to whoever that is \n\nreading this........... ";
    
    if(caseState == 9) opening= "PEACE OUT ";
    
    
    
    bool bNewFrame = false;
    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
    if (bNewFrame){  // if we have a new frame
        
        colorImg.setFromPixels(vidGrabber.getPixels());
        
        grayImage = colorImg;
        if (bLearnBakground == true){  // if we hit space, this grabs a "control" image
            grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // find max 10 blobs with no holes in them
        contourFinder.findContours(grayDiff, 20, (vidX*vidY)/3, 10, false);	// false == dont find holes in our blobs
    }
    

    
    
       
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    switch(caseState){
        case 0: //p1 set contour
            
            ofSetColor(0);
            myFont.drawString(final, width/3, height/4);
            
            if(final.length()>=opening.length()){
            
            ofSetColor(255,255,255);
            if(camState == 1)
                colorImg.draw(width/3.2, height/3.2);
            
            if(camState == 2)
                grayImage.draw(width/3.2,height/3.2);
                
            if(camState == 3)
                grayDiff.draw(width/3.2,height/3.2);
            if(contour %2 == 0)
                contourFinder.draw(width/3.2,height/3.2);
                
                ofSetColor(50);
                ofDrawBitmapString("Press Left/Right to change modes", width/2.6, 640);
                ofDrawBitmapString("Press C to turn on/off contour", width/2.6, 670);
                ofDrawBitmapString("Hover HERE to start", width/2.4, 700);
                
                ofSetColor(48,62,87);
                if (contourFinder.nBlobs > 0) {  // if any detected  TODO: go w largest
                    pointerX = ofMap(contourFinder.blobs[0].boundingRect.x, vidX, 0, 0, ofGetWidth(), true);
                    pointerY = ofMap(contourFinder.blobs[0].boundingRect.y, 0, vidY, 0, ofGetHeight(), true);
                    ofDrawCircle(pointerX, pointerY, pointerRad);
                }
                
                int hit = checkCollision(pointerX, pointerY, pointerRad, width/2.4, 700, 200, 5);
                
                if(hit == 1) {
                    final ="";
                    counter = -1;
                    caseState++;
                }

    

            //ofDrawBitmapString(contour, width/10, height/2);
            //debug
            }
            
            break;
            
        case 1: //p2 intro
            ofSetColor(0);
            myFont.drawString(final, width/10, height/2);
            if(final.length()>=opening.length()) {
                ofSetColor(255,255,255);
                face.draw(width-360,height/4); //draw face
                ofSetColor(0);
                ofDrawBitmapString("Hover the pointer to me!", width-320, height - height/4.2); //pointer guide

                
                ofSetColor(48,62,87);
                if (contourFinder.nBlobs > 0) {  // if any detected  TODO: go w largest
                    pointerX = ofMap(contourFinder.blobs[0].boundingRect.x, vidX, 0, 0, ofGetWidth(), true);
                    pointerY = ofMap(contourFinder.blobs[0].boundingRect.y, 0, vidY, 0, ofGetHeight(), true);
                    ofDrawCircle(pointerX, pointerY, pointerRad);
                }
                
                int hit = checkCollision(pointerX, pointerY, pointerRad, width-360, height/4, 250, 382);
                
                if(hit == 1) {
                    final ="";
                    counter = -1;
                    caseState++;
                }
                
            }
            break;
            
        case 2: //p3 cats
             ofSetColor(0);
             myFont.drawString(final, width/3.5, 150);
            if(final.length()>=opening.length()) {
                ofSetColor(255, 255, 255);
                jen.draw(300,height/3,300,300);
                niko.draw(width-500,height/3,300,300);
                
                ofSetColor(48,62,87);
                if (contourFinder.nBlobs > 0) {  // if any detected  TODO: go w largest
                    pointerX = ofMap(contourFinder.blobs[0].boundingRect.x, vidX, 0, 0, ofGetWidth(), true);
                    pointerY = ofMap(contourFinder.blobs[0].boundingRect.y, 0, vidY, 0, ofGetHeight(), true);
                    ofDrawCircle(pointerX, pointerY, pointerRad);
                }
                //ofDrawBitmapString("Press RETURN for Next page", width-250, height -50);
                int hitJen = checkCollision(pointerX, pointerY, pointerRad, 300, height/3, 300, 300);
                int hitNiko = checkCollision(pointerX, pointerY, pointerRad, width-500, height/3, 300, 300);
                ofDrawBitmapString("Hover to Next page", width-250, height -50);
                int hit = checkCollision(pointerX, pointerY, pointerRad, width-250, height-50, 250, 10);
                if(hit ==1){
                    final ="";
                    counter = -1;
                    caseState++;
                }
                
                if(hitJen == 1) cat1.play();
                
                if(hitNiko == 1) cat2.play();
            
            }
            
            break;
            
        case 3: //p4 cat paragraph
            cat1.stop();
            cat2.stop();
            ofSetColor(0);
            myFont.drawString(final, width/3.5, 250);
            if(final.length()>=opening.length()) {
                ofSetColor(48,62,87);
                if (contourFinder.nBlobs > 0) {  // if any detected  TODO: go w largest
                    pointerX = ofMap(contourFinder.blobs[0].boundingRect.x, vidX, 0, 0, ofGetWidth(), true);
                    pointerY = ofMap(contourFinder.blobs[0].boundingRect.y, 0, vidY, 0, ofGetHeight(), true);
                    ofDrawCircle(pointerX, pointerY, pointerRad);
                }
                ofDrawBitmapString("Hover to Next page", width-250, height -50);
                int hit = checkCollision(pointerX, pointerY, pointerRad, width-250, height-50, 250, 10);
                if(hit ==1){
                    final ="";
                    counter = -1;
                    caseState++;
                }
            }

            break;
            
        case 4: //cat dream food
            ofSetColor(0);
            myFont.drawString(final, width/3.5, 200);
            if(final.length()>=opening.length()) {
                ofSetColor(255, 255, 255);
                food.draw(width/3.2,height/3.2,500,500);
                ofSetColor(48,62,87);
                if (contourFinder.nBlobs > 0) {  // if any detected  TODO: go w largest
                    pointerX = ofMap(contourFinder.blobs[0].boundingRect.x, vidX, 0, 0, ofGetWidth(), true);
                    pointerY = ofMap(contourFinder.blobs[0].boundingRect.y, 0, vidY, 0, ofGetHeight(), true);
                    ofDrawCircle(pointerX, pointerY, pointerRad);
                }
                ofDrawBitmapString("Hover to Next page", width-250, height -50);
                int hit = checkCollision(pointerX, pointerY, pointerRad, width-250, height-50, 250, 10);
                int hitFood = checkCollision(pointerX, pointerY, pointerRad, width/3.2, height/3.2, 500, 500);
                if(hitFood == 1)eat.play();
                if(hit ==1){
                    final ="";
                    counter = -1;
                    caseState++;
                }
            }
            
            break;
            
        case 5: //cat dream master
            eat.stop();
            ofSetColor(0);
            myFont.drawString(final, width/3.5, 200);
            if(final.length()>=opening.length()) {
                ofSetColor(255, 255, 255);
                for(int i =0; i<NUMBERS; i++){
                    james[i].draw();
                }
                for(int j =0; j<NUMBERS; j++){
                    jessie[j].draw();
                }
               
                
                ofSetColor(48,62,87);
                if (contourFinder.nBlobs > 0) {  // if any detected  TODO: go w largest
                    pointerX = ofMap(contourFinder.blobs[0].boundingRect.x, vidX, 0, 0, ofGetWidth(), true);
                    pointerY = ofMap(contourFinder.blobs[0].boundingRect.y, 0, vidY, 0, ofGetHeight(), true);
                    ofDrawCircle(pointerX, pointerY, pointerRad);
                }
                ofDrawBitmapString("Hover to Next page", width-250, height -50);
                int hit = checkCollision(pointerX, pointerY, pointerRad, width-250, height-50, 250, 10);
                if(hit ==1){
                    final ="";
                    counter = -1;
                    caseState++;
                }
                
                
            }

            break;
            
        case 6:
            ofSetColor(0);
            myFont.drawString(final, width/3.5, 400);
            if(final.length()>=opening.length()) {
                opening ="";
                final ="";
                counter = -1;
                caseState++;
            }

            break;
            
        case 7: //video
            ofSetColor(255,255,255);
            video.draw(0,0,1280,800);
            ofSetColor(255);
            ofDrawBitmapString("Press RETURN to skip", width-250, 50);
            if(video.getPosition()-video.getDuration() == 0)caseState++;

            break;
            
            
        case 8: //ending paragraph
            video.stop();
            ofSetColor(0);
            myFont.drawString(final, width/3.2, 100);
            if(final.length()>=opening.length()) {
                final ="";
                counter = -1;
                caseState++;
            }
            

            break;
            
        case 9: //peace out
            myFont.load("Bohemian typewriter.ttf",80);
            ofSetColor(0);
            myFont.drawString(final, width/3.8, height/2);
            break;

    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == OF_KEY_RIGHT && camState < 3){
        camState ++;
        
    }else if(key == OF_KEY_RIGHT && camState >= 3){
        camState -= 2;
    }
    
    if(key == OF_KEY_LEFT && camState >1){
     camState --;
    }else if(key == OF_KEY_LEFT && camState == 1){
        camState += 2;
    }
    
    if(key == 'c' || key == 'C')contour++;
    
    if(key == OF_KEY_RETURN){
//        if(caseState >=0 || caseState == 2){
//            final ="";
//            counter = -1;
//            //cout <<final<<endl; //debug
//            caseState++;
//        }
        
        if(caseState == 7){
            final ="";
            counter = -1;
            caseState++;
        }
    }

    
    
  
 
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

int ofApp::checkCollision(int px, int py, int psize, float obx, float oby, float obxs, float obys){
    if(obx+obxs > px && obx < px + psize && oby < py + psize && oby + obys > py){
        return 1;
    }else{
        return 0;
    }
}



void ofHideCursor(){
#ifdef TARGET_OSX
    CGDisplayHideCursor(kCGDirectMainDisplay);
#else
    glutSetCursor(GLUT_CURSOR_NONE);
#endif
}

//--------------------------------------

void ofShowCursor(){
#ifdef TARGET_OSX
    CGDisplayShowCursor(kCGDirectMainDisplay);
#else
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
#endif
}
