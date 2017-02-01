#ifndef MONITOR_H
#define MONITOR_H

#include <systemc.h>
#include <fstream>

using std::ofstream;

SC_MODULE(Monitor) {
  //variabel som säger att det finns bil/bilar som vill åka
  sc_in<bool> NS_event;
  sc_in<bool> SN_event;
  sc_in<bool> EW_event;
  sc_in<bool> WE_event;
  sc_in<int> trafic_queue[4];
  //variabel som säger om det är grönt eller rött
  sc_out<bool> NS_light;
  sc_out<bool> SN_light;
  sc_out<bool> EW_light;
  sc_out<bool> WE_light;

  SC_HAS_PROCESS(Monitor);
  Monitor(sc_module_name name, char *outfile);
  ~Monitor();

  void monitor_method();
  void check_constraints_method();

  ofstream *out;
};

#endif // MONITOR_H
