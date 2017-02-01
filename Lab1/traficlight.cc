#include <cassert>
#include "traficlight.h"
trafic_queue[1] = 1; // I startläget så har NS och SN högre prioritet än de andra, bara för att ha ett startvärde
trafic_queue[2] = 1;
Monitor::Monitor(sc_module_name name)
  : sc_module(name)
{

SC_THREAD(traficlight_thread);

}
Traficlight::~Traficlight()
{
  delete in;
}

void Traficlight::traficlight_thread()
{
  int NS_cars = NS_cars->read();
  int SN_cars = SN_cars->read();
  int EW_cars = EW_cars->read();
  int WE_cars = WE_cars->read();
  for (;;) {
    wait(1, SC_SEC);     // Generate new inputs every second.
    if((NS_cars > 0)&&(trafic_queue[1]>=trafic_queue[3])&&(trafic_queue[1]>=trafic_queue[4]){
      if(SN_cars > 0){
        NS_event = 1;
        SN_event = 1;
        EW_event = 0;
        WE_event = 0;
      }
      else{
        NS_event = 1;
        SN_event = 0;
        EW_event = 0;
        WE_event = 0;
      }
      if(WE_cars > 0){
        trafic_queue[4] = trafic_queue[4] +1;
      }
      if(EW_cars > 0){
        trafic_queue[3] = trafic_queue[3] +1;
      }
    }
    else if((EW_cars > 0)&&(trafic_queue[3]>=trafic_queue[1])&&(trafic_queue[3]>=trafic_queue[2]){
      if(WE_cars > 0){
        NS_event = 0;
        SN_event = 0;
        EW_event = 1;
        WE_event = 1;
      }
      else{
        NS_event = 0;
        SN_event = 0;
        EW_event = 1;
        WE_event = 0;
      }
      if(NS_cars > 0){
        trafic_queue[1] = trafic_queue[1] +1;
      }
      if(SN_cars > 0){
        trafic_queue[2] = trafic_queue[2] +1;
      }
    }
    else if((WE_cars > 0)&&(trafic_queue[4]>=trafic_queue[1])&&(trafic_queue[4]>=trafic_queue[2]){
      if(EW_cars > 0){
        NS_event = 0;
        SN_event = 0;
        EW_event = 1;
        WE_event = 1;
      }
      else{
        NS_event = 0;
        SN_event = 0;
        EW_event = 0;
        WE_event = 1;
      }
      if(NS_cars > 0){
        trafic_queue[1] = trafic_queue[1] +1;
      }
      if(SN_cars > 0){
        trafic_queue[2] = trafic_queue[2] +1;
      }
    }
    else if((SN_cars > 0)&&(trafic_queue[2]>=trafic_queue[3])&&(trafic_queue[2]>=trafic_queue[4]){
      if(NS_cars > 0){
        NS_event = 1;
        SN_event = 1;
        EW_event = 0;
        WE_event = 0;
      }
      else{
        NS_event = 0;
        SN_event = 1;
        EW_event = 0;
        WE_event = 0;
      }
      if(EW_cars > 0){
        trafic_queue[3] = trafic_queue[3] +1;
      }
      if(WE_cars > 0){
        trafic_queue[4] = trafic_queue[4] +1;
      }
    }
  }


}
