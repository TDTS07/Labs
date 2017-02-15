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
  bool NS_p = false , SN_p = false, EW_p = false, WE_p = false;
  for (;;) {
    wait(15, SC_SEC);     // Generate new inputs every 15 seconds.
    *in >> WE >> EW >> SN >> NS; // Read from the input file.
    if(NS > 0)
    {
      NS_p = ~NS_p;
    }
    if(SN > 0)
    {
      SN_p = ~SN_p;
    }
    if(EW > 0)
    {
      EW_p = ~EW_p;
    }
    if(WE > 0)
    {
      WE_p = ~WE_p;
    }
    NS_cars->write(NS_p);
    SN_cars->write(SN_p);
    EW_cars->write(EW_p);
    WE_cars->write(WE_p);
  }
}
