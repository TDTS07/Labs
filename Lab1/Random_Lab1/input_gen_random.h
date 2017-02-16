#ifndef INPUT_GEN_RANDOM_H
#define INPUT_GEN_RANDOM_H

#include <systemc.h>

SC_MODULE(Generator) {
  sc_out<bool> NS_cars;
  sc_out<bool> SN_cars;
  sc_out<bool> EW_cars;
  sc_out<bool> WE_cars;

  SC_HAS_PROCESS(Generator);
  Generator(sc_module_name name);


  void generate_thread();

};

#endif // INPUT_GEN_H
