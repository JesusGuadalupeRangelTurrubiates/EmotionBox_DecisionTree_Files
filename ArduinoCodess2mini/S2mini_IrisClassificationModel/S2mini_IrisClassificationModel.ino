// file IrisClassification.ino
/**
 * This is a demo project to classify the Iris dataset using
 * the pre-processing pipeline and classifier fitted in Python
 * with the eloquent_tinyml package.
 *
 * It reads the data from the Serial Monitor and performs
 * classification.
 */
#include "Classifier.h"


void setup() {
    Serial.begin(115200);
    Serial.println("This is a demo for the Iris dataset classification");
    Serial.println("Paste a list of features into the Serial Monitor and get the prediction back");
    Serial.println("Here are a few examples for each class: ");
    Serial.println(" > Class 0");
    Serial.println("   > 5.1,3.5,1.4,0.2");
    Serial.println("   > 4.9,3.0,1.4,0.2");
    Serial.println("   > 4.7,3.2,1.3,0.2");
    Serial.println(" > Class 1");
    Serial.println("   > 7.0,3.2,4.7,1.4");
    Serial.println("   > 6.4,3.2,4.5,1.5");
    Serial.println("   > 6.9,3.1,4.9,1.5");
    Serial.println(" > Class 2");
    Serial.println("   > 6.3,3.3,6.0,2.5");
    Serial.println("   > 5.8,2.7,5.1,1.9");
    Serial.println("   > 7.1,3.0,5.9,2.1");
}


void loop() {
    float features[4];
    
    if (!Serial.available())
        return;
        
    for (int i = 0; i < 4; i++)
        features[i] = Serial.readStringUntil(',').toFloat();
    
    // run prediction and print result
    Serial.print("Predicted class: ");
    Serial.println(classifier.predict(features));
    Serial.print("Predicted class label: ");
    Serial.println(classifier.predictLabel(features));
    Serial.print("It took ");
    Serial.print(classifier.latencyInMicros());
    Serial.println(" micros");
}