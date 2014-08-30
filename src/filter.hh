#ifndef FILTER_HH
#define FILTER_HH
#include "safequeue.hh"
#include <thread>

#define ip int

namespace filter {
  class Filter {
  public:
    Filter();
    bool filter(ip current_ip);
  private:
  };
}

#endif
