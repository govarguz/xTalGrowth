// ESPP_CLASS
#ifndef _INTERACTION_ANGULARUNIQUECOSINESQUARED_HPP
#define _INTERACTION_ANGULARUNIQUECOSINESQUARED_HPP

#include "AngularPotential.hpp"
#include "FixedTripleListInteractionTemplate.hpp"
#include <cmath>

namespace espresso {
  namespace interaction {
    /** This class provides methods to compute forces and energies of
        the AngularUniqueCosineSquared angular potential. To create a new angular potential
        one only needs to write the setter/getters and the variable
        dU_dtheta.*/
    class AngularUniqueCosineSquared : public AngularPotentialTemplate< AngularUniqueCosineSquared > {
    private:
      real K;
      real theta0;
      real cos_theta0;

    public:
      static void registerPython();

      AngularUniqueCosineSquared() : K(0.0), theta0(0.0) { }
      AngularUniqueCosineSquared(real _K, real _theta0) : K(_K), theta0(_theta0) {
        cos_theta0 = cos(_theta0);
      }

      void setK(real _K) { K = _K; }
      real getK() const { return K; }

      void setTheta0(real _theta0) {
        theta0 = _theta0;
        cos_theta0 = cos(theta0);
      }
      real getTheta0() const { return theta0; }

      real _computeEnergyRaw(real _theta) const {
        // _theta and theta0 should be in radians
        real energy = K * pow(cos(_theta) - cos_theta0, 2);
	return energy;
      }
/*
      void _computeForceRaw(Real3D& force12,
                            Real3D& force32,
			    const Real3D& dist12,
			    const Real3D& dist32) const {

        real dist12_sqr = dist12 * dist12;
        real dist32_sqr = dist32 * dist32;
        real dist12_magn = sqrt(dist12_sqr);
        real dist32_magn = sqrt(dist32_sqr);
        real dist1232 = dist12_magn * dist32_magn;

        real cos_theta = dist12 * dist32 / dist1232;
        if(cos_theta < -1.0) cos_theta = -1.0;
        if(cos_theta >  1.0) cos_theta =  1.0;
        real sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        real dU_dtheta = -2.0 * K * (cos_theta - cos_theta0) * sin_theta;
        real dnom = dist12_sqr * dist32_sqr * sin_theta;
        dU_dtheta /= dnom;
        force12 = dU_dtheta *
                    (dist1232 * dist32 - cos_theta * dist32_sqr * dist12);
        force32 = dU_dtheta *
                    (dist1232 * dist12 - cos_theta * dist12_sqr * dist32);
        
      }*/


      bool _computeForceRaw(Real3D& force12,
                            Real3D& force32,
                const Real3D& dist12,
                const Real3D& dist32) const {

        real dist12_sqr = dist12 * dist12;
        real dist32_sqr = dist32 * dist32;
        real dist12_magn = sqrt(dist12_sqr);
        real dist32_magn = sqrt(dist32_sqr);
        real dist1232 = dist12_magn * dist32_magn;

        real cos_theta = dist12 * dist32 / dist1232;
        if(cos_theta < -1.0) cos_theta = -1.0;
        else if(cos_theta >  1.0) cos_theta =  1.0;

        real dU_dtheta = 2.0 * K * (cos_theta - cos_theta0);
        
        real a11 = dU_dtheta * cos_theta / dist12_sqr;
        real a12 = -dU_dtheta / dist1232;
        real a22 = dU_dtheta * cos_theta / dist32_sqr;
        
        force12 = a11 * dist12 + a12 * dist32;
        force32 = a22 * dist32 + a12 * dist12;
        
        return true;
      }


      // used to generate the tabulated table
      real _computeForceRaw(real theta) const {

        real cos_theta = cos(theta);
        if(cos_theta < -1.0) cos_theta = -1.0;
        else if(cos_theta >  1.0) cos_theta =  1.0;

        return 2.0 * K * (cos_theta - cos_theta0);

      }
      
    };
  }
}

#endif