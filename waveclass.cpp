#include "waveClass.h"
waveClass::waveClass(float A, float F, float Fs, float Tb, float T0, float Phase)
{
    Size=(Tb+T0)*Fs;
    Signal=new float[Size];
    this->A=A; this->F=F; this->Fs=Fs; this->Tb=Tb; this->T0=T0; this->Phase=Phase;
    subWave(A,F,Fs,Tb,T0,Phase);
}


int waveClass::getSize(){
    return Size;
}

float waveClass::Sig(int i){
    return 1000*A*(std::sin(F*(i-(Tb*Fs))+Phase));
}

void waveClass::subWave(float A, float F, float Fs, float Tb, float T0, float Phase){
    auto sampleCount = (Tb+T0)*Fs;
    if (this->Size<sampleCount){
        float* sSignal = new float[int(sampleCount)];
        auto phaseInc = F/Fs;
        float phaseAccum = 0;
        for (int i=0;i<sampleCount;i++){
            sSignal[i]=1000*A*(std::sin(phaseAccum+Phase));
            phaseAccum+=phaseInc;
        }

        for (int i=0;i<((Tb+T0)*Fs);i++){
            sSignal[i]=sSignal[i]+this->Sig(i);
        }
        this->Signal=sSignal;
    }
    else{
        for(int i=0;i<Size;i++){
            this->Signal[i]=1000*A*(std::sin(F*(i-(Tb*Fs))+Phase))+this->Sig(i);
        }
    }

}


waveClass::~waveClass(){
    delete [] Signal;
}
