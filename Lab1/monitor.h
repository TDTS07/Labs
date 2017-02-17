#ifndef MONITOR_H
#define MONITOR_H

#include <systemc.h>
#include <fstream>

using std::ofstream;

SC_MODULE(Monitor) {
  //variables that tells where there is cars that wants to go
  sc_in<bool> NS_event;
  sc_in<bool> SN_event;
  sc_in<bool> EW_event;
  sc_in<bool> WE_event;
  //variables to send back whether the light should be green or red
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
