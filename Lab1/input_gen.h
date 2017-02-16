#ifndef INPUT_GEN_H
#define INPUT_GEN_H

#include <systemc.h>
#include <fstream>

using std::ifstream;

SC_MODULE(Generator) {
  //variables for detected cars
  sc_out<bool> NS_cars;
  sc_out<bool> SN_cars;
  sc_out<bool> EW_cars;
  sc_out<bool> WE_cars;

  SC_HAS_PROCESS(Generator);
  Generator(sc_module_name name, char *datafile);
  ~Generator();

  void generate_thread();

  ifstream *in;
};

#endif // INPUT_GEN_H
