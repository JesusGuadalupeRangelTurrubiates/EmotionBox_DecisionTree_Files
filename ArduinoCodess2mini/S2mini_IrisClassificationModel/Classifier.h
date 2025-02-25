#ifndef UUID139828857919744
#define UUID139828857919744

/**
  * RandomForestClassifier(base_estimator=deprecated, bootstrap=True, ccp_alpha=0.0, class_name=RandomForestClassifier, class_weight=None, criterion=gini, estimator=DecisionTreeClassifier(), estimator_params=('criterion', 'max_depth', 'min_samples_split', 'min_samples_leaf', 'min_weight_fraction_leaf', 'max_features', 'max_leaf_nodes', 'min_impurity_decrease', 'random_state', 'ccp_alpha'), max_depth=10, max_features=sqrt, max_leaf_nodes=None, max_samples=None, min_impurity_decrease=0.0, min_samples_leaf=1, min_samples_split=2, min_weight_fraction_leaf=0.0, n_estimators=10, n_jobs=None, num_outputs=3, oob_score=False, package_name=everywhereml.sklearn.ensemble, random_state=None, template_folder=everywhereml/sklearn/ensemble, verbose=0, warm_start=False)
 */
class RandomForestClassifier {
    public:

        /**
         * Predict class from features
         */
        int predict(float *x) {
            int predictedValue = 0;
            size_t startedAt = micros();

            
                    
            uint16_t votes[3] = { 0 };
            uint8_t classIdx = 0;
            float classScore = 0;

            
                tree0(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree1(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree2(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree3(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree4(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree5(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree6(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree7(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree8(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            
                tree9(x, &classIdx, &classScore);
                votes[classIdx] += classScore;
            

            // return argmax of votes
            uint8_t maxClassIdx = 0;
            float maxVote = votes[0];

            for (uint8_t i = 1; i < 3; i++) {
                if (votes[i] > maxVote) {
                    maxClassIdx = i;
                    maxVote = votes[i];
                }
            }

            predictedValue = maxClassIdx;

                    

            latency = micros() - startedAt;

            return (lastPrediction = predictedValue);
        }

        
            

            /**
             * Predict class label
             */
            String predictLabel(float *x) {
                return getLabelOf(predict(x));
            }

            /**
             * Get label of last prediction
             */
            String getLabel() {
                return getLabelOf(lastPrediction);
            }

            /**
             * Get label of given class
             */
            String getLabelOf(int8_t idx) {
                switch (idx) {
                    case -1:
                        return "ERROR";
                    
                        case 0:
                            return "setosa";
                    
                        case 1:
                            return "versicolor";
                    
                        case 2:
                            return "virginica";
                    
                    default:
                        return "UNKNOWN";
                }
            }


            /**
             * Get latency in micros
             */
            uint32_t latencyInMicros() {
                return latency;
            }

            /**
             * Get latency in millis
             */
            uint16_t latencyInMillis() {
                return latency / 1000;
            }
            

    protected:
        float latency = 0;
        int lastPrediction = 0;

        
            

        
            
                /**
                 * Random forest's tree #0
                 */
                void tree0(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[3] < 0.75) {
                            
                                
                        *classIdx = 0;
                        *classScore = 37.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.699999988079071) {
                            
                                
                        *classIdx = 1;
                        *classScore = 32.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 4.8500001430511475) {
                            
                                
                        if (x[0] < 5.950000047683716) {
                            
                                
                        *classIdx = 1;
                        *classScore = 32.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 36.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 36.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #1
                 */
                void tree1(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[3] < 0.75) {
                            
                                
                        *classIdx = 0;
                        *classScore = 35.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.6500000357627869) {
                            
                                
                        if (x[0] < 7.0) {
                            
                                
                        if (x[0] < 6.049999952316284) {
                            
                                
                        *classIdx = 1;
                        *classScore = 32.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[1] < 2.6999999284744263) {
                            
                                
                        *classIdx = 2;
                        *classScore = 38.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 32.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 38.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[2] < 4.8500001430511475) {
                            
                                
                        if (x[1] < 3.100000023841858) {
                            
                                
                        *classIdx = 2;
                        *classScore = 38.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 32.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 38.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #2
                 */
                void tree2(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[3] < 0.7000000029802322) {
                            
                                
                        *classIdx = 0;
                        *classScore = 38.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.550000011920929) {
                            
                                
                        *classIdx = 1;
                        *classScore = 39.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[0] < 6.099999904632568) {
                            
                                
                        if (x[0] < 5.75) {
                            
                                
                        *classIdx = 2;
                        *classScore = 28.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 4.950000047683716) {
                            
                                
                        if (x[1] < 3.100000023841858) {
                            
                                
                        *classIdx = 2;
                        *classScore = 28.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 39.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 39.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 28.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #3
                 */
                void tree3(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[3] < 0.75) {
                            
                                
                        *classIdx = 0;
                        *classScore = 40.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.600000023841858) {
                            
                                
                        if (x[2] < 5.25) {
                            
                                
                        *classIdx = 1;
                        *classScore = 34.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 31.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[0] < 5.950000047683716) {
                            
                                
                        if (x[0] < 5.799999952316284) {
                            
                                
                        *classIdx = 2;
                        *classScore = 31.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 34.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 31.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #4
                 */
                void tree4(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[3] < 0.7000000029802322) {
                            
                                
                        *classIdx = 0;
                        *classScore = 33.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 4.75) {
                            
                                
                        *classIdx = 1;
                        *classScore = 40.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[1] < 2.75) {
                            
                                
                        if (x[0] < 6.150000095367432) {
                            
                                
                        if (x[0] < 5.849999904632568) {
                            
                                
                        *classIdx = 2;
                        *classScore = 32.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 40.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 32.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.550000011920929) {
                            
                                
                        *classIdx = 1;
                        *classScore = 40.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 32.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #5
                 */
                void tree5(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[0] < 5.450000047683716) {
                            
                                
                        if (x[2] < 2.599999964237213) {
                            
                                
                        *classIdx = 0;
                        *classScore = 31.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.350000023841858) {
                            
                                
                        *classIdx = 1;
                        *classScore = 34.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 40.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.550000011920929) {
                            
                                
                        if (x[3] < 0.6500000059604645) {
                            
                                
                        *classIdx = 0;
                        *classScore = 31.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 5.25) {
                            
                                
                        *classIdx = 1;
                        *classScore = 34.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 40.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[0] < 6.1000001430511475) {
                            
                                
                        if (x[1] < 3.100000023841858) {
                            
                                
                        *classIdx = 2;
                        *classScore = 40.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 34.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 40.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #6
                 */
                void tree6(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[2] < 5.0) {
                            
                                
                        if (x[3] < 0.75) {
                            
                                
                        *classIdx = 0;
                        *classScore = 28.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.6500000357627869) {
                            
                                
                        *classIdx = 1;
                        *classScore = 33.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 44.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[0] < 6.049999952316284) {
                            
                                
                        if (x[1] < 2.850000023841858) {
                            
                                
                        *classIdx = 1;
                        *classScore = 33.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 44.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 44.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #7
                 */
                void tree7(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[3] < 0.75) {
                            
                                
                        *classIdx = 0;
                        *classScore = 41.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 4.8500001430511475) {
                            
                                
                        if (x[3] < 1.6500000357627869) {
                            
                                
                        *classIdx = 1;
                        *classScore = 30.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[1] < 3.100000023841858) {
                            
                                
                        *classIdx = 2;
                        *classScore = 34.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 30.0;
                        return;

                            
                        }

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 34.0;
                        return;

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #8
                 */
                void tree8(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[3] < 0.75) {
                            
                                
                        *classIdx = 0;
                        *classScore = 41.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 4.950000047683716) {
                            
                                
                        if (x[3] < 1.6500000357627869) {
                            
                                
                        *classIdx = 1;
                        *classScore = 28.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 36.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[3] < 1.699999988079071) {
                            
                                
                        if (x[1] < 2.850000023841858) {
                            
                                
                        *classIdx = 1;
                        *classScore = 28.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 36.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 36.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        
            
                /**
                 * Random forest's tree #9
                 */
                void tree9(float *x, uint8_t *classIdx, float *classScore) {
                    
                        if (x[3] < 1.6500000357627869) {
                            
                                
                        if (x[3] < 0.75) {
                            
                                
                        *classIdx = 0;
                        *classScore = 33.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 1;
                        *classScore = 35.0;
                        return;

                            
                        }

                            
                        }
                        else {
                            
                                
                        if (x[1] < 3.149999976158142) {
                            
                                
                        *classIdx = 2;
                        *classScore = 37.0;
                        return;

                            
                        }
                        else {
                            
                                
                        if (x[2] < 5.1000001430511475) {
                            
                                
                        *classIdx = 1;
                        *classScore = 35.0;
                        return;

                            
                        }
                        else {
                            
                                
                        *classIdx = 2;
                        *classScore = 37.0;
                        return;

                            
                        }

                            
                        }

                            
                        }

                }
            
        


            
};



static RandomForestClassifier classifier;


#endif