#ifndef ORBITDETERMINATIONFILTER_H
#define ORBITDETERMINATIONFILTER_H

#include "FusionEKF.hpp"
#include "Nums/GroundTrackingSolver.hpp"

#define NUMSENSORS_ 3
#define STATION1_ 0
#define STATION2_ 1
#define STATION3_ 2

class OrbitDeterminationFilter : public FusionEKF
{
public:
    OrbitDeterminationFilter();
    void ProcessMeasurement(vector<MeasurementPackage> &measurement_pack_list);
};

#endif // ORBITDETERMINATIONFILTER_H
