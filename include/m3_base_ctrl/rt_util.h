#ifndef M3_BASE_CTRL_RT_UTIL_H
#define M3_BASE_CTRL_RT_UTIL_H

#include <jspace/State.hpp>
#include <stdexcept>


namespace m3_base_ctrl {
  
  
  typedef enum {
    RT_THREAD_UNDEF,
    RT_THREAD_INIT,
    RT_THREAD_RUNNING,
    RT_THREAD_CLEANUP,
    RT_THREAD_ERROR,
    RT_THREAD_DONE
  } rt_thread_state_t;
  
  
  class RTUtil
  {
  public:
    virtual ~RTUtil();
    
    virtual int init(jspace::State const & state) = 0;
    
    virtual int update(jspace::State const & state,
		       jspace::Vector & command) = 0;	
    
    virtual int cleanup(void) = 0;
    
    virtual int slowdown(long long iteration,
			 long long desired_ns,
			 long long actual_ns) = 0;
    
    void start(long long tick_frequency_hz) throw(std::runtime_error);
    
    static rt_thread_state_t getState();
    static rt_thread_state_t shutdown();
  };
  
}

#endif // M3_BASE_CTRL_RT_UTIL_H
