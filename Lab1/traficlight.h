#ifndef TRAFICLIGHT_H
#define TRAFICLIGHT_H

#include <systemc.h>
#include <fstream>


SC_MODULE(Traficlight) {
  //variabel som säger hur många bilar det finns vid varje trafikljus just nu
  sc_in<int> cars;
/*  sc_in<int> SN_cars;
  sc_in<int> EW_cars;
  sc_in<int> WE_cars;*/
  //variabel som säger om det är grönt eller rött
  sc_out<bool> event;
/*  sc_out<bool> SN_event;
  sc_out<bool> EW_event;
  sc_out<bool> WE_event;*/
  int trafic_queue;
  sc_out<int> summed_up_cars;
/*  int summed_up_cars_SN;
  int summed_up_cars_EW;
  int summed_up_cars_WE;*/

  SC_HAS_PROCESS(Traficlight);
  Traficlight(sc_module_name name, char *datafile);
  ~Traficlight();

  void traficlight_thread();


  ifstream *in;
};

#endif // MONITOR_H
