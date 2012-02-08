#ifndef PHOTODISINTEGRATION_H_
#define PHOTODISINTEGRATION_H_

#include "mpc/Module.h"
#include "mpc/MersenneTwister.h"

#include <vector>
#include <map>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

namespace mpc {

struct DisintegrationMode {
	int channel; // number of emitted (n, p, ,H2, H3, He3, He4)
	gsl_spline *rate; // disintegration rate [1/m]
};

/**
 @class PhotoDisintegration
 @brief Photo-disintegration of nuclei with background photons.

 This module simulates photo-disintegration of nuclei with background photons.\n
 Background photons are considered as homogeneous and evolving as the CMB.\n
 */
class PhotoDisintegration: public Module {
public:
	PhotoDisintegration();
	std::string getDescription() const;
	void process(Candidate *candidate);
	bool setNextInteraction(Candidate *candidate);
	void performInteraction(Candidate *candidate);

private:
	MTRand mtrand;
	gsl_interp_accel *acc;
	std::map<int, std::vector<DisintegrationMode> > modeMap;
	int cached_id;
	int cached_channel;
	double cached_distance;
};

} // namespace mpc

#endif /* PHOTODISINTEGRATION_H_ */