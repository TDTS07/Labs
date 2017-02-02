#include <cassert>
#include "traficlight.h"

Traficlight::Traficlight(sc_module_name name, char *datafile)
  : sc_module(name)
{
  assert(datafile != 0);       // An input file should be given.

  in = new ifstream(datafile); // Open the input file.
  assert(*in);                 // Check that everything is OK.
SC_THREAD(traficlight_thread);

}
Traficlight::~Traficlight()
{
  delete in;
}

void Traficlight::traficlight_thread()
{
  int NS_cars_prel = NS_cars->read() + summed_up_cars_NS;
  int SN_cars_prel = SN_cars->read() + summed_up_cars_SN;
  int EW_cars_prel = EW_cars->read() + summed_up_cars_EW;
  int WE_cars_prel = WE_cars->read() + summed_up_cars_WE;
  for (;;) {
    wait(1, SC_SEC);     // Generate new inputs every second.
    if((NS_cars_prel > 0)&&(trafic_queue[1]>=trafic_queue[3])&&(trafic_queue[1]>=trafic_queue[4])){
      if(SN_cars_prel > 0){
        NS_event = 1;
        SN_event = 1;
        EW_event = 0;
        WE_event = 0;
        summed_up_cars_SN = 0;
        summed_up_cars_NS = 0;
      }
      else{
        NS_event = 1;
        SN_event = 0;
        EW_event = 0;
        WE_event = 0;
        summed_up_cars_NS = 0;
      }
      if(WE_cars_prel > 0){
        trafic_queue[4] = trafic_queue[4] +1;
        summed_up_cars_WE = summed_up_cars_WE + WE_cars;
      }
      if(EW_cars_prel > 0){
        trafic_queue[3] = trafic_queue[3] +1;
        summed_up_cars_EW = summed_up_cars_EW + EW_cars;
      }
    }
    else if((EW_cars_prel > 0)&&(trafic_queue[3]>=trafic_queue[1])&&(trafic_queue[3]>=trafic_queue[2])){
      if(WE_cars_prel > 0){
        NS_event = 0;
        SN_event = 0;
        EW_event = 1;
        WE_event = 1;
        summed_up_cars_WE = 0;
        summed_up_cars_EW = 0;
      }
      else{
        NS_event = 0;
        SN_event = 0;
        EW_event = 1;
        WE_event = 0;
        summed_up_cars_EW = 0;
      }
      if(NS_cars_prel > 0){
        trafic_queue[1] = trafic_queue[1] +1;
        summed_up_cars_NS = summed_up_cars_NS + NS_cars;
      }
      if(SN_cars_prel > 0){
        trafic_queue[2] = trafic_queue[2] +1;
        summed_up_cars_SN = summed_up_cars_SN + SN_cars;
      }
    }
    else if((WE_cars_prel > 0)&&(trafic_queue[4]>=trafic_queue[1])&&(trafic_queue[4]>=trafic_queue[2])){
      if(EW_cars_prel > 0){
        NS_event = 0;
        SN_event = 0;
        EW_event = 1;
        WE_event = 1;
        summed_up_cars_WE = 0;
        summed_up_cars_EW = 0;
      }
      else{
        NS_event = 0;
        SN_event = 0;
        EW_event = 0;
        WE_event = 1;
        summed_up_cars_WE = 0;
      }
      if(NS_cars_prel > 0){
        trafic_queue[1] = trafic_queue[1] +1;
        summed_up_cars_NS = summed_up_cars_NS + NS_cars;
      }
      if(SN_cars_prel > 0){
        trafic_queue[2] = trafic_queue[2] +1;
        summed_up_cars_SN = summed_up_cars_SN + SN_cars;
      }
    }
    else if((SN_cars_prel > 0)&&(trafic_queue[2]>=trafic_queue[3])&&(trafic_queue[2]>=trafic_queue[4])){
      if(NS_cars_prel > 0){
        NS_event = 1;
        SN_event = 1;
        EW_event = 0;
        WE_event = 0;
        summed_up_cars_SN = 0;
        summed_up_cars_NS = 0;
      }
      else{
        NS_event = 0;
        SN_event = 1;
        EW_event = 0;
        WE_event = 0;
        summed_up_cars_SN = 0;
      }
      if(EW_cars_prel > 0){
        trafic_queue[3] = trafic_queue[3] +1;
        summed_up_cars_EW = summed_up_cars_EW + EW_cars;
      }
      if(WE_cars_prel > 0){
        trafic_queue[4] = trafic_queue[4] +1;
        summed_up_cars_WE = summed_up_cars_WE + WE_cars;
      }
    }
  }


}
