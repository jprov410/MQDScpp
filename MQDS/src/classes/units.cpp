//
// Created by Justin Provazza on 10/21/18.
//

#include <iostream>
#include <map>
#include "../../include/MQDS/units.h"
#include "../../include/MQDS/output.h"
#include "../../include/MQDS/universe.h"
#include "../../include/MQDS/constants.h"

// TODO: need to add more units and populate the conversion map

// Library of units supported by conversion function
std::string const Units::atomic_energy="au";
std::string const Units::atomic_angular_frequency="au_ang_freq";
std::string const Units::wavenumber="wvnbr";
std::string const Units::seconds="s";
std::string const Units::hertz="hz";

std::map<std::pair<std::string, std::string>, double>
const Units::conversion_map = {
        {std::make_pair(Units::wavenumber, Units::atomic_energy), 1.0}
};

double Units::conversion(std::string const &from_units,std::string const &to_units)
{
    //std::map<std::pair<std::string, std::string>, double> conversion_map;
    //conversion_map[std::make_pair
    //    //        (Units::wavenumber,Units::atomic_energy)] = 1.0;
    //conversion_map[std::make_pair
    //        (Units::wavenumber,Units::atomic_angular_frequency)] = 2.0;


    return Units::conversion_map.at( std::make_pair(from_units,to_units) );
    return 0.;
}


