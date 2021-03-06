/**
 * @author Nathan Halsey
 * @brief Takes in a date, computes planet positions, and returns a vector of orbital elements
 *
 */

#include"Planets.h"
#include<math.h>
#include<iostream>
#include<string>

/**
 * @brief Constructor
 * @param year year of the day
 * @param month month of the day
 * @param day day of the day
 * @param hour hour of the day
 * @param minute minute of the day
 */
Planets::Planets(double year, double month, double day, double hour, double minute){
    double curr_day = computeCurrentDay(year,month,day,hour,minute); // compute the julian day
    computePositions(curr_day); // call computePositions
}
/**
 * @brief Get the vector of orbital elements
 * @return a vector of all the planets orbital elements
 */
std::vector<OrbitalElements> Planets::getPlanets(){
    return planets;
}
/**
 * @brief Compute the planets positions.
 * Gets the orbital eleemnts of every planet, computes pertubations of jupiter,saturn,uranus, pushes the orbital elements to the vector
 * @param day the julian day
 */
void Planets::computePositions(double day){

    OrbitalElements mercuryOE = computeMercuryOE(day);
    OrbitalElements venusOE = computeVenusOE(day);
    OrbitalElements earthOE = computeEarthOE(day);
    OrbitalElements marsOE = computeMarsOE(day);
    OrbitalElements jupiterOE = computeJupiterOE(day);
    OrbitalElements saturnOE = computeSaturnOE(day);
    OrbitalElements uranusOE = computeUranusOE(day);
    OrbitalElements neptuneOE = computeNeptuneOE(day);

    pertubations(&jupiterOE,&saturnOE,&uranusOE);

    planets.push_back(mercuryOE);
    planets.push_back(venusOE);
    planets.push_back(earthOE);
    planets.push_back(marsOE);
    planets.push_back(jupiterOE);
    planets.push_back(saturnOE);
    planets.push_back(uranusOE);
    planets.push_back(neptuneOE);

}
/**
 * @brief Computes the perturbations of jupiter, saturn and uranus.
 * As they act on each other, they have pertubations, so we solve that here.
 * @param jupiterOE Jupiter orbital elements
 * @param saturnOE Saturn orbital elements
 * @param uranusOE Uranus orbital elements
 */
void Planets::pertubations(OrbitalElements* jupiterOE, OrbitalElements* saturnOE, OrbitalElements* uranusOE){

    // This whole function is essentially just a mathematical formula. Without knowing it, it can't be explained
    double jupiter_added_long = 0;
    double saturn_added_long = 0;
    double saturn_added_lat = 0;
    double uranus_added_long = 0;

    double Mj = jupiterOE->getMeanAnom();
    double Ms = saturnOE->getMeanAnom();
    double Mu = uranusOE->getMeanAnom();

    jupiter_added_long += -0.332 * sin(radians(2*Mj - 5*Ms - 67.6));
    jupiter_added_long += -0.056 * sin(radians(2*Mj - 2*Ms + 21));
    jupiter_added_long += +0.042 * sin(radians(3*Mj - 5*Ms + 21));
    jupiter_added_long += -0.036 * sin(radians(Mj - 2*Ms));
    jupiter_added_long += +0.022 * cos(radians(Mj - Ms));
    jupiter_added_long += +0.023 * sin(radians(2*Mj - 3*Ms + 52));
    jupiter_added_long += -0.016 * sin(radians(Mj - 5*Ms - 69));

    jupiterOE->setLong(jupiterOE->getLong() + jupiter_added_long);

    saturn_added_long += 0.812 * sin(radians(2*Mj - 5*Ms - 67.6));
    saturn_added_long += -0.229 * cos(radians(2*Mj - 4*Ms - 2));
    saturn_added_long += 0.119 * sin(radians(Mj - 2*Ms - 3));
    saturn_added_long += 0.046 * sin(radians(2*Mj - 6*Ms - 69));
    saturn_added_long += 0.014 * sin(radians(Mj - 3*Ms + 32));

    saturnOE->setLong(saturnOE->getLong()+saturn_added_long);

    saturn_added_lat += -0.020 * cos(radians(2*Mj - 4*Ms - 2));
    saturn_added_lat += 0.018 * sin(radians(2*Mj - 6*Ms - 49));

    saturnOE->setLat(saturnOE->getLat()+saturn_added_lat);

    uranus_added_long += 0.040 * sin(radians(Ms - 2*Mu + 6));
    uranus_added_long += 0.035 * sin(radians(Ms - 3*Mu + 33));
    uranus_added_long += -0.015 * sin(radians(Mj - Mu + 20));

    uranusOE->setLong(uranusOE->getLong()+uranus_added_long);

}
// Hardcoded orbital element computations for every planet
OrbitalElements Planets::computeMercuryOE(double day){
    double asc_node = 48.3313 + (3.24587E-5*day);
    double incl = 7.0047 + (5.00E-8*day);
    double arg = 29.1241 + (1.01444E-5*day);
    double axis = 0.387098;
    double eccen = 0.205635 + (5.59E-10*day);
    double mean_anon = 168.6562+(4.0923344368*day);

    return OrbitalElements(asc_node,incl,arg,axis,eccen,mean_anon,25);

}
OrbitalElements Planets::computeVenusOE(double day){
    double asc_node = 76.6799 + (2.46590E-5*day);
    double incl = 3.3946 + (2.75E-8*day);
    double arg = 54.8910 + (1.38374E-5*day);
    double axis = 0.723330;
    double eccen = 0.006773 - (1.302E-9*day);
    double mean_anon = 48.0052+(1.6021302244*day);

    return OrbitalElements(asc_node,incl,arg,axis,eccen,mean_anon,50);
}
OrbitalElements Planets::computeEarthOE(double day){
    double asc_node = 0;
    double incl = 0;
    double arg = 282.9404 + (4.70935E-5*day);
    double axis = 1;
    double eccen = 0.016709 - (1.151E-9*day);
    double mean_anon = 356.047 + (0.9856002585*day);

    return OrbitalElements(asc_node,incl,arg,axis,eccen,mean_anon,75);

}
OrbitalElements Planets::computeMarsOE(double day){
    double asc_node = 49.5574 + (2.11081E-5*day);
    double incl = 1.8497 - (1.78E-8*day);
    double arg = 286.5016 + (2.92961E-5*day);
    double axis = 1.523688;
    double eccen = 0.093405 + (2.516E-9 * day);
    double mean_anon = 18.6021 + (0.5240207766 * day);

    return OrbitalElements(asc_node,incl,arg,axis,eccen,mean_anon,100);

}
OrbitalElements Planets::computeJupiterOE(double day){
    double asc_node = 100.4542 + (2.76854E-5*day);
    double incl = 1.3030 - (1.557E-7*day);
    double arg = 273.8777 + (1.64505E-5*day);
    double axis = 5.20256;
    double eccen = 0.048498 + (4.469E-9 * day);
    double mean_anon = 19.8950 + (0.0830853001 * day);

    return OrbitalElements(asc_node,incl,arg,axis,eccen,mean_anon,125);

}
OrbitalElements Planets::computeSaturnOE(double day){
    double asc_node = 113.6634 + (2.38980E-5*day);
    double incl = 2.4886 - (1.081E-7*day);
    double arg = 339.3939 + (2.97661E-5*day);
    double axis = 9.55475;
    double eccen = 0.055546 - (9.499E-9 * day);
    double mean_anon = 316.9670 + (0.0334442282 * day);

    return OrbitalElements(asc_node,incl,arg,axis,eccen,mean_anon,150);
}
OrbitalElements Planets::computeUranusOE(double day){
    double asc_node = 74.0005 + (1.3978E-5*day);
    double incl = 0.7733 + (1.9E-8*day);
    double arg = 96.6612 + (3.0565E-5*day);
    double axis = 19.18171 - (1.55E-8*day);
    double eccen = 0.047318 + (7.45E-9 * day);
    double mean_anon = 142.5905 + (0.011725806 * day);

    return OrbitalElements(asc_node,incl,arg,axis,eccen,mean_anon,175);

}
OrbitalElements Planets::computeNeptuneOE(double day){
    double asc_node = 131.7806 + (3.0173E-5*day);
    double incl = 1.7700 - (2.55E-7*day);
    double arg = 272.8461 - (6.027E-6*day);
    double axis = 30.05826 + (3.313E-8*day);
    double eccen = 0.008606 + (2.15E-9 * day);
    double mean_anon = 260.2471 + (0.005995147 * day);

    return OrbitalElements(asc_node,incl,arg,axis,eccen,mean_anon,200);
}
/**
 * @brief Computes the julian day given a date
 * @param year year of the date
 * @param month month of the date
 * @param day day of the date
 * @param hour hour of the date
 * @param minute minute of the date
 * @return the julian day
 */
double Planets::computeCurrentDay(double year, double month, double day, double hour, double minute){
    double julian_day = ((367 * year - floor(7 * (year + floor((month + 9) / 12)) / 4)) + floor(275 * month / 9) + (day + 1721013.5));
    julian_day = julian_day+hour/24.0 + minute/1440.0;
    return julian_day - 2451543.5;
}
/**
 * @brief Convert from degrees to radians
 * @param x a value in degrees
 * @return a value in radians
 */
double Planets::radians(double x){
    return x*PI/180;
}

