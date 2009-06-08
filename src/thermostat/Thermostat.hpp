#ifndef _THERMOSTAT_HPP
#define _THERMOSTAT_HPP

#include "types.hpp"
#include "error.hpp"
#include "particles/Set.hpp"

namespace espresso {
  namespace thermostat {

    /** Base class for a thermostat. A thermostat consists at least
        of a temperature and a set of particles to which the thermostat is
        applied.

    */

    class Thermostat {

    protected:
      
      static LOG4ESPP_DECL_LOGGER(theLogger);

      boost::shared_ptr<particles::Set> particles;  //!< Particles to which the thermostat is applied

      real temperature;   //!< target temperature for the thermostat

    public:

      /** A constructor of a thermostat needs at least a particle set and a temperature. */

      Thermostat(boost::shared_ptr<particles::Set> _particles, real _temperature): particles(_particles)

      { setTemperature(_temperature); }

      virtual ~Thermostat() { }
      
      /** Setter routine for the temperature

          \param temperature is the new target temperature (must not be negative)
      */

      virtual void setTemperature(real temperature);

      /** Getter routine for the temperature */
      
      virtual real getTemperature() const { return temperature; }

      /** Abstract class needs also registration in Python */

      static void registerPython();
    };

  }
}

#endif