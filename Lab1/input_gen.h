#ifndef INPUT_GEN_H
#define INPUT_GEN_H

#include <systemc.h>
#include <fstream>

using std::ifstream;

SC_MODULE(Generator) {
  sc_out<int> NS_cars;
  sc_out<int> SN_cars;
  sc_out<int> EW_cars;
  sc_out<int> WE_cars;

  SC_HAS_PROCESS(Generator);
  Generator(sc_module_name name, char *datafile);
  ~Generator();

  void generate_thread();

  ifstream *in;
};

#endif // INPUT_GEN_H
