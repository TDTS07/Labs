#include "input_gen.h"
#include <cassert>

Generator::Generator(sc_module_name name, char *datafile)
  : sc_module(name)
{
  assert(datafile != 0);       // An input file should be given.

  in = new ifstream(datafile); // Open the input file.
  assert(*in);                 // Check that everything is OK.

  SC_THREAD(generate_thread);

  NS_cars.initialize(0);
  SN_cars.initialize(0);
  EW_cars.initialize(0);
  WE_cars.initialize(0);
}

Generator::~Generator()
{
  delete in;
}

void Generator::generate_thread()
{
  int NS, SN, EW, WE;
  for (;;){
    wait(15, SC_SEC);     // Generate new inputs every 15 seconds.
    *in >> NS >> SN >> EW >> WE; // Read from the input file.

    if(!in->eof())
    {
    NS_cars->write(NS);
    SN_cars->write(SN);
    EW_cars->write(EW);
    WE_cars->write(WE);
    }
    else
    {
    NS_cars->write(0);
    SN_cars->write(0);
    EW_cars->write(0);
    WE_cars->write(0);
    }
  }
}
