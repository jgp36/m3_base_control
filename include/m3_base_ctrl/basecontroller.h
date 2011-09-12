#ifndef WBC_M3_CTRL_BASE_CONTROLLER_H
#define WBC_M3_CTRL_BASE_CONTROLLER_H

#include <jspace/State.hpp>
#include <jspace/Status.hpp>

namespace m3_base_ctrl {
  
  class BaseController
  {
  public:
    jspace::Status init(jspace::State const & state,
	     		jspace::Vector const & goalpos,
	     		jspace::Vector const & kp,
	     		jspace::Vector const & kd) {
      state_ = state;
      goalpos_ = goalpos;
      kp_ = kp;
      kd_ = kd;
      jspace::Status ok;
      return ok;
    }
    
    jspace::Status update(jspace::State const & state) {
      state_ = state;
      jspace::Status ok;
      return ok;
    }
    
    jspace::State getState() { return state_; }
    
    jspace::Status computeCommand(jspace::Vector & command) {
      command = getCommand();
      jspace::Status ok;
      return ok;
    }
    
    jspace::Vector getCommand() {
      return kp_.cwise()*(goalpos_ - state_.position_) - kd_.cwise()*state_.velocity_;
    }
    
  protected:
    jspace::State state_;
    jspace::Vector goalpos_;
    jspace::Vector kp_; 
    jspace::Vector kd_;
  };
}
#endif 
