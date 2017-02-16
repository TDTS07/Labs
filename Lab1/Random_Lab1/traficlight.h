#ifndef TRAFICLIGHT_H
#define TRAFICLIGHT_H

#include <systemc.h>
#include <fstream>


SC_MODULE(Traficlight) {
  sc_in<bool> cars;
  sc_out<bool> event;
  sc_inout<bool> light;
  sc_in<bool> change_light;

  sc_event new_car;

  bool outgoing_event;


  SC_HAS_PROCESS(Traficlight);
  Traficlight(sc_module_name name);

  void sensor_method();
  void on_off_method();
};

#endif // MONITOR_H
