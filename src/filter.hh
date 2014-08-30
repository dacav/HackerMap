#ifndef FILTER_HH
#define FILTER_HH
#include "safequeue.hh"
#include <thread>

#define ip int

namespace filter {
  class Filter {
  public:
    Filter();
    void set_output(utils::safequeue<ip>* output_queue);
    bool filter(ip current_ip);
  private:
  };
}

#endif
