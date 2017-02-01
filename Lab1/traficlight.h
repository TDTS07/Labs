#ifndef TRAFICLIGHT_H
#define TRAFICLIGHT_H

#include <systemc.h>
#include <fstream>


SC_MODULE(Traficlight) {
  //variabel som säger hur många bilder det finns vid varje trafikljus just nu
  sc_in<int> NS_cars;
  sc_in<int> SN_cars;
  sc_in<int> EW_cars;
  sc_in<int> WE_cars;
  //variabel som säger om det är grönt eller rött
  sc_out<bool> NS_event;
  sc_out<bool> SN_event;
  sc_out<bool> EW_event;
  sc_out<bool> WE_event;
  sc_out<int> trafic_queue[4];

  SC_HAS_PROCESS(Traficlight);
  Traficlight(sc_module_name name);
  ~Traficlight();

  void traficlight_thread();



};

#endif // MONITOR_H
