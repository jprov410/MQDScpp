//
// Created by Justin Provazza on 10/21/18.
//

#include <iostream>
#include <map>
#include "MQDS/units.h"
#include "MQDS/constants.h"

// TODO: need to add more units and populate the conversion map

// Library of units supported by conversion function
std::string const MQDS::Units::atomic_energy="au";
std::string const MQDS::Units::atomic_angular_frequency="au_ang_freq";
std::string const MQDS::Units::wavenumber="wvnbr";
std::string const MQDS::Units::seconds="s";
std::string const MQDS::Units::hertz="hz";
std::string const MQDS::Units::kelvin="kelvin";
std::string const MQDS::Units::femtoseconds="fs";
std::string const MQDS::Units::atomic_time="au_time";

namespace
{
    std::map<std::pair<std::string, std::string>, double>
    const conversion_map = {
            {std::make_pair(MQDS::Units::wavenumber, MQDS::Units::atomic_energy), 4.556335253e-6},
            {std::make_pair(MQDS::Units::atomic_energy, MQDS::Units::wavenumber), 1.0/4.556335253e-6},
            {std::make_pair(MQDS::Units::wavenumber, MQDS::Units::atomic_angular_frequency), 4.556335253e-6},
            {std::make_pair(MQDS::Units::atomic_angular_frequency, MQDS::Units::wavenumber), 1.0/4.556335253e-6},
            {std::make_pair(MQDS::Units::femtoseconds, MQDS::Units::atomic_time), 41.341374575751},
            {std::make_pair(MQDS::Units::atomic_time, MQDS::Units::femtoseconds), 1.0/41.341374575751},
            {std::make_pair(MQDS::Units::kelvin, MQDS::Units::atomic_energy), 3.166811506e-6},
            {std::make_pair(MQDS::Units::atomic_energy, MQDS::Units::kelvin), 1.0/3.166811506e-6}
    };
}

double MQDS::Units::conversion(std::string const &from_units,std::string const &to_units)
{
    return conversion_map.at( std::make_pair(from_units,to_units) );
}
