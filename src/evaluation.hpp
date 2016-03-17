//
// Created by Ashok K. Pant on 3/17/16.
//

#ifndef ACCURACY_EVALUATION_CPP_EVALUATION_HPP
#define ACCURACY_EVALUATION_CPP_EVALUATION_HPP

#include "confusion.hpp"
class Evaluation{
public:
    double  _avgAccuray;
    double  _errRate ;
    double  _precisionMicro ;
    double  _recallMicro ;
    double  _fscoreMicro ;
    double  _precisionMacro ;
    double  _recallMacro ;
    double  _fscoreMacro ;

    Evaluation() {
        _avgAccuray=0.0 ;
        _errRate =0.0 ;
        _precisionMicro =0.0 ;
        _recallMicro =0.0 ;
        _fscoreMicro =0.0 ;
        _precisionMacro =0.0 ;
        _recallMacro =0.0 ;
        _fscoreMacro =0.0 ;
    }

    Evaluation(
            double  avgAccuray,
            double  errRate,
            double  precisionMicro,
            double  recallMicro,
            double  fscoreMicro,
            double  precisionMacro,
            double  recallMacro,
            double  fscoreMacro
    ):
            _avgAccuray(avgAccuray),
            _errRate(errRate),
            _precisionMicro(precisionMicro),
            _recallMicro(recallMicro),
            _fscoreMicro(fscoreMicro),
            _precisionMacro(precisionMacro),
            _recallMacro(recallMacro),
            _fscoreMacro(fscoreMacro){}

    Evaluation(Confusion confusion) {
        _avgAccuray=0.0 ;
        _errRate =0.0 ;
        _precisionMicro =0.0 ;
        _recallMicro =0.0 ;
        _fscoreMicro =0.0 ;
        _precisionMacro =0.0 ;
        _recallMacro =0.0 ;
        _fscoreMacro =0.0 ;

        evaluation(confusion);
    }


    void evaluation(Confusion &confusion){
        vector<vector<double> >per(confusion._per);
        int numClasses = confusion._classes;

        //Average Accuracy (The average per-class effectiveness of a classifier)
        double avgAccuracy=0.0;
        double fn=0.0,fp=0.0,tp=0.0,tn=0.0;
        for (int i=0;i<numClasses;i++){
            fn=per[i][0];
            fp=per[i][1];
            tp=per[i][2];
            tn=per[i][3];
            avgAccuracy=+avgAccuracy+((tp+tn)/(tp+fn+fp+tn));
        }
        avgAccuracy=avgAccuracy/numClasses;

        //Error Rate (The average per-class classification error)
        double errRate=0.0;
        for (int i=0;i<numClasses;i++){
            fn=per[i][0];
            fp=per[i][1];
            tp=per[i][2];
            tn=per[i][3];
            errRate=+errRate+((fp+fn)/(tp+fn+fp+tn));
        }
        errRate=errRate/numClasses;

        //Precision-Micro (Agreement of the data class labels with those of a classifiers if calculated from sums of per-text decisions)
        double  numerator=0.0;
        double  denominator=0.0;
        for (int i=0;i<numClasses;i++){
            fn=per[i][0];
            fp=per[i][1];
            tp=per[i][2];
            tn=per[i][3];
            numerator=numerator+tp;
            denominator=denominator+ (tp+fp);
        }
        double  precisionMicro=numerator/denominator;

        //Recall-Micro (Effectiveness of a classifier to identify class labels if calculated from sums of per-text decisions)
        numerator=0.0;
        denominator=0.0;
        for (int i=0;i<numClasses;i++){
            fn=per[i][0];
            fp=per[i][1];
            tp=per[i][2];
            tn=per[i][3];
            numerator=numerator+tp;
            denominator=denominator+ (tp+fn);
        }
        double   recallMicro=numerator/denominator;

        //Fscore-Micro (Relations between data’s positive labels and those given by a classifier based on sums of per-text decisions)
        double beta=1;
        numerator=((beta*beta)+1)*precisionMicro*recallMicro;
        denominator=(beta*beta)*precisionMicro+recallMicro;

        double fscoreMicro=numerator/denominator;

        //Precision-Macro (An average per-class agreement of the data class labels with those of a classifiers)
        double precisionMacro=0.0;
        for (int i=0;i<numClasses;i++){
            fn=per[i][0];
            fp=per[i][1];
            tp=per[i][2];
            tn=per[i][3];
            precisionMacro=precisionMacro+(tp/(tp+fp));
        }
        precisionMacro=precisionMacro/numClasses;

        //Recall-Micro (An average per-class effectiveness of a classifier to identify class labels)
        double recallMacro=0.0;

        for (int i=0;i<numClasses;i++){
            fn=per[i][0];
            fp=per[i][1];
            tp=per[i][2];
            tn=per[i][3];
            recallMacro=recallMacro+(tp/(tp+fn));
        }
        recallMacro=recallMacro/numClasses;

        //Fscore-Macro (Relations between data’s positive labels and those given by a classifier based on a per-class average)
        beta=1;
        numerator=((beta*beta)+1)*precisionMacro*recallMacro;
        denominator=(beta*beta)*precisionMacro+recallMacro;
        double  fscoreMacro=numerator/denominator;

        _avgAccuray = avgAccuracy;
        _errRate = errRate;
        _precisionMicro=precisionMicro;
        _recallMicro=recallMicro;
        _fscoreMicro=fscoreMicro;
        _precisionMacro=precisionMacro;
        _recallMacro=recallMacro;
        _fscoreMacro=fscoreMacro;
    }

    void print(){
        cout<<"System Evaluation Results"<<endl;
        cout << "=======================================" << endl;
        cout<<"\tAverage System Accuracy(%): "<< _avgAccuray*100<<endl;
        cout<<"\tSystem Error(%)           : "<< _errRate*100<<endl;
        cout<<"\tPrecision (Micro)(%)      : "<< _precisionMicro*100<<endl;
        cout<<"\tRecall (Micro)(%)         : "<< _recallMicro*100<<endl;
        cout<<"\tFscore (Micro)(%)         : "<< _fscoreMicro*100<<endl;
        cout<<"\tPrecision (Macro)(%)      : "<< _precisionMacro*100<<endl;
        cout<<"\tRecall (Macro)(%)         : "<< _recallMacro*100<<endl;
        cout<<"\tFscore (Macro)(%)         : "<< _fscoreMacro*100<<endl;
    }
};
#endif //ACCURACY_EVALUATION_CPP_EVALUATION_HPP
