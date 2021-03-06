//External Libraries
#include <iostream>
#include <stdexcept>
#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <cassert>
//General
#include "MQDS/universe.h"
#include "MQDS/io.h"
#include "MQDS/units.h"
#include "MQDS/random.h"
#include "MQDS/constants.h"
//SuperClasses
#include "MQDS/calculation.h"
#include "MQDS/method.h"
#include "MQDS/system.h"
#include "MQDS/bath.h"
//Factories
#include "MQDS/systemfactory.h"
#include "MQDS/bathfactory.h"
#include "MQDS/methodfactory.h"
#include "MQDS/calculationfactory.h"
//SubClasses
#include "MQDS/electronicsite.h"
#include "MQDS/harmonicbilinear.h"
#include "MQDS/pldm.h"
#include "MQDS/twa.h"
#include "MQDS/redmat.h"
#include "MQDS/absorption.h"
using namespace MQDS;
int main()
{
    std::cout.precision( 17 ); // Set precision for cout
    Universe pe; // Initiate MPI. (Processing Element) = pe
    Random::set_local_seed(pe.my_pe()); // Set local seed

    try
    {
        IO io; // Gather input information
        if (pe.is_master()) io.write_run_parameters(); // start runlog
        auto method = MethodFactory::Create(io);
        auto system = SystemFactory::Create(io);
        auto bath = BathFactory::Create(io);
        auto calculation = CalculationFactory::Create(io);

        calculation->calculate(method,system,bath,io,pe);
    }
    catch(const std::exception &ex)
    {
        IO::write_error("MQDS has encountered a problem");
        IO::write_error(ex.what());
    }


    return 0;
}