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
  //variabel som säger om det är grönt eller rött
  sc_out<bool> NS_change;
  sc_out<bool> SN_change;
  sc_out<bool> EW_change;
  sc_out<bool> WE_change;

  sc_event timer;
  sc_event handle;

  int direction;
  bool handled;


  SC_HAS_PROCESS(Monitor);
  Monitor(sc_module_name name, char *outfile);
  ~Monitor();

  void timer_method();
  void event_method();
  void handle_method();

  ofstream *out;
};

#endif // MONITOR_H
